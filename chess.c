#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

int xi,yi;
float boundary[3],fill[3];
int x1,y3,x2,y2,i;

void boundaryf(float boundary[], float fill[], int x, int y)
{
	float color[3];
	glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,color);
	glColor3f(0,0,0);
	if((color[0]!=boundary[0] || color[1]!=boundary[1] || color[2]!=boundary[2]) && (color[0]!=fill[0] || color[1]!=fill[1] || color[2]!=fill[2]))
	{
		glBegin(GL_POINTS);
		glVertex2d(x,y);
		glEnd();
		glFlush();
		boundaryf(boundary,fill,x+2,y);
		boundaryf(boundary,fill,x-2,y);
		boundaryf(boundary,fill,x,y+2);
		boundaryf(boundary,fill,x,y-2);
	}
}

void bresline(int xa, int ya, int xb, int yb)
{
    int d,c,r,f,dx,dy;
    dx = xb-xa;
    dy = yb-ya;
    if(abs(dx)>abs(dy))
    {
        d = 2*abs(dy)-abs(dx);
        if(dx>0)
        {
            c=xa;
            r=ya;
            f=xb;
        }
        else
        {
            c=xb;
            r=yb;
            f=xa;
        }
        glBegin(GL_POINTS);
        glVertex2d(c,r);
        i=0;
        while(f>c)
        {
            if(d<0)
            {
                c = c+1;
                d = d+2*abs(dy);
            }
            else
            {
                c = c+1;
                d = d+2*abs(dy)-2*abs(dx);
                if((dy>0 && dy>0) || (dy<0 && dx<0))
                {
                    r = r+1;
                }
                else
                {
                    r = r-1;
                }
            }

            i++;
            glVertex2d(c,r);
        }
        glEnd();
	    glFlush();
    }
    else
    {
        d = 2*abs(dx)-abs(dy);
        if(dy>0)
        {
            c=xa;
            r=ya;
            f=yb;
        }
        else
        {
            c=xb;
            r=yb;
            f=ya;
        }
        glBegin(GL_POINTS);
        glVertex2d(c,r);
        while(f>r)
        {
            if(d<0)
            {
                r = r+1;
                d = d+2*abs(dx);
            }
            else
            {
                r = r+1;
                d = d+2*abs(dx)-2*abs(dy);
                if((dy>0 && dx>0) || (dy<0 && dx<0))
                {
                    c = c+1;
                }
                else
                {
                    c = c-1;
                }
            }
            i++;
            glVertex2d(c,r);
        }
        glEnd();
	glFlush();      
    }
}

void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(3.0);
	glBegin(GL_POINTS);
	
	bresline(100,100,500,100);
	bresline(500,100,500,500);
	bresline(500,500,100,500);
	bresline(100,500,100,100);
	bresline(100,200,500,200);
	bresline(100,300,500,300);
	bresline(100,400,500,400);
	bresline(200,100,200,500);
	bresline(300,100,300,500);
	bresline(400,100,400,500);
	
	glEnd();
	glFlush();
}

void mouse1(int button, int state, int x, int y)
{
	y=650-y;
	
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		xi=x;
		yi=y;
		boundaryf(boundary,fill,xi,yi);
	}
}

int main(int argc, char **argv)
{   

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(640,640);
	
	glutCreateWindow("Window");
	
	glClearColor(1,1,1,0.0);
	glColor3f(0.0,0.0,0.0);
	
	gluOrtho2D(0,640,0,640);
	
	glutDisplayFunc(Draw);
	glutMouseFunc(mouse1);
	glutMainLoop();
	
	return 0;
}
