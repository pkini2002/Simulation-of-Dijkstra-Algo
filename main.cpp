// Importing Standard libraries

#include<stdio.h>
#include<iostream>
#include<GL/glut.h>
#include<math.h>
#include <GL/gl.h>

using namespace std;

// defining global variables
#define GL_PI 3.14
#define MAX 25
int n,i=1,a[25],b[25],cost[25][25],tree[25][25],src,l[2],dist[10];
char s[20],*s1;
void *currentfont;

//FUNCTION TO SELECT BITMAP FONT
void setFont(void *font)
{
     currentfont=font;
}

//FUNCTION TO DRAW BITMAP string at (x,y)
// The drawstring function is a custom function for rendering text in an OpenGL application using
// bitmap fonts
void drawstring(GLfloat x,GLfloat y,char *string)
{
   char *c;
   // glRasterPos2f(x, y) - Sets the raster position for subsequent bitmap rendering calls.
   glRasterPos2f(x,y);

   // Loops through each character in the string to be rendered.
   for(c=string;*c!='\0';*c++)
   {
       // Renders each character in the string using the currently selected bitmap font (currentfont).
       // This function takes two arguments: the first is the bitmap font to use, and the second is the
       // character to be rendered.
        glutBitmapCharacter(currentfont,*c);
   }
}

//DISPLAY FUNCTION FOR TITLE PAGE
void title()
{
     glLineWidth(3.0); // draws lines with a width of 3px
     glColor3f(1.0,1.0,0.0);
     glBegin(GL_LINE_LOOP);
     glVertex2f(10,10);
     glVertex2f(10,490);
     glVertex2f(490,490);
     glVertex2f(490,10);
     glEnd();
     setFont(GLUT_BITMAP_HELVETICA_18);
     glColor3f(1.0,1.0,1.0);
     drawstring(100,440,"Topic: Simulation of Dijktra's Algorithm using OpenGL");
     glColor3f(1.0,1.0,1.0);
     drawstring(100,400,"Submitted by");
     glColor3f(0.0,1.0,0.0);
     drawstring(100,360,"PRATHIKSHA KINI");
     drawstring(100,340,"PALGUNI SAMAGA")
     glColor3f(0.0,1.0,0.0);
     drawstring(100,320,"VI CSE - SEC C");
     glColor3f(0.0,1.0,0.0);
     drawstring(100,280,"4NM20CS139");
     drawstring(100,240,"4NM20CS127");
     glColor3f(1.0,1.0,1.0);
     drawstring(100,100,"Right click in My Window for options");
     glFlush();
}

// When clicked on items of context menu it should call these functions
void top_menu(int option)
{
     switch(option)
     {
        // Reads the weighted matrix and number of vertices, source node
        case 1:read();
               glutPostRedisplay();
               break;
        // connects the nodes based on the values provided in the weight matrix
        case 2:drawline();
               glutPostRedisplay();
               break;
        // Computes the shortest path b/w src node to all other nodes
        case 3:shortestpath();
               glutPostRedisplay();
               break;
        // terminates the program
        case 4:exit(0);
     }
}

// Event handler function which draws squares (Basically nodes) when left button of mouse is pressed
void mouse(int bin, int state , int x , int y)
{
     if(bin==GLUT_LEFT_BUTTON&&state==GLUT_DOWN)
         drawSquare(x,y);
}

// Used to initialize the settings of OpenGl library of all other screens
void init (void)
{
     glClearColor (1.0, 1.0, 1.0, 1.0);
     glClear(GL_COLOR_BUFFER_BIT);
     // Sets the viewport (the area of the window where drawing occurs) to be the entire window,
     // with a width and height of 500 pixels.
     glViewport( 0,0, 500, 500 );
     // Sets the current matrix mode to the projection matrix.
     glMatrixMode( GL_PROJECTION );
     // Sets the current projection matrix to an orthographic projection that maps the 2D viewport to
     // the range (0, 500) in both x and y directions.
     glOrtho( 0.0, 500.0, 0.0, 500.0, 1.0, -1.0 );
     // Sets the current matrix mode to the modelview matrix.
     glMatrixMode(GL_MODELVIEW);
     // Replaces the current matrix with the identity matrix.
     glLoadIdentity();
     glFlush();
}

// Used to initialize some settings of OpenGL Library (Used for 1st page)
void myInit1()
{
   // Sets the clear color for the color buffer to black.
   glClearColor(0.0,0.0,0.0,0.0);
   // Sets the current drawing color to black.
   glColor3f(0.0f,0.0f,0.0f);
   //  Sets the size of points that will be drawn with glBegin(GL_POINTS) to 5 pixels.
   glPointSize(5.0);
   // Sets the current projection matrix to an orthographic projection that maps the 2D viewport to the
   // range (0, 500) in both x and y directions.
   gluOrtho2D(0.0,500.0,0.0,500.0);
   // Sets the current matrix mode to the projection matrix.
   glMatrixMode(GL_PROJECTION);
   // Replaces the current matrix with the identity matrix.
   glLoadIdentity();
   // Sets the current font to GLUT_BITMAP_HELVETICA_18. This means that any subsequent text drawn
   // using glutBitmapCharacter() will use this font.
   setFont(GLUT_BITMAP_HELVETICA_18);
}


// Screen to display project title,name,usn
void display1(void)
{
   glClear(GL_COLOR_BUFFER_BIT);
   title();
}

int main(int argc,char *argv[]){
    glutInit(&argc,argv);

    /*glutInitDisplayMode is a function from the GLUT (OpenGL Utility Toolkit) library used to set the
     initial display mode for an OpenGL window.*/
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);

    // GLUT_SINGLE: This flag specifies that the window should use a single buffering display mode.
    // GLUT_RGB: This flag specifies that the window should use an RGB color model for rendering.

    glutInitWindowPosition(820,100);
    glutInitWindowSize(450,450);

    // glutInitWindowPosition and glutInitWindowSize are functions from the GLUT (OpenGL Utility Toolkit)
    //  library used to set the initial position and size of an OpenGL window.

    glutCreateWindow("Front Sheet");
    glutDisplayFunc(display1);
    myInit1();

    glutInitDisplayMode( GLUT_SINGLE|GLUT_RGB );
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("My Window");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);


    glutCreateMenu(top_menu);
    glutAddMenuEntry("Read Cost Matrix",1);
    glutAddMenuEntry("Display Weighted Graph",2);
    glutAddMenuEntry("Display Shortest Path",3);
    glutAddMenuEntry("Exit",4);
    glutAttachMenu(GLUT_RIGHT_BUTTON); // creates a context menu on right click of the mouse


    printf("\nGO TO MY WINDOW AND CLICK RIGHT BUTTON FOR NEXT OPTION\n");
    init();

    glutMainLoop(); // used to display the screen until the program is terminated
}



