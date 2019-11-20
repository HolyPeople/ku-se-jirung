cmake_minimum_required(VERSION 3.0)

# project settings
PROJECT(DIGITAL_WATCH LANGUAGES C)
set(CMAKE_C_STANDARD 11)

# create common variable
file(GLOB MY_SRCS ${PROJECT_SOURCE_DIR}/*.c)

ADD_EXECUTABLE(${PROJECT_NAME}
        ${MY_SRCS}
        )
target_include_directories(${PROJECT_NAME} PUBLIC
        ${MY_INCLUDES}
        )