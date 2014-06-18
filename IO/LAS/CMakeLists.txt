find_package(libLAS REQUIRED)

mark_as_advanced(libLAS_INCLUDE_DIRS libLAS_LIBRARIES)

set(libLAS_SRCS vtkLASReader.cxx)

include_directories(${libLAS_INCLUDE_DIRS})

vtk_module_library(vtkIOLAS ${libLAS_SRCS})

target_link_libraries(vtkIOLAS LINK_PRIVATE  ${libLAS_LIBRARIES})
