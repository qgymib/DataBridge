cmake_minimum_required(VERSION 3.15)
project(DataBridge
    VERSION 0.0.1
)

# Require CMake 3.15
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

###############################################################################
# Functions
###############################################################################

# Enable all reasonable warnings and make all warnings into errors.
function(setup_target_wall name)
    if (CMAKE_C_COMPILER_ID STREQUAL "MSVC")
        target_compile_options(${name} PRIVATE /W4 /WX /utf-8)
    else ()
        target_compile_options(${name} PRIVATE -Wall -Wextra -Werror)
    endif ()
endfunction()

###############################################################################
# Executable
###############################################################################

set(db_sources
    "src/protocol/__init__.cpp"
    "src/protocol/socks5.cpp"
    "src/widgets/MainFrame.cpp"
    "src/main.cpp"
)

if (WIN32)
    add_executable(${PROJECT_NAME} WIN32 ${db_sources} "resource.rc")
else()
    add_executable(${PROJECT_NAME} ${db_sources})
endif ()

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

target_compile_options(${PROJECT_NAME}
    PRIVATE
        -DCMAKE_PROJECT_NAME="${CMAKE_PROJECT_NAME}"
        -DCMAKE_PROJECT_VERSION="${CMAKE_PROJECT_VERSION}"
        -D_WIN32_WINNT=0x0600
)
target_link_libraries(${PROJECT_NAME} PRIVATE Iphlpapi Ws2_32)
setup_target_wall(${PROJECT_NAME})

# https://cmake.org/cmake/help/latest/prop_tgt/CXX_STANDARD.html
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

if (MINGW)
    target_link_options(${PROJECT_NAME} PRIVATE
            -static-libgcc
            -static-libstdc++
            -static
    )
endif ()

###############################################################################
# Dependency
###############################################################################

include(third_party/json.cmake)
target_include_directories(${PROJECT_NAME} PRIVATE ${JSON_INCLUDE_DIRS})

set(wxBUILD_SHARED OFF)
add_subdirectory(third_party/wxWidgets)
target_link_libraries(${PROJECT_NAME} PUBLIC wx::net wx::core wx::base)

include(third_party/result.cmake)
target_include_directories(${PROJECT_NAME} PRIVATE ${RESULT_INCLUDE_DIRS})
