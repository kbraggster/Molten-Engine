cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(MoltenEngine)

# If using macOS, set system name to "macOS" instead of "Darwin"
Set(SystemName ${CMAKE_SYSTEM_NAME})
if (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    Set(SystemName "macOS")
endif ()

# Set Output and Target directories
set(TargetDir "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}-${SystemName}-${CMAKE_SYSTEM_PROCESSOR}")
set(ObjDir "${CMAKE_SOURCE_DIR}/bin-int/${CMAKE_BUILD_TYPE}-${SystemName}-${CMAKE_SYSTEM_PROCESSOR}")

# Set optimizations for Release build
# -fno-exceptions can be added as argument to strip exceptions
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -flto -march=native -fno-rtti")

# Set the directory containing your header files
set(SOURCE_DIR "Molten/src")
set(INCLUDE_DIR "Molten/src")

# Recursively find source and header files
file(GLOB_RECURSE SOURCE_FILES "${SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE OBJ_FILES "${SOURCE_DIR}/*.mm")
file(GLOB_RECURSE HEADER_FILES "${INCLUDE_DIR}/*.h")

# Create executable
add_executable("${PROJECT_NAME}" ${SOURCE_FILES} ${OBJ_FILES})

# Set output directory
set(TargetDir ${TargetDir}/${PROJECT_NAME})
set(ObjDir ${ObjDir}/${PROJECT_NAME})
set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${TargetDir}"
        ARCHIVE_OUTPUT_DIRECTORY "${ObjDir}"
        LIBRARY_OUTPUT_DIRECTORY "${ObjDir}"
)

set_source_files_properties(${OBJ_FILES} PROPERTIES SKIP_PRECOMPILE_HEADERS ON)

# Add precompiled header
target_precompile_headers(${PROJECT_NAME} PRIVATE Molten/src/mltnpch.h)

# TODO: Platform specific macros
# Build Configurations
if (CMAKE_BUILD_TYPE MATCHES Debug)
    # Define the macro to enable debug breaks only for Debug build
    target_compile_definitions(${PROJECT_NAME} PRIVATE MLTN_ENABLE_ASSERTS)
    add_compile_definitions(MLTN_BUILD_TYPE_DEBUG)
endif ()
if (CMAKE_BUILD_TYPE MATCHES Release)
    add_compile_definitions(MLTN_BUILD_TYPE_RELEASE)
endif ()

add_subdirectory(Molten/vendor/glfw)
add_subdirectory(Molten/vendor/spdlog)
#add_subdirectory(vendor/imgui)


# Set output directory for libraries
set_target_properties(glfw PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${ObjDir}
        LIBRARY_OUTPUT_DIRECTORY ${ObjDir})
set_target_properties(spdlog PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${ObjDir}
        LIBRARY_OUTPUT_DIRECTORY ${ObjDir})

target_include_directories(${PROJECT_NAME}
        PRIVATE ${SOURCE_DIR}
        PRIVATE Molten/vendor/metal-cpp
        PRIVATE Molten/vendor/glfw/include
        PRIVATE Molten/vendor/spdlog/include)

target_link_libraries(${PROJECT_NAME}
        "-framework Metal"
        "-framework Foundation"
        "-framework QuartzCore"
        glfw
        spdlog)