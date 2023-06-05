#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

int x1,y3,x2,y2,ch,i;	

void bresline(int xa, int ya, int xb, int yb, int ch)
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
            //Simple Line
            if(ch==1) 
            {
                glVertex2d(c,r);
            }
            //Dotted Line
            else if(ch==2)
            {
                if(i%2==0)
                {
                    glVertex2d(c,r);
                }
            }
            //Dashed line
            else if(ch==3)
            {
                if(i%8!=0)
                {
                    glVertex2d(c,r);
                }
            }
            //Solid Line
            else if(ch==4)
            {
                glPointSize(4.0);
                glBegin(GL_POINTS);
                glVertex2d(c,r);
            }
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
            //Simple Line
            if(ch==1) {
                glVertex2d(c,r);
            }
            //Dotted Line
            else if(ch==2){
                if(i%2==0){
                    glVertex2d(c,r);
                }
            }
            //Dashed line
            else if(ch==3){
                if(i%8==0)
                {
                    i = i+4;
                }
                else
                {
                    glVertex2d(c,r);
                }
            }
            //Solid Line
            else if(ch==4){
                glPointSize(4.0);
                glVertex2d(c,r);
            }
        }
        glEnd();
	    glFlush();      
    }
}

void mouse1(int button, int state, int x,int y)
{
	y=480-y;
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		x1=x;
		y3=y;
	}
	if(button==GLUT_LEFT_BUTTON && state==GLUT_UP)
	{
		x2=x;
		y2=y;
		glColor3f(1.0,0.0,1.0);
		bresline(x1,y3,x2,y2,ch);
	}
}

void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	bresline(0,240,640,240,1);
	bresline(320,0,320,640,1);
	
	int i=0;
	while(i<640)
	{
		bresline(i,237,i,243,1);
		bresline(317,i,323,i,1);
		i+=20;
	}
	
	bresline(x1,y3,x2,y2,ch);
	//glVertex2d(100,100);
	glEnd();
	glFlush();
}

int main(int argc, char **argv)
{
	printf("\nWhich Type of Line You Want to Draw ");
    printf("\n1.Simple Line \n2.Dotted Line \n3.Dashed Line \n4.Solid Line \n> > > ");
   	scanf("%d",&ch);
    
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
