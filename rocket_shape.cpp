#include <GL/glut.h>

void display(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
    glClear(GL_COLOR_BUFFER_BIT);
    
    glBegin(GL_LINE_LOOP);

    glColor3f(0.0f,1.0f,0.0f);
    
    glVertex2f(0.1f, -0.6f);
    glVertex2f(0.7f, -0.6f);
    glVertex2f(0.4f, -0.1f);
    
    glEnd();
    
    glFlush();
}


int main(int argc,char** argv){
    //Initialize glut
    glutInit(&argc,argv);
    //creating a window
    glutCreateWindow("Rocket");
    //Set the window's initial width and height
    glutInitWindowSize(50,50);
    //Initial position of the top-left corner
    glutInitWindowPosition(0,0);
    //display call back function
    glutDisplayFunc(display);
    //enter the event-processing loop
    glutMainLoop();
    
    return 0;
}