#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>
#include<bits/stdc++.h>
#include "BmpLoader.h"
#include<string>
using namespace std;

const int width = 800;
const int height = 600;
const float rat = 1.0 * width / height;

GLfloat eyeX = 0;
GLfloat eyeY = 500;
GLfloat eyeZ = -1;

GLfloat lookX = 0;
GLfloat lookY = 0;
GLfloat lookZ = 0;

float x=-270, z=270, x1=-250,z1=150;

bool mov=0;

int angle=0;

//float wdr=.398, wdg=.203,wdb=0;
float wdr=.5, wdg=.2,wdb=0;

double score=0;
float l_height = 20;
float l2_height = 23;
float spt_cutoff = 30;

bool l1_on = true;
bool l2_on = true;
bool l3_on = true;
bool a=true;
bool d=true;
bool s=true;

float rot = 0;

const double PI = 3.14159265389;
int bcar=180,scar=180;

const int L=20;
const int dgre=3;
int ncpt=L+1;
int clikd=0;
const int nt = 40;				//number of slices along x-direction
const int ntheta = 20;

unsigned int ID[50];

float kkk=.5;
bool lokc=false;

static int font_index=0;

void print_bitmap_string(/*void* font,*/ char* s)
{

      while (*s) {
         glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, *s);
         s++;
      }

}


void draw_stuff(float R=1, float G=1, float B=1)
{
    GLfloat m_no[] = {0, 0, 0, 1.0};
    GLfloat m_amb[] = {R,G,B,1};
    GLfloat m_diff[] = {R,G,B,1};
    GLfloat m_spec[] = {1,1,1,1};
    GLfloat m_sh[] = {60};

    GLfloat m_em[] = {R,G,B,1};

    glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, m_diff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, m_spec);
    glMaterialfv(GL_FRONT, GL_SHININESS, m_sh);

    std::ostringstream strs;
    strs << score;
    std::string str = strs.str();

    char *cstr = new char[str.length()+1];
    str.copy(cstr, str.length());
    cstr[str.length()] = '\0';

   char* bitmap_font_names[7] = {cstr};

   GLfloat x, y, ystep, yild, stroke_scale;

   /* Draw the strings, according to the current mode and font. */
   glTranslatef(0.5,-1.0,0);
   glColor4f(1.0, 1.0, 0.0, 0.0);
   x = -225.0;
   y = 70.0;
   ystep  = 100.0;
   yild   = 20.0;
      glRasterPos2f(-150, y+1.25*yild);
     print_bitmap_string(bitmap_font_names[0]);
}

GLfloat ctrlpoints2[L+1][3] =
{
    { 0, kkk, 0.0}, { .25, kkk, 0.0},
    { .5, kkk, 0.0}, { .75, kkk, 0.0},
    { 1.0, kkk, 0.0}, { 1.25, kkk, 0.0},
    { 1.5, kkk, 0.0}, { 1.75, kkk, 0.0},
    { 2.0, kkk, 0.0}, { 2.25, kkk, 0.0},
    { 2.5, kkk, 0.0}, { 2.75, kkk, 0.0},
    { 3.0, kkk, 0.0}, { 3.25, kkk, 0.0},
    { 3.5, kkk, 0.0}, { 3.75, kkk, 0.0},
    { 3.0, kkk, 0.0}, { 3.25, kkk, 0.0},
    { 3.5, kkk, 0.0}, { 3.75, kkk, 0.0},
    {4.0, kkk, 0.0}
};

GLfloat ctrlpoints1[L+1][3] =
{
    { .925, 1.25, 0.0}, { 1, 1.25, 0.0},
    { 1.125, 1.2, 0.0}, { 1.35, 1.1, 0.0},
    { 1.5, 1.07, 0.0}, { 1.625, 1.05, 0.0},
    { 1.8, 1.05, 0.0}, { 1.95, 1.05, 0.0},
    { 2.15, 1.025, 0.0}, { 2.35, 1.035, 0.0},
    { 2.6, 1.025, 0.0}, { 2.8, 1.025, 0.0},
    { 2.925, 1.025, 0.0}, { 3.05, 1.025, 0.0},
    { 3.3, 1.05, 0.0}, { 3.525, 1.025, 0.0},
    { 3.525, 1.05, 0.0}, { 3.7, 1.05, 0.0},
    { 3.97, 1.05, 0.0}, { 4.475, 1.05, 0.0},
    {4.75, 1.025, 0.0}
};

GLfloat ctrlpoints[L+1][3] =
{
    { 2.7, .5, 0.0}, { 2.7, 1, 0.0},
    { 2.7, 1.7, 0.0}, { 2.57, 2.025, 0.0},
    { 2.8, 2.25, 0.0},{ 2.825, 2.37, 0.0},
    {2.9, 2.57, 0.0}, {3.12, 2.75, 0.0},
    {3.22, 2.28, 0.0}, {3.65, 2.85, 0.0},
    {3.87, 2.85, 0.0}, {4.1, 2.775, 0.0},
    {4.25, 2.77, 0.0}, {4.37, 2.75, 0.0},
    {4.55, 2.65, 0.0}, {4.67, 2.45, 0.0},
    {4.87, 2.27, 0.0}, {5, 1.82, 0.0},
    {5.075, 1.55, 0.0}, {5.12, 1.4, 0.0},
    {5.075, .42, 0.0}
};

double ex=0, ey=0, ez=15, lx=0,ly=0,lz=0, hx=0,hy=1,hz=0;

static GLfloat v_cube[8][3] =
{
    {0,0,0},
    {0,0,1},
    {0,1,0},
    {0,1,1},

    {1,0,0},
    {1,0,1},
    {1,1,0},
    {1,1,1}
};

static GLubyte c_ind[6][4] =
{
    {0,2,6,4},
    {1,5,7,3},
    {0,4,5,1},
    {2,3,7,6},
    {0,1,3,2},
    {4,6,7,5}
};

//control points
long long nCr(int n, int r)
{
    if(r > n / 2) r = n - r; // because C(n, r) == C(n, n - r)
    long long ans = 1;
    int i;

    for(i = 1; i <= r; i++)
    {
        ans *= n - r + i;
        ans /= i;
    }

    return ans;
}
void BezierCurve2 ( double t,  float xy[2])
{

    double y=0;
    double x=0;
    t=t>1.0?1.0:t;
    for(int i=0; i<=L; i++)
    {
        int ncr=nCr(L,i);
        double oneMinusTpow=pow(1-t,double(L-i));
        double tPow=pow(t,double(i));
        double coef=oneMinusTpow*tPow*ncr;
        x+=coef*ctrlpoints2[i][0];
        y+=coef*ctrlpoints2[i][1];

    }
    xy[0] = float(x);
    xy[1] = float(y);

    //return y;
}
//polynomial interpretation for N points
void BezierCurve1 ( double t,  float xy[2])
{

    double y=0;
    double x=0;
    t=t>1.0?1.0:t;
    for(int i=0; i<=L; i++)
    {
        int ncr=nCr(L,i);
        double oneMinusTpow=pow(1-t,double(L-i));
        double tPow=pow(t,double(i));
        double coef=oneMinusTpow*tPow*ncr;
        x+=coef*ctrlpoints1[i][0];
        y+=coef*ctrlpoints1[i][1];

    }
    xy[0] = float(x);
    xy[1] = float(y);

    //return y;
}
void BezierCurve ( double t,  float xy[2])
{
    double y=0;
    double x=0;
    t=t>1.0?1.0:t;
    for(int i=0; i<=L; i++)
    {
        int ncr=nCr(L,i);
        double oneMinusTpow=pow(1-t,double(L-i));
        double tPow=pow(t,double(i));
        double coef=oneMinusTpow*tPow*ncr;
        x+=coef*ctrlpoints[i][0];
        y+=coef*ctrlpoints[i][1];

    }
    xy[0] = float(x);
    xy[1] = float(y);

    //return y;
}

///////////////////////
void setNormal(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(-Nx,-Ny,-Nz);
}

void rod(float R=0, float G=0, float B=0)
{
     GLfloat m_no[] = {0, 0, 0, 1.0};
    GLfloat m_amb[] = {R,G,B,1};
    GLfloat m_diff[] = {R,G,B,1};
    GLfloat m_spec[] = {R,G,B,1};
    GLfloat m_sh[] = {60};

    GLfloat m_em[] = {R,G,B,1};

    glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, m_diff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, m_spec);
    glMaterialfv(GL_FRONT, GL_SHININESS, m_sh);

    int i, j;
    float x, y, z, r;				//current coordinates
    float x1, y1, z1, r1;			//next coordinates
    float theta;

    const float startx = 0, endx = ctrlpoints[L][0];
    //number of angular slices
    const float dx = (endx - startx) / nt;	//x step size
    const float dtheta = 2*PI / ntheta;		//angular step size

    float t=0;
    float dt=1.0/nt;
    float xy[2];
    BezierCurve2( t,  xy);
    x = xy[0];
    r = xy[1];
    //rotate about z-axis
    float p1x,p1y,p1z,p2x,p2y,p2z;
    for ( i = 0; i < nt; ++i )  			//step through x
    {
        theta = 0;
        t+=dt;
        BezierCurve2( t,  xy);
        x1 = xy[0];
        r1 = xy[1];

        //draw the surface composed of quadrilaterals by sweeping theta
        glBegin( GL_QUAD_STRIP );
        for ( j = 0; j <= ntheta; ++j )
        {
            theta += dtheta;
            double cosa = cos( theta );
            double sina = sin ( theta );
            y = r * cosa;
            y1 = r1 * cosa;	//current and next y
            z = r * sina;
            z1 = r1 * sina;	//current and next z

            //edge from point at x to point at next x
            glVertex3f (x, y, z);

            if(j>0)
            {
                setNormal(p1x,p1y,p1z,p2x,p2y,p2z,x, y, z);
            }
            else
            {
                p1x=x;
                p1y=y;
                p1z=z;
                p2x=x1;
                p2y=y1;
                p2z=z1;

            }
            glVertex3f (x1, y1, z1);

            //forms quad with next pair of points with incremented theta value
        }
        glEnd();
        x = x1;
        r = r1;
    } //for i

}

