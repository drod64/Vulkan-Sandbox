cmake_minimum_required(VERSION 3.20)

project(CONDUIT)

# Dependencies
set(GLFW_VERSION 3.5.1)
find_package(glfw3 ${GLFW_VERSION} QUIET) # QUIET or REQUIRED
if (NOT glfw3_FOUND) # If there's none, fetch and build glfw
    include(FetchContent)
    FetchContent_Declare(
        glfw
        DOWNLOAD_EXTRACT_TIMESTAMP OFF
        URL https://github.com/glfw/glfw/archive/refs/tags/${GLFW_VERSION}.tar.gz
    )
    FetchContent_GetProperties(glfw)
    if (NOT glfw_POPULATED) # Have we downloaded glfw yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_MakeAvailable(glfw)
    endif()
endif()

set(
    SOURCE_FILES
    src/framework/Time.cpp

    src/input/gamepad/GamepadState.cpp

    src/input/keyboard/KeyboardState.cpp

    src/input/mouse/MouseState.cpp

    src/input/Input.cpp

    src/tests/InputTester.cpp

    src/window/Window.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

# Select the platform backend.
set(CONDUIT_PLATFORM_BACKEND
    "GLFW"
    CACHE STRING
    "Platform backend"
)
set_property(
    CACHE CONDUIT_PLATFORM_BACKEND
    PROPERTY STRINGS GLFW
)

# Build the actual cpp files needed for the platform backend.
if(CONDUIT_PLATFORM_BACKEND STREQUAL "GLFW")
    set(CONDUIT_PLATFORM_BACKEND_GLFW 1)
    target_sources(${PROJECT_NAME} PRIVATE
        src/backend/glfw/input/GLFWInput.cpp
        src/backend/glfw/input/GLFWInputMapping.cpp

        src/backend/glfw/platform/GLFWPlatform.cpp

        src/backend/glfw/window/GLFWWindow.cpp
    )

else()
    message(FATAL_ERROR
        "Unsupported platform backend: ${CONDUIT_PLATFORM_BACKEND}"
    )
endif()

# Store the results in a generated config.hpp.
set(
    CONDUIT_GENERATED_INCLUDE_DIR
    ${CMAKE_CURRENT_BINARY_DIR}/generated/include
)
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/conduit/core/config.hpp.in
    ${CONDUIT_GENERATED_INCLUDE_DIR}/conduit/core/config.hpp
)

# Link conduit's header files to itself.
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CONDUIT_GENERATED_INCLUDE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link glfw to conduit
target_link_libraries(${PROJECT_NAME} glfw)

# Link entt (version 4.0.0) to conduit
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/external/entt/include)

# Link custom math directory to conduit
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/external/sm/include)
target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/external/sm)
target_link_libraries(${PROJECT_NAME} SM)