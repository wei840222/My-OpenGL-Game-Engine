#ifndef _Header_H_
#define _Header_H_

#include <math.h>
#include <GL/glut.h>

const float PI = 3.14159265359;

class Vector {
public:
	float i, j, k;
	Vector() {
		i = 0;
		j = 0;
		k = 0;
	}
	Vector(float i, float j, float k) {
		this->i = i;
		this->j = j;
		this->k = k;
	}
	Vector operator+(Vector V) {
		Vector U;
		U.i = i + V.i;
		U.j = j + V.j;
		U.k = k + V.k;
		return U;
	}
	Vector operator-(Vector V) {
		Vector U;
		U.i = i - V.i;
		U.j = j - V.j;
		U.k = k - V.k;
		return U;
	}
	Vector operator*(float t) {
		Vector V;
		V.i = t*i;
		V.j = t*j;
		V.k = t*k;
		return V;
	}
	float length() {
		return sqrt(pow(i, 2) + pow(j, 2) + pow(k, 2));
	}
	Vector normalize() {
		Vector N;
		if (length() <= 0)
			return *this;
		else {
			N.i = i / length();
			N.j = j / length();
			N.k = k / length();
			return N;
		}
	}
};
float dot(Vector U, Vector V) {
	return U.i*V.i + U.j*V.j + U.k*V.k;
}
Vector cross(Vector U, Vector V) {
	Vector C;
	C.i = U.j*V.k - U.k*V.j;
	C.j = U.k*V.i - U.i*V.k;
	C.k = U.i*V.j - U.j*V.i;
	return C;
}

class Quaternion {
public:
	float s;
	Vector v;
	Quaternion() {
		s = 0;
	}
	Quaternion(float w, float x, float y, float z) {
		s = w;
		v.i = x;
		v.j = y;
		v.k = z;
	}
	Quaternion(Vector v, float a) {
		s = cos(a*PI / 360);
		this->v = v*sin(a*PI / 360);
	}
	Quaternion operator+(Quaternion q) {
		Quaternion Q;
		Q.s = s + q.s;
		Q.v = v + q.v;
		return Q;
	}
	Quaternion operator-(Quaternion q) {
		Quaternion Q;
		Q.s = s - q.s;
		Q.v = v - q.v;
		return Q;
	}
	Quaternion operator*(Quaternion q) {
		Quaternion Q;
		Q.s = s*q.s - dot(v, q.v);
		Q.v = q.v*s + v*q.s + cross(v, q.v);
		return Q;
	}
	float length() {
		return sqrt(pow(s, 2) + pow(v.length(), 2));
	}
	Quaternion normalize() {
		Quaternion Q;
		Q.s = s / length();
		Q.v = v*(1 / length());
		return Q;
	}
	Quaternion conjugate() {
		Quaternion Q;
		Q.s = s;
		Q.v = v*(-1);
		return Q;
	}
	Quaternion inverse() {
		Quaternion Q;
		Q.s = s / pow(length(), 2);
		Q.v = v*(-1)*(1 / pow(length(), 2));
		return Q;
	}
	void apply() {
		float m[16] = { 1 - 2 * (v.j*v.j + v.k*v.k), 2 * (v.i*v.j - s*v.k), 2 * (v.i*v.k + s*v.j), 0,
			2 * (v.i*v.j + s*v.k), 1 - 2 * (v.i*v.i + v.k*v.k), 2 * (v.j*v.k - s*v.i), 0,
			2 * (v.i*v.k - s*v.j), 2 * (v.j*v.k + s*v.i), 1 - 2 * (v.i*v.i + v.j*v.j), 0,
			0,0,0,1 };
		glMultMatrixf(m);
	}
};
float dot(Quaternion Q1, Quaternion Q2) {
	return Q1.s*Q2.s + Q1.v.i*Q2.v.i + Q1.v.j*Q2.v.j + Q1.v.k*Q2.v.k;
}
Quaternion lerp(float t, Quaternion Q1, Quaternion Q2) {
	Quaternion Q3;
	Q3.s = (1 - t)*Q1.s + t*Q2.s;
	Q3.v.i = (1 - t)*Q1.v.i + t*Q2.v.i;
	Q3.v.j = (1 - t)*Q1.v.j + t*Q2.v.j;
	Q3.v.k = (1 - t)*Q1.v.k + t*Q2.v.k;
	return Q3;
}
Quaternion slerp(float t, Quaternion Q1, Quaternion Q2) {
	Quaternion Q3;
	float Deg = acos(dot(Q1, Q2));
	Q3.s = sin((1 - t)*Deg)*Q1.s / sin(Deg) + sin(t*Deg)*Q2.s / sin(Deg);
	Q3.v.i = sin((1 - t)*Deg)*Q1.v.i / sin(Deg) + sin(t*Deg)*Q2.v.i / sin(Deg);
	Q3.v.j = sin((1 - t)*Deg)*Q1.v.j / sin(Deg) + sin(t*Deg)*Q2.v.j / sin(Deg);
	Q3.v.k = sin((1 - t)*Deg)*Q1.v.k / sin(Deg) + sin(t*Deg)*Q2.v.k / sin(Deg);
	return Q3;
}

