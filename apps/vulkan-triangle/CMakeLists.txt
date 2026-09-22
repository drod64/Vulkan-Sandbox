cmake_minimum_required(VERSION 3.20)

project(VULKAN_TRIANGLE_APP)

find_package(Vulkan REQUIRED)

set(
    SOURCE_FILES
    src/App.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

# Link app's own headers
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Link conduit
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/external/conduit/include)
target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/external/conduit)
target_link_libraries(${PROJECT_NAME} CONDUIT)

# Link to entt
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/external/entt/include)

# Link glfw
target_link_libraries(${PROJECT_NAME} glfw)

# Link Vulkan
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/external/vulkan/include)
target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan)