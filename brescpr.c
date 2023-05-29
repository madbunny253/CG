#include <stdio.h>
#include <GL/glut.h>

int xc,yc,r;

int Round(float a)
{
	return (int)(a+0.5);
}

void brescircle(int xc, int yc, int r)
{
	int x,y,d;
	x=0;
	y=r;
	d=3-2*r;
	
	do
	{
		glVertex2d(x+yc,y+xc);
		glVertex2d(y+xc,x+yc);
		glVertex2d(x+yc,-y+xc);
		glVertex2d(y+xc,-x+yc);
		glVertex2d(-x+yc,-y+xc);
		glVertex2d(-y+xc,-x+yc);
		glVertex2d(-x+yc,y+xc);
		glVertex2d(-y+xc,x+yc);
		
		if(d<0)
		{
			x=x+1;
			d=d+4*x+6;
		}
		else
		{
			x=x+1;
			y=y-1;
			d=d+4*x-4*y+10;
		}
	}
	while(y>=x);
}

int ddaline(int xa, int ya, int xb, int yb)
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
	
	glVertex2d(Round(x),Round(y));
	
	for(int i=0;i<steps;i++)
	{
		x=x+xin;
		y=y+yin;
		glVertex2d(Round(x),Round(y));
	}
}

void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	//glVertex2d(100,100);
	ddaline(320,0,320,480);
	ddaline(0,240,640,240);
	
	brescircle(xc,yc,r);
	glEnd();
	glFlush();
}

void mouse1(int button, int state, int x, int y)
{
	y=y-480;
	if(button==GLUT_LEFT_BUTTON)
	{
		if(state==GLUT_DOWN)
			brescircle(xc,yc,r);
	}
}

int main(int argc, char **argv)
{
	printf("Enter radius: ");
	scanf("%d",&r);
	printf("Enter the coordinates of center: ");
	scanf("%d%d",&xc,&yc);
	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(0,0);
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
