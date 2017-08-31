/*
    Program:    Visualization Toolkit
    Module:     MazeGUI.cxx

    This program renders a GUI for the maze generating file Grid.cxx using VTK
    It was built as a project for CIS 441 at the University of Oregon

    Samantha Mintzmyer
*/

#include "vtkSmartPointer.h"
#include "vtkSphereSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkInteractorStyle.h"
#include "vtkInteractorStyleFlight.h"
#include "vtkObjectFactory.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkInteractorStyleTerrain.h>
#include "vtkRenderWindowInteractor.h"
#include "vtkProperty.h"
#include "vtkCamera.h"
#include "vtkLight.h"
#include "vtkOpenGLPolyDataMapper.h"
#include "vtkJPEGReader.h"
#include "vtkImageData.h"
#include <vtkAppendPolyData.h>
#include <vtkTimerLog.h>
#include <vtkTransform.h>
#include <vtkDepthSortPolyData.h>

#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkPolyDataReader.h>
#include <vtkPoints.h>
#include <vtkUnsignedCharArray.h>
#include <vtkFloatArray.h>
#include <vtkDoubleArray.h>
#include <vtkCellArray.h>
#include "Grid.cxx"

#include "vtkOpenGL.h"

/*
    class WASDInteractorStyle : public vtkInteractorStyleFlight

    This class extends vtkInteractorStyleFlight
    It defines OnKeyPress() function that maps movement to the WASD keys
*/



/*
    class vtk441SceneMapper : public vtkOpenGLPolyDataMapper

    This class extends vtkOpenGLPolyDataMapper
    It's responsible for setting up the lighting for the scene
*/



/*
    class vtk441MazeMapper : public vtk441SceneMapper

    This class extends vtk441SceneMapper
    It's responsible for rendering a 4D representation of the maze from Grid.cxx
*/



/*
    This is the main() function of MazeGUI.cxx
    It calls Grid.cxx to generate a maze
    It creates a new GUI scene and maze
    It creates a new Camera and WASD control
*/

int main()
{

    // Create a sphere
    vtkSmartPointer<vtkSphereSource> sphereSource = 
        vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetCenter(0.0, 0.0, 0.0);
    sphereSource->SetRadius(1.0);
    sphereSource->Update();
 
    // Create a mapper and actor
    vtkSmartPointer<vtkPolyDataMapper> mapper = 
        vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(sphereSource->GetOutputPort());
 
    vtkSmartPointer<vtkActor> actor = 
        vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
 
    vtkSmartPointer<vtkCamera> camera = 
        vtkSmartPointer<vtkCamera>::New();
    camera->SetPosition(0, 0, 20);
    camera->SetFocalPoint(0, 0, 0);
 
    // Create a renderer, render window, and interactor
    vtkSmartPointer<vtkRenderer> renderer = 
        vtkSmartPointer<vtkRenderer>::New();
 
    renderer->SetActiveCamera(camera);
 
    vtkSmartPointer<vtkRenderWindow> renderWindow = 
        vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
        vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);
 
    // Add the actor to the scene
    renderer->AddActor(actor);
    renderer->SetBackground(1,1,1); // Background color white
 
    // Render and interact
    renderWindow->Render();
    renderWindowInteractor->Start();




//    Call to Grid.cxx for new Maze Object
/*
    std::cout<<"Generate a new Grid\n";
    Grid Game1 = Grid(M);     // Function for making new grid
    Game1.Boundaries(M);
    Game1.genMaze();        //Function for building maze
    
    //  Create new GUI scene and Maze
    std::cout << "Create new GUI scene and Maze" << std::endl;

    vtkSmartPointer<vtkSphereSource> sphere =
      vtkSmartPointer<vtkSphereSource>::New();
    std::cout << "Setting sphere center, ";
    sphere->SetCenter(0.0, 0.0, 0.0);
    std::cout << "radius, ";
    sphere->SetRadius(5.0);
    std::cout << "Theta res, ";
    sphere->SetThetaResolution(100);
    std::cout << "Phi res, ";
    sphere->SetPhiResolution(100);
    std::cout << "and updating" << std::endl;
    sphere->Update();

    //  Create a mapper and actor
    std::cout << "//  Create a mapper";
    vtkSmartPointer<vtkPolyDataMapper> mapper = 
      vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(sphere->GetOutputPort();
    std::cout << " tie mapper to game, ";
    win1Mapper->Game = Game1;
    std::cout << " and set up lights";
    win1Mapper->SetupLight();

    std::cout << " and actor"
        << std::endl;
    vtkSmartPointer<vtkActor> win1Actor =
      vtkSmartPointer<vtkActor>::New();
    win1Actor->SetMapper(win1Mapper);

    vtkSmartPointer<vtkCamera> camera = 
      vtkSmartPointer<vtkCamera>::New();
    camera->SetPosition(0, 0, 20);
    camera->SetFocalPoint(0, 0, 0);

    //  Create a renderer, render window, and interactor
    std::cout << "//  Create a renderer, render window, and interactor"
        << std::endl;
    vtkSmartPointer<vtkRenderer> ren1 =
        vtkSmartPointer<vtkRenderer>::New();

    ren1->SetActiveCamera(camera);
    ren1->SetViewport(0, 0, 1, 1);

    win1Mapper->RenderPiece(ren1, win1Actor);

    //  Create a new Camera and WASD control to traverse Maze
    std::cout << "//  Create a new Camera and WASD control to traverse Maze"
        << std::endl;

    vtkSmartPointer<vtkRenderWindow> renWin =
        vtkSmartPointer<vtkRenderWindow>::New();
    renWin->AddRenderer(ren1);

    vtkSmartPointer<vtkRenderWindowInteractor> iren =
        vtkSmartPointer<vtkRenderWindowInteractor>::New();
    iren->SetRenderWindow(renWin);

    //  Add actor to the scene
    std::cout << "//  Add actor to the scene"
        << std::endl;
    bool doWindow1 = true;
    if (doWindow1)
        ren1->AddActor(win1Actor);
    ren1->SetBackground(0.0, 0.0, 0.0);
    
    vtkSmartPointer<vtkLight> Hlight = vtkSmartPointer<vtkLight>::New();
    Hlight->SetLightTypeToHeadlight();
    
    renWin->SetSize(1000, 1000);

    //  Render and interact
    renWin->Render();
    iren->Initialize();
    iren->Start();
    return EXIT_SUCCESS;
*/



}


