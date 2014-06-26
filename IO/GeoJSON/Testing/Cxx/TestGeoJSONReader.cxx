/*=========================================================================

  Program:   Visualization Toolkit
  Module:    TestGeoJSONReader.cxx

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkGeoJSONReader.h"

// VTK includes
#include <vtkActor.h>
#include <vtkMapper.h>
#include <vtkNew.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkRegressionTestImage.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkTestUtilities.h>

// Main program
int TestGeoJSONReader(int argc, char* argv[])
{
  const char* vectorFileName = vtkTestUtilities::ExpandDataFileName(argc, argv, "Data/GeoJSON/india.json");

  // Create reader to read shape file.
  vtkNew<vtkGeoJSONReader> reader;
  reader->SetFileName(vectorFileName);
  delete [] vectorFileName;

  reader->Update();

  // We need a renderer
  vtkNew<vtkRenderer> renderer;

  // Get the data
  vtkSmartPointer<vtkPolyData> polydata = reader->GetOutput();

  // Create scene
  vtkNew<vtkActor> actor;
  vtkNew<vtkPolyDataMapper> mapper;

  mapper->SetInputData(polydata);
  actor->SetMapper(mapper.GetPointer());
  renderer->AddActor(actor.GetPointer());

  //Create a render window, and an interactor
  vtkNew<vtkRenderWindow> renderWindow;
  vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
  renderWindow->AddRenderer(renderer.GetPointer());
  renderWindowInteractor->SetRenderWindow(renderWindow.GetPointer());

  //Add the actor to the scene
  renderer->SetBackground(0.0, 0.0, 0.0);
  renderWindow->SetSize(400, 400);
  renderWindow->Render();
  renderer->ResetCamera();
  renderWindow->Render();

  int retVal = vtkRegressionTestImage(renderWindow.GetPointer());

  if ( retVal == vtkRegressionTester::DO_INTERACTOR)
    {
    renderWindowInteractor->Start();
    }
  return retVal;
}
