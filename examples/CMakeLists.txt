# cmake file

# requirements

# configuration

# aggregate example targets under a pseudo-target
add_custom_target(examples)

list(APPEND PRJ_EXAMPLE_NAMES "no_output")
list(APPEND PRJ_EXAMPLE_NAMES "no_output_derived")

foreach(prj_example_name ${PRJ_EXAMPLE_NAMES})
  set(EXAMPLE_SOURCES "${prj_example_name}.cpp")

  add_executable(${prj_example_name} ${EXAMPLE_SOURCES})

  set_target_properties(${prj_example_name} PROPERTIES 
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
    CMAKE_CXX_EXTENSIONS OFF)

  target_include_directories(${prj_example_name} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR})
  target_include_directories(${prj_example_name} PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include/>)
  target_include_directories(${prj_example_name} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>)

  # exclude example targets from main build
  set_target_properties(${prj_example_name} PROPERTIES EXCLUDE_FROM_ALL TRUE)

  add_dependencies(examples ${prj_example_name})
endforeach()

