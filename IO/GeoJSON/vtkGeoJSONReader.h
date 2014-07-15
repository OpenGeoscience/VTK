/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkGeoJSONReader.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkGeoJSONReader - Convert Geo JSON format to vtkPolyData
// .SECTION Description
// Outputs a vtkPolyData from the input
// Geo JSON Data (http://www.geojson.org) 

#ifndef __vtkGeoJSONReader_h
#define __vtkGeoJSONReader_h

// VTK Includes
#include "vtkPolyDataAlgorithm.h"
#include "vtkIOGeoJSONModule.h" // For export macro
#include "vtk_jsoncpp.h" // For json parser

class vtkPolyData;
class vtkStdString;

class VTKIOGEOJSON_EXPORT vtkGeoJSONReader: public vtkPolyDataAlgorithm
{
public:
  static vtkGeoJSONReader* New();
  vtkTypeMacro(vtkGeoJSONReader,vtkPolyDataAlgorithm);
  virtual void PrintSelf(ostream &os, vtkIndent indent);

  // Decription:
  // Accessor for name of the file to be read
  vtkSetStringMacro(FileName);
  vtkGetStringMacro(FileName);

  // Decription:
  // Accessor for string data
  vtkSetMacro(StringData, vtkStdString);
  vtkGetMacro(StringData, vtkStdString);

  enum ReadSources{
    ReadFromFile = 1,
    ReadFromString = 2
  };

  // Decription:
  // Accessor for string data
  vtkSetMacro(Source, ReadSources);
  vtkGetMacro(Source, ReadSources);

protected:
  vtkGeoJSONReader();
  virtual ~vtkGeoJSONReader();

  // Decription:
  // Core implementation of the
  int RequestData(vtkInformation* request, vtkInformationVector** inputVector,
                  vtkInformationVector* outputVector);

  // Decription:
  // Parse the Json Value corresponding to the root of the geoJSON data from the file
  void ParseRoot(Json::Value root, vtkPolyData *output);

  // Decription:
  // Verify if file exists and can be read by the parser
  // If exists, parse into Jsoncpp data structure
  int CanParse(Json::Value &root);

  // Description:
  // Case insensitive string comparison
  bool IsEqual(vtkStdString str1, vtkStdString str2);
  char *FileName;
  vtkStdString StringData;
  ReadSources Source;

private:
  vtkGeoJSONReader(const vtkGeoJSONReader&);  // Not implemented
  void operator=(const vtkGeoJSONReader&);    // Not implemented
};

#endif // __vtkGeoJSONReader_h
