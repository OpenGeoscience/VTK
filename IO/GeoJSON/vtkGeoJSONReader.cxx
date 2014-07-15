/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkGeoJSONReader.cxx

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include "vtkGeoJSONReader.h"

// VTK Includes
#include "vtkPolyData.h"
#include "vtkStdString.h"
#include "vtkInformation.h"
#include "vtkInformationVector.h"
#include "vtkObjectFactory.h"
#include "vtkTriangleFilter.h"
#include "vtkCellArray.h"
#include "vtkGeoJSONFeature.h"

// C++ includes
#include <fstream>
#include <iostream>

vtkStandardNewMacro(vtkGeoJSONReader);

//----------------------------------------------------------------------------
vtkGeoJSONReader::vtkGeoJSONReader()
{
  this->FileName = NULL;
  this->StringData = "";
  this->SetNumberOfInputPorts(0);
  this->SetNumberOfOutputPorts(1);
  this->Source = ReadFromFile;
}

//----------------------------------------------------------------------------
vtkGeoJSONReader::~vtkGeoJSONReader()
{
  delete[] FileName;
}

//----------------------------------------------------------------------------
int vtkGeoJSONReader::CanParse(Json::Value &root)
{
  Json::Reader reader;
  bool parsedSuccess = false;

  if (Source == ReadFromFile)
    {
    ifstream file;
    file.open( this->FileName );

    if ( ! file.is_open() )
      {
      vtkErrorMacro(<< "Unable to Open File " << this->FileName);
      return VTK_ERROR;
      }

    //parse the entire geoJSON data into the Json::Value root
    parsedSuccess = reader.parse(file, root, false);
    }
  else if (Source == ReadFromString)
    {
      parsedSuccess = reader.parse(StringData, root, false);
    }

  if ( ! parsedSuccess )
    {
    // Report failures and their locations in the document
    vtkErrorMacro(<<"Failed to parse JSON" << endl << reader.getFormatedErrorMessages());
    return VTK_ERROR;
    }

  return VTK_OK;
}

//----------------------------------------------------------------------------
int vtkGeoJSONReader::RequestData(vtkInformation* vtkNotUsed(request),
                                   vtkInformationVector** vtkNotUsed(request),
                                   vtkInformationVector* outputVector)
{
  // Get the info object
  vtkInformation* outInfo = outputVector->GetInformationObject(0);

  // Get the ouptut
  vtkPolyData* output = vtkPolyData::SafeDownCast(outInfo->Get(vtkDataObject::DATA_OBJECT()));

  Json::Value root;
  if ( CanParse(root) == VTK_ERROR )
    {
    return VTK_ERROR;
    }

  // If parsed successfully into Json parser Values and Arrays, then convert it
  // into appropriate vtkPolyData
  if ( root.isObject() )
    {
    ParseRoot(root, output);

    //Convert Concave Polygons to convex polygons using triangulation
    vtkTriangleFilter *filter = vtkTriangleFilter::New();
    filter->SetInputData(output);
    filter->Update();

    output->ShallowCopy(filter->GetOutput());
    }
  return VTK_OK;
}

//----------------------------------------------------------------------------
void vtkGeoJSONReader::ParseRoot(Json::Value root, vtkPolyData *output)
{
  output->SetPoints( vtkPoints::New() );//Initialising containers for points,
  output->SetVerts( vtkCellArray::New() );//Vertices,
  output->SetLines( vtkCellArray::New() );//Lines and
  output->SetPolys( vtkCellArray::New() );//Polygons

  Json::Value rootType = root.get( "type", -1 );
  Json::Value rootFeatures = root.get( "features", -1 );

  if ( rootFeatures == -1 )
    {

    // For specific cases if GeoJSON Data is not in standard format as specified here: http://www.geojson.org
    // For PostGIS GeoJSON Output follows the example
    vtkGeoJSONFeature *feature = vtkGeoJSONFeature::New();
    if(feature->ExtractGeoJSONFeatureGeometry(root, output)) // Data in GeoJSON format as specified by PostGIS
      return;

    // No match to any GeoJSON format
    vtkErrorMacro (<<"Error parsing root");
    return;
    }

  if ( rootFeatures.isArray() )
    {
    // If it is a collection of features
    for (int i = 0; i < rootFeatures.size(); i++)
      {
      // Append extracted geometry to existing outputData
      Json::Value child = rootFeatures[i];
      vtkGeoJSONFeature *feature = vtkGeoJSONFeature::New();
      feature->ExtractGeoJSONFeature(child, output);
      }
    }
  else
    {
    // Single feature in the geoJSON data
    vtkGeoJSONFeature *feature = vtkGeoJSONFeature::New();
    feature->ExtractGeoJSONFeature(rootFeatures, output);
    }
}

//----------------------------------------------------------------------------
void vtkGeoJSONReader::PrintSelf(ostream &os, vtkIndent indent)
{
  Superclass::PrintSelf(os, indent);
  os << "vtkGeoJSONReader" << std::endl;
  os << "Filename: " << this->FileName << std::endl;
}