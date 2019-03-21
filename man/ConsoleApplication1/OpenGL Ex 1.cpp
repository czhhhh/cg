


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
GLUquadricObj *pObj2, *pObj3, *pObj4;
GLUquadricObj *pObj1;

typedef struct point { // define a structure for 3D point (x, y, z)
	GLfloat x;
	GLfloat y;
	GLfloat z;
} vertex;

vertex mesh[GRIDSIZE][GRIDSIZE];           // define a mesh whose elements are 3D point (x, y, z)
//31 * 31

void calculateplane(void)
// calculate the parameters of the plane mesh  输入不同参数画不同的形状
{
	for (int i = 0; i < GRIDSIZE; i++)
		for (int j = 0; j < GRIDSIZE; j++)  //-1 到 1 
		{
			mesh[i][j].x = 2 * float(i) / (GRIDSIZE - 1) - 1;
			mesh[i][j].y = 2 * float(j) / (GRIDSIZE - 1) - 1;
			mesh[i][j].z = 0;  //1:改成根号1 - x2 - y2  非参数形式 有问题       2：
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
	glPushMatrix();
	glScalef(0.1, 0.5, 0.1);
	glutSolidCube(1);
	glPopMatrix();

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
	gluLookAt(0, 0, 7, 0, 0, 0, 0, 1, 0); //camera 物体太大就回看不全
	glMultMatrixf(gsrc_getmo());  // get the rotation matrix from the rotation user-interface   可以用鼠标旋转
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


	glTranslatef(0, -0.35, 0);

	glutSolidSphere(0.1, 31, 31);

	glutSwapBuffers(); //两个图像缓存区 互相交替图像演变过程 这个方法用来交换缓存区 动画才会动起来

}

void drawing(GLubyte key, GLint xMouse, GLint yMouse)
{
	/* simple animation can be achieved by repeating key tabs */

	switch (key) {
	case 'w':		 y = y + 1;
		break;
	case 's':		y = y - 1;
		break;
	case 'a':		x = x - 1;
		break;
	case 'd':		x = x + 1;
		break;
	case '0':		x = 0; y = 0;
		break;

	default:		printf("invalid choices!");
	}

	glutPostRedisplay();                   // redisplay the modified object

}

void main(int argc, char** argv)
{

	calculateplane();   // calculate data for the planar mesh

	glutInit(&argc, argv);  //初始化glut包                                    // Initialize GLUT
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
	glutKeyboardFunc(drawing);
	printf("Type                                              \n");
	printf("0 : Initial position							   \n");
	printf("w : translate up           \n");
	printf("s : translate down      \n");
	printf("a : translate left    \n");
	printf("d : translate right   \n");




	glutMouseFunc(gsrc_mousebutton);
	glutMotionFunc(gsrc_mousemove);
	x = y = z = 0;
	//
	//////////////////////////////////////////////////////////////////
	pObj1 = gluNewQuadric();

	glutDisplayFunc(displayobject);	 // Send planar mesh to display window.
	glutMainLoop();			               // Display everything and wait.
}

