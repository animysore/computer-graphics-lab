#include <stdio.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>

int choice =0;

void edgeDetect(float x1, float y1, float x2, float y2, int *ll , int *rl) { 
    float mx, x, temp;
    if ((y2-y1)<0){ 
        temp = y1;
        y1 = y2;
        y2 = temp; 
        temp = x1; 
        x1 = x2;
        x2 = temp;
    }
    if ((y2-y1)!=0) mx = (x2-x1)/(y2-y1);
    else mx = x2 - x1;
    x = x1;
    for (int i=y1; i<=y2; i++){ 
        if(x < ll[i] ) ll[i] = (int) x;
        if(x > rl[i]) rl[i] = (int) x;
        x+=mx;
    }
}

void drawPixel(int x, int y) { 
    glColor3f(1,1,0);
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
    glFlush();
}


void scanfile(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4){
    int ll[500], rl[500];
    for(int i=0; i<500; i++) { 
        ll[i] = 500;
        rl[i] = 0;
    }
    edgeDetect(x1,y1,x2,y2,ll,rl);
    edgeDetect(x2,y2,x3,y3,ll,rl);
    edgeDetect(x3,y3,x4,y4,ll,rl);
    edgeDetect(x4,y4,x1,y1,ll,rl);
    for (int j=0; j<500; j++){ 
        if(ll[j] <= rl[j])
            for(int i =(int)ll[j]; i<=(int)rl[j]; i++)
                drawPixel(i,j);
    }
}

void credentials(float x, float y, float r, float g, float b, void* font, char *string)
{
  glColor3f( r, g, b );
  glRasterPos2f(x, y);
  int len, i;
  len = (int)strlen(string);
  for (i = 0; i < len; i++) {
    glutBitmapCharacter(font, string[i]);
  }
}

void display() { 
    float x1=200, y1=200, x2=100, y2=300, x3=200, y3=400, x4=300, y4=400;
    glClear(GL_COLOR_BUFFER_BIT);
    credentials(380,20,1,1,1,GLUT_BITMAP_HELVETICA_12, "Aniruddha Mysore");
    glColor3f(1,1,0);
    if(choice == 1) {
        glBegin(GL_LINE_LOOP);
        glVertex2f(x1,y1);
        glVertex2f(x2,y2);
        glVertex2f(x3,y3);
        glVertex2f(x4,y4);
        glEnd();
    }
    if (choice >= 2) { 
        printf("filling\n");
        scanfile(x1,x2,x2,y2,x3,y3,x4,y4);
    } 
    glFlush();
}

void myinit ()  { 
   glClearColor(0,0,0,1);
   glColor3f(1,0,0);
   glPointSize(1);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0,500,0,500); 
}

void mymenu(int id) { 
    glClear(GL_COLOR_BUFFER_BIT);
    switch(id) { 
        case 1: exit(0);
        case 2: choice = 1; break;
        case 3: choice = 2; break;
    }
    glutPostRedisplay();
}


int main(int argc, char * argv[]) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutCreateWindow("Scanlines");
    glutDisplayFunc(display);
    glutCreateMenu(mymenu);
    glutAddMenuEntry("Exit",1);
    glutAddMenuEntry("Draw Polygon", 2);
    glutAddMenuEntry("Fill Polygon", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    myinit();   
    glutMainLoop();
}
