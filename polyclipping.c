#include<stdio.h>
#include<GL/glut.h>
#include<stdlib.h>
#include<unistd.h>


int xmin,ymin,xmax,ymax;
int lv,rv,bv,tv;
int v;

int input[2][10];
int left[2][10];
int right[2][10];
int bottom[2][10];
int top[2][10];



void left_clip(int xa,int ya, int xb, int yb)
{
 int x,y;
 float m;
 m=(yb-ya)/(float)(xb-xa);
 
 if(xa<xmin && xb>xmin)
 {
  x=xmin;
  y=ya+m*(x-xa);
  left[0][lv]=x;
  left[1][lv]=y;
  lv++;
 }
 
 if(xa>xmin && xb>xmin)
 {
  left[0][lv]=xa;
  left[1][lv]=ya;
  lv++;
  
  left[0][lv]=xb;
  left[1][lv]=yb;
  lv++;
 }
 
 if(xa>xmin && xb<xmin)
 {
  x=xmin;
  y=ya+m*(x-xa);
  left[0][lv]=x;
  left[1][lv]=y;
  lv++;
 }
 
 }
   
void right_clip(int xa,int ya, int xb, int yb)
{ 
   int x,y;
   float m;
   m=(yb-ya)/(float)(xb-xa);
   
  if(xa>xmax && xb<xmax)
  {
   x=xmax;
   y=ya+m*(x-xa);
   right[0][rv]=x;
   right[1][rv]=y;
   rv++;
  }
  
  if(xa<xmax && xb<xmax)
  {
   right[0][rv]=xa;
   right[1][rv]=ya;
   rv++;
   
   right[0][rv]=xb;
   right[1][rv]=yb;
   rv++;
   
  }
 
  if(xa<xmax && xb>xmax)
  {
   x=xmax;
   y=ya+m*(x-xa);
   right[0][rv]=x;
   right[1][rv]=y;
   rv++;
  }
  
 }

void bottom_clip(int xa, int ya, int xb, int yb)
{
 float m;
 int x,y;
 m=(yb-ya)/(float)(xb-xa);
	
 if(ya<ymin && yb>ymin)
 {
  y=ymin;
  x=xa+(y-ya)/m;
  
  bottom[0][bv]=x;
  bottom[1][bv]=y;
  bv++;
  
  
  bottom[0][bv]=xb;
  bottom[1][bv]=yb;
  bv++;
  
 }
	
 if(ya>ymin && yb>ymin)
 {
  
  bottom[0][bv]=xb;
  bottom[1][bv]=yb;
  bv++;
 }
	
 if(ya>ymin && yb<ymin)
 {
  y=ymin;
  x=xa+(y-ya)/m;
  
  bottom[0][bv]=x;
  bottom[1][bv]=y;
  bv++;
 }
	
	
}

void top_clip(int xa, int ya, int xb, int yb)
{
 float m;
 int x,y;
 m=(yb-ya)/(float)(xb-xa);
	
 
 if(ya>ymax && yb<ymax)
 {
   y=ymax;
   x=xa+(y-ya)/m;
   
   top[0][tv]=x;
   top[1][tv]=y;
   tv++;
   
   top[0][tv]=xb;
   top[1][tv]=yb;
   tv++;
 }
 
 if(ya<ymax && yb<ymax)
 {
  top[0][tv]=xb;
   top[1][tv]=yb;
   tv++;
  }
  
  if(ya<ymax && yb>ymax)
  {
   y=ymax;
   x=xa+(y-ya)/m;
   
   top[0][tv]=x;
   top[1][tv]=y;
   tv++;
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
   
   if(abs(dx)> abs(dy))
   {
     steps=abs(dx);
   }
   
   else
   {
    steps=abs(dy);
   }
   
     float xin,yin;
     xin=dx/(float)steps;
     yin=dy/(float)steps;
     
   float x=xa;
   float y=ya;
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
  glColor3f(1.0,0.0,0.0);
 ddaline(xmin,ymin,xmax,ymin);
 ddaline(xmax,ymin,xmax,ymax);
 ddaline(xmax,ymax,xmin,ymax);
 ddaline(xmin,ymax,xmin,ymin);

int w;
	for(w=0;w<v-1; w++)
	{
	 ddaline(input[0][w],input[1][w],input[0][w+1],input[1][w+1]);
	}
	ddaline(input[0][w],input[1][w],input[0][0],input[1][0]);
 glEnd();
 glFlush();	 
 
 	sleep(2.0);
 
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_POINTS);
  glColor3f(0.0,1.0,0.0);
  
  int u;
	for(u=0;u<tv-1; u++)
	{
	 ddaline(top[0][u],top[1][u],top[0][u+1],top[1][u+1]);
	}
	 ddaline(top[0][u],top[1][u],top[0][0],top[1][0]);
  glEnd();
  glFlush();
	 
  
 }

