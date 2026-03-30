cmake_minimum_required(VERSION 3.20)
project(Calculissimo)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

find_package(raylib QUIET)

if (NOT raylib_FOUND)
	message(STATUS "raylib not found, fetching from GitHub...")
	FetchContent_Declare(
			raylib
			GIT_REPOSITORY https://github.com/raysan5/raylib.git
			GIT_TAG 5.5
	)
	FetchContent_MakeAvailable(raylib)
endif()

set(SOURCE_FILES
		src/main.cpp
		src/core/Application.cpp
		src/game/Difficulty.cpp
		src/game/Question.cpp
		src/game/QuestionGenerator.cpp
)

add_executable(Calculissimo ${SOURCE_FILES})

target_include_directories(Calculissimo PRIVATE include)
target_link_libraries(Calculissimo PRIVATE raylib)