void branch(float R=1, float G=1, float B=1)
{
     GLfloat m_no[] = {0, 0, 0, 1.0};
    GLfloat m_amb[] = {R,G,B,1};
    GLfloat m_diff[] = {R,G,B,1};
    GLfloat m_spec[] = {1,1,1,1};
    GLfloat m_sh[] = {60};

    GLfloat m_em[] = {R,G,B,1};

    glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, m_diff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, m_spec);
    glMaterialfv(GL_FRONT, GL_SHININESS, m_sh);




    int i, j;
    float x, y, z, r;				//current coordinates
    float x1, y1, z1, r1;			//next coordinates
    float theta;

    const float startx = 0, endx = ctrlpoints1[L][0];
    //number of angular slices
    const float dx = (endx - startx) / nt;	//x step size
    const float dtheta = 2*PI / ntheta;		//angular step size

    float t=0;
    float dt=1.0/nt;
    float xy[2];
    BezierCurve1( t,  xy);
    x = xy[0];
    r = xy[1];
    //rotate about z-axis
    float p1x,p1y,p1z,p2x,p2y,p2z;
    for ( i = 0; i < nt; ++i )  			//step through x
    {
        theta = 0;
        t+=dt;
        BezierCurve1( t,  xy);
        x1 = xy[0];
        r1 = xy[1];

        //draw the surface composed of quadrilaterals by sweeping theta
        glBegin( GL_QUAD_STRIP );
        for ( j = 0; j <= ntheta; ++j )
        {
            theta += dtheta;
            double cosa = cos( theta );
            double sina = sin ( theta );
            y = r * cosa;
            y1 = r1 * cosa;	//current and next y
            z = r * sina;
            z1 = r1 * sina;	//current and next z

            //edge from point at x to point at next x
            glVertex3f (x, y, z);

            if(j>0)
            {
                setNormal(p1x,p1y,p1z,p2x,p2y,p2z,x, y, z);
            }
            else
            {
                p1x=x;
                p1y=y;
                p1z=z;
                p2x=x1;
                p2y=y1;
                p2z=z1;

            }
            glVertex3f (x1, y1, z1);

            //forms quad with next pair of points with incremented theta value
        }
        glEnd();
        x = x1;
        r = r1;
    } //for i

}

void leaf(float R=0, float G=0, float B=0)
{
     GLfloat m_no[] = {0, 0, 0, 1.0};
    GLfloat m_amb[] = {R,G,B,1};
    GLfloat m_diff[] = {R,G,B,1};
    GLfloat m_spec[] = {1,1,1,1};
    GLfloat m_sh[] = {60};

    GLfloat m_em[] = {R,G,B,1};

    glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, m_diff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, m_spec);
    glMaterialfv(GL_FRONT, GL_SHININESS, m_sh);

    int i, j;
    float x, y, z, r;				//current coordinates
    float x1, y1, z1, r1;			//next coordinates
    float theta;

    const float startx = 0, endx = ctrlpoints[L][0];
    //number of angular slices
    const float dx = (endx - startx) / nt;	//x step size
    const float dtheta = 2*PI / ntheta;		//angular step size

    float t=0;
    float dt=1.0/nt;
    float xy[2];
    BezierCurve( t,  xy);
    x = xy[0];
    r = xy[1];
    //rotate about z-axis
    float p1x,p1y,p1z,p2x,p2y,p2z;
    for ( i = 0; i < nt; ++i )  			//step through x
    {
        theta = 0;
        t+=dt;
        BezierCurve( t,  xy);
        x1 = xy[0];
        r1 = xy[1];

        //draw the surface composed of quadrilaterals by sweeping theta
        glBegin( GL_QUAD_STRIP );
        for ( j = 0; j <= ntheta; ++j )
        {
            theta += dtheta;
            double cosa = cos( theta );
            double sina = sin ( theta );
            y = r * cosa;
            y1 = r1 * cosa;	//current and next y
            z = r * sina;
            z1 = r1 * sina;	//current and next z

            //edge from point at x to point at next x
            glVertex3f (x, y, z);

            if(j>0)
            {
                setNormal(p1x,p1y,p1z,p2x,p2y,p2z,x, y, z);
            }
            else
            {
                p1x=x;
                p1y=y;
                p1z=z;
                p2x=x1;
                p2y=y1;
                p2z=z1;

            }
            glVertex3f (x1, y1, z1);

            //forms quad with next pair of points with incremented theta value
        }
        glEnd();
        x = x1;
        r = r1;
    } //for i

}

void showControlPoints()
{
    glPointSize(5.0);
    glColor3f(1.0, 0.0, 1.0);
    //glBegin(GL_POINTS);
    for (int i = 0; i <=L; i++)
        glVertex3fv(&ctrlpoints[i][0]);
    glEnd();
}
void circle(float R=0, float G=1, float B=0, bool e=false)
{

    GLfloat m_no[] = {0, 0, 0, 1.0};
    GLfloat m_amb[] = {R,G,B,1};
    GLfloat m_diff[] = {R,G,B,1};
    GLfloat m_spec[] = {1,1,1,1};
    GLfloat m_sh[] = {30};

    GLfloat m_em[] = {0,0,1,1};

    glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, m_diff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, m_spec);
    glMaterialfv(GL_FRONT, GL_SHININESS, m_sh);

    if(e) glMaterialfv(GL_FRONT, GL_EMISSION, m_em);
    else glMaterialfv(GL_FRONT, GL_EMISSION, m_no);

    glBegin(GL_QUADS);
    glutSolidSphere(1,50,50);
    glEnd();
}
void tree()
{
    glPolygonMode( GL_FRONT,GL_FILL ) ;
    glPolygonMode( GL_BACK, GL_FILL ) ;


    glPushMatrix();
    glTranslated(0,-3.5,0);
    glRotatef( 90, 0.0, 0.0, 1.0);
    //
    glPushMatrix();
        glTranslated(11.5,0,0);
        glScaled(2,2,2);
        circle();
    glPopMatrix();
    glPushMatrix();
        glTranslated(5,0,0);
        glScaled(1.2,1.5,1.5);
        //glTranslated(-1,-.5,0);
        leaf(.5,1,0);
    glPopMatrix();
    glPushMatrix();
        ///glTranslated(0,2,0);

        glScaled(2,1,1);

        branch(.398,.203,0);
    glPopMatrix();
    glPopMatrix();


    showControlPoints();

}
static void getNormal3p(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}

void cube(float R=0.5, float G=0.5, float B=0.5, bool e=false)
{
    ///glColor3f(1,1,1);
    GLfloat m_no[] = {0, 0, 0, 1.0};
    GLfloat m_amb[] = {R,G,B,1};
    GLfloat m_diff[] = {R,G,B,1};
    GLfloat m_spec[] = {1,1,1,1};
    GLfloat m_sh[] = {60};

    GLfloat m_em[] = {R,G,B,1};

    glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, m_diff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, m_spec);
    glMaterialfv(GL_FRONT, GL_SHININESS, m_sh);

    if(e) glMaterialfv(GL_FRONT, GL_EMISSION, m_em);
    else glMaterialfv(GL_FRONT, GL_EMISSION, m_no);

    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(v_cube[c_ind[i][0]][0], v_cube[c_ind[i][0]][1], v_cube[c_ind[i][0]][2],
                    v_cube[c_ind[i][1]][0], v_cube[c_ind[i][1]][1], v_cube[c_ind[i][1]][2],
                    v_cube[c_ind[i][2]][0], v_cube[c_ind[i][2]][1], v_cube[c_ind[i][2]][2]);

        glVertex3fv(&v_cube[c_ind[i][0]][0]);glTexCoord2f(1,1);
        glVertex3fv(&v_cube[c_ind[i][1]][0]);glTexCoord2f(1,0);
        glVertex3fv(&v_cube[c_ind[i][2]][0]);glTexCoord2f(0,0);
        glVertex3fv(&v_cube[c_ind[i][3]][0]);glTexCoord2f(0,1);
    }
    glEnd();
}

