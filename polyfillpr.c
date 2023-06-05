#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

int v,inp [2][10],xi,yi,ch;
float boundary[3],fill[3],bg[3];

void getdata()
{
	printf("Enter no. of vertex: ");
	scanf("%d",&v);
	
	for(int i=0;i<v;i++)
	{
		printf("Enter x: ");
		scanf("%d",&inp[0][i]);
		printf("Enter y: ");
		scanf("%d",&inp[1][i]);
	}
	
	printf("Enter background color: ");
	for(int j=0;j<3;j++)
	{
		scanf("%f",&bg[j]);
	}
	
	printf("Enter boundary color: ");
	for(int j=0;j<3;j++)
	{
		scanf("%f",&boundary[j]);
	}
	
	printf("Enter fill color: ");
	for(int j=0;j<3;j++)
	{
		scanf("%f",&fill[j]);
	}
	
	//printf("Enter X of inside point: ");
	//scanf("%d",&xi);
	//printf("Enter Y of inside point: ");
	//scanf("%d",&yi);
}

void display()
{
	for(int a;a<2;a++)
	{
		for(int i=0;i<v;i++)
		{
			printf("%d\t",inp[a][i]);
			
		}
		printf("\n");
	}
	
}

void boundaryf(float boundary[], float fill[], int x, int y)
{
	float color[3];
	glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,color);
	glColor3f(fill[0],fill[1],fill[2]);
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

void floodf(float bg[], float fill[], int x, int y)
{
	float color[3];
	glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,color);
	glColor3f(fill[0],fill[1],fill[2]);
	if((color[0]==bg[0] && color[1]==bg[1] && color[2]==bg[2]) && (color[0]!=fill[0] || color[1]!=fill[1] || color[2]!=fill[2]))
	{
		glBegin(GL_POINTS);
		glVertex2d(x,y);
		glEnd();
		glFlush();
		floodf(bg,fill,x+2,y);
		floodf(bg,fill,x-2,y);
		floodf(bg,fill,x,y+2);
		floodf(bg,fill,x,y-2);
	}
}

int Round(float a)
{
	return (int)(a+0.5);
}

void ddaline(int xa, int ya, int xb, int yb)
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
	glPointSize(3.0);
	glBegin(GL_POINTS);
	int i;
	glColor3f(boundary[0],boundary[1],boundary[2]);
	for(i=0;i<v-1;i++)
	{
		ddaline(inp[0][i],inp[1][i],inp[0][i+1],inp[1][i+1]);
	}
	ddaline(inp[0][0],inp[1][1],inp[0][i],inp[1][i]);
	
	glEnd();
	glFlush();
}

void mouse1(int button, int state, int x, int y)
{
	y=480-y;
	
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		xi=x;
		yi=y;
		if(ch==1)
			boundaryf(boundary,fill,xi,yi);
		else if(ch==2)
			floodf(bg,fill,xi,yi);
	}
}

int main(int argc, char **argv)
{   

	getdata();	
	//display();
	printf("What to do:\n 1.Boundary Fill\n 2.Flood Fill\n ");
	scanf("%d",&ch);
	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(640,480);
	
	glutCreateWindow("Window");
	
	glClearColor(bg[0],bg[1],bg[2],0.0);
	glColor3f(0.0,0.0,0.0);
	
	gluOrtho2D(0,640,0,480);
	
	glutDisplayFunc(Draw);
	glutMouseFunc(mouse1);
	glutMainLoop();
	
	return 0;
}