class Matrix2x2 {
public:
	float  element[2][2];
	Matrix2x2() {
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				element[i][j] = 0;
	}
	Matrix2x2(float a, float b, float c, float d) {
		element[0][0] = a;
		element[0][1] = b;
		element[1][0] = c;
		element[1][1] = d;
	}
	Matrix2x2 operator+(Matrix2x2 M) {
		Matrix2x2 N;
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				N.element[i][j] = element[i][j] + M.element[i][j];
		return N;
	}
	Matrix2x2 operator-(Matrix2x2 M) {
		Matrix2x2 N;
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				N.element[i][j] = element[i][j] - M.element[i][j];
		return N;
	}
	Matrix2x2 operator*(Matrix2x2 M) {
		Matrix2x2 N;
		N.element[0][0] = element[0][0] * M.element[0][0] + element[0][1] * M.element[1][0];
		N.element[0][1] = element[0][0] * M.element[0][1] + element[0][1] * M.element[1][1];
		N.element[1][0] = element[1][0] * M.element[0][0] + element[1][1] * M.element[1][0];
		N.element[1][1] = element[1][0] * M.element[0][1] + element[1][1] * M.element[1][1];
		return N;
	}
	Matrix2x2 operator*(float f) {
		Matrix2x2 N;
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				N.element[i][j] = element[i][j] * f;
		return N;
	}
	float det() {
		return element[0][0] * element[1][1] - element[1][0] * element[0][1];
	}
	Matrix2x2 inverse() {
		float D = det();
		if (D == 0)
			return *this;
		else {
			Matrix2x2 M;
			M.element[0][0] = element[1][1] / D;
			M.element[1][1] = element[0][0] / D;
			M.element[0][1] = -element[0][1] / D;
			M.element[1][0] = -element[1][0] / D;
			return M;
		}
	}
};

class Matrix3x3 {
public:
	float element[3][3];
	Matrix3x3() {
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				element[i][j] = 0;
	}
	Matrix3x3(float a, float b, float c, float d, float e, float f, float g, float h, float i) {
		element[0][0] = a;
		element[0][1] = b;
		element[0][2] = c;
		element[1][0] = d;
		element[1][1] = e;
		element[1][2] = f;
		element[2][0] = g;
		element[2][1] = h;
		element[2][2] = i;
	}
	Matrix3x3(Vector u, Vector v, Vector w) {
		element[0][0] = u.i;
		element[0][1] = u.j;
		element[0][2] = u.k;
		element[1][0] = v.i;
		element[1][1] = v.j;
		element[1][2] = v.k;
		element[2][0] = w.i;
		element[2][1] = w.j;
		element[2][2] = w.k;
	}
	Matrix3x3 operator+(Matrix3x3 M) {
		Matrix3x3 N;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				N.element[i][j] = element[i][j] + M.element[i][j];
		return N;
	}
	Matrix3x3 operator-(Matrix3x3 M) {
		Matrix3x3 N;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				N.element[i][j] = element[i][j] - M.element[i][j];
		return N;
	}
	Matrix3x3 operator*(Matrix3x3 M) {
		Matrix3x3 N;
		for (int i = 0; i < 3; i++) {
			Vector V(element[i][0], element[i][1], element[i][2]);
			for (int j = 0; j < 3; j++) {
				Vector U(element[0][j], element[1][j], element[2][j]);
				N.element[i][j] = dot(V, U);
			}
		}
		return N;
	}
	Matrix3x3 operator*(float f) {
		Matrix3x3 N;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				N.element[i][j] = element[i][j] * f;
		return N;
	}
	Vector operator*(Vector V) {
		Vector U;
		U.i = element[0][0] * V.i + element[0][1] * V.j + element[0][2] * V.k;
		U.j = element[1][0] * V.i + element[1][1] * V.j + element[1][2] * V.k;
		U.k = element[2][0] * V.i + element[2][1] * V.j + element[2][2] * V.k;
		return U;
	}
	float cofactor(int ci, int cj) {
		Matrix2x2 M;
		int fi, fj;
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++) {
				if (ci + i + 1 > 2)
					fi = ci + i - 2;
				else
					fi = ci + i + 1;
				if (cj + j + 1 > 2)
					fj = cj + j - 2;
				else
					fj = cj + j + 1;
				M.element[i][j] = this->element[fi][fj];
			}
		return M.det();
	}
	float det() {
		return element[0][0] * cofactor(0, 0) + element[0][1] * cofactor(0, 1) + element[0][2] * cofactor(0, 2);
	}
	Matrix3x3 inverse() {
		float D = det();
		if (D == 0)
			return *this;
		else {
			Matrix3x3 M;
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					M.element[i][j] = cofactor(j, i) / D;
			return M;
		}
	}
};