void triangle(float R=0.5, float G=0.5, float B=0.5, bool e=false)
{
    GLfloat m_no[] = {0, 0, 0, 1.0};
    GLfloat m_amb[] = {R,G,B,1};
    GLfloat m_diff[] = {R,G,B,1};
    GLfloat m_spec[] = {1,1,1,1};
    GLfloat m_sh[] = {60};

    GLfloat m_em[] = {R,G,B,1};

    glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, m_diff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, m_spec);
    glMaterialfv(GL_FRONT, GL_SHININESS, m_sh);


    if(e) glMaterialfv(GL_FRONT, GL_EMISSION, m_em);
    else glMaterialfv(GL_FRONT, GL_EMISSION, m_no);
    //glMaterialfv(GL_FRONT, GL_EMISSION, m_em);

    glBegin(GL_TRIANGLES);
		glColor3f(1.0,1.0,1.0);
		glVertex2f(0,1.0);
		glColor3f(1.0,1.0,1.0);
		glVertex2f(1.0,0.0);
		glColor3f(1.0,1.0,1.0);
		glVertex2f(0.0,0.0);
	glEnd();
}

void axes()
{
    float length = 10;
    float width = 0.3;

    // X-axis
    glPushMatrix();
    glTranslatef(length/2,0,0);
    glScalef(length,width,width);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(0.8,0.1,0.1);
    glPopMatrix();

    // Y-axis
    glPushMatrix();
    glTranslatef(0,length/2,0);
    glScalef(width,length,width);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(0.1,0.8,0.1);
    glPopMatrix();

    // Z-axis
    glPushMatrix();
    glTranslatef(0,0,length/2);
    glScalef(width,width,length);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(0.1,0.1,0.8);
    glPopMatrix();
}

void wall()
{
    glPushMatrix();
        glScalef(40,1,40);
        cube();
    glPopMatrix();
}
void bsflr(float R=0, float G=0, float B=1)
{
    glPushMatrix();

        glScalef(50,10,20);
        cube(R,G,B);

    glPopMatrix();
    glPushMatrix();
        glTranslated(4,3,-.1);
        glScalef(4,4,20.2);
        cube(0,0,0);

    glPopMatrix();
      glPushMatrix();
        glTranslated(12,3,-.1);
        glScalef(4,4,20.2);
        cube(0,0,0);

    glPopMatrix();
     glPushMatrix();
        glTranslated(20,3,-.1);
        glScalef(4,4,20.2);
        cube(0,0,0);

    glPopMatrix();
     glPushMatrix();
        glTranslated(28,0,-.1);
        glScalef(4,8,20.2);
        cube(0,0,0);

    glPopMatrix();
     glPushMatrix();
        glTranslated(36,3,-.1);
        glScalef(4,4,20.2);
        cube(0,0,0);

    glPopMatrix();
     glPushMatrix();
        glTranslated(44,3,-.1);
        glScalef(4,4,20.2);
        cube(0,0,0);

    glPopMatrix();
}


void bflr(float R=0, float G=0, float B=1)
{
    glPushMatrix();

        glScalef(50,10,20);
        cube(R,G,B);

    glPopMatrix();
    glPushMatrix();
        glTranslated(4,3,-.1);
        glScalef(4,4,20.2);
        cube(0,0,0);

    glPopMatrix();
      glPushMatrix();
        glTranslated(12,3,-.1);
        glScalef(4,4,20.2);
        cube(0,0,0);

    glPopMatrix();
     glPushMatrix();
        glTranslated(20,3,-.1);
        glScalef(4,4,20.2);
        cube(0,0,0);

    glPopMatrix();
     glPushMatrix();
        glTranslated(28,3,-.1);
        glScalef(4,4,20.2);
        cube(0,0,0);

    glPopMatrix();
     glPushMatrix();
        glTranslated(36,3,-.1);
        glScalef(4,4,20.2);
        cube(0,0,0);

    glPopMatrix();
     glPushMatrix();
        glTranslated(44,3,-.1);
        glScalef(4,4,20.2);
        cube(0,0,0);

    glPopMatrix();
}

void building(int n, float R=.2, float G=.2, float B=1)
{
    if (n<4)
        n=4;
    bsflr(R,G,B);
    for(int i=1;i<n;i++)
    {

        glPushMatrix();

            glTranslatef(0,i*10,0);
            bflr(R,G,B);

        glPopMatrix();
    }
    glPushMatrix();
        glTranslated(0,n*10-1,0);
        glScalef(50,2,20);
        cube();
    glPopMatrix();
}
void road1d()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[0]);

    glPushMatrix();

        glTranslated(-.5,-.5,-.5);
        cube();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    glFlush();
}
void road()
{

    glPushMatrix();
        glTranslated(-270,0,0);
        glScaled(60,1,560);
        road1d();
    glPopMatrix();
    glPushMatrix();
        glTranslated(-145,0,-270);
        glRotated(90,0,1,0);
        glScaled(60,1,300);
        road1d();
    glPopMatrix();
    glPushMatrix();
        glTranslated(20,0,-150);
        glScaled(60,1,300);
        road1d();
    glPopMatrix();
    glPushMatrix();
        glTranslated(125,0,-20);
        glRotated(90,0,1,0);
        glScaled(60,1,270);
        road1d();
    glPopMatrix();
    glPushMatrix();
        glTranslated(270,0,125);
        glScaled(60,1,340);
        road1d();
    glPopMatrix();

    glPushMatrix();
        glTranslated(178,0,373);
        glRotated(135,0,1,0);
        glScaled(60,1,270);
        road1d();
    glPopMatrix();

    glPushMatrix();
        glTranslated(0,0,465);
        glRotated(90,0,1,0);
        glScaled(60,1,200);
        road1d();
    glPopMatrix();


    glPushMatrix();
        glTranslated(-175,0,370);
        glRotated(45,0,1,0);
        glScaled(60,1,290);
        road1d();
    glPopMatrix();



}

void fan()
{
    //center
    glPushMatrix();
        glScalef(2,.5,2);
        cube(0,.8,0);
    glPopMatrix();

    glPushMatrix();
        glTranslated(2,0,.4);
        glScalef(6,.5,1.2);
        cube(0,.8,0);
    glPopMatrix();

    glPushMatrix();
        glTranslated(-6,0,.4);
        glScalef(6,.5,1.2);
        cube(0,.8,0);
    glPopMatrix();

    glPushMatrix();
        glTranslated(.4,0,2);
        glScalef(1.2,.5,6);
        cube(0,.8,0);
    glPopMatrix();
    glPushMatrix();
        glTranslated(.4,0,-6);
        glScalef(1.2,.5,6);
        cube(0,.8,0);
    glPopMatrix();


}

void sritipoll()
{
    //triangle();
    glPushMatrix();
        glTranslated(0,0,-.5);
        glPushMatrix();
            glScaled(5,5,5);
            triangle(1,1,1,true);
        glPopMatrix();
        glPushMatrix();
            glTranslated(0,0,1);
            glScaled(5,5,5);
            triangle(1,1,1,true);
        glPopMatrix();
        glPushMatrix();
            glScaled(.1,5,1);
            cube();
        glPopMatrix();
        glPushMatrix();
            glTranslated(5, 0,0);
            glRotated(45,0,0,1);
            glScaled(.1,7,1);
            cube();
        glPopMatrix();

    glPopMatrix();
}

void sritisooidho()
{

    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D, ID[5]);
    ///1
    glPushMatrix();
        glRotated(20,0,1,0);
        glScalef(1, 7, 1);
        sritipoll();
    glPopMatrix();
    glPushMatrix();
        glRotated(160,0,1,0);
        glScalef(1, 7, 1);
        sritipoll();
    glPopMatrix();
    ///2
    glPushMatrix();
        glTranslated(0,0,2);
        glRotated(20,0,1,0);
        glScalef(1.8, 6, 1);
        sritipoll();
    glPopMatrix();
    glPushMatrix();
        glTranslated(0,0,2);
        glRotated(160,0,1,0);
        glScalef(1.8, 6, 1);
        sritipoll();
    glPopMatrix();
    ///3
    glPushMatrix();
        glTranslated(0,0,4);
        glRotated(20,0,1,0);
        glScalef(2.6, 5, 1);
        sritipoll();
    glPopMatrix();
    glPushMatrix();
        glTranslated(0,0,4);
        glRotated(160,0,1,0);
        glScalef(2.6, 5, 1);
        sritipoll();
    glPopMatrix();
    ///4
    glPushMatrix();
        glTranslated(0,0,6);
        glRotated(20,0,1,0);
        glScalef(3.4, 4, 1);
        sritipoll();
    glPopMatrix();
    glPushMatrix();
        glTranslated(0,0,6);
        glRotated(160,0,1,0);
        glScalef(3.4, 4, 1);
        sritipoll();
    glPopMatrix();
    ///5
    glPushMatrix();
        glTranslated(0,0,8);
        glRotated(20,0,1,0);
        glScalef(4.2, 3, 1);
        sritipoll();
    glPopMatrix();
    glPushMatrix();
        glTranslated(0,0,8);
        glRotated(160,0,1,0);
        glScalef(4.2, 3, 1);
        sritipoll();
    glPopMatrix();
    ///6
    glPushMatrix();
        glTranslated(0,0,10);
        glRotated(20,0,1,0);
        glScalef(5, 2, 1);
        sritipoll();
    glPopMatrix();
    glPushMatrix();
        glTranslated(0,0,10);
        glRotated(160,0,1,0);
        glScalef(5, 2, 1);
        sritipoll();
    glPopMatrix();
    ///7
    glPushMatrix();
        glTranslated(0,0,12);
        glRotated(20,0,1,0);
        glScalef(5.8, 1, 1);
        sritipoll();
    glPopMatrix();
    glPushMatrix();
        glTranslated(0,0,12);
        glRotated(160,0,1,0);
        glScalef(5.8, 1, 1);
        sritipoll();
    glPopMatrix();

    //glDisable(GL_TEXTURE_2D);
    //glFlush();

}

