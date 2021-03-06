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
    static void DrawMaze(void);
    static void DrawFloor(void);
    void DrawWalls(void);
    void keyboard(unsigned char ch, int x, int y);
    void SetLights(void);
};


//  Draw the floor, and eventually ceiling of the maze 
void MazeMapper::DrawFloor(void)
{
    std::cout << "Drawing Floor\n";
    glClear(GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);

    glBegin(GL_QUADS);
    glColor3f(0.855, 0.647, 0.125);
    glVertex3f(-(M/2)*1.0, -(M/2)*1.0, -20.0);
        glVertex3f((M/2)*1.0, -(M/2)*1.0, -20.0);
        glVertex3f((M/2)*1.0, (M/2)*1.0, -20.0);
        glVertex3f(-(M/2)*1.0, (M/2)*1.0, -20.0);
    glEnd();
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    
    glutSwapBuffers();
}

//  Draw walls of maze
void MazeMapper::DrawWalls(void)
{
    std::cout << "Starting on the walls of " << M << "x"<< M <<" grid!\n";
    for (int i = 0; i < M*M; i++)
    {
        if (Game.Tiles[i].Walls[1])
        {
            std::cout << "Making " << i << "th west wall\n";
            glBegin(GL_QUADS);
            glColor3f(0.678, 1.000, 0.184);
            glTexCoord2f(0,1);
            glVertex3f(((i%M)-10)+0.05, ((i/M)-10), -20);
            glTexCoord2f(0,0);
            glVertex3f(((i%M)-10)+0.05, (((i/M)+1)-9.0), -20);
            glTexCoord2f(1,0);
            glVertex3f(((i%M)-10)+0.05, (((i/M)+1)-9.0), -19);
            glTexCoord2f(1,1);
            glVertex3f(((i%M)-10)+0.05, ((i/M)-10), -19);
            glEnd();
        }
        if (Game.Tiles[i].Walls[2])
        {
            std::cout << "Making " << i << "th north wall\n";
            glBegin(GL_QUADS);
            glColor3f(0.678, 1.000, 0.184);
            glTexCoord2f(0,0);
            glVertex3f(((i%M)-10), ((i/M)-9)-0.05, -20);
            glTexCoord2f(1,0);
            glVertex3f(((i%M)-9), ((i/M)-9)-0.05, -20);
            glTexCoord2f(1,1);
            glVertex3f(((i%M)-9), ((i/M)-9)-0.05, -19);
            glTexCoord2f(0,1);
            glVertex3f(((i%M)-10), ((i/M)-9)-0.05, -19);
            glEnd();

        }
        if (Game.Tiles[i].Walls[3])
        {
            std::cout << "Making " << i << "th east wall\n";
            glBegin(GL_QUADS);
            glColor3f(0.678, 1.000, 0.184);
            glTexCoord2f(1,0);
            glVertex3f(((i%M)-9)-0.05, (i/M)-9, -20);
            glTexCoord2f(1,1);
            glVertex3f(((i%M)-9)-0.05, ((i/M))-10, -20);
            glTexCoord2f(0,1);
            glVertex3f(((i%M)-9)-0.05, ((i/M))-10, -19);
            glTexCoord2f(0,0);
            glVertex3f(((i%M)-9)-0.05, (i/M)-9, -19);
            glEnd();

        }
        if (Game.Tiles[i].Walls[4])
        {
            std::cout << "Making " << i << "th south wall\n";
            glBegin(GL_QUADS);
            glColor3f(0.678, 1.000, 0.184);
            glTexCoord2f(1,1);
            glVertex3f(((i%M)-9), (((i/M))-10)+0.05, -20);
            glTexCoord2f(1,0);
            glVertex3f(((i%M)-10), ((i/M)-10)+0.05, -20);
            glTexCoord2f(0,0);
            glVertex3f(((i%M)-10), ((i/M)-10)+0.05, -19);
            glTexCoord2f(0,1);
            glVertex3f(((i%M)-9), (((i/M))-10)+0.05, -19);
            glEnd();
        }
/*
        glBegin(GL_QUADS);
        glColor3f(0.722, 0.525, 0.043);
        glVertex3f((i%M)-9.0, (i/M)-9.0, -19.0);
        glVertex3f((i%M)-10.0, (i/M)-9.0, -19.0);
        glVertex3f((i%M)-10.0, (i/M)-10.0, -19.0);
        glVertex3f((i%M)-9.0, (i/M)-10.0, -19.0);
        glEnd();
*/

    }
    glutSwapBuffers();
}

//  Calls the methods to draw each piece of the maze 
void MazeMapper::DrawMaze(void)
{
    std::cout<<"Generate a new Grid\n";
    //  Grid Game1 = Grid();     // Function for making new grid


    MazeMapper::DrawFloor();
    MazeMapper* Mapper = new MazeMapper();
    //  Mapper->Game = Game1;
    Mapper->DrawWalls();
}
 
void keyboard(unsigned char ch, int x, int y)
{
    switch (ch) {
    //  ESC
    case 27:    
        exit(0);
        break;
    }
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
    //  Create a MazeMapper
    std::cout << "Generate new MazeMapper\n";
    //  MazeMapper* Mapper = new MazeMapper();
    //  Mapper->DrawFloor();
    //  Mapper->SetLights();

    //  Create a camera
 
    //  Create a renderer, render window, and interactor
    std::cout << "glutInit and window\n";
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
    //  Set Window size, position, and create with label
    glutInitWindowSize(900, 900);
    //  glutInitWindowPosition(0, 0);
    glutCreateWindow("Maze 98");

    glutDisplayFunc(MazeMapper::DrawMaze);
    glutKeyboardFunc(keyboard);
    //  glutVisibilityFunc(visible);

    //  Set up OpenGL state
    glClearDepth(1.0);
    glClearColor(0.0, 1.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 20);
    glMatrixMode(GL_MODELVIEW);

    //  Add Maze

    //  Start event processing
    glutMainLoop();
    return 0;
}

