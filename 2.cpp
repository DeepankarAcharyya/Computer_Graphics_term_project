#include <GL/glut.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>

int count=0;

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

myPoint p1(250,40);//earth
myPoint p2(325,60);//moon
myPoint origin;///sun/x=0, y=0

const int maxMemory=10000;
myPoint path[maxMemory];

// myPoint myTranslate(myPoint p, float dx,float dy){
//     myPoint p2;
//     p2.x=p.x+dx;
//     p2.y=p.y+dy;

//     return p2;
// }

// myPoint myScale(myPoint p, float dx,float dy){
//     myPoint p2;
//     p2.x=p.x*dx;
//     p2.y=p.y*dy;
//     return p2;
// }

myPoint myRotate(myPoint p, float theta){
    float rtheta=3.14/180.0 * theta;
    myPoint p2;
    p2.x=p.x*cos(rtheta)-p.y*sin(rtheta);
    p2.y=p.x*sin(rtheta)+p.y*cos(rtheta);
    return p2;
}

// myPoint myRotateWRTArbitraryPoint(myPoint p,myPoint rp, float theta){
//     myPoint p2;
//     p2=myTranslate(p,-rp.x,-rp.y);
//     p2=myRotate(p2,theta);
//     p2=myTranslate(p2,rp.x,rp.y);
//     return p2;
// }

void display(){
  printf("\ndisplay is being called %d",count);  //to create the world window of user size.

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluOrtho2D(-500,500,-500,500);//size of world wiondow xmin,xmax,ymin,ymax.
  glClearColor(1,1,1,0);//background color is white as rgb all r set to 1.
  glClear(GL_COLOR_BUFFER_BIT);//applies the background color.
  glColor4f(1, 0, 0, 1);//color of the object u want to draw.
  glPointSize(10);//size of point.
  
//   glBegin(GL_POINTS);
//       glVertex2f(origin.x,origin.y);
//   glEnd();

 int i=0;
 glBegin(GL_POINTS);
   glVertex2f(p1.x,p1.y);
 glEnd();

// glBegin(GL_POINTS);
//   glVertex2f(p2.x,p2.y);
// glEnd();

// glBegin(GL_LINES);
//       glVertex2f(origin.x,origin.y);
//       glVertex2f(p1.x,p1.y);
//       glVertex2f(p1.x,p1.y);
//       glVertex2f(p2.x,p2.y);
// glEnd();
// int j=0;
// glBegin(GL_LINES);
//     for(j=0;j<count;j++){
//         glVertex2f(path[j].x,path[j].y);
//     }
// glEnd();
glutSwapBuffers();
}

void createScene(int x);

void f1(){
count++;
if(count>=maxMemory){
    count=0;
}
//path[count]=p2;
//myPoint prevEarth=p1;
p1=myRotate(p1,4);
// p2=myRotateWRTArbitraryPoint(p2,prevEarth,-4);
// p2=myTranslate(p2,-1*prevEarth.x,-1*prevEarth.y);
// p2=myTranslate(p2,p1.x,p1.y);
glutTimerFunc(10,createScene,100);
}

void createScene(int x){
    f1();
    glutPostRedisplay();
}

int main(int argc, char **argv){
    int mode=GLUT_RGB|GLUT_DOUBLE;
    glutInit(&argc, argv);
    glutInitDisplayMode(mode);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Computer");

    glutTimerFunc(10,createScene,100);
    glutDisplayFunc(display);
    
    glutMainLoop();
 }