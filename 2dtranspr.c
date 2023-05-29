#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <unistd.h>

int inp[3][20],v,tmat[3][3],omat[3][20],smat[3][3],ch,rmat[3][3];

void getdata()
{
	printf("Enter vertex: ");
	scanf("%d",&v);
	
	for(int i=0;i<v;i++)
	{
		printf("Enter X vertex: ");
		scanf("%d",&inp[0][i]);
		
		printf("Enter Y vertex: ");
		scanf("%d",&inp[1][i]);
		
		inp[2][i]=1;
	}
	
}

void mul(int imat[3][20], int tmat[3][3])
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<v;j++)
		{
			omat[i][j]=0;
			for(int k=0;k<3;k++)
			{
				omat[i][j]=omat[i][j]+(tmat[i][k]*imat[k][j]);
			}
		}
	}
}

void translation()
{
	int tx,ty;
	printf("Enter tx: ");
	scanf("%d",&tx);
	printf("Enter ty: ");
	scanf("%d",&ty);
		
	tmat[0][0]=1;
	tmat[0][1]=0;
	tmat[0][2]=tx;
	tmat[1][0]=0;
	tmat[1][1]=1;
	tmat[1][2]=ty;
	tmat[2][0]=0;
	tmat[2][1]=0;
	tmat[2][2]=1;
	
	mul(inp,tmat);
}

void scaling()
{
	int sx,sy,xf,yf;
	printf("Enter Sx: ");
	scanf("%d",&sx);
	printf("Enter Sy: ");
	scanf("%d",&sy);
	printf("Enter Xf: ");
	scanf("%d",&xf);
	printf("Enter Yf: ");
	scanf("%d",&yf);
		
	smat[0][0]=sx;
	smat[0][1]=0;
	smat[0][2]=xf*(1-sx);
	smat[1][0]=0;
	smat[1][1]=sy;
	smat[1][2]=yf*(1-sy);
	smat[2][0]=0;
	smat[2][1]=0;
	smat[2][2]=1;
	
	mul(inp,smat);
}

/*void rotation()
{
	double angle,rad,cosv,sinv;
	int xr,yr;
	
	printf("Enter angle: ");
	scanf("%lf",&angle);
	
	printf("Enter Xr: ");
	scanf("%d",&xr);
	printf("Enter Yr: ");
	scanf("%d",&yr);
	
	rad=angle*(pi/180);
	cosv=cos(rad);
	sinv=sin(rad);
	
	rmat[0][0]=cosv;
	rmat[0][1]=-sinv;
	rmat[0][2]=(xr*(1-cosv))+(yr*sinv);
	rmat[1][0]=sinv;
	rmat[1][1]=cosv;
	rmat[1][2]=(yr*(1-cosv))-(xr*sinv);
	rmat[2][0]=0;
	rmat[2][1]=0;
	rmat[2][2]=1;
	
	mul(inp,rmat);
}*/


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
	glBegin(GL_POINTS);
	
	int j;
	for(j=0;j<v-1;j++)
	{
		ddaline(inp[0][j],inp[1][j],inp[0][j+1],inp[1][j+1]);
	}
	ddaline(inp[0][j],inp[1][j],inp[0][0],inp[1][0]);
	glEnd();
	glFlush();
	
	
	sleep(2);
	
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,1.0);
	glBegin(GL_POINTS);
	int i;
	for(i=0;i<v-1;i++)
	{
		ddaline(omat[0][i],omat[1][i],omat[0][i+1],omat[1][i+1]);
	}
	ddaline(omat[0][i],omat[1][i],omat[0][0],omat[1][0]);
	
	glEnd();
	glFlush();
}

int main(int argc, char **argv)
{		
	printf("What to do:\n 1.Translate\n 2.Scale\n");
	scanf("%d",&ch);
		getdata();
		if(ch==1)
			translation();
		else if(ch==2)
			scaling();
		
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(640,480);
	
	glutCreateWindow("Window");
	
	glClearColor(0.0,0.0,0.0,0.0);
	glColor3f(1.0,0.0,0.0);
	
	gluOrtho2D(0,640,0,480);
	
	glutDisplayFunc(Draw);
	glutMainLoop();
	
	return 0;
}
