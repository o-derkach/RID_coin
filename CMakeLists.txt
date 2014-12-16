cmake_minimum_required(VERSION 2.8)	 # Проверка версии CMake.

project(RID_coin)			# Название проекта

AUX_SOURCE_DIRECTORY("Src/utils" SRC_DIRS)
AUX_SOURCE_DIRECTORY("Src" SRC_DIRS)

set(HEADER_FILES "Inc")			# Тоже самое, но для библиотеки

include_directories(${HEADER_FILES})

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++0x")

add_executable(main ${SRC_DIRS})	# Создает исполняемый файл с именем main
