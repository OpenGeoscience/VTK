#netcdf cxx

PROJECT(VTKNETCDFCXX)

SET(SOURCES
  netcdf.cpp
  ncvalues.cpp
  )


foreach(file ${SOURCES})
  set(path_SOURCES ${path_SOURCES} ${PROJECT_SOURCE_DIR}/${file})
endforeach(file ${SOURCES})

set(netcdf_cxx_SOURCES ${path_SOURCES} CACHE INTERNAL "" FORCE)

VTK_ADD_LIBRARY(vtkNetCDFCXX ${netcdf_cxx_SOURCES})
TARGET_LINK_LIBRARIES(vtkNetCDFCXX LINK_PUBLIC vtkNetCDF)

#-----------------------------------------------------------------------------
#package the result
#-----------------------------------------------------------------------------

IF(NOT VTK_INSTALL_NO_DEVELOPMENT)
  INSTALL(FILES
    #${VTKNETCDFCXX_SOURCE_DIR}/include/vtk_netcdfcxx_mangle.h
    ${VTKNETCDFCXX_SOURCE_DIR}/include/netcdfcpp.h
    ${VTKNETCDFCXX_SOURCE_DIR}/cxx/netcdf.hh
    ${VTKNETCDFCXX_SOURCE_DIR}/cxx/ncvalues.h
    ${VTKNETCDF_BINARY_DIR}/vtk_netcdf_config.h
    DESTINATION ${VTK_INSTALL_INCLUDE_DIR}/vtknetcdf/include
    COMPONENT Development)
ENDIF(NOT VTK_INSTALL_NO_DEVELOPMENT)

