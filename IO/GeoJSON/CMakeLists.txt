set(Module_SRCS
  vtkGeoJSONWriter.cxx
  vtkGeoJSONReader.cxx
  vtkGeoJSONFeature.cxx
  )

vtk_module_library(vtkIOGeoJSON ${Module_SRCS})