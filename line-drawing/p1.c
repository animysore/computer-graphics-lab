#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

int X1, X2, Y1, Y2;

void init() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0,0.0,0.0,1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,350,0,350);
}
void drawPixel(int x, int y){
    glPointSize(2);
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
    //sleep(1);
    glFlush();

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

void drawLine(int x1, int x2, int y1, int y2) {
    int dy, dx, incx, incy, inc1, inc2, i,x, y, e;
    dy = fabs(y2 - y1);
    printf("%d %d %d", y2, y1, dy);
    dx = fabs(x2 - x1);
    incx = (x2 < x1)? -1: 1; // L2R scanning
    incy = (y2 < y1)? -1: 1; // L2R scanning
    x = x1;
    y = y1;
    if (dx > dy) { //slope < 1
        drawPixel(x,y);
        e = 2*dy - dx;
        inc1 = 2*(dy-dx);
        inc2 = 2*dy;
        for(i=0; i<dx; i++) {
            if (e>=0) {
                y += incy;
                e += inc1;
            }
            else e += inc2;
            x += incx;
            drawPixel(x,y);
        }
    } else {
        drawPixel(x,y);
        e = 2*dx - dy;
        inc1 = 2*(dx-dy);
        inc2 = 2*dx;
        for (i=0; i<dy; i++) {
            if(e>=0) {
                x += incx;
                e += inc1;
            }
            else e += inc2;
            y += incy;
            drawPixel(x,y);
        }
    }
}
void display() {
    credentials(135,320,1.0,1.0,1.0,GLUT_BITMAP_HELVETICA_12,"-ve slope > 1");
    credentials(130,300,1.0,1.0,1.0,GLUT_BITMAP_HELVETICA_10,"(25,100) (75,25)");
    credentials(250,20,1.0,1.0,1.0,GLUT_BITMAP_HELVETICA_10,"Aniruddha Mysore");
    drawLine(X1,X2,Y1,Y2);

}
int main(int argc, char * argv[]) {
    printf("Enter x1, y1, x2, y2\n");
    scanf("%d%d%d%d",&X1,&Y1,&X2,&Y2);
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(350,350);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Line Drawing");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
}
