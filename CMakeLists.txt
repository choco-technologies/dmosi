# =====================================================================
#               DMOD OSI CMake Configuration
# =====================================================================
cmake_minimum_required(VERSION 3.10)

# ======================================================================
#               DMOD OSI
# ======================================================================
project(dmosi
    VERSION 1.0
    DESCRIPTION "DMOD Operating System Interface"
    LANGUAGES C CXX)

set(DMOSI_DONT_IMPLEMENT_DMOD_API OFF CACHE BOOL "Do not implement DMOD API in dmosi library")


# ======================================================================
#               Fetch DMOD repository
# ======================================================================
include(FetchContent)

# Only fetch and build dmod if it's not already available as a target
if(NOT TARGET dmod_inc)
    FetchContent_Declare(
        dmod
        GIT_REPOSITORY https://github.com/choco-technologies/dmod.git
        GIT_TAG        develop
    )

    # ======================================================================
    #               DMOD Configuration
    # ======================================================================
    set(DMOD_MODE "DMOD_SYSTEM" CACHE STRING "DMOD build mode")
    set(DMOD_BUILD_TESTS OFF CACHE BOOL "Build tests")
    set(DMOD_BUILD_EXAMPLES OFF CACHE BOOL "Build examples")
    set(DMOD_BUILD_TOOLS OFF CACHE BOOL "Build tools")
    set(DMOD_BUILD_TEMPLATES OFF CACHE BOOL "Build templates")
    
    # Pass coverage flags to DMOD if enabled
    if(ENABLE_COVERAGE)
        set(DMOD_ENABLE_COVERAGE ON CACHE BOOL "Enable DMOD coverage")
    endif()

    FetchContent_MakeAvailable(dmod)
    set(DMOD_DIR ${dmod_SOURCE_DIR} CACHE PATH "DMOD source directory" FORCE)
else()
    message(STATUS "dmod target already exists, skipping FetchContent")
endif()

# ======================================================================
#               DMOD OSI Library
# ======================================================================
set(MODULE_NAME dmosi)
add_library(${MODULE_NAME} STATIC
    src/dmosi.c
)

target_compile_definitions(${MODULE_NAME} 
    PRIVATE 
        $<$<BOOL:${DMOSI_DONT_IMPLEMENT_DMOD_API}>:DMOSI_DONT_IMPLEMENT_DMOD_API>
        DMOSI_VERSION="${PROJECT_VERSION}"
)

target_include_directories(${MODULE_NAME} 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)   

target_link_libraries(${MODULE_NAME} 
    PRIVATE    
        dmod_inc
    )

# Enable coverage for dmosi library if requested
if(ENABLE_COVERAGE)
    target_compile_options(${MODULE_NAME} PRIVATE --coverage)
    target_link_options(${MODULE_NAME} PRIVATE --coverage)
endif()

create_library_makefile(${MODULE_NAME})

# ======================================================================
#               Tests
# ======================================================================
option(DMOSI_BUILD_TESTS "Build tests" OFF)

if(DMOSI_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
