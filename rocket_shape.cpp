#include <GL/glut.h>

void display(){
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
   
    //top triangle
    glBegin(GL_TRIANGLES);
         glColor3f(1.0f, 1.0f, 0.0f);
        glVertex2i(50,70);
        glVertex2i(70,70);
        glVertex2i(60,90);
    glEnd();
    //mddle rectangle
    glBegin(GL_LINE_LOOP);
        glVertex2d(5,7);
        glVertex2d(5,0);
        glVertex2d(7,0);
        glVertex2d(7,7);
    glEnd();
    //left triangle
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2d(5,15);
        glVertex2d(5,0);
        glVertex2d(4,0);
    glEnd();
    //right triangle
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2d(70,15);
        glVertex2d(70,0);
        glVertex2d(80,0);
    glEnd();
    
    glFlush();
}


int main(int argc,char** argv){
    //Initialize glut
    glutInit(&argc,argv);
    //creating a window
    glutCreateWindow("Rocket");
    //Set the window's initial width and height
    glutInitWindowSize(500,500);
    //Initial position of the top-left corner
    glutInitWindowPosition(50,50);
    //display call back function
    glutDisplayFunc(display);
    //enter the event-processing loop
    glutMainLoop();
    
    return 0;
}