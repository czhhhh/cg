


////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Specification:
//   Display a 31 x 31 quadrilateral mesh for PLANE in perspective projection.
//   Added an axis-angle rotation user-interface, such that the mesh can be rotated by draging the screen.
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "glut.h"

//////////////////////////////////////////////////////////////////
// 
// Include the header file of our rotation user-interface.
// 
#include "gsrc.h"
// 
//////////////////////////////////////////////////////////////////

#define PI 3.141592654
#define GRIDSIZE 31
#define WIN_POSX   50
#define WIN_POSY   100
#define WIN_WIDTH  400
#define WIN_HEIGHT 300

double x, y, z;
double t_prev;
GLUquadricObj *pObj2, *pObj3, *pObj4;
GLUquadricObj *pObj1;
double position;
double rotation;

typedef struct point { // define a structure for 3D point (x, y, z)
	GLfloat x;
	GLfloat y;
	GLfloat z;
} vertex;

vertex mesh[GRIDSIZE][GRIDSIZE];           // define a mesh whose elements are 3D point (x, y, z)
//31 * 31

void calculateplane(void)
// calculate the parameters of the plane mesh  ���벻ͬ��������ͬ����״
{
	for (int i = 0; i < GRIDSIZE; i++)
		for (int j = 0; j < GRIDSIZE; j++)  //-1 �� 1 
		{
			mesh[i][j].x = 2 * float(i) / (GRIDSIZE - 1) - 1;
			mesh[i][j].y = 2 * float(j) / (GRIDSIZE - 1) - 1;
			mesh[i][j].z = 0;  //1:�ĳɸ���1 - x2 - y2  �ǲ�����ʽ ������       2��
		}
}

void draw_neck() {
	glColor3f(1, 0, 0);
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	gluCylinder(pObj1, 0.15, 0.15, 0.1, 10, 10);
	glPopMatrix();
}
void draw_rightHand() {
	
	glColor3f(1, 0, 1);
	glPushMatrix();
	glRotatef(rotation, 1, 0, 0);
	glTranslatef(0.35, 0.3, 0);

	glPushMatrix();
	glTranslatef(-0.08, -0.1, 0);
	glutSolidSphere(0.1, 31, 31);

	glPopMatrix();
	glPushMatrix();

	glTranslatef(0, -0.3, 0);

	glScalef(0.1, 0.5, 0.1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -0.6, 0);
	
	glutSolidSphere(0.1, 31, 31);
	glPopMatrix();

	glTranslatef(0, -0.7, 0);

	glScalef(0.01, 0.02, 0.01);
	glutSolidCube(3);


	glPopMatrix();
}

void draw_leftHand() {
	glPushMatrix();
 
	glColor3f(1, 0, 0);
	glTranslatef(-0.2, 0, 0);

	gluCylinder(pObj1, 0.3, 0.2, 0.1, 10, 10);
	glPopMatrix();
}
void draw_bodyAndrightLegs() {
	glTranslatef(0, -0.1, 0);
	glPushMatrix();
	
	glColor3f(1, 0, 0);
	glScalef(0.6, 0.8, 0.3);
	glutSolidCube(1);
	glPopMatrix();

	glTranslatef(0, -0.7, 0);

	glColor3f(1, 1, 0);
	glPushMatrix();
	glScalef(0.6, 0.6, 0.1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.2, -0.45, 0);
	glPushMatrix();
	glScalef(0.1, 0.5, 0.1);
	glutSolidCube(1);
	glPopMatrix();
	glTranslatef(0, -0.35, 0);

	glutSolidSphere(0.1, 31, 31);
	glPopMatrix();
	glPopMatrix();

}

void draw_leftLeg() {

	
	glTranslatef(0, position, 0);
	glPushMatrix();
	
	glScalef(0.1, 0.5, 0.1);
	glutSolidCube(1);

	glPopMatrix();
	glTranslatef(0, -0.35, 0);

	glutSolidSphere(0.1, 31, 31);
}


