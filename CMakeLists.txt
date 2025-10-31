cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME "OOP_2021_Game")
project(${PROJECT_NAME} LANGUAGES CXX)

message("${PROJECT_NAME} by")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "src/*.cpp" "src/*.c")
file(GLOB_RECURSE HDR_FILES CONFIGURE_DEPENDS "src/*.hpp" "src/*.h")

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src PREFIX "Source Files" FILES ${SRC_FILES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src PREFIX "Header Files" FILES ${HDR_FILES})

add_executable(${PROJECT_NAME} ${SRC_FILES})

set(RESOURCE_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/GameOver.txt"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Title.txt"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Shop.txt"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Sprite6.txt"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Sprite7.txt"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Sprite8.txt"
)

add_custom_target(CopyResources
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${RESOURCE_FILES}
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMENT "Copia dei file .txt necessari nella cartella di build (Debug/Release)"
)

add_dependencies(${PROJECT_NAME} CopyResources)

set_property(TARGET ${PROJECT_NAME} PROPERTY
    VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
)