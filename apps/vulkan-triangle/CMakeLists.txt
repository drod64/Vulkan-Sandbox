cmake_minimum_required(VERSION 3.20)

project(VULKAN_TRIANGLE_APP)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -static")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ======================
# |    Dependencies    |
# ======================
find_package(Vulkan REQUIRED)
set(
    SLANGC_EXECUTABLE
    "$ENV{VULKAN_SDK}/Bin/slangc.exe"
)
if (NOT EXISTS "${SLANGC_EXECUTABLE}")
    message(
        FATAL_ERROR
        "slangc.exe not found at ${SLANGC_EXECUTABLE}"
    )
endif()

# =================
# |    Shaders    |
# =================
set(
    SHADER_SLANG_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/shaders/shader.slang
)

function (add_slang_shader_target TARGET)
    cmake_parse_arguments(
        SHADER
        ""
        ""
        "SOURCES"
        ${ARGN}
    )

    set(
        SHADERS_DIR
        ${CMAKE_CURRENT_BINARY_DIR}/shaders
    )

    set(
        ENTRY_POINTS
        -entry vertMain
        -entry fragMain
    )

    add_custom_command(
        OUTPUT ${SHADERS_DIR}/slang.spv

        COMMAND ${CMAKE_COMMAND}
            -E make_directory
            ${SHADERS_DIR}

        COMMAND ${SLANGC_EXECUTABLE}
            ${SHADER_SOURCES}
            -target spirv
            -profile spirv_1_4
            -emit-spirv-directly
            -fvk-use-entrypoint-name
            ${ENTRY_POINTS}
            -o ${SHADERS_DIR}/slang.spv

        DEPENDS ${SHADER_SOURCES}

        COMMENT "Compiling Slang shaders"

        VERBATIM
    )

    add_custom_target(
        ${TARGET}
        DEPENDS ${SHADERS_DIR}/slang.spv
    )
endfunction()

add_slang_shader_target(${PROJECT_NAME}_SHADERS SOURCES ${SHADER_SLANG_SOURCES})

# =============
# |    App    |
# =============
set(
    SOURCE_FILES
    src/App.cpp
    src/util.cpp
)
add_library(
    ${PROJECT_NAME}
    STATIC
    ${SOURCE_FILES}
)
add_dependencies(
    ${PROJECT_NAME}
    ${PROJECT_NAME}_SHADERS
)

# =============================
# |    Include directories    |
# =============================
target_include_directories(
    ${PROJECT_NAME}
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/external/conduit/include
        ${CMAKE_SOURCE_DIR}/external/vulkan/include
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
        ${CMAKE_SOURCE_DIR}/external/entt/include
)

# ===================
# |    Libraries    |
# ===================
target_link_directories(
    ${PROJECT_NAME}
    PRIVATE
        ${CMAKE_SOURCE_DIR}/external/conduit
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
        CONDUIT
        glfw
        Vulkan::Vulkan
)