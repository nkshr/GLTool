#include "nkgl_math.h"

using namespace nkgl;

void Mat4x4f::print()
{
	char str[200];
	sprintf(str,
		"%f, %f, %f, %f, \n,"
		"%f, %f, %f, %f, \n,"
		"%f, %f, %f, %f, \n,"
		"%f, %f, %f, %f \n",
		m[0][0], m[0][1], m[0][2], m[0][3],
		m[1][0], m[1][1], m[1][2], m[1][3],
		m[2][0], m[2][1], m[2][2], m[2][3],
		m[3][0], m[3][1], m[3][2], m[3][3]);
	cout << str << endl;
}

Mat4x4f Mat4x4f::operator*(Mat4x4f& right)
{
	Mat4x4f ret;
	for (unsigned int i = 0; i < 4; ++i)
	{
		for (unsigned int j = 0; j < 4; ++j)
		{
			ret.m[i][j] = m[i][0] * right.m[0][j] +
				m[i][1] * right.m[1][j] +
				m[i][2] * right.m[2][j] +
				m[i][3] * right.m[3][j];
		}
	}
	return ret;
}

//Mat4x4f operator*(Mat4x4f& left, Mat4x4f& right)
//{
//	Mat4x4f ret;
//	for (unsigned int i = 0; i < 4; ++i)
//	{
//		for (unsigned int j = 0; j < 4; ++j)
//		{
//			ret.m[i][j] = left.m[i][0] * right.m[0][j] +
//				left.m[i][1] * right.m[1][j] +
//				left.m[i][2] * right.m[2][j] +
//				left.m[i][3] * right.m[3][j];
//		}
//	}
//	return ret;
//}

void Mat4x4f::eye()
{
	m[0][0] = 1.0, m[0][1] = 0.0, m[0][2] = 0.0, m[0][3] = 0.0;
	m[1][0] = 0.0, m[1][1] = 1.0, m[1][2] = 0.0, m[1][3] = 0.0;
	m[2][0] = 0.0, m[2][1] = 0.0, m[2][2] = 1.0, m[2][3] = 0.0;
	m[3][0] = 0.0, m[3][1] = 0.0, m[3][2] = 0.0, m[3][3] = 1.0;
}

void Mat2x2f::print()
{
	char str[100];
	sprintf(str,
		"%f, %f, \n"
		"%f, %f, \n",
		m[0][0], m[0][1],
		m[1][0], m[1][1]);
	cout << str << endl;
}

float Mat2x2f::det()
{
	return m[0][0] * m[1][1] - m[0][1] * m[1][0];
}

void Mat2x2f::eye()
{
	m[0][0] = 1.0, m[0][1] = 0.0;
	m[1][0] = 0.0, m[1][1] = 1.0;
}

Quaternion Quaternion::conjugate()
{
	Quaternion conj(w, -x, -y, -z);
	return conj;
}

Quaternion operator*(const Quaternion& left, const Quaternion& right)
{
	const float w = (left.w * right.w) - (left.x * right.x) - (left.y * right.y) - (left.z * right.z);
	const float x = (left.x * right.w) + (left.w * right.x) + (left.y * right.z) - (left.z * right.y);
	const float y = (left.y * right.w) + (left.w * right.y) + (left.z * right.x) - (left.x * right.z);
	const float z = (left.z * right.w) + (left.w * right.z) + (left.x * right.y) - (left.y * right.x);

	Quaternion ret(w, x, y, z);
	return ret;
}

void Vec3f::normalize()
{
	float dist = sqrtf(x * x + y * y + z * z);
	x /= dist;
	y /= dist;
	z /= dist;
}

Vec3f Vec3f::cross(Vec3f right)
{
	Vec3f ret;
	ret.x = y * right.z - z * right.y;
	ret.y = z * right.x - x * right.z;
	ret.z = x * right.y - y * right.x;

	return ret;
}

void qrotate()
{

}