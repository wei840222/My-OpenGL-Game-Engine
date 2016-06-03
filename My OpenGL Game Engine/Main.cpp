#include <iostream>
#include <GL/glut.h>
#include "header.h"

using namespace std;

int old_x = 0, old_y = 0;
GLfloat spin_x = 0, spin_y = 0;

Point P1(0, 0, 0), P2(0, 40, 0), P3(20, 20, 20), P4(0, 0, 40);
Vector T1(100, 0, 0), T2(-100, 0, 0);
hermiteCurves cubeHC(P1, P2, T1, T2);
bezierCurves cubeBC(P1, P2, P3, P4);
catmullRomSpline cubeCC(P1, P2, P3, P4);
float t = 0;
bool go = true;

////////////////��l��////////////////
void Initialize() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50, 50, -50, 50, -50, 50);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(1, 1, 1, 1);
}

////////////////�R�O�C��T////////////////
void Showdata() {
	system("CLS");
	printf("hermiteCurves:\nX: %f Y: %f Z: %f\n", cubeHC.parameter(t).x, cubeHC.parameter(t).y, cubeHC.parameter(t).z);
	printf("bezierCurves:\nX: %f Y: %f Z: %f\n", cubeBC.parameter(t).x, cubeBC.parameter(t).y, cubeBC.parameter(t).z);
	printf("catmullRomSpline:\nX: %f Y: %f Z: %f\n", cubeCC.parameter(t).x, cubeCC.parameter(t).y, cubeCC.parameter(t).z);
}

////////////////�yø�e��////////////////
void Display() {
	//�M�z�C��w�İ�
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//�O�s��e�ҫ����ϯx�}
	glPushMatrix();
	//�e������
	glTranslatef(-0.5, 0, 0);
	glRotatef(spin_y, 1.0, 0.0, 0.0);
	glRotatef(spin_x, 0.0, 1.0, 0.0);

	//hermiteCurves���
	glPushMatrix();
	glColor3f(0, 0, 1);
	glTranslatef(cubeHC.parameter(t).x, cubeHC.parameter(t).y, cubeHC.parameter(t).z);
	glutSolidCube(1);
	glPopMatrix();

	//bezierCurves���
	glPushMatrix();
	glColor3f(0, 1, 0);
	glTranslatef(cubeBC.parameter(t).x, cubeBC.parameter(t).y, cubeBC.parameter(t).z);
	glutSolidCube(1);
	glPopMatrix();

	//catmullRomSpline���
	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslatef(cubeCC.parameter(t).x, cubeCC.parameter(t).y, cubeCC.parameter(t).z);
	glutSolidCube(1);
	glPopMatrix();

	//�u�X���
	glPopMatrix();
	//��ܩR�O�C���
	Showdata();
	//�洫�w�İ�
	glutSwapBuffers();
	//�N�J�Ѽ�
	if (go) {
		t += 0.01;
		if (t > 1)
			go = false;
	}
	else {
		t -= 0.01;
		if (t < 0)
			go = true;
	}
}

////////////////����ƹ����U////////////////
void MouseClick(int button, int state, int x, int y) {
	old_x = x;
	old_y = y;
	glutPostRedisplay();
}

////////////////����ƹ��즲////////////////
void MouseMotion(int x, int y) {
	spin_x = x - old_x;
	spin_y = y - old_y;
	glutPostRedisplay();
}

////////////////�����L���U////////////////
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

int main() {
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glEnable(GL_DEPTH_TEST);						//�}�Ҳ`�״���
	glutInitWindowSize(800, 600);					//�������e
	glutInitWindowPosition(400, 300);				//�������W������m
	glutCreateWindow("My OpenGL Projects");			//�إߵ����å��W���D

	Initialize();
	glutMouseFunc(MouseClick);						//�ƹ����U
	glutMotionFunc(MouseMotion);					//�ƹ��즲
	glutSpecialFunc(SpecialKeyPress);				//�B�z����
	glutDisplayFunc(Display);						//�t�d�yø
	glutIdleFunc(Display);							//�t�d�ʵe
	glutMainLoop();									//�i�J�D�j��
	return 0;
}