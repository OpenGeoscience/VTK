vtk_add_test_cxx(${vtk-module}CxxTests tests
  TestGeoJSONReader.cxx
)

ExternalData_add_test(VTKData
  NAME ${vtk-module}Cxx-IndiaOutlineMap
  COMMAND ${vtk-module}CxxTests TestGeoJSONReader
            -D ${VTK_TEST_DATA_DIR}
            -T ${VTK_TEST_OUTPUT_DIR}
            -V "DATA{../Data/Baseline/TestGeoJSONReader.png,:}"
  )

vtk_test_cxx_executable(${vtk-module}CxxTests tests
  RENDERING_FACTORY
  )