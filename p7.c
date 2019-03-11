#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <GL/glut.h>

GLfloat v[4][3] = {{0,0,1},{0,0.942809,-0.33333},{-0.8196497,-0.47145,-0.33333},{0.8196497,-0.47145,-0.33333}};
int N;

void triangle(GLfloat* a, GLfloat* b, GLfloat* c) {
    glBegin(GL_POLYGON);
    glVertex3fv(a);
    glVertex3fv(b);
    glVertex3fv(c);
    glEnd();
}

void divide_triangle(GLfloat* a, GLfloat* b, GLfloat* c,  int n) {
    GLfloat v1[3], v2[3], v3[3];
    int j;
    if(n>0) {
        for(j=0; j<3; j++) v1[j] = (a[j]+b[j])/2;
        for(j=0; j<3; j++) v2[j] = (a[j]+c[j])/2;
        for(j=0; j<3; j++) v3[j] = (b[j]+c[j])/2;
        divide_triangle(a,v1,v2,n-1);
        divide_triangle(c,v2,v3,n-1);
        divide_triangle(b,v3,v1,n-1);
    }

    else triangle(a,b,c);
}

void tetrahedron(int N) {
    glColor3f(1.0, 0.0, 0.0);
    divide_triangle(v[0],v[1],v[2],N);
    glColor3f(0.0, 1.0, 0.0);
    divide_triangle(v[3],v[2],v[1],N);
    glColor3f(0.0, 0.0, 1.0);
    divide_triangle(v[0],v[3],v[1],N);
    glColor3f(0.0, 0.0, 0.0);
    divide_triangle(v[0],v[2],v[3],N);
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

void Display() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    tetrahedron(N);
    credentials(-0.3,1.8,0.0,0.0,0.0,GLUT_BITMAP_HELVETICA_18,"Progam 7 ");
    credentials(-0.4,1.66,0.0,0.0,0.0,GLUT_BITMAP_HELVETICA_12,"Sierpinski Gasket");
    credentials(1,-1.8,0.0,0.0,0.0,GLUT_BITMAP_HELVETICA_12,"Aniruddha Mysore");
    glFlush();
    /*int i = 100;
    while(1) {
        //i = (i+10)%360 ;
        glRotated(i,100,100,100);
        glFlush();
    }*/

}

void myinit() {
    glOrtho(-2.0, 2.0,-2.0, 2.0, -10.0, 10.0);
    glClearColor(1.0,1.0,1.0,1.0);
}

int run(int argc, char * argv[])
{
    printf("Enter number of divisions: ");
    scanf("%d",&N);
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutCreateWindow("Sierpinski Gasket");
    glutDisplayFunc(Display);
    myinit();
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}
