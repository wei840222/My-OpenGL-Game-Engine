#include <iostream>
#include <GL/glut.h>
#include "header.h"

using namespace std;

int old_x = 0, old_y = 0, spin_x = 0, spin_y = 0;

bool animationPlay = true;
int animationDelay = 20;
float t = 0;

Point O(0, 0, 0), Q1(50, 0, 0), Q2(0, 50, 0);
Vector X(1, 0, 0), Y(0, 1, 0), Z(0, 0, 1);

Quaternion q1(X, 90), q2(Z, 90);

void CommandIO() {
	//�R�O�C��T
	system("CLS");
}

void Display() {
	////�yø�e��
	//�M�z�C��w�İ�
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//�O�s��e�ҫ����ϯx�}
	glPushMatrix();
	//�e������
	glRotatef(spin_y, 1.0, 0.0, 0.0);
	glRotatef(spin_x, 0.0, 1.0, 0.0);

	//�|���Ʊ���
	Quaternion q3 = slerp(t, q1, q2);
	q3.apply();
	//����
	glColor3f(0.2, 0.7, 0.1);
	glutWireTeapot(50);

	//�u�X���
	glPopMatrix();

	//�洫�w�İ�
	glutSwapBuffers();
}

void AnimationTimer(int id) {
	//�ʵe
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
	////����ƹ����U
	old_x = x;
	old_y = y;
	glutPostRedisplay();
}

void MouseMotion(int x, int y) {
	////����ƹ��즲
	spin_x = x - old_x;
	spin_y = y - old_y;
	glutPostRedisplay();
}

void SpecialKeyPress(int key, int x, int y) {
	//�����L���U
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
	//�ϧΪ�l��
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glEnable(GL_DEPTH_TEST);							//�}�Ҳ`�״���
	glutInitWindowSize(600, 600);						//�������e
	glutInitWindowPosition(600, 50);					//�������W������m
	glutCreateWindow("My OpenGL Projects");				//�إߵ����å��W���D
	glOrtho(-100, 100, -100, 100, -100, 100);			//�e���d��
	glClearColor(1, 1, 1, 1);							//�I����
	glutMouseFunc(MouseClick);							//�ƹ����U
	glutMotionFunc(MouseMotion);						//�ƹ��즲
	glutSpecialFunc(SpecialKeyPress);					//�B�z����
	glutDisplayFunc(Display);							//�t�d�yø
	glutIdleFunc(Display);								//�t�d�ʵe
	glutTimerFunc(animationDelay, AnimationTimer, 1);	//�ʵe����ɶ�
}

int main() {
	CommandIO();		//��ܩR�O�C���
	Initialize();		//�ϧΪ�l��
	glutMainLoop();		//�i�J�D�j��
	return 0;
}