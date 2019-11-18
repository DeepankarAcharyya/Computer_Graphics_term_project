//program to animate a point
#include <GL/glut.h>

void initGL() {
   glClearColor(1.0f, 1.0f, 1.0f, 0.0f); 
}

void Timer(int value) {
   glutPostRedisplay(); // Post a re-paint request to activate display()
   glutTimerFunc(30,Timer,0);
}

GLfloat angle = 0.0f,x=0.0f,y=0.0f;

void display(){
   glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer
   glMatrixMode(GL_MODELVIEW);     // To operate on Model-View matrix
   glLoadIdentity();               // Reset the model-view matrix
 
   glPushMatrix();                     // Save model-view matrix setting
   glRotatef(angle, 0.0f, 0.0f, 1.0f); // rotate by angle in degrees
   glBegin(GL_LINES);
      glColor3f(1.0f, 0.0f, 0.0f);
      glVertex2f(-0.2f, -0.2f);
      glVertex2f(-0.1f, -0.1f);
   glEnd();
   glPopMatrix();
   glutSwapBuffers(); 
   angle+=1.0f;
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
