file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")

add_executable(PseudorandomNoise ${SOURCES})

target_link_libraries(PseudorandomNoise PRIVATE OpenGarlicEngine)

add_custom_command(
    TARGET PseudorandomNoise POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/bin/shaders
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/shaders
            ${CMAKE_BINARY_DIR}/bin/shaders
)