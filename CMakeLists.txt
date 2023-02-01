# Specify the minimum required version of CMake
cmake_minimum_required(VERSION 3.0)

# Project name
project(GFSharp)

# Set the C++ standard to use for the project
# In this case, the C++17 standard is used
set(CMAKE_CXX_STANDARD 17)

# Include directories
# These are directories where the compiler will look for header files
# In this case, the include directory is specified
include_directories(include)

# Gather all the .cpp files in the src directory into the SOURCES variable
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Add an executable to be built from the sources
# The name of the executable is "GFSharp"
# The sources are specified in the SOURCES variable
add_executable(GFSharp ${SOURCES})