void comBase()
{

    glPushMatrix();
        glTranslated(-.5, 0,-1);
        cube(.79, .25, .32);
    glPopMatrix();

}
void lake(int im=5)
{


    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[im]);

    glPushMatrix();


        glScaled(5,1,5);
        glTranslated(-.5,0,-.5);
        cube();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    glFlush();

    glPushMatrix();
        glTranslated(0,0,2.8);
        glScaled(6,1.3,.5);
        glTranslated(-.5,0,-.5);
        cube(.398,.203,0);
    glPopMatrix();
    glPushMatrix();
        glTranslated(2.8,0,0);
        glScaled(.5,1.3,6);
        glTranslated(-.5,0,-.5);
        cube(.398,.203,0);
    glPopMatrix();
    glPushMatrix();
        glTranslated(0,0,-2.8);
        glScaled(6,1.3,.5);
        glTranslated(-.5,0,-.5);
        cube(.398,.203,0);
    glPopMatrix();
    glPushMatrix();
        glTranslated(-2.8,0,0);
        glScaled(.5,1.3,6);
        glTranslated(-.5,0,-.5);
        cube(.398,.203,0);
    glPopMatrix();


}
void lake1(int k=0)
{
    int im=5;
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[im]);

    glPushMatrix();


        glScaled(5,1,5);
        glTranslated(-.5,0,-.5);
        cube();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    glFlush();

    glPushMatrix();
        glTranslated(0,0,2.8);
        glScaled(6,1.3,.5);
        glTranslated(-.5,0,-.5);
        cube(.398,.203,0);
    glPopMatrix();
    glPushMatrix();
        glTranslated(0,0,-2.8);
        glScaled(6,1.3,.5);
        glTranslated(-.5,0,-.5);
        cube(.398,.203,0);
    glPopMatrix();
    if(k==1)
    {

        glPushMatrix();
            glTranslated(2.8,0,0);
            glScaled(.5,1.3,6);
            glTranslated(-.5,0,-.5);
            cube(.398,.203,0);
        glPopMatrix();

        glPushMatrix();
            glTranslated(-2.8,0,-2);
            glScaled(.5,1.3,2);
            glTranslated(-.5,0,-.5);
            cube(.398,.203,0);
        glPopMatrix();
        glPushMatrix();
            glTranslated(-2.8,0,2);
            glScaled(.5,1.3,2);
            glTranslated(-.5,0,-.5);
            cube(.398,.203,0);
        glPopMatrix();
    }
    else
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, ID[im]);

        glPushMatrix();
            glTranslated(2.8,0,0);
            glScaled(.5,1,6);
            glTranslated(-.5,0,-.5);
            cube(1,1,1);
        glPopMatrix();
        glPushMatrix();
            glTranslated(-2.8,0,0);
            glScaled(.5,1,6);
            glTranslated(-.5,0,-.5);
            cube(1,1,1);
        glPopMatrix();

        glDisable(GL_TEXTURE_2D);
        glFlush();
    }


}

void sriticomplx()
{

    glPushMatrix();
        glTranslated(0, 5,0);
        sritisooidho();
    glPopMatrix();
    ///steps
    glPushMatrix();
        glTranslated(0, 4,10);
        //glRotated(45,0,0,1);
        glScaled(80,2,20);
        comBase();
    glPopMatrix();
    glPushMatrix();
        glTranslated(0, 2,10);
        //glRotated(45,0,0,1);
        glScaled(80,2,40);
        comBase();
    glPopMatrix();
    glPushMatrix();
        glTranslated(0, 0,10);
        //glRotated(45,0,0,1);
        glScaled(80,2,100);
        comBase();
    glPopMatrix();
    glPushMatrix();
        glTranslated(0, 2,-60);
        //glRotated(45,0,0,1);
        glScaled(5,1,8);
        lake();
    glPopMatrix();

}

void sohidpoll()
{
    glPolygonMode( GL_FRONT,GL_FILL ) ;
    glPolygonMode( GL_BACK, GL_FILL ) ;
    glPushMatrix();
        glTranslated(2,0,0);
        glScalef(.2,5,.5);
        cube(1,1,1,true);
    glPopMatrix();
    glPushMatrix();
        glTranslated(0,0,0);
        glScalef(.2,5,.5);
        cube(1,1,1,true);
    glPopMatrix();
    glPushMatrix();
        glTranslated(0,5,0);
        glScalef(2.2,.2,.5);
        cube(1,1,1,true);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(.5,0,0);
        glScaled(.05,1.25,.05);
        glRotated(90,0,0,1);
        rod(0.0,0.0,0.0);
        glPointSize(5.0);
        glColor3f(0.0,0.0,0.0);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(.75,0,0);
        glScaled(.05,1.25,.05);
        glRotated(90,0,0,1);
        rod(0.0,0.0,0.0);
        glPointSize(5.0);
        glColor3f(0.0,0.0,0.0);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(1,0,0);
        glScaled(.05,1.25,.05);
        glRotated(90,0,0,1);
        rod(0.0,0.0,0.0);
        glPointSize(5.0);
        glColor3f(0.0,0.0,0.0);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(1.25,0,0);
        glScaled(.05,1.25,.05);
        glRotated(90,0,0,1);
        rod(0.0,0.0,0.0);
        glPointSize(5.0);
        glColor3f(0.0,0.0,0.0);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(1.5,0,0);
        glScaled(.05,1.25,.05);
        glRotated(90,0,0,1);
        rod(0.0,0.0,0.0);
        glPointSize(5.0);
        glColor3f(0.0,0.0,0.0);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(1.75,0,0);
        glScaled(.05,1.25,.05);
        glRotated(90,0,0,1);
        rod(0.0,0.0,0.0);
        glPointSize(5.0);
        glColor3f(0.0,0.0,0.0);
    glPopMatrix();
    showControlPoints();

}
void sohidminar()
{
    //middle left
    glPushMatrix();
        glTranslatef(0,0,4);
        glScalef(3,5,3);
        sohidpoll();
    glPopMatrix();
    //middle right
    glPushMatrix();
        glTranslatef(-6,0,4);
        glScalef(3,5,3);
        sohidpoll();
    glPopMatrix();
    //middle left top
    glPushMatrix();
        glTranslatef(0,25,4);
        glRotated(-55,1,0,0);
        glScalef(3,1.5,3);
        sohidpoll();
    glPopMatrix();
    //middle right top
    glPushMatrix();
        glTranslatef(-6,25,4);
        glRotated(-55,1,0,0);
        glScalef(3,1.5,3);
        sohidpoll();
    glPopMatrix();

    //second
    glPushMatrix();
        glTranslatef(10,0,1.5);
        glRotated(35,0,1,0);
        glScalef(2.5,4,2.5);
        sohidpoll();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-13,0,-2.5);
        glRotated(-35,0,1,0);
        glScalef(2.5,4,2.5);
        sohidpoll();
    glPopMatrix();

    //third
    glPushMatrix();
        glTranslatef(16,0,-4);
        glRotated(45,0,1,0);
        glScalef(2.5,3,2.5);
        sohidpoll();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-19,0,-8.5);
        glRotated(-45,0,1,0);
        glScalef(2.5,3,2.5);
        sohidpoll();
    glPopMatrix();
    //circle
    glPushMatrix();
        glTranslated(0,16,6);
        glScaled(8,8,.1);
        glRotated(180,0,1,0);
        circle(1,0,0);
    glPopMatrix();

}
void sohidcomplx()
{

    glPushMatrix();
        glTranslated(0, 5,0);
        sohidminar();
    glPopMatrix();
    ///steps
    glPushMatrix();
        glTranslated(0, 4,10);
        //glRotated(45,0,0,1);
        glScaled(80,2,20);
        comBase();
    glPopMatrix();
    glPushMatrix();
        glTranslated(0, 2,10);
        //glRotated(45,0,0,1);
        glScaled(80,2,40);
        comBase();
    glPopMatrix();
    glPushMatrix();
        glTranslated(0, 0,10);
        //glRotated(45,0,0,1);
        glScaled(80,2,100);
        comBase();
    glPopMatrix();
    glPushMatrix();
        glTranslated(0, 2,-60);
        //glRotated(45,0,0,1);
        glScaled(5,1,8);
        lake(6);
    glPopMatrix();

}

void wheel()
{
    leaf(0,0,0);
}
void headlight()
{
    GLfloat l_no[] = {0, 0, 0, 1.0};
    GLfloat l_amb[] = {1, 1, 1, 1.0};
    GLfloat l_dif[] = {1,1,1,1};
    GLfloat l_spec[] = {1,1,1,1};
    GLfloat l2_pos[] = {0,2,15,1.0};

    glEnable(GL_LIGHT1);

    if(l2_on)
    {
        if(a)
            glLightfv(GL_LIGHT1, GL_AMBIENT, l_amb);
        else
            glLightfv(GL_LIGHT1, GL_AMBIENT, l_no);
        if(d)
            glLightfv(GL_LIGHT1, GL_DIFFUSE, l_dif);
        else
            glLightfv(GL_LIGHT1, GL_DIFFUSE, l_no);
        if(s)
            glLightfv(GL_LIGHT1, GL_SPECULAR, l_spec);
        else
            glLightfv(GL_LIGHT1, GL_SPECULAR, l_no);
    }
    else
    {
        glLightfv(GL_LIGHT1, GL_AMBIENT, l_no);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, l_no);
        glLightfv(GL_LIGHT1, GL_SPECULAR, l_no);
    }

    glLightfv(GL_LIGHT1, GL_POSITION, l2_pos);

    // spot light extra
    GLfloat l_spt[] = {0,-.1,1,1};
    GLfloat spt_ct[] = {spt_cutoff};
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, l_spt);
    glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, spt_ct);
}