class Color {
public:
	float r, g, b;
	Color() {
		r = 0;
		g = 0;
		b = 0;
	}
	Color(float r, float g, float b) {
		this->r = r;
		this->g = g;
		this->b = b;
	}
};

class Point {
public:
	float x, y, z;
	Point() {
		x = 0;
		y = 0;
		z = 0;
	}
	Point(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
};

class Line {
public:
	Point P;
	Vector V;
	Line();
	Line(Point P, Vector V) {
		this->P = P;
		this->V = V;
	}
	Line(Point P, Point Q) {
		this->P = P;
		V.i = P.x - Q.x;
		V.j = P.y - Q.y;
		V.k = P.z - Q.z;
	}
	void draw(Color C) {
		glBegin(GL_LINES);
		glColor3f(C.r, C.g, C.b);
		glVertex3f(P.x, P.y, P.z);
		glVertex3f(P.x + V.i, P.y + V.j, P.z + V.k);
		glEnd();
	}
};

class Plane {
public:
	Point P;
	Vector V;
	Plane();
	Plane(Point P, Vector V) {
		this->P = P;
		this->V = V.normalize();
	}
	void drawSquare(float SL, Color C) {
		Vector A(1, 0, 0);
		Vector B(0, 1, 0);
		Vector D = cross(V, A);
		if (D.i == 0 && D.j == 0 && D.k == 0)
			A = cross(V, B);
		else
			A = D;
		B = cross(V, A);
		A = A.normalize();
		B = B.normalize();
		SL = SL / 2;
		glBegin(GL_QUADS);
		glColor3f(C.r, C.g, C.b);
		glVertex3f(P.x + SL*A.i + SL*B.i, P.y + SL*A.j + SL*B.j, P.z + SL*A.k + SL*B.k);
		glVertex3f(P.x - SL*A.i + SL*B.i, P.y - SL*A.j + SL*B.j, P.z - SL*A.k + SL*B.k);
		glVertex3f(P.x - SL*A.i - SL*B.i, P.y - SL*A.j - SL*B.j, P.z - SL*A.k - SL*B.k);
		glVertex3f(P.x + SL*A.i - SL*B.i, P.y + SL*A.j - SL*B.j, P.z + SL*A.k - SL*B.k);
		glEnd();
	}
};

float distance(Point P, Point Q) {
	return sqrt(pow(P.x - Q.x, 2) + pow(P.y - Q.y, 2) + pow(P.z - Q.z, 2));
}
float distance(Point P, Line L) {
	Vector V(P.x - L.P.x, P.y - L.P.y, P.z - L.P.z);
	return sqrt(pow(V.length(), 2) - pow(dot(V, L.V) / pow(L.V.length(), 2), 2));
}
float distance(Line L, Line M) {
	Matrix2x2 N(pow(L.V.length(), 2), -dot(L.V, M.V), dot(L.V, M.V), -pow(M.V.length(), 2));
	Vector U(L.P.x - M.P.x, L.P.y - M.P.y, L.P.z - M.P.z);
	float s, t;
	s = N.inverse().element[0][0] * dot(U, L.V) + N.inverse().element[0][1] * dot(U, M.V);
	t = N.inverse().element[1][0] * dot(U, L.V) + N.inverse().element[1][1] * dot(U, M.V);
	Point S(L.P.x + s * L.V.i, L.P.y + s * L.V.j, L.P.z + s * L.V.k);
	Point T(M.P.x + t * M.V.i, M.P.y + t * M.V.j, M.P.z + t * M.V.k);
	return distance(S, T);
}
Point collisionPoint(Line L, Plane P) {
	Vector p(P.P.x, P.P.y, P.P.z);
	Vector s(L.P.x, L.P.y, L.P.z);
	float D = -dot(p, P.V);
	float t = -(dot(L.V, s) + D) / dot(L.V, P.V);
	Point CP(L.P.x + t*L.V.i, L.P.y + t*L.V.j, L.P.z + t*L.V.k);
	return CP;
}

class hermiteCurves {
public:
	Point P1, P2;
	Vector T1, T2;
	hermiteCurves();
	hermiteCurves(Point p1, Point p2, Vector t1, Vector t2) {
		P1 = p1;
		P2 = p2;
		T1 = t1;
		T2 = t2;
	}
	Point parameter(float t) {
		Point HC;
		HC.x = (1 - 3 * pow(t, 2) + 2 * pow(t, 3))*P1.x + pow(t, 2)*(3 - 2 * t)*P2.x + t*pow((t - 1), 2)*T1.i + pow(t, 2)*(t - 1)*T2.i;
		HC.y = (1 - 3 * pow(t, 2) + 2 * pow(t, 3))*P1.y + pow(t, 2)*(3 - 2 * t)*P2.y + t*pow((t - 1), 2)*T1.j + pow(t, 2)*(t - 1)*T2.j;
		HC.z = (1 - 3 * pow(t, 2) + 2 * pow(t, 3))*P1.z + pow(t, 2)*(3 - 2 * t)*P2.y + t*pow((t - 1), 2)*T1.k + pow(t, 2)*(t - 1)*T2.k;
		return HC;
	}
};

class bezierCurves {
public:
	Point P1, P2, P3, P4;
	bezierCurves();
	bezierCurves(Point p1, Point p2, Point p3, Point p4) {
		P1 = p1;
		P2 = p2;
		P3 = p3;
		P4 = p4;
	}
	Point parameter(float t) {
		Point BC;
		BC.x = pow((1 - t), 3)*P1.x + 3 * t*pow((1 - t), 2)*P2.x + 3 * pow(t, 2)*(1 - t)*P3.x + pow(t, 3)*P4.x;
		BC.y = pow((1 - t), 3)*P1.y + 3 * t*pow((1 - t), 2)*P2.y + 3 * pow(t, 2)*(1 - t)*P3.y + pow(t, 3)*P4.y;
		BC.z = pow((1 - t), 3)*P1.z + 3 * t*pow((1 - t), 2)*P2.z + 3 * pow(t, 2)*(1 - t)*P3.z + pow(t, 3)*P4.z;
		return BC;
	}
};

class catmullRomSpline {
public:
	Point P0, P1, P2, P3;
	catmullRomSpline();
	catmullRomSpline(Point p0, Point p1, Point p2, Point p3) {
		P0 = p0;
		P1 = p1;
		P2 = p2;
		P3 = p3;

	}
	Point parameter(float t) {
		Point CC;
		CC.x = 0.5*(-t*pow((t - 1), 2)*P0.x + (3 * pow(t, 3) - (5 * pow(t, 2)) + 2)*P1.x + (-3 * pow(t, 3) + 4 * pow(t, 2) + t)*P2.x + (pow(t, 2)*(t - 1))*P3.x);
		CC.y = 0.5*(-t*pow((t - 1), 2)*P0.y + (3 * pow(t, 3) - (5 * pow(t, 2)) + 2)*P1.y + (-3 * pow(t, 3) + 4 * pow(t, 2) + t)*P2.y + (pow(t, 2)*(t - 1))*P3.y);
		CC.z = 0.5*(-t*pow((t - 1), 2)*P0.z + (3 * pow(t, 3) - (5 * pow(t, 2)) + 2)*P1.z + (-3 * pow(t, 3) + 4 * pow(t, 2) + t)*P2.z + (pow(t, 2)*(t - 1))*P3.z);
		return CC;
	}
};
#endif