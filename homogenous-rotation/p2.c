#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

GLfloat input[3][3] = {
    {100.0,175.0,250.0},
    {100.0,250.0,100.0},
    {1,1,1}
}, res[3][3], m[3][3];

GLfloat xf, yf, theta;

void init() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0,0.0,0.0,1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,500,0,500);
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
void drawTriangle(GLfloat coords[3][3], int color) {
    glBegin(GL_TRIANGLES);
    //glIndexd(color);
    (color)?glColor3f(0.0,1.0,1.0):glColor3f(1.0,0.0,1.0);
    for (int i=0; i<3; i++){
        glVertex2f(coords[0][i],coords[1][i]);
    }
    glEnd();

}

void calculateRotation() {
    m[0][0] = cos(theta);
    m[0][1] = -sin(theta);
    m[0][2] = xf * (1-cos(theta)) + yf*sin(theta);
    m[1][0] = sin(theta);
    m[1][1] = cos(theta);
    m[1][2] = yf * (1-cos(theta)) - xf *sin(theta);
    m[2][0] = 0;
    m[2][1] = 0;
    m[2][2] = 1;
}

void transform() {
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            res[i][j] = 0;
            for (int k=0; k<3; k++) {
                res[i][j] += m[i][k] * input[k][j];
            }
        }
    }
}

void display() {
    drawTriangle(input,0);
    calculateRotation();
    transform();
    drawTriangle(res,1);
    credentials(135,420,1.0,1.0,1.0,GLUT_BITMAP_HELVETICA_12,"Rotating Triangle about a fixed internal point");
    credentials(200,400,1.0,1.0,1.0,GLUT_BITMAP_HELVETICA_10,"point: (100, 100) | deg: 30");
    //credentials(135,420,1.0,1.0,1.0,GLUT_BITMAP_HELVETICA_12,"Rotating Triangle about origin");
    //credentials(200,400,1.0,1.0,1.0,GLUT_BITMAP_HELVETICA_10,"point: (0, 0) | deg: 15");

    credentials(400,20,1.0,1.0,1.0,GLUT_BITMAP_HELVETICA_10,"Aniruddha Mysore");
    glFlush();
}

int main(int argc, char * argv[]) {
    printf("Enter  xf yf theta\n");
    scanf("%f %f %f", &xf,&yf,&theta);
    theta = theta * 3.14/180;
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Rotation");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
}
