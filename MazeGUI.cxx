/*
    Program:    OpenGL
    Module:     MazeGUI.cxx

    This program renders a GUI for the maze generating file Grid.cxx using OpenGL
    It was built as a project for CIS 441 at the University of Oregon

    Samantha Mintzmyer
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifndef WIN32
#include <unistd.h>
#else
#define random rand
#define srandom srand
#endif

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Grid.cxx"

/*
    class MazeMapper

    This class uses OpenGL to map the maze into graphics
    It's responsible for setting up the maze floor, walls, lighting
*/
class MazeMapper 
{
  protected:

  public:
//    MazeMapper();   
    static MazeMapper* New();
    Grid Game;
    //  void DrawFloor(void);
    void DrawWalls(void);
    void SetLights(void);
};
  
//  Draw the floor, and eventually ceiling of the maze 
void DrawFloor(void)
{
    std::cout << "In DrawFloor\n";
    //  glDisable(GL_LIGHTING);
    glBegin(GL_QUADS);
    std::cout << "Begun quad definition\n";
    glColor3f(0.855, 0.647, 0.125);
    std::cout << "Color set to goldenrod\n";
    glVertex3f(-18.0, 0.0, 27.0);
        std::cout << "One gl vertex defined\n";
        glVertex3f(27.0, 0.0, 27.0);
        glVertex3f(27.0, 0.0, -18.0);
        glVertex3f(-18.0, 0.0, -18.0);
    glEnd();
    std::cout << "Finished DrawFloor\n";
    //  glEnable(GL_LIGHTING);
}

//  Draw walls of maze
void MazeMapper::DrawWalls(void)
{


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


/*
    This is the main() function of MazeGUI.cxx
    It calls Grid.cxx to generate a maze
    It creates a new GUI scene and maze
    It creates a new Camera and WASD control
*/

int main(int argc, char *argv[])
{
    std::cout<<"Generate a new Grid\n";
    Grid Game1 = Grid(M);     // Function for making new grid

    //  Create a MazeMapper
    std::cout << "Generate new MazeMapper\n";
    //  MazeMapper* Mapper = new MazeMapper();
    //  DrawFloor();
    //  Mapper->SetLights();

    //  Create a camera
 
    //  Create a renderer, render window, and interactor
    std::cout << "glutInit and window\n";
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutCreateWindow("glutMaze");

    glutDisplayFunc(DrawFloor);
    //  glutKeyboardFunc(keyboard);
    //  glutVisibilityFunc(visible);

    //  Set up OpenGL state
    glClearDepth(1.0);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 20);
    glMatrixMode(GL_MODELVIEW);

    //  Add Maze

    //  Start event processing
    glutMainLoop();
    return 0;
}

