cmake_minimum_required(VERSION 3.10)
project(fft VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(COMPILE_OPTIONS  "${CMAKE_CXX_FLAGS} -Wall -Wextra")


add_subdirectory(pffft)

add_executable(fft
        wav_reader.cpp
#    main.cpp
        )

target_link_libraries(fft PFFFT)
target_compile_features(fft PRIVATE cxx_auto_type)
target_compile_options(fft PRIVATE -Werror -Wall)
set_target_properties(fft PROPERTIES LINKER_LANGUAGE CXX)
set_property(TARGET fft PROPERTY CXX_STANDARD 20)
