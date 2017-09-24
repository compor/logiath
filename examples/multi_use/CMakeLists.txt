# cmake file

# configuration

set(EXAMPLE_SOURCES "use1.cpp" "use2.cpp")

add_executable(multi_use ${EXAMPLE_SOURCES})

set_target_properties(multi_use PROPERTIES 
  CXX_STANDARD 11
  CXX_STANDARD_REQUIRED ON
  CMAKE_CXX_EXTENSIONS OFF)

target_include_directories(multi_use PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(multi_use PUBLIC 
  $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include/>)
target_include_directories(multi_use PUBLIC
  $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>)

# exclude example targets from main build
set_target_properties(multi_use PROPERTIES EXCLUDE_FROM_ALL TRUE)

add_dependencies(examples multi_use)

