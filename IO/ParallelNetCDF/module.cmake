vtk_module(vtkIOParallelNetCDF
  GROUPS
    MPI
  DEPENDS
    vtkCommonCore
    vtkParallelMPI
  COMPILE_DEPENDS
    vtkNetCDF
  TEST_DEPENDS
    vtkCommonExecutionModel
    vtkRenderingOpenGL
    vtkTestingRendering
    vtkInteractionStyle
  )