void displayobject(void)
{
	int i, j;
	int K = GRIDSIZE - 1;

	//////////////////////////////////////////////////////////////////
	// 
	// Setup perspective projection and the rotation
	// 
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport); // viewport is by default the display window
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, double(viewport[2]) / viewport[3], 0.1, 10);  //2D iamge
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 7, 0, 0, 0, 0, 1, 0); //camera ����̫��ͻؿ���ȫ
	glMultMatrixf(gsrc_getmo());  // get the rotation matrix from the rotation user-interface   �����������ת
  //
  //////////////////////////////////////////////////////////////////


	/*  Enable Z buffer method for visibility determination. */
	//  Z buffer code starts

	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	// Z buffer code ends */

	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);  // Clear display window.

	  // Set line segment color to red.
	// Advice: draw as few lines as possible. Eliminate all redundant drawing.


	glTranslatef(x, y, 0);





	glColor3f(0, 1, 0);
	glPushMatrix();
	glutSolidSphere(0.2, 31, 31);

	glPopMatrix();
	glTranslatef(0, -0.25, 0);
	//neck
	draw_neck();

	glTranslatef(0, -0.3, 0);
	//right hand
	draw_rightHand();
	//left hand
	draw_leftHand();
	//body	//right legs
	draw_bodyAndrightLegs();




	glTranslatef(-0.2, -0.45, 0);

	//left leg
	draw_leftLeg();


	

	glutSwapBuffers(); //����ͼ�񻺴��� ���ཻ��ͼ���ݱ���� ��������������������� �����Żᶯ����

}
void animate(void)
// this animation function will swing theta from 0 deg. to 90 deg. in 1 seconds, then stop at 90 deg.
{
	double	t;
	double swing_angle = -90;                  // 90 degrees
	double swing_positionup = 0.6;
	double swing_time = 1000.0;				 // 1000 ms
	double swingPosition_time = 4000.0;
	t = glutGet(GLUT_ELAPSED_TIME) - t_prev;            // return elapsed time in ms since the last call  

	if (t < swing_time)
	{


		rotation = swing_angle * (1 - pow(cos(PI * t / (2 * swing_time)), 1));
		position = swing_positionup;
	}
	else
		rotation = swing_angle;                     // stop at swing_angle
	if (t< 1000) {
		position = swing_positionup* (1 - pow(cos(PI * t /( swing_time)), 1));
	}
	else if(t > 1000&&t< 2000) {
		position = swing_positionup * (1 - pow(cos(PI * t /(swing_time)), 1));
	}
	
	else
	
		position = 0;
	glutPostRedisplay();
}

void main(int argc, char** argv)
{

	calculateplane();   // calculate data for the planar mesh

	glutInit(&argc, argv);  //��ʼ��glut��                                    // Initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  // Set display mode.
	glutInitWindowPosition(WIN_POSX, WIN_POSY);                // Set display-window position at (WIN_POSX, WIN_POSY) 
																 // where (0, 0) is top left corner of monitor screen
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);		           // Set display-window width and height.
	glutCreateWindow("OpenGL Program for Quadrilateral Mesh"); // Create display window.

	//////////////////////////////////////////////////////////////////
	// 
	// Register mouse-click and mouse-move glut callback functions
	// for the rotation user-interface.
	// 
 
	printf("Type                                              \n");
	printf("0 : Initial position							   \n");
	printf("w : translate up           \n");
	printf("s : translate down      \n");
	printf("a : translate left    \n");
	printf("d : translate right   \n");




	glutMouseFunc(gsrc_mousebutton);
	glutMotionFunc(gsrc_mousemove);
	t_prev = glutGet(GLUT_ELAPSED_TIME);
	//
	//////////////////////////////////////////////////////////////////
	pObj1 = gluNewQuadric();
	glutIdleFunc(animate);
	glutDisplayFunc(displayobject);	 // Send planar mesh to display window.
	glutMainLoop();			               // Display everything and wait.
}

