cmake_minimum_required (VERSION 2.6)
project (REDEYEFILTER_TASK)

add_compile_options(-Ofast)
add_compile_options(-Wall)
add_compile_options(-pedantic)

add_executable(eye cpp/main.cpp cpp/Solution.cpp cpp/utils/Image.cpp cpp/EyePatternConverter.cpp)

