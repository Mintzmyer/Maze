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
#include "vtkMapper.h"

/* 
    //  vtkInteractorStyleTerrain
    class WASDInteractorStyle : public vtkInteractorStyleFlight

    This class extends vtkInteractorStyleFlight
    It defines OnKeyPress() function that maps movement to the WASD keys
*/



/*
    class MazeMapper

    This class uses OpenGL to map the maze into graphics
    It's responsible for setting up the maze floor, walls, lighting
*/
class MazeMapper 
{
  protected:

  public:
    MazeMapper();   
    static MazeMapper* New();
    Grid Game;
    void DrawFloor(void);
    void SetLights(void);
    void MapMaze(vtkRenderer *, vtkActor *);
};
  
//  Draw the floor, and eventually ceiling of the maze 
void MazeMapper::DrawFloor(void)
{
    glDisable(GL_LIGHTING);
    glBegin(GL_QUADS);
    glVertex3f(-18.0, 0.0, 27.0);
        glVertex3f(27.0, 0.0, 27.0);
        glVertex3f(27.0, 0.0, -18.0);
        glVertex3f(-18.0, 0.0, -18.0);
    glEnd();
    glEnable(GL_LIGHTING);
}

//  Set up lighting
void MazeMapper::SetLights(void)
{
    //  diffuse, ambient, and specular lighting
    GLfloat diffuse[4] = { 0.8, 0.8, 0.8, 1};
    GLfloat ambient[4] = {0.2, 0.2, 0.2, 1};
    GLfloat specular[4] = {0.0, 0.0, 0.0, 1};

    //  lighting locations; center and four corners
    GLfloat SWcorner[4] = { 1, 2, 13, 0 };
    GLfloat NWcorner[4] = { 10*M, 2, 13, 0 };
    GLfloat center[4] = { 10*M/2, 10*M/2, 13, 0 };
    GLfloat SEcorner[4] = { 1, 10*M, 13, 0 };
    GLfloat NEcorner[4] = { 10*M, 10*M, 13, 0 };
    GLfloat *pos[5] = {SWcorner, NWcorner, center, SEcorner, NEcorner};

    //  Add lights
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, center);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    
/*
    //  Array of lights
    GL_LIGHT *light[5] = {GL_LIGHT0, GL_LIGHT1, GL_LIGHT2, GL_LIGHT3, GL_LIGHT4};
    for (int i = 0; i < 5; i++)
    {
        glEnable(light[i]);
        glLightfv(light[i], GL_POSITION, pos[i];
    }
*/
}


void MazeMapper::MapMaze(vtkRenderer *ren, vtkActor *act)
{


}




/*
    This is the main() function of MazeGUI.cxx
    It calls Grid.cxx to generate a maze
    It creates a new GUI scene and maze
    It creates a new Camera and WASD control
*/

int main()
{
    std::cout<<"Generate a new Grid\n";
    Grid Game1 = Grid(M);     // Function for making new grid

    //  Create a MazeMapper
    MazeMapper* Mapper = new MazeMapper();
    Mapper->DrawFloor();
    Mapper->SetLights();

    //  Create a camera
 
    // Create a renderer, render window, and interactor

    // Add the actor to the scene

    // Render and interact

}




//    Call to Grid.cxx for new Maze Object
/*
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



