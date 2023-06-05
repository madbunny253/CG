#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

int px1,py1,px2,py2,it;

int Round(float a)
{
    return (int)(a+0.5);
}

void ddaline(int xa, int ya, int xb, int yb)
{
	int dx, dy, steps;
	
	dx = xb - xa;
	dy = yb - ya;
	
	if(abs(dx) > abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);
		
	float xinc, yinc;
	xinc = dx/(float)(steps);
	yinc = dy/(float)(steps);
	
	float x=xa;
	float y=ya;
	
	glVertex2d(Round(x), Round(y));
	
	for(int i=0; i<steps; i++)
	{
		x = x + xinc;
		y = y + yinc;
		glVertex2d(Round(x), Round(y));
	}
}

void koch(int xa, int ya, int xb, int yb, int itr)
{
	int x2 = (2*xa+xb)/3;
	int y2 = (2*ya+yb)/3;
	int x3 = (xa+2*xb)/3;
	int y3 = (ya+2*yb)/3;
	float ang=1.0472;
	
	int x=x2+(x3-x2)*cos(ang) + (y3-y2)*sin(ang);
	int y=y2-(x3-x2)*sin(ang) + (y3-y2)*cos(ang);
	
	if(itr>0)
	{
		koch(xa,ya,x2,y2,itr-1);
		koch(x2,y2,x,y,itr-1);
		koch(x,y,x3,y3,itr-1);
		koch(x3,y3,xb,yb,itr-1);
	}
	else
	{
		ddaline(xa,ya,x2,y2);
		ddaline(x2,y2,x,y);
		ddaline(x,y,x3,y3);
		ddaline(x3,y3,xb,yb);
	}
}

void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	koch(px1,py1,px2,py2,it);
	glEnd();
	glFlush();
}

int main(int argc, char**argv)
{
	printf("Enter starting point: ");
	scanf("%d%d",&px1,&py1);
	printf("Enter end point: ");
	scanf("%d%d",&px2,&py2);
	printf("Enter no. of iterations: ");
	scanf("%d",&it);
	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(640,480);
	
	glutCreateWindow("WINDOW");
	
	glClearColor(1,1,1,0);
	glColor3f(0,0,0);
	
	gluOrtho2D(0,640,0,480);
	
	glutDisplayFunc(Draw);
	glutMainLoop();
}
