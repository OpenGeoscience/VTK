vtk_module(vtkIOMINC
  GROUPS
    StandAlone
  DEPENDS
    vtkIOGeometry
    vtkCommonExecutionModel
    vtkRenderingCore
    vtkFiltersHybrid
    vtkIOImage
  PRIVATE_DEPENDS
    vtksys
    vtkNetCDF
  )