void car()
{

    glPushMatrix();
        //glTranslated(0,0,-.1);
        glScalef(8,4,15);
        cube(.0,.0,0.3,0);
    glPopMatrix();
    glPushMatrix();
        glTranslated(0,4,3.5);
        glScalef(8,4,7);
        cube(.0,.0,0.3,0);
    glPopMatrix();

    ///back
    glPushMatrix();
        glTranslatef(8,4,3.5);
        glRotated(90,0,1,0);
        glScalef(2,4,1);
        triangle(.0,.0,0.3,0);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0,4,3.5);
        glRotated(90,0,1,0);
        glScalef(2,4,1);
        triangle(.0,.0,0.3,0);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0,4,1.5);
        glRotated(26.566,1,0,0);
        glScalef(8,4.472,.25);
        cube(.0,.0,0.3,0);
    glPopMatrix();

    ///fornt
    glPushMatrix();
        glTranslatef(8,4,10.5);
        glRotated(-90,0,1,0);
        glScalef(2,4,1);
        triangle(.0,.0,0.3,0);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0,4,10.5);
        glRotated(-90,0,1,0);
        glScalef(2,4,1);
        triangle(.0,.0,0.3,0);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0,4,12.5);
        glRotated(-26.566,1,0,0);
        glScalef(8,4.472,.25);
        cube(.0,.0,0.3,0);
    glPopMatrix();

    ///wheel
    //back
    glPushMatrix();
        glTranslatef(-2.5,1,3.5);
        //glRotated(-26.566,1,0,0);
        glScalef(.8, .8, .8);
        wheel();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(4.5,1,3.5);
        //glRotated(-26.566,1,0,0);
        glScalef(.8, .8, .8);
        wheel();
    glPopMatrix();
    //front
    glPushMatrix();
        glTranslatef(-2.5,1,11.5);
        //glRotated(-26.566,1,0,0);
        glScalef(.8, .8, .8);
        wheel();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(4.5,1,11.5);
        //glRotated(-26.566,1,0,0);
        glScalef(.8, .8, .8);
        wheel();
    glPopMatrix();
    glPushMatrix();
        glTranslated(6,0,0);
        headlight();
    glPopMatrix();
    glPushMatrix();
        glTranslated(2,0,0);
        headlight();
    glPopMatrix();
    glPushMatrix();
        glTranslated(2,13,0);
        glScalef(.002,.002,.002);
        draw_stuff();
    glPopMatrix();
}

void bigcar()
{
    glPushMatrix();
        //glTranslated(0,0,-.1);
        glScalef(8,6,8);
        ///glTranslatef(-.5,-.5,-.5);
        cube(1,1,0,0);
    glPopMatrix();
    glPushMatrix();
        //glTranslated(0,0,-.1);
        glScalef(8,8,6);
        glTranslatef(0,0,-1);
        cube(1,1,0,0);
    glPopMatrix();
    ///back wheel
    glPushMatrix();
        //glTranslated(0,0,-.1);
        //glScalef(8,8,6);
        glTranslatef(5,3.5,-2);
        glScalef(1,1.5,1.5);
        wheel();
    glPopMatrix();
    glPushMatrix();
        //glTranslated(0,0,-.1);
        //glScalef(8,8,6);
        glTranslatef(-5,3.5,-2);
        glScalef(1,1.5,1.5);
        wheel();
    glPopMatrix();
    ///front wheel
    glPushMatrix();
        //glTranslated(0,0,-.1);
        //glScalef(8,8,6);
        glTranslatef(-8.27,4.7,13);
        glScalef(3.2,1.7,1.7);
        wheel();
    glPopMatrix();
    ///front bar
    glPushMatrix();
        glTranslated(-1,3.7,3);
        glScalef(1,2,11);
        ///glTranslatef(-1,0,0);
        cube(1,1,0,0);
    glPopMatrix();

    glPushMatrix();
        glTranslated(8,3.7,3);
        glScalef(1,2,11);
        ///glTranslatef(-1,0,0);
        cube(1,1,0,0);
    glPopMatrix();

    ///barbr
    glPushMatrix();
        glTranslated(0,6,0);
        glScalef(.5,10,.5);
        ///glTranslatef(-1,0,0);
        cube(1,1,0,0);
    glPopMatrix();
    ///barbl
    glPushMatrix();
        glTranslated(7.5,6,0);
        glScalef(.5,10,.5);
        ///glTranslatef(-1,0,0);
        cube(1,1,0,0);
    glPopMatrix();
    ///barfr
    glPushMatrix();
        glTranslated(0,6,7.5);
        glScalef(.5,10,.5);
        ///glTranslatef(-1,0,0);
        cube(1,1,0,0);
    glPopMatrix();
    ///barfl
    glPushMatrix();
        glTranslated(7.5,6,7.5);
        glScalef(.5,10,.5);
        ///glTranslatef(-1,0,0);
        cube(1,1,0,0);
    glPopMatrix();
    ///roof
    glPushMatrix();
        glTranslated(0,16,0);
        glScalef(8,.2,8);
        ///glTranslatef(-1,0,0);
        cube(1,1,0,0);
    glPopMatrix();

}
void tubelight()
{
    glPushMatrix();
        glScalef(8,1,.8);
        cube(0,0,0);
    glPopMatrix();
    glPushMatrix();
        glTranslated(0,0,-.8);
        glScalef(8,1,.8);
        cube(1,1,1,l1_on);
    glPopMatrix();
}

void chair()
{
    glPushMatrix();
        ///glTranslatef(-1.5,0,0);
        glScalef(2,.25,2);
        cube(wdr,wdg, wdb);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,-2,0);
        glScalef(.25,2,0.25);
        cube(wdr,wdg, wdb);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(1.75,-2,0);
        glScalef(.25,2,0.25);
        cube(wdr,wdg, wdb);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,-2,2);
        glScalef(.25,5,0.25);
        cube(wdr,wdg, wdb);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(1.75,-2,2);
        glScalef(.25,5,0.25);
        cube(wdr,wdg, wdb);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,2.60,2);
        glScalef(2,0.25,0.25);
        cube(wdr,wdg, wdb);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,2,2);
        glScalef(2,0.25,0.25);
        cube(wdr,wdg, wdb);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,1.40,2);
        glScalef(2,0.25,0.25);
        cube(wdr,wdg, wdb);
    glPopMatrix();


    glPushMatrix();
        glTranslatef(0,-1.5,2);
        glScalef(.25,0.25, -2);
        cube(wdr,wdg, wdb);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(1.75,-1.5,2);
        glScalef(.25,0.25, -2);
        cube(wdr,wdg, wdb);
    glPopMatrix();
}

void spotlight()
{
    glPushMatrix();
        cube(1,1,1,l2_on);
    glPopMatrix();
    glPushMatrix();
        glTranslated(0,0,-.1);
        glScalef(1.1,1.3,.1);
        cube(0,0,0);
    glPopMatrix();
    glPushMatrix();
        glTranslated(0,0,1.1);
        glScalef(1.1,1.3,.1);
        cube(0,0,0);
    glPopMatrix();
    glPushMatrix();
        glTranslated(-.1,0,0);
        glScalef(.1,1.3,1.1);
        cube(0,0,0);
    glPopMatrix();
    glPushMatrix();
        glTranslated(1.1,0,0);
        glScalef(.1,1.3,1.1);
        cube(0,0,0);
    glPopMatrix();
}

