#include <iostream>  
#include <GL/glut.h>  
#include "header.h"  

using namespace std;

//�ƹ��즲�e������
int mouseClick_x = 0, mouseClick_y = 0, mouseMotion_x = 0, mouseMotion_y = 0;

//�ʵe����
bool animationPlay = true;
int animationDelay = 10;
float t = 0;

//ø�Ϫ���
Point O(0, 0, 0), Q1(10, 0, 0);
Vector X(1, 0, 0), Y(0, 1, 0), Z(0, 0, 1);
Quaternion q1(90, X), q2(90, Y);


void CommandIO() {
	system("CLS");
}

void Display() {
	//�M���C��w�İ�
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	//�B�z�e������
	glRotatef(mouseMotion_y, 1.0, 0.0, 0.0);
	glRotatef(mouseMotion_x, 0.0, 1.0, 0.0);

	//�|���Ƥ���
	Quaternion q3 = slerp(t, q1, q2);
	q3.apply(Q1);
	//�e����
	glColor3f(0.2, 0.7, 0.1);
	glutWireTeapot(50);


	glPopMatrix();
	//�洫�w�İ�
	glutSwapBuffers();
}

void AnimationTimer(int id) {
	if (animationPlay) {
		t += 0.01;
		if (t > 1)
			animationPlay = false;
	}
	else {
		t -= 0.01;
		if (t < 0)
			animationPlay = true;
	}
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

void Initialize() {
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glEnable(GL_DEPTH_TEST);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(600, 50);
	glutCreateWindow("My OpenGL Game Engine");
	glOrtho(-100, 100, -100, 100, -100, 100);
	glClearColor(1, 1, 1, 1);
	glutMouseFunc(MouseClick);
	glutMotionFunc(MouseMotion);
	glutSpecialFunc(SpecialKeyPress);
	glutDisplayFunc(Display);
	glutIdleFunc(Display);
	glutTimerFunc(animationDelay, AnimationTimer, 1);
}

int main() {
	CommandIO();
	Initialize();
	glutMainLoop();
	return 0;
}