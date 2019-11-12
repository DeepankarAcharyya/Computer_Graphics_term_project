//animating a point 
#include <stdio.h> 
#include <GL/glut.h> 
#include <math.h>


int main(int argc, char** argv){

    glutInit(&argc, argv); 
    // Display mode which is of RGB (Red Green Blue) type 
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
    // Declares window size 
    glutInitWindowSize(1360, 768); 
      
    // Declares window position which is (0, 0) 
    glutInitWindowPosition(0, 0); 
    // Name to window 
    glutCreateWindow("Point Animation"); 
  
    // Call to myInit() 
    myInit(); 
    glutDisplayFunc(display); 
    glutMainLoop();
}