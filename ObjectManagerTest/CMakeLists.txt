file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")

add_executable(ObjectsManagerTest ${SOURCES})

target_link_libraries(ObjectsManagerTest PRIVATE OpenGarlicEngine)

