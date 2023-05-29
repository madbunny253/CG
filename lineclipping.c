#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
float xa , ya ,xb ,yb;
float slope;
float org_xa,org_ya,org_xb,org_yb;
float xmin ,ymin ,xmax,ymax;
int outcode1[4],outcode2[4];

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
 glBegin(GL_POINTS);
 ddaline(xmin,ymin,xmax,ymin);
 ddaline(xmax,ymin,xmax,ymax);
 ddaline(xmax,ymax,xmin,ymax);
 ddaline(xmin,ymax,xmin,ymin);
 ddaline(org_xa,org_ya,org_xb,org_yb);
 
 glColor3f(1,0,0);
 ddaline(xa , ya , xb ,yb);
 
 glEnd();
 glFlush();
}

int main(int argc,char **argv)
{
	printf("Enter the window size :\n");
	printf("Enter the value of Xmin: ");
	scanf("%f",&xmin);
	printf("Enter the value of Ymin: ");
	scanf("%f",&ymin);
	printf("Enter the value of Xmax: ");
	scanf("%f",&xmax);
	printf("Enter the value of Ymax: ");
	scanf("%f",&ymax);
	
	printf("Enter the value of the start point:\n");
	printf("X value :");
	scanf("%f",&org_xa);
	printf("Y value :");
	scanf("%f",&org_ya);
	printf("Enter the value of the end point:\n");
	printf("X value :");
	scanf("%f",&org_xb);
	printf("Y value :");
	scanf("%f",&org_yb);
	
	for (int i=0;i<4;i++)
	{
		outcode1[i]=0;
		outcode2[i]=0;
	}
	
	
	if(org_ya > ymax)
	{
		outcode1[0]=1;	
	}
	
	if(org_ya < ymin)
	{
		outcode1[1]=1;
	}
	
	if(org_xa > xmax)
	{
		outcode1[2]=1;
	}
	
	if(org_xa < xmin)
	{
		outcode1[3]=1;
	}
	
	
	if(org_yb > ymax)
	{
		outcode2[0]=1;	
	}
	
	if(org_yb < ymin)
	{
		outcode2[1]=1;
	}
	
	if(org_xb > xmax)
	{
		outcode2[2]=1;
	}
	
	if(org_xb < xmin)
	{
		outcode2[3]=1;
	}
	
	
	printf("Outcodes are :\n");
	for(int i=0 ; i<4 ; i++)
	{
		printf("\n%d\t%d",outcode1[i],outcode2[i]);
		printf("\n");
	}
	
	int count1=0;
	for (int j=0;j<4 ;j++)
	{
		if(outcode1[j]==0 && outcode2[j]==0)
		{
			count1+=1;
		}
	}
	if(count1==4)
	{
		printf("The line is accepted!!!!! ");
		
	}
	else
	{
		int count2=0;
		for (int j=0;j<4 ;j++)
		{
			if((outcode1[j] && outcode2[j])==0)
			{
				count2+=1;
			}
		}
		if(count2==4)
		{
			printf("The line is partially accepted!!!!");
			
			slope=((org_yb-org_ya)/(org_xb-org_xa));
			
			if (outcode1[0]==1)
			{
				ya=ymax;
				xa=org_xa+((ya-org_ya)/slope);
			}
			else if (outcode1[1]==1)
			{
				ya=ymin;
				xa=org_xa+((ya-org_ya)/slope);
			}
			else if (outcode1[2]==1)
			{
				xa=xmax;
				yb=org_ya+((xa-org_xa)*slope);
			}
			else if (outcode1[3]==1)
			{
				xa=xmin;
				ya=org_ya+((xa-org_xa)*slope);
			}
			
			else
			{
				xa=org_xa;
				ya=org_ya;
			}
			
			
			if (outcode2[0]==1)
			{
				yb=ymax;
				xb=org_xb+((yb-org_yb)/slope);
			}
			else if (outcode2[1]==1)
			{
				yb=ymin;
				xb=org_xb+((yb-org_yb)/slope);
			}
			else if (outcode2[2]==1)
			{
				xb = xmax;
				yb = org_yb+((xb-org_xb)*slope);
			}
			else if (outcode2[3]==1)
			{
				xb = xmin;
				yb = org_yb+((xb-org_xb)*slope);
			}
			else
			{
				xb=org_xb;
				yb=org_yb;
			}
			
		}
		else
		{
			printf("The line is rejected!!!!");
		}
	}
	
	 glutInit(&argc,argv); //It is used to initialise the GLUT library.
	 glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//set the initial display mode.
	 glutInitWindowPosition(0,0);
	 glutInitWindowSize(640,480);
	 glutCreateWindow("Scaling");
	 glClearColor(0.0,0.0,0.0,0);
	 glColor3f(0,0,1);
	 gluOrtho2D(0,640,0,480);
	 glutDisplayFunc(Draw);
	 glutMainLoop();
	return 0;
}
