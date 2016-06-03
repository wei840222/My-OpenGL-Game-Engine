#include <iostream>
#include <GL/glut.h>
#include "header.h"

using namespace std;

int old_x = 0, old_y = 0;
GLfloat spin_x = 0, spin_y = 0;

Color red(1, 0, 0), green(0, 1, 0), blue(0, 0, 1);
Point O(0, 0, 0), cube(0, 20, 0);
Vector N(0, 1, 0), V(0, 40, 0);
Line L(O, V);
Plane P(O, N);

////////////////��l��////////////////
void Initialize() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50, 50, -50, 50, -50, 50);
	glMatrixMode(GL_MODELVIEW);
}

////////////////��ܭp�⵲�G////////////////
void ShowData() {
	system("CLS");
	cout << "cube(" << cube.x << ", " << cube.y << ", " << cube.z << ")" << endl;
	cout << "CollisionPoint(" << collisionPoint(L, P).x << ", " << collisionPoint(L, P).y << ", " << collisionPoint(L, P).z << ")" << endl;
}

////////////////�yø�e��////////////////
void Display() {
	glClearColor(1, 1, 1, 1);				//���z���¦�I��
	glClear(GL_COLOR_BUFFER_BIT);			//�M�z�C��w�İ�

											//�e������
	glPushMatrix();
	glTranslatef(-0.5, 0, 0);
	glRotatef(spin_y, 1.0, 0.0, 0.0);
	glRotatef(spin_x, 0.0, 1.0, 0.0);


	//����
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex3f(10, 0, 10);
	glVertex3f(-10, 0, 10);
	glVertex3f(-10, 0, -10);
	glVertex3f(10, 0, -10);
	glEnd();

	//�u
	L.draw(green);

	//���
	glPushMatrix();
	glColor3f(0, 0, 1);
	glTranslatef(0, cube.y, 0);
	glutSolidCube(1);
	glPopMatrix();

	//��s�e��
	glPopMatrix();
	glFlush();
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
		if (cube.y < 40)
			cube.y++;
		glutPostRedisplay();
		ShowData();
		break;
	case GLUT_KEY_DOWN:
		if (cube.y != collisionPoint(L, P).y)
			cube.y--;
		glutPostRedisplay();
		ShowData();
		break;
	}
}

int main() {
	glutInitWindowSize(800, 600);					//�������e
	glutInitWindowPosition(400, 300);				//�������W������m
	glutCreateWindow("My OpenGL Projects");			//�إߵ����å��W���D

	Initialize();
	ShowData();
	//�U���T�ӻPCallback�禡����
	glutMouseFunc(MouseClick);						//�ƹ����U
	glutMotionFunc(MouseMotion);					//�ƹ��즲
	glutSpecialFunc(SpecialKeyPress);				//�B�z����
	glutDisplayFunc(Display);						//�t�d�yø
	glutMainLoop();									//�i�J�D�j��
	return 0;
}