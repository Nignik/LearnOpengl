file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")

FetchContent_MakeAvailable(rapidcsv)

add_executable(PerfectlyBlack ${SOURCES})

target_link_libraries(PerfectlyBlack PRIVATE OpenGarlicEngine rapidcsv)

add_custom_command(
    TARGET PerfectlyBlack POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/bin/data
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/data
            ${CMAKE_BINARY_DIR}/bin/data
)