void update(int value)
{
    score+=.01;

    if(mov)
    {
        score-=.01;
    }
    else if(x==-270&&z<=270&&z>-270)
    {
        bcar=180;
        z=z-0.5;
    }
    else if(z==-270&&x<15&&x>=-270)
    {
        bcar=90;
        x+=.5;
    }
    else if(x==15&&z<-15&&z>=-270)
    {
        bcar=0;
        z+=.5;
    }
    else if(z==-15&&x<270&&x>=15)
    {
        bcar=90;
        x+=.5;

    }
    else if(x==270&&z>=-15&&z<270)
    {
        bcar=0;
        z+=.5;

    }
    else if(x>15&&z>=270&&z<467)
    {
        bcar=-45;
        z+=.25;
        x-=.25;
    }
    else if(z==467&&x<=73&&x>-73)
    {
        bcar=-90;
        x-=.5;
    }
    else if(z>270)
    {
        bcar=-135;
        z-=.25;
        x-=.25;
    }

    ///small car
    if(!mov)
    {
        x1=x1 +.5*sin ( scar * 3.1416 / 180.0 );
        z1=z1 + .5*cos(scar*3.1416/180.0);
    }
    if(mov)
    {

    }
    else if(z1<=260&&z1>=-240&&x1>=-300&&x1<=-240)
    {
        double ang=sin ( scar * 3.1416 / 180.0 );
        if(x1+30*ang>=-240)
        {
            //cout<<"k";
            x1=x1-ang;
            scar+=2;
            score-=.01;
        }
        else if(x1+34*ang<=-282)
        {
            //cout<<"l";
            x1=x1-ang;
            scar-=2;
            score-=.01;
        }

        //cout<<"k1"<<endl;
    }
    else if(z1<-240&&x1<-240)
    {
        double ang=sin ( scar * 3.1416 / 180.0 );
        if(x1+34*ang<=-282)
        {
            //cout<<"l";
            x1=x1-ang;
            scar-=2;
            score-=.01;
        }
        ang=cos ( scar * 3.1416 / 180.0 );
        if(z1+34*ang<=-282)
        {
            z1=z1-ang;
            scar-=2;
            score-=.01;
        }
        //cout<<"k2"<<endl;
    }
    else if(z1<=-240&&z1>=-282&&x1>=-240&&x1<=-10)
    {
        double ang=cos ( scar * 3.1416 / 180.0 );
        if(z1+30*ang>=-240)
        {
            //cout<<"k";
            z1=z1-ang;
            scar+=2;
            score-=.01;
        }
        else if(z1+34*ang<=-282)
        {
            //cout<<"l";
            z1=z1-ang;
            scar-=2;
            score-=.01;
        }
        //cout<<"k3"<<endl;
    }
    else if(z1<-240&&x1>-10)
    {
        double ang=sin ( scar * 3.1416 / 180.0 );
        if(x1+34*ang>=40)
        {
            //cout<<"l";
            x1=x1-ang;
            scar-=2;
            score-=.01;

        }
        ang=cos ( scar * 3.1416 / 180.0 );
        if(z1+34*ang<=-282)
        {
            //cout<<"k";
            z1=z1-ang;
            scar-=2;
            score-=.01;
        }
        //cout<<"k4"<<endl;
    }

    else if(z1<=-80&&z1>=-240&&x1>=-10&&x1<=50)
    {
        double ang=sin ( scar * 3.1416 / 180.0 );
        if(x1+30*ang<=-10)
        {
            //cout<<"k";
            x1=x1-ang;
            scar+=2;
            score-=.01;
        }
        else if(x1+34*ang>=36)
        {
            //cout<<"l";
            x1=x1-ang;
            scar-=2;
            score-=.01;
        }
        //cout<<"k5"<<endl;
    }
    else if(z1>-80&&z1<5&&x1<=50&&x1>-20)
    {
        double ang=sin ( scar * 3.1416 / 180.0 );
        if(x1+30*ang<=-10)
        {
            //cout<<"k";
            x1=x1-ang;
            scar+=2;
            score-=.01;
        }
        ang=cos ( scar * 3.1416 / 180.0 );
        if(z1+34*ang>10)
        {
            //cout<<"k";
            z1=z1-ang;
            scar+=2;
            score-=.01;
        }
        //cout<<"k6"<<endl;
    }
    else if(z1<=10&&z1>=-50&&x1>=50&&x1<=240)
    {
        double ang=cos ( scar * 3.1416 / 180.0 );
        if(z1+30*ang<=-28)
        {
            //cout<<"k";
            z1=z1-ang;
            scar-=2;
            score-=.01;
        }
        else if(z1+34*ang>=10)
        {
            //cout<<"l";
            z1=z1-ang;
            scar+=2;
            score-=.01;
        }
        //cout<<"k7"<<endl;
    }
    else if(z1<10&&x1>=240)
    {
        double ang=sin ( scar * 3.1416 / 180.0 );
        if(x1+30*ang>=282)
        {
            //cout<<"k";
            x1=x1-ang;
            scar-=2;
            score-=.01;
        }
        ang=cos ( scar * 3.1416 / 180.0 );
        if(z1+34*ang<-50)
        {
            //cout<<"k";
            z1=z1-ang;
            scar-=2;
            score-=.01;
        }
        //cout<<"k8"<<endl;
    }
    else if(z1<=270&&z1>=10&&x1>=240&&x1<=300)
    {
        double ang=sin ( scar * 3.1416 / 180.0 );
        if(x1+30*ang<=240)
        {
            //cout<<"k";
            x1=x1-ang;
            scar+=2;
            score-=.01;
        }
        else if(x1+34*ang>=282)
        {
            //cout<<"l";
            x1=x1-ang;
            scar-=2;
            score-=.01;
        }
        //cout<<"k9"<<endl;
    }
    /*else if(z1<=435&&z1>=270)
    {
        //double ang=sin ( scar * 3.1416 / 180.0 );
        if(x1-240>z1-270)
        {
            //cout<<"k";
            x1=x1-.12;
            z1=z1+.12;
            scar-=1;
            score-=.01;
        }
        /*else if(282.26-x1>z1-270)
        {
            //cout<<"l";
            z1=z1+.12;
            x1=x1-.12;
            scar+=1;
            score-=.01;
        }
        //cout<<x1<<endl;
    }*/
    else if(z1>=435&&z1<=495&&x1>=-75&&x1<=75)
    {
        double ang=cos ( scar * 3.1416 / 180.0 );
        if(z1+30*ang<=435)
        {
            //cout<<"k";
            z1=z1-ang;
            scar+=2;
            score-=.01;
        }
        else if(z1+34*ang>=477)
        {
            cout<<"l";
            z1=z1-ang;
            scar-=2;
            score-=.01;
        }
        //cout<<"k10"<<endl;
    }
    //cout<<x1<<" "<<z1<<endl;
    /*else if(z1==-270&&x1<15&&x1>=-270)
    {
        scar=90;
        x1+=.5;
    }
    else if(x1==15&&z1<-15&&z1>=-270)
    {
        scar=0;
        z1+=.5;
    }
    else if(z1==-15&&x1<270&&x1>=15)
    {
        scar=90;
        x1+=.5;

    }
    else if(x1==270&&z1>=-15&&z1<270)
    {
        scar=0;
        z1+=.5;

    }
    else if(x1>15&&z1>=270&&z1<467)
    {
        scar=-45;
        z1+=.25;
        x1-=.25;
    }
    else if(z1==467&&x1<=73&&x1>-73)
    {
        scar=-90;
        x1-=.5;
    }
    else if(z1>270)
    {
        scar=-135;
        z1-=.25;
        x1-=.25;
    }*/
    if(lokc)
    {

        eyeX=x1-10*sin ( scar * 3.1416 / 180.0 );
        lookX=x1+30*sin ( scar * 3.1416 / 180.0 );
    }
    if(lokc)
    {
        eyeZ=z1-10*cos ( scar * 3.1416 / 180.0 );
        lookZ=z1+30*cos ( scar * 3.1416 / 180.0 );
    }

    if(sqrt((x-x1)*(x-x1)+(z-z1)*(z-z1))<40)
    {
        lokc=false;
        mov=true;
    }

    /*if(mov)
    {

    }
    else if(x1==-270&&z1<=270&&z1>-270)
    {
        scar=180;
        z1=z1-0.5;
    }
    else if(z1==-270&&x1<15&&x1>=-270)
    {
        scar=90;
        x1+=.5;
    }
    else if(x1==15&&z1<-15&&z1>=-270)
    {
        scar=0;
        z1+=.5;
    }
    else if(z1==-15&&x1<270&&x1>=15)
    {
        scar=90;
        x1+=.5;

    }
    else if(x1==270&&z1>=-15&&z1<270)
    {
        scar=0;
        z1+=.5;

    }
    else if(x1>15&&z1>=270&&z1<467)
    {
        scar=-45;
        z1+=.25;
        x1-=.25;
    }
    else if(z1==467&&x1<=73&&x1>-73)
    {
        scar=-90;
        x1-=.5;
    }
    else if(z1>270)
    {
        scar=-135;
        z1-=.25;
        x1-=.25;
    }
        //cout<<x<<" "<<z<<endl;
    /*}
    else if(eyeX==-270&&eyeZ<=270&&eyeZ>-270)
    {
        bcar=180;

        eyeZ-=.5;
        lookZ=eyeZ-60;
        lookX=eyeX;
        x=eyeX;
        z=eyeZ;
    }
    else if(eyeZ==-270&&eyeX<15&&eyeX>=-270)
    {
        bcar=90;
        eyeX+=.5;
        lookZ=eyeZ;
        lookX=eyeX+60;

        x=eyeX;
        z=eyeZ;
    }
    else if(eyeX==15&&eyeZ<-15&&eyeZ>=-270)
    {
        bcar=0;
        eyeZ+=.5;
        lookZ=eyeZ+60;
        lookX=eyeX;

        x=eyeX;
        z=eyeZ;
    }
    else if(eyeZ==-15&&eyeX<270&&eyeX>=15)
    {
        bcar=90;
        eyeX+=.5;
        lookZ=eyeZ;
        lookX=eyeX+60;

        x=eyeX;
        z=eyeZ;
    }
    else if(eyeX==270&&eyeZ>=-15&&eyeZ<270)
    {
        bcar=0;
        eyeZ+=.5;
        lookZ=eyeZ+60;
        lookX=eyeX;

        x=eyeX;
        z=eyeZ;
    }
    else if(eyeX>15&&eyeZ>=270&&eyeZ<467)
    {
        bcar=-45;
        eyeZ+=.25;
        eyeX-=.25;
        lookZ=eyeZ+60;
        lookX=eyeX-60;

        x=eyeX;
        z=eyeZ;
    }
    else if(eyeZ==467&&eyeX<=73&&eyeX>-73)
    {
        bcar=-90;
        eyeX-=.5;
        lookZ=eyeZ;
        lookX=eyeX-60;

        x=eyeX;
        z=eyeZ;
    }
    else if(eyeZ>270)
    {
        bcar=-135;
        eyeZ-=.25;
        eyeX-=.25;
        lookZ=eyeZ-60;
        lookX=eyeX-60;


        x=eyeX;
        z=eyeZ;
    }*/
    glutPostRedisplay();
}


