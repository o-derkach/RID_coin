cmake_minimum_required(VERSION 2.8)	 # �������� ������ CMake.

project(RID_coin)			# �������� �������

aux_source_directory("Src/utils" 	SRC_DIRS)
aux_source_directory("Src/paytree" 	SRC_DIRS)
aux_source_directory("Src/crypto"	SRC_DIRS)
aux_source_directory("Src" 		SRC_DIRS)

set(HEADER_FILES "Inc")			# ���� �����, �� ��� ����������

set(EXTRA_LIBS crypto)

include_directories(${HEADER_FILES})

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++0x")

add_executable(main ${SRC_DIRS})	# ������� ����������� ���� � ������ main

target_link_libraries(main ${EXTRA_LIBS})
