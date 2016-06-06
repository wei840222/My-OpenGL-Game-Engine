#include <iostream>  
#include <GL/glut.h>  
#include "header.h"  

using namespace std;

//�����]�w
const int windowSizeW = 600, windowSizeH = 600;
const char windowName[] = "My OpenGL Game Engine";

//�ƹ��즲�e������
int mouseClick_x = 0, mouseClick_y = 0, mouseMotion_x = 0, mouseMotion_y = 0;

//�ʵe����(�@��)
bool animationPlay = true;
int animationDelay = 5;
float t = 0;

//ø�Ϫ���
Color red(1, 0, 0), green(0, 1, 0), blue(0, 0, 1);
Point o(0, 0, 0);
Vector x(150, 0, 0), y(0, 150, 0), z(0, 0, 150);
Line X(o, x), Y(o, y), Z(o, z);

//�ߪ���B��
Point start(0, 50, 0);
Vector speed(0, 0, 0);
Vector acceleration(0, 0, 0);


void Display() {
	//�M���C��w�İ�
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPushMatrix();
	//�B�z�e������
	glRotatef(mouseMotion_y, 1.0, 0.0, 0.0);
	glRotatef(mouseMotion_x, 0.0, 1.0, 0.0);

	//X Y Z�b
	glLineWidth(2);
	X.draw(red); Y.draw(green); Z.draw(blue);

	//�שY
	glLineWidth(1);
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 50, 0);
	glVertex3f(85, 0, 0);
	glEnd();

	//�����O�U�ƹB��
	glColor3f(0, 0, 0);
	glPushMatrix();
	AccelerationMoving(start, speed, Friction(30), t);
	glutSolidCube(5);
	glPopMatrix();

	glPopMatrix();
	//�洫�w�İ�
	glutSwapBuffers();
}

void AnimationTimer(int id) {
	if (animationPlay) {
		t < 50 ? t+=0.01 : t = 0;
	}
	glutPostRedisplay();
	glutTimerFunc(animationDelay, AnimationTimer, 1);
}

void MouseClick(int button, int state, int x, int y) {
	mouseClick_x = x;
	mouseClick_y = y;
	glutPostRedisplay();
}

void MouseMotion(int x, int y) {
	mouseMotion_x = x - mouseClick_x;
	mouseMotion_y = y - mouseClick_y;
	glutPostRedisplay();
}

void SpecialKeyPress(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		glutPostRedisplay();
		break;
	}
}

void GLInitialize() {
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50, 200, -50, 200, -50, 200);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(1, 1, 1, 1);
}

int main() {
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(windowSizeW, windowSizeH);
	glutCreateWindow(windowName);
	glutMouseFunc(MouseClick);
	glutMotionFunc(MouseMotion);
	glutSpecialFunc(SpecialKeyPress);
	glutDisplayFunc(Display);
	glutTimerFunc(animationDelay, AnimationTimer, 1);

	GLInitialize();
	glutMainLoop();
	return 0;
}