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

//DRAW A BITMAP NUMBER i at (x,y)
/* This function draws a single digit number (0-9) as a bitmap character at a specified location (x,y)
 on the screen. It takes three parameters: x and y, which specify the coordinates of the location where
  the digit will be drawn, and i, which is the digit to be drawn. */
void raster(int x,int y,int i)
{
     char z=i+'0';
     glRasterPos2f(x-5,y-5);
     glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,z);
}

// This function takes a character array str and its length length as inputs and reverses the contents of
// the array in-place.
void reverse(char str[], int length)
{
    int start = 0;
    int end = length -1;
    while (start < end)
    {
        swap(*(str+start), *(str+end));
        start++;
        end--;
    }
}

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


//DISPLAY FUNCTION FOR INITIALIZING (DRAWING) THE  INPUT AND OUTPUT AREAS
// initial function is a custom function that sets up the initial state of an OpenGL application.
void initial()
{
    // Clears the color buffer
     glClear(GL_COLOR_BUFFER_BIT);
     // sets the font to helvetica
     setFont(GLUT_BITMAP_HELVETICA_18);
     glColor3f(0.0,0.0,0.0);
     // Used to write strings on the winodw
     drawstring(20,230,"Input Area");
     drawstring(20,470,"Output Area");
     glColor3f(0.0,0.0,0.0);
     glLineWidth(3.0);
     glBegin(GL_LINES);
     glVertex2f(10,10);
     glVertex2f(10,490);
     glVertex2f(10,490);
     glVertex2f(490,490);
     glVertex2f(490,490);
     glVertex2f(490,10);
     glVertex2f(490,10);
     glVertex2f(10,10);
     glVertex2f(10,250);
     glVertex2f(490,250);
     glEnd();
     glFlush();
}

// This function itoa() converts an integer value to a null-terminated string using the specified base
// and stores the result in the given character array str.

/*
The function handles negative numbers (only for base 10), and uses the ASCII characters '0' to '9' and 'a'
 to 'z' (or 'A' to 'Z') to represent digits greater than 9, depending on the base.
*/
char* itoa(int num, char* str, int base)
{
    int i = 0;
    bool isNegative = false;

    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    // In standard itoa(), negative numbers are handled only with
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10)
    {
        isNegative = true;
        num = -num;
    }

    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }

    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';

    str[i] = '\0'; // Append string terminator

    // Reverse the string
    reverse(str, i);
    return str;
}

//READ DATA: |V|,COST MATRIX, SOURCE VERTEX
void read()
{
    // Enter the number of vertices
     printf("Enter the number of vertices\n");
     scanf("%d",&n);
     // Enter the weighted matrix
     printf("Enter the cost matrix\n");
     for(int j=1;j<=n;j++)
     for(int k=1;k<=n;k++)
     {
        scanf("%d",&cost[j][k]);
        if(cost[j][k]==0)
            cost[j][k]=999;
     }
      // Enter the src node
      printf("Enter the source\n");
      scanf("%d",&src);

      printf("\nGO TO MY WINDOW AND CLICK RIGHT BUTTON FOR NEXT OPTION\n");
      initial(); //Draw the initial screen which shows blank i/p and o/p box
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
     glRasterPos2f(250, 360); // set position for next string
     glBitmap(10, 0, 0, 0, 0, 0, NULL); // add some space between the two names
     drawstring(260, 360, "4NM20CS139");
     glColor3f(0.0,1.0,0.0);
     drawstring(100,320,"PALGUNI SAMAGA");
     glRasterPos2f(250, 320);
     glBitmap(10, 0, 0, 0, 0, 0, NULL);
     drawstring(260, 320, "4NM20CS127");
     glColor3f(1.0,1.0,1.0);
     drawstring(100, 200, "Submitted to:");
     setFont(GLUT_BITMAP_TIMES_ROMAN_24);
     glColor3f(1.0, 1.0, 0.0);
     drawstring(250, 200, "Dr. Sannidhan MS");
     glColor3f(1.0, 1.0, 1.0);
     setFont(GLUT_BITMAP_HELVETICA_18);
     drawstring(250, 170, "Associate Professor");
     drawstring(250, 140, "Department of Computer Science and Engineering");
     drawstring(250, 110, "NMAM Institute Of Technology");
     drawstring(250, 80, "Nitte");
     drawstring(100,100,"Right click in My Window for options");
     glFlush();
}

//DRAW THE NODES (SQUARES)

/*The function first checks whether i is less than or equal to n, where n is some predefined constant
 indicating the maximum number of squares to draw. If i is greater than n, the function does nothing.
 If i is less than or equal to n, the function converts the y coordinate from screen coordinates to
 Open GL co-ordinates. It then sets the point size to 40 and chooses a color for the square based on
  whether i is equal to some global variable src. If so, the color is a shade of orange; otherwise, it is a
 shade of blue. The function then begins a GL_POINTS primitive and adds a single vertex at the (x,y)
 location. It ends the primitive with glEnd() and updates two global arrays a and b with the (x,y) coordinates of the square.
The function then sets the color to green, converts the integer i to a string using the itoa function,
and calls drawstring to draw the string near the square. Finally, the function calls glFlush() to ensure
that all OpenGL commands are executed immediately. The global variable i is incremented by 1 at the end of
the function.*/

void drawSquare(int x, int y)
{
     if(i<=n)
     {
        y = 500-y;                              //Convert from screen coordinates
        glPointSize(40);
        if(i==src)
            glColor3f(0.7f, 0.4f, 0.0f);
        else
            glColor3f(0.5f, 0.5f, 0.8f);
        glBegin(GL_POINTS);
        glVertex2f(x , y);
        glEnd();
        a[i]=x;
        b[i]=y;
        glColor3f(0.0f, 1.0f, 0.0f);
        s1=itoa(i,s,10);
        drawstring(x-5,y-5,s1);
        glFlush();
    }
    i=i+1;
}


