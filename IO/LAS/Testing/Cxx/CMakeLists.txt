vtk_add_test_cxx(${vtk-module}CxxTests tests
  TestLASReader.cxx
)
vtk_test_cxx_executable(${vtk-module}CxxTests tests)