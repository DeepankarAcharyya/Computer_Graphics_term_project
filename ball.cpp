#include <GL/glut.h>  // GLUT, includes glu.h and gl.h
#include <math.h>     // Needed for sin, cos
#define PI 3.14159265f
 
// Global variables
char title[] = "Bouncing Ball";  // Windowed mode's title
int windowWidth  = 640;     // Windowed mode's width
int windowHeight = 480;     // Windowed mode's height
int windowPosX   = 50;      // Windowed mode's top-left corner x
int windowPosY   = 50;      // Windowed mode's top-left corner y
 
GLfloat ballRadius = 0.1f;   // Radius of the bouncing ball

GLfloat ballX1 = 0.0f;         // Ball's center (x, y) position
GLfloat ballY1 = 0.0f;
GLfloat ballX2 = 0.0f;         // Ball's center (x, y) position
GLfloat ballY2 = 0.0f;

GLfloat ballXMax, ballXMin, ballYMax, ballYMin; // Ball's center (x, y) bounds

GLfloat xSpeed1 = 0.02f;      // Ball's speed in x and y directions
GLfloat ySpeed1 = 0.007f;
GLfloat xSpeed2 = 0.02f;      // Ball's speed in x and y directions
GLfloat ySpeed2 = 0.007f;

int refreshMillis = 30;      // Refresh period in milliseconds
 
// Projection clipping area
GLdouble clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop;
 
/* Initialize OpenGL Graphics */
void initGL() {
   glClearColor(1.0, 1.0, 1.0, 0.0); // Set background (clear) color to black
}
 
/* Callback handler for window re-paint event */
void display() {
   glClear(GL_COLOR_BUFFER_BIT);  // Clear the color buffer
   glMatrixMode(GL_MODELVIEW);    // To operate on the model-view matrix
   glLoadIdentity();              // Reset model-view matrix
 
   glTranslatef(ballX1, ballY1, 0.0f);  // Translate to (xPos, yPos)
   // Use triangular segments to form a circle
   glBegin(GL_TRIANGLE_FAN);
      glColor3f(0.0f, 0.0f, 1.0f); 
      glVertex2f(0.0f, 0.0f);       
      int numSegments = 90;
      GLfloat angle;
      for (int i = 0; i <= numSegments; i++) { // Last vertex same as first vertex
         angle = i * 2.0f * PI / numSegments;  // 360 deg for all segments
         glVertex2f(cos(angle) * ballRadius, sin(angle) * ballRadius);
      }
   glEnd();
 
   glTranslatef(ballX2, ballY2, 0.0f);  // Translate to (xPos, yPos)
   // Use triangular segments to form a circle
   glBegin(GL_TRIANGLE_FAN);
      glColor3f(0.0f, 1.0f, 0.0f); 
      glVertex2f(0.0f, 0.0f);       
      numSegments = 90;
      angle;
      for (int i = 0; i <= numSegments; i++) { // Last vertex same as first vertex
         angle = i * 2.0f * PI / numSegments;  // 360 deg for all segments
         glVertex2f(cos(angle) * ballRadius, sin(angle) * ballRadius);
      }
   glEnd();
 
   glutSwapBuffers();  // Swap front and back buffers (of double buffered mode)
 
   // Animation Control - compute the location for the next refresh
   ballX1 += xSpeed1;
   ballY1 += ySpeed1;

   ballX2 += xSpeed2;
   ballY2 += ySpeed2;
  // Check if the ball exceeds the edges
   if (ballX2 > ballXMax) {
      ballX2 = ballXMax;
      xSpeed2 = -xSpeed2;
   } else if (ballX2 < ballXMin) {
      ballX2 = ballXMin;
      xSpeed2 = -xSpeed2;
   }
   if (ballY2 > ballYMax) {
      ballY2 = ballYMax;
      ySpeed2 = -ySpeed2;
   } else if (ballY2 < ballYMin) {
      ballY2 = ballYMin;
      ySpeed2 = -ySpeed1;
   }
   // Check if the ball exceeds the edges
   if (ballX1 > ballXMax) {
      ballX1 = ballXMax;
      xSpeed1 = -xSpeed1;
   } else if (ballX1 < ballXMin) {
      ballX1 = ballXMin;
      xSpeed1 = -xSpeed1;
   }
   if (ballY1 > ballYMax) {
      ballY1 = ballYMax;
      ySpeed1 = -ySpeed1;
   } else if (ballY1 < ballYMin) {
      ballY1 = ballYMin;
      ySpeed1 = -ySpeed1;
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