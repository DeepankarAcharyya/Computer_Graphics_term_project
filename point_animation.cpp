//program to animate a point
#include <GL/glut.h>
#include <math.h>

GLfloat x=0.0f,y=0.0f;
GLfloat PointRadius = 0.1f;   // Radius of the bouncing Point
GLfloat ballX = 0.0f;         // Point's center (x, y) position
GLfloat ballY= 0.0f;
//GLfloat PointXMax, PointXMin, PointYMax, PointYMin; // Point's center (x, y) bounds
GLfloat xSpeed = 0.02f;      // Point's speed in x and y directions
GLfloat ySpeed = 0.007f;
int refreshMillis = 60;      // Refresh period in milliseconds
//GLdouble clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop;

//initial velocity-->to be taken randomly
//here taken constant
GLfloat u=15;
GLfloat theta=45;
GLfloat ux=u*cos(theta);
GLfloat uy=u*sin(theta);
int t=1;

void initGL() {
   glClearColor(1.0f, 1.0f, 1.0f, 0.0f); 
}

void Timer(int value) {
   glutPostRedisplay(); // Post a re-paint request to activate display()
   glutTimerFunc(refreshMillis,Timer,0);
}

void display(){
   glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer
   glMatrixMode(GL_MODELVIEW);     // To operate on Model-View matrix
   glLoadIdentity();               // Reset the model-view matrix
   
   glPushMatrix();                     // Save model-view matrix setting
   glTranslatef(ballX, ballY, 0.0f);
   //glRotatef(angle, 0.0f, 0.0f, 1.0f); // rotate by angle in degrees
   
   glBegin(GL_TRIANGLE_FAN);
      glColor3f(0.0f, 0.0f, 1.0f);  // Blue
      glVertex2f(0.0f, 0.0f);       // Center of circle
      int numSegments = 100;
      GLfloat angle;
      for (int i = 0; i <= numSegments; i++) { // Last vertex same as first vertex
         angle = i * 2.0f * 3.14 / numSegments;  // 360 deg for all segments
         glVertex2f(cos(angle) * PointRadius, sin(angle) * PointRadius);
      }
   glEnd();
   
   glPopMatrix();
   
   glutSwapBuffers(); 

   // Animation Control - compute the location for the next refresh
   xSpeed=ux*t;
   ySpeed=uy*t-0.5*9.8*t*t;
   ballX += xSpeed;
   ballY += ySpeed;
}

int main(int argc,char** argv){
    //Initialize glut
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    //creating a window
    glutCreateWindow("Point Animation");
    //Set the window's initial width and height
    glutInitWindowSize(640,480);
    //Initial position of the top-left corner
    glutInitWindowPosition(50,50);
    //display call back function
    glutDisplayFunc(display);
    glutTimerFunc(0,Timer,0);        
    initGL();         
    //enter the event-processing loop
    glutMainLoop();
    
    return 0;
}
