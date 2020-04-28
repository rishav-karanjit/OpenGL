#include <windows.h>
#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//float xmin=-30,xmax=30,ymin=-30,ymax=30,p1x,p1y,p2x,p2y;
float xmin,xmax,ymin,ymax,p1x,p1y,p2x,p2y;
float input(char *str){
    float f;
    printf("Enter %s",str);
    scanf("%f",&f);
    return f;
}

void takeinput(){
    int i;
    xmin=input("xmin:");
    xmax=input("xmax:");
    ymin=input("ymin:");
    ymax=input("ymax:");
    p1x=input("point1:x ");
    p1y=input("point1:y ");
    p2x=input("point2:x ");
    p2y=input("point2:y ");
    printf("----------------------------------------------------------------\n");
    return;
}
void outcodesdisplay(int x,int y,char *c){
    int i;
    glRasterPos2d(x,y);
    int length=strlen(c);
    for(i=0;i<length;i++)
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13,c[i]);
}

void outcodes(int* b,int x,int y){
    //b0
    if(y>ymax)
        b[0]=1;
    else
        b[0]=0;
    //b1
    if(y<ymin)
        b[1]=1;
    else
        b[1]=0;
    //b2
    if(x>xmax)
        b[2]=1;
    else
        b[2]=0;
    //b3
    if(x<xmin)
        b[3]=1;
    else
        b[3]=0;
}
int checkzero(int* a){
    int i;
    for(i=0;i<4;i++)
        if(a[i]!=0)
            return 1;
    return 0;
}
int bitwiseout(int* a1,int* a2){
    int i;
    for(i=0;i<4;i++)
        if(a1[i] * a2[i])
            return 1;
    return 0;
}
int cases4(int* o1,int* o2){
    int z1=checkzero(o1);
    int z2=checkzero(o2);

    //case1
    if(z1==0 && z2==0)
        return 1;

    //case2
    if( (z1!=0 && z2==0)||(z1==0 && z2!=0) )
        return 2;

    if(bitwiseout(o1,o2))
        return 3;
    else
        return 4;
}

void init()
{
    glClearColor(1.0,1.0,1.0,1.0);
    gluOrtho2D(-50.0,50.0,-50.0,50.0);
}
void display()
{
    int b1[4],b2[4];
    glClear(GL_COLOR_BUFFER_BIT);
    printf("Step1:\tExtend the sides of window to infinity\n\tBreak the window to 9 regions");
    glColor3d(0,0,0);
    glBegin(GL_LINES);
        glVertex2f(-50,ymax);
        glVertex2f(50,ymax);

        glVertex2f(-50,ymin);
        glVertex2f(50,ymin);

        glVertex2f(xmin,-50);
        glVertex2f(xmin,50);

        glVertex2f(xmax,-50);
        glVertex2f(xmax,50);
    glEnd();
    glFlush();
    Sleep(1000);

    printf("\n\nStep2:\tAssign each region with a unique 4bit binary number\n\tCheck the rules for assigning");
    //center
    outcodesdisplay((xmin+xmax)/2,ymin+10,"0000");
    outcodesdisplay(xmin-10,ymin+10 ,"0001");
    outcodesdisplay(xmax+10,ymin+10 ,"0010");
    //top
    outcodesdisplay((xmin+xmax)/2,ymax+10 ,"1000");
    outcodesdisplay(xmin-10,ymax+10 ,"1001");
    outcodesdisplay(xmax+10,ymax+10 ,"1010");
    //bottom
    outcodesdisplay((xmin+xmax)/2,ymin-10,"0100");
    outcodesdisplay(xmin-10,ymin-10 ,"0101");
    outcodesdisplay(xmax+10,ymin-10 ,"0110");
    glFlush();
    Sleep(1000);

    printf("\n\nStep3:\tFor each end points compute its outcode");
    glPointSize(8);
    glBegin(GL_POINTS);
        glVertex2f(p1x,p1y);

        glVertex2f(p2x,p2y);
    glEnd();

    glBegin(GL_LINES);
        glVertex2f(p1x,p1y);

        glVertex2f(p2x,p2y);
    glEnd();

    outcodes(b1,p1x,p1y);
    outcodes(b2,p2x,p2y);
    glFlush();
    Sleep(1000);

    printf("\n\nStep4:\tWe select which end points falls inside and which endpoints falls outside using 4cases");
    printf("\n\tcase1:\to1=o2=0 both points falls in the clipping window\n");
    printf("\tcase2:\to1!=0 or o2=0 or vice versa one point fall inside the window and another outside\n");
    printf("\tcase3:\to1&o2!=0 both points and outside in the window\n");
    printf("\tcase4:\to1&o2=0 both points outside in the window\n");

    int c=cases4(b1,b2);
    printf("\n\n\tGiven points falls under Case:%d\n",c);
    glFlush();
}

int main(int argc, char *argv[])
{
    takeinput();
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
    glutInitWindowSize(1000,680);
    glutInitWindowPosition(380,000);
    glutCreateWindow("Cohen Sutherland Line Clipping Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
