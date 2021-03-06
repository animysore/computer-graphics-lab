#include <stdio.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>

GLfloat vertices[][3] = {
    {-1,-1,1},
    {-1,1,1},
    {1,1,1},
    {1,-1,1},
    {-1,-1,-1},
    {-1,1,-1},
    {1,1,-1},
    {1,-1,-1}
};
GLfloat colors[][3] = {
{0,0,0}, {0,0,1},{0,1,0},{0,1,1},{1,0,0},{1,0,1},{1,1,0},{1,1,1}
};

void polygon(int a, int b, int c,int d){
    glBegin(GL_POLYGON);
    glColor3fv(colors[a]);
    glVertex3fv(vertices[a]);
    glColor3fv(colors[b]);
    glVertex3fv(vertices[b]);
    glColor3fv(colors[c]);
    glVertex3fv(vertices[c]);
    glColor3fv(colors[d]);
    glVertex3fv(vertices[d]);
    glEnd();
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
void colorcube() {
    polygon(0,3,2,1);
    polygon(2,3,7,6);
    polygon(0,4,7,3);
    polygon(1,2,6,5);
    polygon(4,5,6,7);
    polygon(0,1,5,4);
}

static GLfloat theta[] = {0,0,0};
static GLuint axis = 2;


void disp() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glRotatef(theta[0],1,0,0);
    glRotatef(theta[1],0,1,0);
    glRotatef(theta[2],0,0,1);
    colorcube();
    //credentials(1,1,1.0,1.0,1.0,GLUT_BITMAP_HELVETICA_12,"Rotating Cube about a fixed internal point");
    glFlush();
    glutSwapBuffers();
}
void spincube() {
    theta[axis] += 0.01;
    if(theta[axis]>360.0)
        theta[axis] -= 360;
    glutPostRedisplay();
}
void mouse(int btn, int state, int x, int y){
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN) axis =0;
    if(btn==GLUT_MIDDLE_BUTTON && state==GLUT_DOWN) axis =1;
    if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN) axis =2;
}
void myReshape(int w, int h) {
    //GLfloat w = W, h = H;
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(w<=h) glOrtho(-2,2,-2*(GLfloat)h/(GLfloat)w, 2*(GLfloat)h/(GLfloat)w, -10,10);
    else glOrtho(-2*(GLfloat)w/(GLfloat)h,2*(GLfloat)w/(GLfloat)h,-2, 2, -10,10);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char * argv[]) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(500,500);
    //glutInitWindowPosition(0,0);
    glutCreateWindow("Rotating a cube");
    glutReshapeFunc(myReshape);
    glutDisplayFunc(disp);
    glutIdleFunc(spincube);
    glutMouseFunc(mouse);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
}
