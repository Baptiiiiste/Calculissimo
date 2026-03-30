cmake_minimum_required(VERSION 3.20)
project(Calculissimo)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_FILES
		src/main.cpp
		src/core/Application.cpp
		src/game/QuestionGenerator.cpp
		src/game/QuestionGenerator.cpp
		include/game/Operation.hpp
		include/game/GenerationSettings.hpp
		src/game/Question.cpp
)

add_executable(Calculissimo ${SOURCE_FILES}
		src/game/QuestionGenerator.cpp)

target_include_directories(Calculissimo PRIVATE include)
