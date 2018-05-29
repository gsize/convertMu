#####################################################
cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

#####################################################
project(convvertMU)

message("project source dir: ${PROJECT_SOURCE_DIR}")

#SET(PETHEADER_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/../../include)


#add include files
include_directories(
${PROJECT_SOURCE_DIR}
)


IF (WIN32)
	message(STATUS "Now is windows")
	add_definitions(-Dwin32)
ELSE ()
	message(STATUS "Now is Linux")
	add_definitions(-DLinux)
	set(CMAKE_CXX_STANDARD 11)	
ENDIF()

#AUX_SOURCE_DIRECTORY(./ LIB_LOCAL_SRC)
#SET(LIB_SRC  ${LIB_LOCAL_SRC} )
SET(SRC convertMU.cpp muvoxel.cpp)

#find_package(Threads)

###  additional libraries
#generate executable file by SRC_LIST
add_executable(convertMU ${SRC}  )

#target_link_libraries(convBin2Spectra Threads::Threads  )

