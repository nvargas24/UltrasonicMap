# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/Homework/esp/esp-idf/components/bootloader/subproject"
  "E:/Documentos/Workspace/Proyectos_varios/UltrasonicMap/sensor_ultrasonic/build/bootloader"
  "E:/Documentos/Workspace/Proyectos_varios/UltrasonicMap/sensor_ultrasonic/build/bootloader-prefix"
  "E:/Documentos/Workspace/Proyectos_varios/UltrasonicMap/sensor_ultrasonic/build/bootloader-prefix/tmp"
  "E:/Documentos/Workspace/Proyectos_varios/UltrasonicMap/sensor_ultrasonic/build/bootloader-prefix/src/bootloader-stamp"
  "E:/Documentos/Workspace/Proyectos_varios/UltrasonicMap/sensor_ultrasonic/build/bootloader-prefix/src"
  "E:/Documentos/Workspace/Proyectos_varios/UltrasonicMap/sensor_ultrasonic/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "E:/Documentos/Workspace/Proyectos_varios/UltrasonicMap/sensor_ultrasonic/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "E:/Documentos/Workspace/Proyectos_varios/UltrasonicMap/sensor_ultrasonic/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