//DRAW THE EDGES
// This function drawline() is responsible for drawing the edges of a graph in a visual representation
//  using OpenGL.

/* It iterates through all pairs of vertices and draws a line if there exists an edge between them with a
weight. The function takes the cost array, which represents the cost of each edge, and the a and b arrays,
which represent the x and y coordinates of each vertex respectively.
If the cost of the edge is not 999 (which usually represents an infinite cost or no edge), it draws a line
between the vertices with a green color and the weight of the edge is drawn in the middle of the line.
If the cost of the edge is not symmetric (i.e., cost[j][k]!=cost[k][j]), it means that the graph is
directed, and it draws the edge with an orange color and the weight of the edge is drawn slightly above
the line.*/


void drawline()
{
   int j,k,x1,x2,y1,y2;
   for(j=1;j<=n;j++)
   {
    for(k=1;k<=n;k++)
    {
     if(cost[j][k]!=999 && j<k)
     {
      x1=a[j];
      y1=b[j];
      x2=a[k];
      y2=b[k];


      glColor3f(0.0,0.5,0.0);

      glLineWidth(3);
      glBegin(GL_LINES);
                       glVertex2i(x1,y1);
                       glVertex2i(x2,y2);
      glEnd();

      s1=itoa(cost[j][k],s,10);
      drawstring((x1+x2-16)/2,(y1+y2+22)/2,s1);
      glFlush();
     }

     if(cost[j][k]!=cost[k][j] && cost[j][k]!=999 && j>k)
     {
      x1=a[j];
      y1=b[j];
      x2=a[k];
      y2=b[k];

      glColor3f(1.0,0.5,0.0);
      glBegin(GL_LINES);
                        glVertex2i(x1+10,y1+18);
                        glVertex2i(x2+10,y2+18);
      glEnd();

      s1=itoa(cost[j][k],s,10);
      drawstring((x1+x2+20)/2,(y1+y2+36)/2,s1);
      glFlush();
     }
    }
   }
}

// This function implements Dijkstra's algorithm to find the shortest path from a source vertex to all
// other vertices in a weighted, directed graph.
void shortestpath()
{
     //START OF DIJIKSTRA's
     int w,j,u,v,k,p,q,x1,y1,x2,y2,x,y;
     int dist[MAX],visit[MAX],parent[MAX],mincost,min;
     for(w=1;w<=n;w++)
     {
        visit[w]=0;
        dist[w]=cost[src][w];
        parent[w]=src;
     }
     visit[src]=1;
     mincost=0;
     k=1;
     for(w=1;w<n;w++)
     {
        min=999;
        u=-1;
        for(j=1;j<=n;j++)
        {
            if(!visit[j]&&dist[j]<min)
            {
                min=dist[j];
                u=j;
            }
        }
        visit[u]=1;
        mincost=mincost+dist[u];
        tree[k][1]=parent[u];
        tree[k++][2]=u;
        for(v=1;v<=n;v++)
        {
            if(!visit[v]&&(cost[u][v]+dist[u]<dist[v]))
            {
                dist[v]=dist[u]+cost[u][v];
                parent[v]=u;
            }
        }
     }
     printf("\nThe cost from source to other vertices are\n\n");
     for(w=1;w<=n;w++)
     {
        if(w!=src)
            printf("%d-->%d = %d\n",src,w,dist[w]);
     }

      //END OF DIJIKSTRAS
      for(int r=1;r<=n;r++)
      {
        x=a[r];
        y=b[r];
        glPointSize(25);
        if(r==src)
            glColor3f(0.7f, 0.4f, 0.0f);
        else
            glColor3f(0.5f, 0.5f, 0.8f);
        glBegin(GL_POINTS);
        glVertex2f(x,y+250);
        glEnd();
        glColor3f(0.0,1.0,0.0);
        s1=itoa(r,s,10);
        drawstring(x,y+250,s1);
        glFlush();
        for(int x=1;x<n;x++)
        {
            p=tree[x][1];
            q=tree[x][2];
            x1=a[p];
            y1=b[p];
            x2=a[q];
            y2=b[q];
            if(p<q)
            {
                glColor3f(0.0,0.5,0.0);
                glBegin(GL_LINES);
                glVertex2i(x1,y1+250);
                glVertex2i(x2,y2+250);
                glEnd();
                s1=itoa(cost[p][q],s,10);
                drawstring((x1+x2)/2,(y1+y2+500)/2,s1);
            }
            else
            {
                glColor3f(1.0,0.5,0.0);
                glBegin(GL_LINES);
                glVertex2i(x1,y1+250);
                glVertex2i(x2,y2+250);
                glEnd();
                s1=itoa(cost[p][q],s,10);
                drawstring((x1+x2)/2,(y1+y2+500)/2,s1);
            }
        }
        glFlush();
      }
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

//BLANK DISPLAY FUNCTION
void display (void)
{
     glFlush();
}


int main(int argc,char *argv[]){
    glutInit(&argc,argv);

    /*glutInitDisplayMode is a function from the GLUT (OpenGL Utility Toolkit) library used to set the
     initial display mode for an OpenGL window.*/
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);

    // GLUT_SINGLE: This flag specifies that the window should use a single buffering display mode.
    // GLUT_RGB: This flag specifies that the window should use an RGB color model for rendering.

    glutInitWindowPosition(920,100);
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



