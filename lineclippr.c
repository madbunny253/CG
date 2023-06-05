#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#include <unistd.h>
float xa,ya,xb,yb;
float m;
float orgxa,orgya,orgxb,orgyb;
float xmin,ymin,xmax,ymax;
int outcode1[4],outcode2[4];
int cnt1,cnt2;

int Round(float a)
{
      return (int)(a+0.5);
}
     
void ddaline(float xa,float ya,float xb,float yb)
{
        int dx,dy,steps;
        dx = xb-xa;
        dy = yb-ya;
        if(abs(dx)>abs(dy))
        {
        	steps = abs(dx);
        }
        else
        {
         	steps = abs(dy);
        }


     	float xincrement , yincrement;
     	xincrement = dx/(float)(steps);
     	yincrement = dy/(float)(steps);
     	float x = xa;
     	float y = ya;

       glVertex2d(Round(x),Round(y));

      for(int k = 0; k<steps; k++)
     {
	      x=x+xincrement;
	      y=y+yincrement;
	      glVertex2d(Round(x),Round(y));
     }
}

void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(3.0);
	glBegin(GL_POINTS);
	ddaline(xmin,ymin,xmax,ymin);
 	ddaline(xmax,ymin,xmax,ymax);
 	ddaline(xmax,ymax,xmin,ymax);
 	ddaline(xmin,ymax,xmin,ymin);
 	glColor3f(1,0,0);
 	ddaline(orgxa,orgya,orgxb,orgyb);
 	glEnd();
	glFlush();
 	
 	sleep(5.0);
 	
 	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(3.0);
	glBegin(GL_POINTS);
	glColor3f(0,1,0);
	ddaline(xa,ya,xb,yb);
	glEnd();
	glFlush();
}

int main(int argc, char **argv)
{
	
	xmax=400;
	ymax=400;
	xmin=100;
	ymin=100;
	
	printf("Enter start point x and y: \n");
	scanf("%f %f",&orgxa,&orgya);
	printf("Enter end point x and y: \n");
	scanf("%f %f",&orgxb,&orgyb);
	
	for(int i=0;i<4;i++)
	{
		outcode1[i]=0;
		outcode2[i]=0;
	}
	if(orgya>ymax)
		outcode1[0]=1;
	if(orgya<ymin)
		outcode1[1]=1;
	if(orgxa>xmax)
		outcode1[2]=1;
	if(orgxa<xmin)
		outcode1[3]=1;
		
	if(orgyb>ymax)
		outcode2[0]=1;
	if(orgyb<ymin)
		outcode2[1]=1;
	if(orgxb>xmax)
		outcode2[2]=1;
	if(orgxb<xmin)
		outcode2[3]=1;
	printf("Outcodes are: \n");
	for(int i=0;i<4;i++)
	{
		printf("\n%d\t%d", outcode1[i], outcode2[i]);
		printf("\n");
	}
	
	cnt1=0;
	for(int j=0;j<4;j++)
	{
		if(outcode1[j]==0 && outcode2[j]==0)
			cnt1=cnt1+1;
	}
	if(cnt1==4)
	{
		printf("Line Accepted !");
	}
	else
	{
		cnt2=0;
		for(int j=0;j<4;j++)
		{
			if((outcode1[j] && outcode2[j])==0)
				cnt2=cnt2+1;
		}
		if(cnt2==4)
		{
			printf("Line Partially Accepted !");
			m=(orgyb-orgya)/(orgxb-orgxa);
			
			if(outcode1[0]==1)
			{
				ya=ymax;
				xa=orgxa+(ya-orgya)/m;
			}
			else if(outcode1[1]==1)
			{
				ya=ymin;
				xa=orgxa+(ya-orgya)/m;
			}
			else if(outcode1[2]==1)
			{
				xa=xmax;
				ya=orgya+(xa-orgxa)*m;
			}
			else if(outcode1[3]==1)
			{
				xa=xmin;
				ya=orgya+(xa-orgxa)*m;
			}
			else
			{
				xa=orgxa;
				ya=orgya;
			}
			
			if(outcode2[0]==1)
			{
				yb=ymax;
				xb=orgxb+(yb-orgyb)/m;
			}
			else if(outcode2[1]==1)
			{
				yb=ymin;
				xb=orgxb+(yb-orgyb)/m;
			}
			else if(outcode2[2]==1)
			{
				xb=xmax;
				yb=orgyb+(xb-orgxb)*m;
			}
			else if(outcode2[3]==1)
			{
				xb=xmin;
				yb=orgyb+(xb-orgxb)*m;
			}
			else
			{
				xb=orgxb;
				yb=orgyb;
			}
		}
		else
			printf("Line Rejected !");
	}
	 glutInit(&argc,argv);
	 glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	 glutInitWindowPosition(0,0);
	 glutInitWindowSize(640,480);
	 glutCreateWindow("Window");
	 glClearColor(1.0,1.0,1.0,0);
	 glColor3f(0,0,0);
	 gluOrtho2D(0,640,0,480);
	 glutDisplayFunc(Draw);
	 glutMainLoop();
	 return 0;
}
