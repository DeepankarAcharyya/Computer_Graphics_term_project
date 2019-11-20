#include <GL/glut.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<time.h>
int count=0;

void drawHouse()
{
    glBegin(GL_LINES);

    glVertex2d(0,0);
    glVertex2d(0,50);

    glVertex2d(0,50);
    glVertex2d(100,50);


    glVertex2d(100,50);
    glVertex2d(100,0);

    glVertex2d(100,0);
    glVertex2d(0,0);
    glEnd();
}

class myPoint{
   public:
      float x,y;
      
      myPoint(){
            x=0;
            y=0;}

      myPoint(float x1,float y1){
         x=x1;
         y=y1; }
};


 void display()
 {
     int wws=500;


count++;
  //printf("\ndisplay is being called %d",count);  //to create the world window of user size.


     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
     gluOrtho2D(-wws,wws,-wws,wws);//size of world wiondow xmin,xmax,ymin,ymax.


     glClearColor(1,1,1,0);//background color is white as rgb all r set to 1.
        glClear(GL_COLOR_BUFFER_BIT);//applies the background color.
      glColor4f(1, 0, 0, 1);//color of the object u want to draw.
      glPointSize(3);//size of point.



glPushMatrix();
drawHouse();

glRotated(30,0,0,1);

drawHouse();

glPopMatrix();
glTranslated(10,60,0);
drawHouse();

glutSwapBuffers();
}

void spinDisplay ()          // ORIGINAL FUNCTION
{
    int i=0;
    glutPostRedisplay();
}

void timer_func(int n)           // NEW FUNCTION
{
        // Update the object positions, etc.
        spinDisplay();

         //glutTimerFunc(n, timer_func, n);
        glutTimerFunc(100, timer_func, 1000);
}


 int main(int argc, char **argv)
  {


    int mode=GLUT_RGB|GLUT_DOUBLE;
      glutInit(&argc, argv);
      glutInitDisplayMode(mode);
      glutInitWindowSize(800, 800);
       glutCreateWindow("Computer");

       glutTimerFunc(1, timer_func, 1000);
       glutDisplayFunc(display);

         glutMainLoop();
 }