static void res(int width, int height)
{
    glViewport(0, 0, width, width/rat);
}


void light()
{
    //light
    GLfloat l_no[] = {0, 0, 0, 1.0};
    GLfloat l_amb[] = {1, 1, 1, 1.0};
    GLfloat l_dif[] = {1,1,1,1};
    GLfloat l_spec[] = {1,1,1,1};
    GLfloat l_pos[] = {0,20,0,1.0};

    glEnable(GL_LIGHT0);

    if(l1_on)
    {
        if(a)
            glLightfv(GL_LIGHT0, GL_AMBIENT, l_amb);
        else
            glLightfv(GL_LIGHT0, GL_AMBIENT, l_no);
        if(d)
            glLightfv(GL_LIGHT0, GL_DIFFUSE, l_dif);
        else
            glLightfv(GL_LIGHT0, GL_DIFFUSE, l_no);
        if(s)
            glLightfv(GL_LIGHT0, GL_SPECULAR, l_spec);
        else
            glLightfv(GL_LIGHT0, GL_SPECULAR, l_no);
    }
    else
    {
        glLightfv(GL_LIGHT0, GL_AMBIENT, l_no);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, l_no);
        glLightfv(GL_LIGHT0, GL_SPECULAR, l_no);
    }


    glLightfv(GL_LIGHT0, GL_POSITION, l_pos);

}

void allbuilding()
{

    ///center to left
    glPushMatrix();
        glTranslatef(50,0,-90);
        glScaled(1.5,1,2);
        building(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(130,0,-90);
        glScaled(1.5,1,2);
        building(3,1,.2,.2);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(210,0,-90);
        glScaled(1.5,1,2);
        building(4,1,1,.2);
    glPopMatrix();

    ///left to top
    glPushMatrix();
        glTranslatef(330,0,-45);
        glRotated(-90,0,1,0);
        glScaled(2,1,1.5);
        building(4,1,.35,.2);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(330,0,70);
        glRotated(-90,0,1,0);
        glScaled(2,1,1.5);
        building(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(330,0,190);
        glRotated(-90,0,1,0);
        glScaled(2,1,1.5);
        building(1);
    glPopMatrix();

    /// left angle to top
    glPushMatrix();
        glTranslatef(325,0,315);
        glRotated(-135,0,1,0);
        glScaled(2,1,1.5);
        building(3,1,1,.2);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(250,0,390);
        glRotated(-135,0,1,0);
        glScaled(2,1,1.5);
        building(1);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(174,0,467);
        glRotated(-135,0,1,0);
        glScaled(1.5,1,1.5);
        building(1,1,.2,.2);
    glPopMatrix();

    ///top
    glPushMatrix();
        glTranslatef(2,0,500);
        glScaled(1.8,1,2);
        building(1,1,1,.2);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-2,0,540);
        glRotated(180,0,1,0);
        glScaled(1.8,1,2);
        building(1);
    glPopMatrix();


    /// right angle to top
    glPushMatrix();
        glTranslatef(-300,0,290);
        glRotated(-45,0,1,0);
        glScaled(2,1,1.5);
        building(3,1,1,.2);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-225,0,365);
        glRotated(-45,0,1,0);
        glScaled(2,1,1.5);
        building(1,1,.2,.2);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-150,0,442);
        glRotated(-45,0,1,0);
        glScaled(1.5,1,1.5);
        building(1);
    glPopMatrix();

    ///right


    glPushMatrix();
        glTranslatef(-300,0,180);
        glRotated(-90,0,1,0);
        glScaled(2,1,1.5);
        building(1,1,1,.2);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-300,0,70);
        glRotated(-90,0,1,0);
        glScaled(2,1,1.5);
        building(4,1,.2,.2);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-300,0,-35);
        glRotated(-90,0,1,0);
        glScaled(2,1,1.5);
        building(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-300,0,-140);
        glRotated(-90,0,1,0);
        glScaled(2,1,1.5);
        building(3,1,1,.2);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-300,0,-280);
        glRotated(-90,0,1,0);
        glScaled(2.5,1,1.5);
        building(4);
    glPopMatrix();



    ///most bottom
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[2]);

        glPushMatrix();
            glTranslated(-100,0,-330);
            glScaled(150,40,30);
            cube();
        glPopMatrix();


    glDisable(GL_TEXTURE_2D);
    glFlush();

    glPushMatrix();
        glTranslated(-205,0,-330);
        glScaled(2,1,1.5);
        building(2,1,1,.2);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-310,0,-330);
        glScaled(2,1,1.5);
        building(1);
    glPopMatrix();


    ///bottom to center
    glPushMatrix();
        glTranslatef(50,0,-95);
        glRotated(90,0,1,0);
        glScaled(2,1,1.5);
        building(1,1,.2,.2);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(50,0,-200);
        glRotated(90,0,1,0);
        glScaled(2,1,1.5);
        building(3);
    glPopMatrix();



}
void ckpnt()
{
    ///points start
    glPushMatrix();
        glTranslated(0,5,0);
        glScaled(20,20,20);
        cube(1,1,1);
    glPopMatrix();

    glPushMatrix();
        glTranslated(250,5,0);
        glScaled(20,20,20);
        cube(.7,.7,.2);
    glPopMatrix();

    glPushMatrix();
        glTranslated(0,5,-250);
        glScaled(20,20,20);
        cube(1,0,0);
    glPopMatrix();

    glPushMatrix();
        glTranslated(250,5,250);
        glScaled(20,20,20);
        cube(0,1,0);
    glPopMatrix();

    glPushMatrix();
        glTranslated(-250,5,250);
        glScaled(20,20,20);
        cube(0,0,1);
    glPopMatrix();

    glPushMatrix();
        glTranslated(-250,5,-250);
        glScaled(20,20,20);
        cube(1,1,0);
    glPopMatrix();

    glPushMatrix();
        glTranslated(60,5,406);
        glScaled(20,20,20);
        cube(1,0,1);
    glPopMatrix();

    glPushMatrix();
        glTranslated(-60,5,406);
        glScaled(20,20,20);
        cube(0,1,1);
    glPopMatrix();

    ///points ends
}

void grass()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[6]);

    glPushMatrix();
        glTranslatef(-250,-.1,0);
        glScalef(500,.1,250);
        cube(1,1,1);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-250,-.1,-250);
        glScalef(250,.1,250);
        cube(1,1,1);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-125,-.1,250);
        glScalef(250,.1,250);
        cube(1,1,1);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(120,-.1,250);
        glScalef(150,.1,150);
        cube(1,1,1);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-270,-.1,250);
        glScalef(150,.1,150);
        cube(1,1,1);
    glPopMatrix();


    glDisable(GL_TEXTURE_2D);
    glFlush();
}

void alltrees()
{
    glPushMatrix();
        glTranslated(-50,0,-10);
        glScaled(10,5,10);
        tree();

    glPopMatrix();

    glPushMatrix();
        glTranslated(-75,0,100);
        glScaled(10,5,10);
        tree();

    glPopMatrix();
    glPushMatrix();
        glTranslated(75,0,100);
        glScaled(10,5,10);
        tree();

    glPopMatrix();
    glPushMatrix();
        glTranslated(140,0,280);
        glScaled(10,5,10);
        tree();

    glPopMatrix();
    glPushMatrix();
        glTranslated(-140,0,280);
        glScaled(10,5,10);
        tree();

    glPopMatrix();
    glPushMatrix();
        glTranslated(-200,0,-200);
        glScaled(10,5,10);
        tree();

    glPopMatrix();
}

void allchair()
{
    glPushMatrix();
        glTranslated(220,0,170);
        glScaled(4,4,12);
        glRotated(90,0,1,0);
        glTranslated(0,2,0);
        chair();

    glPopMatrix();
    glPushMatrix();
        glTranslated(220,0,250);
        glScaled(4,4,12);
        glRotated(90,0,1,0);
        glTranslated(0,2,0);
        chair();
    glPopMatrix();
    glPushMatrix();
        glTranslated(-220,0,230);
        glScaled(4,4,12);
        glRotated(-90,0,1,0);
        glTranslated(0,2,0);
        chair();
    glPopMatrix();
    glPushMatrix();
        glTranslated(-220,0,150);
        glScaled(4,4,12);
        glRotated(-90,0,1,0);
        glTranslated(0,2,0);
        chair();
    glPopMatrix();
}

