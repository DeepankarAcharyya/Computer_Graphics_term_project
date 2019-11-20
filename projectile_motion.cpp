#include <GL/glut.h>  // GLUT, includes glu.h and gl.h
#include <math.h>     // Needed for sin, cos
#define PI 3.14159265f
 
// Global variables
char title[] = "Projectile Motion";  // Windowed mode's title
int windowWidth  = 1000;     // Windowed mode's width
int windowHeight = 800;     // Windowed mode's height
int windowPosX   = 50;      // Windowed mode's top-left corner x
int windowPosY   = 50;      // Windowed mode's top-left corner y
GLfloat xSpeed = 0.02f;      // Ball's speed in x and y directions
GLfloat ySpeed = 0.007f;
 
GLfloat ballRadius = 0.1f;   // Radius of the bouncing ball
GLfloat ballX = 0.0f;         // Ball's center (x, y) position
GLfloat ballY = 0.0f;
GLfloat ballXMax, ballXMin, ballYMax, ballYMin; // Ball's center (x, y) bounds
GLfloat u=15;
GLfloat theta=45;
float t=0.01;
int refreshMillis = 100;      // Refresh period in milliseconds
 
// Projection clipping area
GLdouble clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop;
 
/* Initialize OpenGL Graphics */
void initGL() {
   glClearColor(1.0f, 1.0f, 1.0f, 0.0f); }
 
/* Callback handler for window re-paint event */
void display() {
   glClear(GL_COLOR_BUFFER_BIT);  // Clear the color buffer
   glMatrixMode(GL_MODELVIEW);    // To operate on the model-view matrix
   glLoadIdentity();              // Reset model-view matrix
 
   glTranslatef(ballX, ballY, 0.0f);  // Translate to (xPos, yPos)
   glBegin(GL_QUADS);
      glColor3f(0.0f, 0.0f, 1.0f); 
      glVertex2f(0.0f, 0.2f);       
      glVertex2f(0.0f,0.0f);
      glVertex2f(0.2f,0.0f);
      glVertex2f(0.2f,0.2f);
   glEnd();
 
   glutSwapBuffers();  // Swap front and back buffers (of double buffered mode)
 
   // Animation Control - compute the location for the next refresh
   ballX += xSpeed;
   ballY += ySpeed;
   
   xSpeed = u*cos(theta)*t;
   ySpeed = u*sin(theta)*t-0.5*9.8*t*t;
   t+=0.1;
   // Check if the ball exceeds the edges
   if (ballX > ballXMax) {
      //reset
   } else if (ballX < ballXMin) {
      //reset
   }
   if (ballY > ballYMax) {
      //reset
   } else if (ballY < ballYMin) {
     //reset
   }
}
 
/* Call back when the windows is re-sized */
void reshape(GLsizei width, GLsizei height) {
   // Compute aspect ratio of the new window
   if (height == 0) height = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;
 
   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);
 
   // Set the aspect ratio of the clipping area to match the viewport
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();             // Reset the projection matrix
   if (width >= height) {
      clipAreaXLeft   = -1.0 * aspect;
      clipAreaXRight  = 1.0 * aspect;
      clipAreaYBottom = -1.0;
      clipAreaYTop    = 1.0;
   } else {
      clipAreaXLeft   = -1.0;
      clipAreaXRight  = 1.0;
      clipAreaYBottom = -1.0 / aspect;
      clipAreaYTop    = 1.0 / aspect;
   }
   gluOrtho2D(clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop);
   ballXMin = clipAreaXLeft + ballRadius;
   ballXMax = clipAreaXRight - ballRadius;
   ballYMin = clipAreaYBottom + ballRadius;
   ballYMax = clipAreaYTop - ballRadius;
}
 
/* Called back when the timer expired */
void Timer(int value) {
   glutPostRedisplay();    // Post a paint request to activate display()
   glutTimerFunc(refreshMillis, Timer, 0); // subsequent timer call at milliseconds
}
 
/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
   glutInit(&argc, argv);            // Initialize GLUT
   glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
   glutInitWindowSize(windowWidth, windowHeight);  // Initial window width and height
   glutInitWindowPosition(windowPosX, windowPosY); // Initial window top-left corner (x, y)
   glutCreateWindow(title);      // Create window with given title
   glutDisplayFunc(display);     // Register callback handler for window re-paint
   glutReshapeFunc(reshape);     // Register callback handler for window re-shape
   glutTimerFunc(0, Timer, 0);   // First timer call immediately
   initGL();                     // Our own OpenGL initialization
   glutMainLoop();               // Enter event-processing loop
   return 0;
}