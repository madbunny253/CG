#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

int v,ch,ch1,tx,ty,sx,sy,xf,yf,xr,yr;
int inp[3][10],omat[3][10];
float trans[3][3],scale[3][3],rotate[3][3],r1[3][3];
double ang,rad,cosv,sinv;
const float pi=3.14159;

void mul(float trans[3][3],int inp[3][10], int omat[3][10])
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<v;j++)
		{
			omat[i][j]=0;
			for(int k=0;k<3;k++)
			{
				omat[i][j]+=trans[i][k]*inp[k][j];
			}
		}
	}
}

int Round(float a)
{
  return (int)(a+0.5);
}
 
void ddaline(int xa,int ya,int xb,int yb)
{
     int dx,dy,steps;
      dx=xb-xa;
      dy=yb-ya;
     
      if(abs(dx)>abs(dy))
      {
       steps=abs(dx);
      }
      else
      {
          steps=abs(dy);
       }
       
     float xinc,yinc;
     
     xinc=dx/(float)(steps);
     yinc=dy/(float)(steps);
     
     
     float x,y;
     
     x=xa;
     y=ya;
     
     int k;
     
     glVertex2d(Round(x)+320,Round(y)+240);
     
     for(k=0;k<steps;k++)
     {
        x=x+xinc;
        y=y+yinc;
        glVertex2d(Round(x)+320,Round(y)+240);
      }
}
void tras()
{
	printf("Enter Tx and Ty: \n");
			scanf("%d%d",&tx,&ty);
			trans[0][0]=1;
			trans[0][1]=0;
			trans[0][2]=tx;
			trans[1][0]=0;
			trans[1][1]=1;
			trans[1][2]=ty;
			trans[2][0]=0;
			trans[2][1]=0;
			trans[2][2]=1;
}

void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(2.0);
	glBegin(GL_POINTS);
	glColor3f(0,0,0);
	
	int i;
	for(i=0;i<v-1;i++)
	{
		ddaline(inp[0][i],inp[1][i],inp[0][i+1],inp[1][i+1]);
	}
	ddaline(inp[0][0],inp[1][0],inp[0][i],inp[1][i]);
	glEnd();
	glFlush();
	
	glBegin(GL_POINTS);
	glColor3f(1,0,0);
	
	int u;
	for(u=0;u<v-1;u++)
	{
		ddaline(omat[0][u],omat[1][u],omat[0][u+1],omat[1][u+1]);
	}
	ddaline(omat[0][0],omat[1][0],omat[0][u],omat[1][u]);
	
	glEnd();
	glFlush();
}

int main(int argc, char **argv)
{
	printf("Enter no. of vertices: ");
	scanf("%d",&v);
	
	for(int i=0;i<v;i++)
	{
		printf("Enter the x and y value: \n");
		scanf("%d%d",&inp[0][i],&inp[1][i]);
		inp[2][i]=1;
	}
	
	printf("Select operation: \n 1.Translation\n 2.Scaling\n 3.Rotation\n 4.Reflection\n 5.Shear\n ");
	scanf("%d",&ch);
	
	switch(ch)
	{
		case 1:
			tras();
			mul(trans,inp,omat);
			break;
			
		case 2:
			printf("Enter Sx and Sy: \n");
			scanf("%d%d",&sx,&sy);
			printf("Enter xf and yf (Fixed Point): \n");
			scanf("%d%d",&xf,&yf);
			scale[0][0]=sx;
			scale[0][1]=0;
			scale[0][2]=xf*(1-sx);
			scale[1][0]=0;
			scale[1][1]=sy;
			scale[1][2]=yf*(1-sy);
			scale[2][0]=0;
			scale[2][1]=0;
			scale[2][2]=1;
			
			mul(scale,inp,omat);
			break;
			
		case 3:
			printf("Enter Xr and Yr: \n");
			scanf("%d%d",&xr,&yr);
			printf("enter the value of angle :");
			scanf("%lf",&ang);
			rad=ang*(pi/180);
			cosv=cos(rad);
			sinv=sin(rad);
			
			rotate[0][0]=cosv;
			rotate[0][1]=-sinv;
			rotate[0][2]=(xr*(1-cosv))+(yr*sinv);
			rotate[1][0]=sinv;
			rotate[1][1]=cosv;
			rotate[1][2]=(yr*(1-cosv))-(xr*sinv);
			rotate[2][0]=0;
			rotate[2][1]=0;
			rotate[2][2]=1;
			
			mul(rotate,inp,omat);
			break;
			
		case 4:
			printf("Reflection along: \n 1.x-axis \n 2.y-axis\n 3.z-axis\n 4.x=-y\n ");
			scanf("%d",&ch1);
			
			switch(ch1)
			{
				case 1:
					r1[0][0]=1;
					r1[0][1]=0;
					r1[0][2]=0;
					r1[1][0]=0;
					r1[1][1]=-1;
					r1[1][2]=0;
					r1[2][0]=0;
					r1[2][1]=0;
					r1[2][2]=1;
					
					mul(r1,inp,omat);
					break;
			}
	}
	
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
