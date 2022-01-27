cmake_policy(SET CMP0048 NEW)

cmake_minimum_required(VERSION 3.10)
project(fft VERSION 1.0.0 LANGUAGES CXX)

# Force default build type to Release
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING
            "Choose the type of build, options are: Debug, Release (default), RelWithDebInfo and MinSizeRel."
            FORCE)
endif (NOT CMAKE_BUILD_TYPE)

option(BUILD_EXAMPLES "Build examples" OFF)
option(BUILD_PYTHON "Build python bindings" ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(COMPILE_OPTIONS "${CMAKE_CXX_FLAGS} -Wall -Wextra")


set(BUILD_SHARED_LIBS ON)
add_subdirectory(pffft)
add_subdirectory(pybind11)

set_target_properties(PFFFT PROPERTIES POSITION_INDEPENDENT_CODE TRUE)

add_library(fft
        fft.hpp
        )
target_link_libraries(fft PFFFT)

target_compile_features(fft PRIVATE cxx_auto_type)
target_compile_options(fft PRIVATE -Werror -Wall)
set_target_properties(fft PROPERTIES LINKER_LANGUAGE CXX)
set_property(TARGET fft PROPERTY CXX_STANDARD 20)

if (BUILD_PYTHON)
    add_library(pyfft MODULE
            bindings.cpp
            )
    pybind11_extension(pyfft)
    pybind11_strip(pyfft)

    set_target_properties(pyfft PROPERTIES
            CXX_VISIBILITY_PRESET "hidden"
            CUDA_VISIBILITY_PRESET "hidden")
    target_link_libraries(pyfft PRIVATE
            pybind11::module
            pybind11::lto
            fft
            )

    # Copy build lib into python directory with python package
    set(PYTHON_MODULE_PATH ${CMAKE_SOURCE_DIR}/python/fft)
    add_custom_command(TARGET pyfft POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:pyfft> ${PYTHON_MODULE_PATH}/
            COMMENT "Copying python build library into python module"
            )

endif ()

if (BUILD_EXAMPLES)
    add_subdirectory(libsndfile)
    add_executable(wav-reader-snd
            wav_reader_snd.cpp
            )
    target_link_libraries(wav-reader-snd sndfile fft)
    target_compile_features(wav-reader-snd PRIVATE cxx_auto_type)
    target_compile_options(wav-reader-snd PRIVATE -Werror -Wall)
    set_target_properties(wav-reader-snd PROPERTIES LINKER_LANGUAGE CXX)
    set_property(TARGET wav-reader-snd PROPERTY CXX_STANDARD 20)
endif ()
