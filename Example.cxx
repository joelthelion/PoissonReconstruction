#include <vtkSmartPointer.h>
#include <vtkPolyDataReader.h>
#include <vtkPolyDataWriter.h>

#include "vtkPoissonReconstruction.h"

int main(int argc, char *argv[])
{
  if( argc < 4 )
    {
    cout << "PoissonReconstruction takes 3 arguments: " << endl;
    cout << "1-Input file (*.vtk)" << endl;
    cout << "2-Depth" << endl;
    cout << "3-Output file (*.vtk)" << endl;
    return EXIT_FAILURE;
    }

  vtkstd::string inputFileName = argv[1];//"horsePoints.vtp";
  vtkstd::string outputFileName = argv[3];//"horse.vtp";
  int depth = atoi( argv[2] );
  
  vtkSmartPointer<vtkPolyDataReader> reader =
      vtkSmartPointer<vtkPolyDataReader>::New();
  reader->SetFileName(inputFileName.c_str());
  reader->Update();
  
  vtkSmartPointer<vtkPoissonReconstruction> poissonFilter = 
      vtkSmartPointer<vtkPoissonReconstruction>::New();
  poissonFilter->SetDepth( depth );
  poissonFilter->SetInputConnection(reader->GetOutputPort());
  poissonFilter->Update();
  
  vtkSmartPointer<vtkPolyDataWriter> writer =
    vtkSmartPointer<vtkPolyDataWriter>::New();
  writer->SetInputConnection(poissonFilter->GetOutputPort());
  writer->SetFileName(outputFileName.c_str());
  writer->Update();
  
  return EXIT_SUCCESS;
}

