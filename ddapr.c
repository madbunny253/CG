#include <stdio.h>
#include <GL/glut.h>

int xa,ya,xb,yb;
int linetype;


int Round(float a)
{
	return (int)(a+0.5);
}

void ddaline(int xa, int ya, int xb, int yb, int linetype)
{
	int dx,dy,steps;
	dx=xb-xa;
	dy=yb-ya;
	if(abs(dx)>abs(dy))
		steps=abs(dx);
	else
		steps=abs(dy);
		
	float xin,yin;
	xin=dx/(float)(steps);
	yin=dy/(float)(steps);
	
	float x,y;
	x=xa;
	y=ya;
	
	glBegin(GL_POINTS);
	glVertex2d(Round(x),Round(y));
	
	for(int k=0; k<steps; k++)
	{
		if(linetype==4)
		{
			glPointSize(3.0);
			glBegin(GL_POINTS);
			x=x+xin;
			y=y+yin;
			glVertex2d(Round(x),Round(y));
			glEnd();
		}
		if(linetype==3)
		{
			x=x+xin;
			y=y+yin;
			if(k%4!=0)
				glVertex2d(Round(x),Round(y));
		}
		else if(linetype==2)
		{
			x=x+xin;
			y=y+yin;
			if(k%4==0)
				glVertex2d(Round(x),Round(y));
		}
		else
		{
			x=x+xin;
			y=y+yin;
			glVertex2d(Round(x),Round(y));
		}
	}
	glEnd();
	glFlush();
}

void mouse1(int button, int state, int x, int y)
{
	y=480-y;
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		xa=x;
		ya=y;
	}
	if(button==GLUT_LEFT_BUTTON && state==GLUT_UP)
	{
		xb=x;
		yb=y;
		glColor3f(1.0,0.0,0.0);
		ddaline(xa,ya,xb,yb,linetype);
	}
	
}

void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	ddaline(0,240,640,240,1); //xaxis
	ddaline(320,0,320,480,1); //yaxis
}

int main(int argc, char **argv)
{
	printf("Enter type of line to be drawn: 1.Simple 2.Dotted 3.Dashed 4.Solid >> ");
	scanf("%d", &linetype);
	printf("Drag A line across screen to plot it !");
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(640,480);
	
	glutCreateWindow("Window");
	
	glClearColor(0.0,0.0,0.0,0.0);
	glColor3f(1.0,0.0,0.0);
	
	gluOrtho2D(0,640,0,480);
	
	glutDisplayFunc(Draw);
	glutMouseFunc(mouse1);
	glutMainLoop();
	
	return 0;
}
