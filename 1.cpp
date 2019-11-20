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
myPoint p1(-200,-300);
myPoint p2(-200,-300);

//functions
void draw_line(){
   glColor3f(0, 0, 1);
   glLineWidth(5);
   glBegin(GL_LINES);
   glVertex2f(-300,-300);
   glVertex2f(1000,-300);
   glEnd();
}
void draw_point(myPoint P,int i) {
   if(i==1)
    glColor3f(1, 0, 0);
   else glColor3f(0,1, 0);
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
float u=2000;

float theta=30.0f;

myPoint cal_path(myPoint p1,float u){
   float rtheta=3.14/180.0 * theta;
   myPoint p3;
   float x=p1.x;
   x=x+1;
   p3.x=x;
   p3.y=x*tan(rtheta)-(g*x*x*0.5f/(u*cos(rtheta)*cos(rtheta)));
   
   return p3;
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
   p1=cal_path(p1,u);
   p2=cal_path(p2,u+5102);
   glutTimerFunc(10,create_scenery,100);
}

void display(){
//   printf("\ndisplay is being called %d",count);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluOrtho2D( -300,1000,-500,500);
   glClear(GL_COLOR_BUFFER_BIT);
   
   draw_point(p1,1);
   draw_point(p2,0);
   
   draw_line();

   //path tracing
   int j=0;
   glBegin(GL_LINES);
   for(j=0;j<count;j++){
        glVertex2f(path[j].x,path[j].y);
    }
   glEnd();

   glutSwapBuffers();

   if(p1.y<-300){
      p1=myPoint(-200,-300);
   }

   if(p2.y<-300){
      p2=myPoint(-200,-300);
   }
}

int main(int argc, char** argv){
   
   int mode=GLUT_RGB|GLUT_DOUBLE;
   glutInit(&argc, argv);
   glutInitDisplayMode(mode);
   
   glutInitWindowSize(1000, 800);

   glutCreateWindow("Point");
     
   glutDisplayFunc(display);
   glutTimerFunc(1000,create_scenery,0);
   
   initGL();
   glutMainLoop();               
}