void getdata(int input[2][10])
{
	for(int i=0;i<v;i++)
	{
		printf("Enter x: ");
		scanf("%d",&input[0][i]);
		printf("Enter y: ");
		scanf("%d",&input[1][i]);
	}
}

int main(int argc,char **argv)
{
 	xmin=100;
 	ymin=100;
 	xmax=400;
 	ymax=400;
 
    printf("Enter vertex: ");
    scanf("%d",&v);
    getdata(input);

	int p;
	for(p=0;p<v-1; p++)
	{
	 left_clip(input[0][p],input[1][p],input[0][p+1],input[1][p+1]);
	}
	 left_clip(input[0][p],input[1][p],input[0][0],input[1][0]);
	 
	
	printf("LEFT MATRIX :\n");
	for(int a=0; a<2;a++)
	{
	 for(int b=0; b<lv;b++)
	 {
	  printf("%d\t",left[a][b]);
	 }
	 printf("\n");
	}
	
	int q;
	for(q=0;q<lv-1; q++)
	{
	 right_clip(left[0][q],left[1][q],left[0][q+1],left[1][q+1]);
	}
	 right_clip(left[0][q],left[1][q],left[0][0],left[1][0]);
	 
	printf("\nRIGHT MATRIX :\n"); 
	for(int a=0; a<2;a++)
	{
	 for(int b=0; b<lv;b++)
	 {
	  printf("%d\t", right[a][b]);
	 }
	 printf("\n");
	}
	 
	 int r;
	for(r=0;r<rv-1; r++)
	{
	 bottom_clip(right[0][r],right[1][r],right[0][r+1],right[1][r+1]);
	}
	 bottom_clip(right[0][r],right[1][r],right[0][0],right[1][0]);
	 
	printf("\nBOTTOM MATRIX :\n"); 
	for(int a=0; a<2;a++)
	{
	 for(int b=0; b<bv;b++)
	 {
	  printf("%d\t", bottom[a][b]);
	 }
	 printf("\n");
	}
	 
	 int s;
	for(s=0;s<bv-1; s++)
	{
	 top_clip(bottom[0][s],bottom[1][s],bottom[0][s+1],bottom[1][s+1]);
	}
	 top_clip(bottom[0][s],bottom[1][s],bottom[0][0],bottom[1][0]);
	 
	 printf("\nTOP MATRIX :\n"); 
	for(int a=0; a<2;a++)
	{
	 for(int b=0; b<tv;b++)
	 {
	  printf("%d\t", top[a][b]);
	 }
	 printf("\n");
	}
	
	
	glutInit(&argc,argv);
 	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//SET THE INITIAL DISPLAY MODE
	glutInitWindowPosition(0,0);
	glutInitWindowSize(640,480);
	glutCreateWindow("Window");
	glClearColor(1.0,1.0,1.0,0.0);//set clear color to white
	glColor3f(1.0,0.0,0.0);//set fill color to black
	gluOrtho2D(0,640,0,480);
	glutDisplayFunc(Draw);//CALL TO DISPLAYING FUNCTION
	glutMainLoop();//keep displaying until the programm is close
   
   return 0;
}
