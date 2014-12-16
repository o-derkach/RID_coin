cmake_minimum_required(VERSION 2.8)	 # Проверка версии CMake.

project(RID_coin)			# Название проекта

set(SOURCE_FILES Src/*.cpp)		# Установка переменной со списком исходников для исполняемого файла

set(HEADER_FILES Inc/*.h)			# Тоже самое, но для библиотеки

include_directories(HEADER_FILES)

#add_library(foo STATIC ${SOURCE_LIB})	# Создание статической библиотеки с именем foo

add_executable(main ${SOURCE_FILES})	# Создает исполняемый файл с именем main

#target_link_libraries(main foo)		# Линковка программы с библиотекой