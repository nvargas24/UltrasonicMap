#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>
#include <esp_log.h>
#include <esp_timer.h>

#define TRIGGER_GPIO GPIO_NUM_4
#define ECHO_GPIO    GPIO_NUM_5

static const char *TAG = "ultrasonic";

typedef struct {
    float distance;
    TaskHandle_t task_handle;
} UltrasonicData;

void ultrasonic_task(void *pvParameters) {
    UltrasonicData *data = (UltrasonicData *)pvParameters;
    
    gpio_set_direction(TRIGGER_GPIO, GPIO_MODE_OUTPUT);
    gpio_set_direction(ECHO_GPIO, GPIO_MODE_INPUT);

    while (1) {
        // Generar pulso de 10 us en el pin de trigger
        gpio_set_level(TRIGGER_GPIO, 1);
        esp_rom_delay_us(10);
        gpio_set_level(TRIGGER_GPIO, 0);

        // Medir el tiempo de pulso en el pin de echo
        int64_t start_time = esp_timer_get_time();
        int64_t echo_duration = 0;
        while (gpio_get_level(ECHO_GPIO) == 0) {
            start_time = esp_timer_get_time();
        }
        while (gpio_get_level(ECHO_GPIO) == 1) {
            echo_duration = esp_timer_get_time() - start_time;
        }

        // Calcular distancia en cm
        float distance = (echo_duration * 0.0343) / 2;

        ESP_LOGI(TAG, "Distancia: %.2f cm", distance);

        // Actualizar los datos en la estructura compartida
        data->distance = distance;

        // Notificar a los observadores
        if (data->task_handle != NULL) {
            xTaskNotifyGive(data->task_handle);
        }

        vTaskDelay(pdMS_TO_TICKS(1000));  // Esperar 1 segundo
    }
}

void observer_task(void *pvParameters) {
    UltrasonicData *data = (UltrasonicData *)pvParameters;

    while (1) {
        // Esperar a la notificación del cambio de distancia
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        // Realizar acciones de observación
        // En este ejemplo, solo mostraremos el valor de distancia
        ESP_LOGI(TAG, "Distancia actualizada: %.2f cm", data->distance);
    }
}

void app_main() {
    ESP_ERROR_CHECK(gpio_install_isr_service(0));

    UltrasonicData ultrasonic_data;
    ultrasonic_data.distance = 0;
    ultrasonic_data.task_handle = xTaskGetCurrentTaskHandle();

    xTaskCreate(ultrasonic_task, "ultrasonic_task", 2048, &ultrasonic_data, 5, NULL);
    xTaskCreate(observer_task, "observer_task", 2048, &ultrasonic_data, 5, NULL);
}
