//projectile motion
#include <GL/glut.h> 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>     
#define PI 3.14f
#define g 9.81f

//class
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

//global variables
const int max_memory=10000;
myPoint path[max_memory];
int count=0;
myPoint p1(0,0);

//functions
void draw_point(myPoint P) {
   glColor3f(1, 0, 0);
   glPointSize(10);
   glBegin(GL_POINTS);
   glVertex2f(P.x,P.y);
   glEnd();
}

void Timer(int value) {
   glutPostRedisplay();    // Post a paint request to activate display()
   glutTimerFunc(30, Timer, 0); // subsequent timer call at milliseconds
}

void initGL() {
   glClearColor(1.0f, 1.0f, 1.0f, 0.0f); 
   }

//initial values
int u=5000;
float theta=30.0f;

myPoint cal_path(myPoint p1){
   float rtheta=3.14/180.0 * theta;
   myPoint p2;
   float x=p1.x;
   x=x+1;
   p2.x=x;
   p2.y=x*tan(rtheta)-(g*x*x*0.5f/(u*cos(rtheta)*cos(rtheta)));
   //printf("\n%f\n",p2.y);
   return p2;
};

void f1();
void create_scenery(int value){
    f1();
    glutPostRedisplay();
}

void f1(){
   count++;
   if(count>=max_memory){
       count=0;
   }
   p1=cal_path(p1);
   glutTimerFunc(10,create_scenery,100);
}

void display(){
   printf("\ndisplay is being called %d",count);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluOrtho2D( -300,1000,-500,500);
   glClear(GL_COLOR_BUFFER_BIT);
   
   draw_point(p1);
   
   //path tracing
   int j=0;
   glBegin(GL_LINES);
   for(j=0;j<count;j++){
        glVertex2f(path[j].x,path[j].y);
    }
   glEnd();

   glutSwapBuffers();

   if(p1.y<0){
      p1=myPoint(0,0);
   }
}

int main(int argc, char** argv){
   
   int mode=GLUT_RGB|GLUT_DOUBLE;
   glutInit(&argc, argv);
   glutInitDisplayMode(mode);
   
   glutInitWindowSize(1000, 800);

   glutCreateWindow("Point");
     
   glutTimerFunc(1000,create_scenery,0);
   glutDisplayFunc(display);
   
   initGL();
   glutMainLoop();               
}