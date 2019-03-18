#include <stdio.h>
#include <stdbool.h>
#include <GL/glut.h>

#define outcode int
#define true 1
#define false 0

double xmin = 50, ymin = 50, xmax = 100, ymax = 100;
double xvmin = 200, yvmin = 200, xvmax = 300, yvmax = 300;
float x0[4], y0[4], x1[4], y1[4];

int n;
const int LEFT = 1, RIGHT = 2, BOTTOM = 4, TOP = 8;

outcode compute(double x, double y) { 
    outcode code = 0;
    if(y>ymax) code |= TOP;
    else if(y<ymin) code |= BOTTOM;
    
    if(x>xmax) code |= RIGHT;
    else if(x<xmin) code |= LEFT;
    return code;
}

void cohensutherland(double x0, double y0, double x1, double y1) {
    outcode outcode0, outcode1, outcodeout;
    bool accept = false;
    bool done = false; 
    outcode0 = compute(x0,y0);
    outcode1 = compute(x1,y1);
    do { 
        if(! (outcode0|outcode1) ) { 

            accept = true;
            done = true;
        }
        else if (outcode0&outcode1) { 
            done = true;
        }
        else { 
            double x,y;
            outcodeout = outcode0 ? outcode0 : outcode1;
            double m = (y1-y0)/(x1-x0);
            if(outcodeout & TOP) { 
                x = x0 + (ymax - y0)/m;
                y = ymax;
            }
            else if (outcodeout & BOTTOM) { 
                x = x0 + (ymin - y0)/m;
                y = ymin;       
            }
            else if (outcodeout & RIGHT) { 
                y = y0 + m*(xmax-x0);
                x = xmax;
            }
            else { 
                y = y0 + m*(xmin-x0);
                x = xmin;
            }
            if(outcodeout==outcode0) { 
                x0 = x;
                y0 = y;
                outcode0 = compute(x0,y0);
            }
            else { 
                x1 = x;
                y1 = y;
                outcode1 = compute(x1,y1);
            }
        }
    } while (!done);
    if(accept) { 
        double sx = (xvmax - xvmin)/(xmax - xmin);
        double sy = (yvmax - yvmin)/(ymax - ymin);
        double vx0 = xvmin+ (x0-xmin)*sx;
        double vy0 = yvmin+ (y0-ymin)*sy;
        double vx1 = xvmin+ (x1-xmin)*sx;
        double vy1 = yvmin+ (y1-ymin)*sy;
        glColor3f(0,1,0);
        glBegin(GL_LINE_LOOP);
        glVertex2f(xvmin,yvmin);
        glVertex2f(xvmax,yvmin);
        glVertex2f(xvmax,yvmax);
        glVertex2f(xvmin,yvmax);
        glEnd();
        glColor3f(0,1,1);
        glBegin(GL_LINES);
        glVertex2d(vx0,vy0);
        glVertex2d(vx1,vy1);
        glEnd();
    }
}

void display() { 
    glClear(GL_COLOR_BUFFER_BIT);
    for (int k=0; k<n; k++) { 
        glColor3f(1,1,0);
        glBegin(GL_LINES);
        glVertex2d(x0[k],y0[k]);
        glVertex2d(x1[k],y1[k]);
        glEnd(); 
    }

    glColor3f(1,0,1);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin,ymin);
    glVertex2f(xmax,ymin);
    glVertex2f(xmax,ymax);
    glVertex2f(xmin,ymax);
    glEnd();
    for( int j=0; j<n; j++) { 
        cohensutherland(x0[j],y0[j],x1[j],y1[j]);
        glFlush();
    }
}


void init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char * argv[]) {
    printf("Number of lines : ");
    scanf("%d", &n);
    printf("Enter x0 y0 x1 y1 for each: \n");
    for (int i=0; i<n; i++) { 
        scanf("%f%f%f%f", &x0[i],&y0[i],&x1[i],&y1[i]);
    }
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    //glutInitWindowPosition(0,0);
    glutCreateWindow("Cohen-Sutherland Line Clipping Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
}
