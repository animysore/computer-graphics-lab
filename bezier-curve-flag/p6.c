#include <math.h>
#include <GL/glut.h>

#define PI 3.14

int choice = 0;

GLsizei minWidth = 600, minHeight = 600;
GLfloat xwcMin = 0, xwcMax = 130;
GLfloat ywcMin = 0, ywcMax = 130;

typedef struct wcPt3D { 
    GLfloat x,y,z;
} wcPt3D;

// compute binomial coefficient 
void bino (GLint n, GLint *c) { 
    for(int k=0; k<=n; k++) { 
        c[k] = 1;
        for(int j=n; j>=(k+1); j--)
            c[k] *= j;
        for(int j=n-k; j>=2; j--) 
            c[k] /= j;
    }
}

void computeBezPt (GLfloat u, wcPt3D *bezPt, GLint nCtrlPts, wcPt3D *ctrlPts, GLint *C) { 
    GLint k, n=nCtrlPts -1;
    GLfloat bezBlendFnc;
    bezPt->x = bezPt->y = bezPt->z  = 0;
    for ( k=0; k<nCtrlPts; k++) { 
        bezBlendFnc = C[k] * pow(u,k) * pow(1-u,n-k);
        bezPt->x += ctrlPts[k].x * bezBlendFnc;
        bezPt->y += ctrlPts[k].y * bezBlendFnc;
        bezPt->z += ctrlPts[k].z * bezBlendFnc;
    }
}

void bezier(wcPt3D *ctrlPts, GLint nCtrlPts, GLint nBezCurvePts) { 
    wcPt3D bezCurvePt;
    GLfloat u;
    GLint *c;
    c = new GLint [nCtrlPts];
    bino(nCtrlPts-1,c);
    glBegin(GL_LINE_STRIP);
    for (int k=0; k<=nBezCurvePts; k++) { 
        u = GLfloat(k)/GLfloat(nBezCurvePts);
        computeBezPt(u,&bezCurvePt,nCtrlPts,ctrlPts,c);
        glVertex2f(bezCurvePt.x,bezCurvePt.y);
    }
    glEnd();
    delete []c;
}

void displayFunc(){ 
    glClear(GL_COLOR_BUFFER_BIT);
    if(choice==2||choice==3){ 
        GLint nCtrlPts = 4, nBezCurvePts = 20;
        static float theta = 0;
        wcPt3D ctrlPts[4] = { 
            {20,100,0},
            {30,110,0},
            {50,90,0},
            {60,100,0}
        };
        ctrlPts[1].x += 10*sin(theta *PI/180);
        ctrlPts[1].y += 5*sin(theta * PI/180);
        ctrlPts[2].x -= 10*sin((theta+30)*PI/180);
        ctrlPts[2].y -= 10*sin((theta+30)*PI/180);
        ctrlPts[3].x -= 4*sin(theta*PI/180);
        ctrlPts[3].y += sin((theta-30)*PI/180);
        if(choice==3) theta +=1.0;
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1,1,1);
        glPointSize(5);
        glPushMatrix();
        glLineWidth(5);
        glColor3f(255.0/255, 153.0/255, 51.0/255);
        for(int i=0; i<8; i++) { 
            glTranslatef(0,-0.8,0);
            bezier(ctrlPts, nCtrlPts, nBezCurvePts);
        }
        glColor3f(1,1,1);
        for(int i=0; i<8; i++) { 
            glTranslatef(0,-0.8,0);
            bezier(ctrlPts, nCtrlPts, nBezCurvePts);
        }
        glColor3f(19/255.0,136/255.0,2/255.0);
        for (int i=0; i<8; i++) { 
            glTranslatef(0,-0.8,0);
            bezier(ctrlPts, nCtrlPts, nBezCurvePts);
        }
        glPopMatrix();
        glColor3f(0.7,0.5,0.3);
        glLineWidth(5);
        glBegin(GL_LINES);
        glVertex2f(20,100);
        glVertex2f(20,60);
        glEnd();
        glFlush();
    }
    glutPostRedisplay();
    glutSwapBuffers();
}

void demo_menu(int id){
    switch(id) { 
        case 1: exit(0);
        case 2: 
            choice = 2;
            break;
        case 3:
            choice = 3;
    }
    glutPostRedisplay();
}

void winReshapeFunc(GLint newWidth, GLint newHeight) { 
    glViewport(0,0,newWidth,newHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(xwcMin,xwcMax,ywcMin,ywcMax);
    glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char *argv[]) { 
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(minWidth,minHeight);
    glutInitWindowPosition(50,50);
    glutCreateWindow("Flag");
    int submenu = glutCreateMenu(demo_menu);
    glutAddMenuEntry("Draw",2);
    glutAddMenuEntry("Start ", 3);
    glutAddMenuEntry("Stop", 2);
    glutCreateMenu(demo_menu);
    glutAddMenuEntry("Exit",1);
    glutAddSubMenu("Flag",submenu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    choice = 0;
    glClearColor(1,1,1,0);
    glutDisplayFunc(displayFunc);
    glutReshapeFunc(winReshapeFunc);
    glutMainLoop();
}