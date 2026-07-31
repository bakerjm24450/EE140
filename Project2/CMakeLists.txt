cmake_minimum_required(VERSION 4.0.0)

project(Project2 VERSION 1.0 LANGUAGES C CXX)

message(STATUS "Starting Project2 build...")

add_executable(${PROJECT_NAME})
add_subdirectory(src)

# compiling for PC/Mac, not zybooks
target_compile_definitions(${PROJECT_NAME} PUBLIC NO_ZYBOOKS)

target_link_libraries(${PROJECT_NAME} PRIVATE ImGui-SFML::ImGui-SFML)

# Copy images to build directory
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/images
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/images
)
