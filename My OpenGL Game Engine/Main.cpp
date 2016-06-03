#include <iostream>
#include <GL/glut.h>
#include "header.h"

using namespace std;

int old_x = 0, old_y = 0;
GLfloat spin_x = 0, spin_y = 0;

Color red(1, 0, 0), green(0, 1, 0), blue(0, 0, 1);
Point o(0, 0, 0);
Vector u(1, 2, 3), v(10, 10, 10);

Vector V[3] = { { 1, 2, 3 },{ 4, 5, 6 },{ 7, 8, 9 } };
Matrix3x3 M(V[0], V[1], V[2]);

void Initialize() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-20, 20, -20, 20, -20, 20);
	glMatrixMode(GL_MODELVIEW);
}

////////////////�yø�e��////////////////
void Display() {
	glClearColor(0, 0, 0, 1);				//���z���¦�I��
	glClear(GL_COLOR_BUFFER_BIT);			//�M�z�C��w�İ�

	glPushMatrix();
	glTranslatef(-0.5, 0, 0);
	glRotatef(spin_y, 1.0, 0.0, 0.0);
	glRotatef(spin_x, 0.0, 1.0, 0.0);

	//ø��
	Line lu(o, u), lv(o, v), luvCN(o, cross(u, v).normalize());
	lu.draw(red);
	lv.draw(green);
	luvCN.draw(blue);

	glutWireCube(20);

	glPopMatrix();
	glFlush();								//��s�e��
}

////////////////����ƹ����U////////////////
void MouseClick(int button, int state, int x, int y) {
	old_x = x;
	old_y = y;
	Display();
}

////////////////����ƹ��즲////////////////
void MouseMotion(int x, int y) {
	spin_x = x - old_x;
	spin_y = y - old_y;
	Display();
}

////////////////��ܭp�⵲�G////////////////
void ShowData() {
	//�V�q�B���
	cout << "Practice 1: " << u.length() << endl;
	cout << "length u: " << u.length() << endl;
	cout << "length v: " << v.length() << endl;
	cout << "normalize u: " << u.normalize().i << ' ' << u.normalize().j << ' ' << u.normalize().k << endl;
	cout << "normalize v: " << v.normalize().i << ' ' << v.normalize().j << ' ' << v.normalize().k << endl;
	cout << "dot product u.v: " << dot(u, v) << endl;
	cout << "cross product uxv: " << cross(u, v).i << ' ' << cross(u, v).j << ' ' << cross(u, v).k << endl;
	//�x�}�B���
	cout << "\nPractice 2: " << endl;
	cout << "M = " << endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
			cout << M.element[i][j] << ' ';
		cout << endl;
	}
	cout << "M cofactor (1,0) = " << M.cofactor(1, 0) << endl;
	cout << "M's det = " << M.det() << endl;
	if (M.det() == 0)
		cout << "M is singular !" << endl;
	else {
		Matrix3x3 Mi = M.inverse();
		cout << "M is invertible !" << endl;
		cout << "M's inverse = " << endl;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++)
				cout << Mi.element[i][j] << ' ';
			cout << endl;
		}
	}
}


int main() {
	glutInitWindowSize(400, 300);					//�������e
	glutInitWindowPosition(400, 300);				//�������W������m
	glutCreateWindow("My OpenGL Projects");			//�إߵ����å��W���D

	Initialize();
	ShowData();
	//�U���T�ӻPCallback�禡����
	glutMouseFunc(MouseClick);						//�ƹ����U
	glutMotionFunc(MouseMotion);					//�ƹ��즲
	glutDisplayFunc(Display);						//�t�d�yø
	glutMainLoop();									//�i�J�D�j��
	return 0;
}