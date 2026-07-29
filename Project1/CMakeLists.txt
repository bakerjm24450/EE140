cmake_minimum_required(VERSION 4.4.0)

project(Project1 VERSION 1.0 LANGUAGES C CXX)

message(STATUS "Starting Project1 build...")

add_executable(${PROJECT_NAME})
add_subdirectory(src)

target_link_libraries(${PROJECT_NAME} PRIVATE ImGui-SFML::ImGui-SFML)

# Copy images to build directory
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/images
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/images
)