void stwrf()
{
    glPushMatrix();
        //glTranslated(-200,0,-200);
        glScaled(25,3,15);
        cube();

    glPopMatrix();

    glPushMatrix();
        glTranslated(5,3,5);
        glScaled(15,5,5);
        cube();

    glPopMatrix();
    glPushMatrix();
        glTranslated(0,3,13);
        glScaled(25,5,2);
        cube();

    glPopMatrix();
    glPushMatrix();
        glTranslated(0,3,0);
        glScaled(25,5,2);
        cube();

    glPopMatrix();
    glPushMatrix();
        glTranslated(1,3,1);
        glScaled(.5,4,.5);
        glRotatef( 90, 0.0, 0.0, 1.0);
        rod(0,0,0);

    glPopMatrix();
    glPushMatrix();
        glTranslated(1,3,14);
        glScaled(.5,4,.5);
        glRotatef( 90, 0.0, 0.0, 1.0);
        rod(0,0,0);

    glPopMatrix();
    glPushMatrix();
        glTranslated(24,3,1);
        glScaled(.5,4,.5);
        glRotatef( 90, 0.0, 0.0, 1.0);
        rod(0,0,0);

    glPopMatrix();
    glPushMatrix();
        glTranslated(24,3,14);
        glScaled(.5,4,.5);
        glRotatef( 90, 0.0, 0.0, 1.0);
        rod(0,0,0);

    glPopMatrix();

    glPushMatrix();
        glTranslated(0,22.5,7.4);
        glRotated(30,1,0,0);
        glScaled(25,.25,8.66);
        cube();
    glPopMatrix();
    glPushMatrix();
        glTranslated(0,18,.1);
        glRotated(-30,1,0,0);
        glScaled(25,.25,8.66);
        cube();
    glPopMatrix();
    glPushMatrix();
        glTranslated(12.5,3,7.5);
        glScaled(.75,4.9,.75);
        glRotatef( 90, 0.0, 0.0, 1.0);
        rod(0,0,0);

    glPopMatrix();
    glPushMatrix();
        glTranslated(-2,-2,0);
        ///glRotated(-30,1,0,0);
        glScaled(2,2,15);
        cube();
    glPopMatrix();
    glPushMatrix();
        glTranslated(-4,-4,0);
        ///glRotated(-30,1,0,0);
        glScaled(4,2,15);
        cube();
    glPopMatrix();
    glPushMatrix();
        glTranslated(-6,-6,0);
        ///glRotated(-30,1,0,0);
        glScaled(6,2,15);
        cube();
    glPopMatrix();

    glPushMatrix();
        glTranslated(25,-2,0);
        ///glRotated(-30,1,0,0);
        glScaled(2,2,15);
        cube();
    glPopMatrix();
    glPushMatrix();
        glTranslated(25,-4,0);
        ///glRotated(-30,1,0,0);
        glScaled(4,2,15);
        cube();
    glPopMatrix();
    glPushMatrix();
        glTranslated(25,-6,0);
        ///glRotated(-30,1,0,0);
        glScaled(6,2,15);
        cube();
    glPopMatrix();
}

void lakevie()
{
    glPushMatrix();
        glTranslated(150,0,200);

        glScaled(20,5,21);
        lake1(1);

    glPopMatrix();
    glPushMatrix();
        glTranslated(-150,0,200);
        glRotatef(180,0,1,0);
        glScaled(20,5,21);
        lake1(1);
    glPopMatrix();
    glPushMatrix();
        glTranslated(0,0,200);
        glScaled(33,5,7);
        lake1(0);
    glPopMatrix();


}
static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-3, 3, -3, 3, 2.0, 1000.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX,eyeY,eyeZ, lookX,lookY,lookZ, 0,1,0);
    glViewport(0, 0, width, height);

    glRotatef(rot, 0,1,0);
    axes();

    /*glPushMatrix();
        glTranslatef(8,l_height,19);
        tubelight();
    glPopMatrix();*/
    /*glPushMatrix();
        glTranslatef(15,l2_height,0);
        spotlight();
    glPopMatrix();*/
    /*glPushMatrix();
        glTranslatef(15,7,3.5);
        circle();
    glPopMatrix();*/
    /*glPushMatrix();
        glTranslatef(-8,l_height,20);
        glScaled(.6, .6, .6);
        circle(0,0,0,l3_on);
    glPopMatrix();*/



    glPushMatrix();
        glTranslatef(0,17,0);
        glScaled(.8, .8, .8);
        glPushMatrix();
          glTranslated(1,.5,1);
            glScalef(.5,2,.5);
            cube(0,.8,0);
        glPopMatrix();
        glTranslated(1,0,1);
        glRotated(angle,0,1,0);
        glTranslated(-1,0,-1);
        fan();
    glPopMatrix();

    ///ckpnt();
    allbuilding();
    alltrees();

    glPushMatrix();
        road();
    glPopMatrix();


    ///bigcar
    glPushMatrix();
        glTranslated(x,0,z);
        glScaled(2.5,1.5,2.5);
        glRotated(bcar,0,1,0);
        glTranslated(-.5,-.5,-.5);

        bigcar();
    glPopMatrix();




    ///Sritisoudho
    glPushMatrix();
        glTranslated(0,0,130);
        glScaled(1.5,1.5,1.2);
        sriticomplx();

    glPopMatrix();

    ///car
    glPushMatrix();
        glTranslated(x1,4,z1);

        glRotated(scar,0,1,0);
        glScaled(2,1.5,2);
        car();
    glPopMatrix();



    lakevie();
    glPushMatrix();
        glTranslated(-150,0,-140);
        glScaled(15,1,70);
        cube(.5,.2,0);

    glPopMatrix();


    ///grass
    grass();
    allchair();

    glPushMatrix();
        glTranslated(0,0,300);
        glScaled(1.5,1.5,1.2);
        glRotated(180,0,1,0);
        sohidcomplx();

    glPopMatrix();
    glPushMatrix();
        glTranslated(0,7,177);
        glScaled(2,1,1.8);
        glRotatef(-90,0,1,0);
        stwrf();

    glPopMatrix();
    light();


    glutTimerFunc(25,update,0);
    glutSwapBuffers();
}



static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27 :
    case 'q':
        exit(0);
        break;
    case ',':
        rot++;
        break;
    case '.':
        rot--;
        break;
    case '6':
        lookX--;
        eyeX--;
        break;
    case '4':
        lookX++;
        eyeX++;
        break;
    case '8':
        lookZ++;
        eyeZ++;
        break;
    case '5':
        lookZ--;
        eyeZ--;
        break;
    case 'z':
        lookY++;
        eyeY++;
        break;
    case 'o':
        lookY--;
        eyeY--;
        break;
    case '1':
        l1_on=1-l1_on;
        break;
    case '2':
        l2_on=1-l2_on;
        break;
    case '3':
        l3_on=1-l3_on;
        break;
    case 'a':
        a=1-a;
        break;
    case 'm':
        mov=1-mov;
        break;
    case 'd':
        d=1-d;
        break;
    case 'v':
        eyeY = 10;
        eyeZ = -30;
        eyeX=0;
        lookX = 0;
        lookY = 0;
        lookZ = 0;
        break;
    case 'r':
        lokc=1-lokc;
        lookY=0;
        eyeY=40;
        break;
    case 't':
        eyeY = 20;
        eyeZ = z;
        eyeX = x;
        break;
    case 'b':
        eyeY = 500;
        eyeZ = -1;
        eyeX=0;
        lookX = 0;
        lookY = 0;
        lookZ = 0;
        break;
    case 's':
        s=1-s;
        break;
    case 'c':
        x=-250;
        z=250;
        break;
    case 'k':
        scar+=2;

        break;
    case 'l':
        scar-=2;
        break;

    }

    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

/* Program entry point */

void LoadTexture(const char*filename, int i)
{

    glBindTexture(GL_TEXTURE_2D, ID[i]);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID[i]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(width,height);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Game");

    glGenTextures(50, ID);

    LoadTexture("H:\\4-2\\graphics lab\\lab4\\Texture\\images\\road.bmp", 0);
    LoadTexture("H:\\4-2\\graphics lab\\lab4\\Texture\\images\\building.bmp", 1);
    LoadTexture("H:\\4-2\\graphics lab\\lab4\\Texture\\images\\waterfall.bmp", 2);
    LoadTexture("H:\\4-2\\graphics lab\\lab4\\Texture\\images\\building1.bmp", 3);
    LoadTexture("H:\\4-2\\graphics lab\\lab4\\Texture\\images\\building2.bmp", 4);
    LoadTexture("H:\\4-2\\graphics lab\\lab4\\Texture\\images\\water.bmp", 5);
    LoadTexture("H:\\4-2\\graphics lab\\lab4\\Texture\\images\\grass.bmp", 6);


    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);
    glutReshapeFunc(res);


    glEnable(GL_DEPTH_TEST);
    glShadeModel( GL_SMOOTH );
    glEnable(GL_NORMALIZE);
    glEnable(GL_BLEND);


    glEnable(GL_LIGHTING);

    printf(" Press '4' to look left \n Press '6' to look right \n press '8' to look up \n Press '5' to look down \n");
    printf(" Press ',' to move left \n Press '.' to move right \n press 'z' to zoom in \n Press 'o' to zoom out\n");
    printf(" Press '1' to off/on tubelight \n Press '2' to off/on spotlight \n");
    printf(" Press 'a' to off/on ambient  \n Press 'd' to off/on diffuse \n Press 's' to off/on specular \n");
    printf(" Press 'k' to rotate the car left \n Press 'l' to rotate the car right \n Press 'r' to follow the car \n press 'b' to back to top view \n");
    printf(" Press 'm' to move/pause the game \n");
    printf(" Press 'q' to quit \n");

    glutMainLoop();

    return EXIT_SUCCESS;
}
