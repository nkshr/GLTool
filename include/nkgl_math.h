#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <math.h>

using namespace std;

namespace nkgl
{
#define ToRadian(x) ((x) * M_PI / 180.0)
#define ToDegree(x) ((x) * 180.0 / M_PI) 

	struct Vec3f
	{
		float x, y, z;

		Vec3f()
		{
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
		}
		
		Vec3f(float x, float y, float z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		void normalize();
		Vec3f cross(Vec3f right);
	};

	class Mat
	{
	public:
		virtual void transpose() = 0;
		virtual void print() = 0;
		virtual void eye() = 0;
	};

	class Mat4x4f : public Mat
	{
	public:
		float m[4][4];
		//friend Mat4x4f operator*(Mat4x4f& left, Mat4x4f& right);
		void transpose(){}
		void print();
		Mat4x4f operator*(Mat4x4f& right);
		void eye();
	};

	class Mat2x2f :public Mat
	{
	public:
		float m[2][2];

		void transpose(){}
		void print();
		float det();
		void eye();
	};

	struct Quaternion
	{
		float w, x, y, z;
		
		Quaternion()
		{
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
		}

		Quaternion(float _w, float _x, float _y, float _z)
		{
			w = _w;
			x = _x;
			y = _y;
			z = _z;
		}

		Quaternion(float _w, Vec3f vec)
		{
			vec.normalize();

			w = _w;
			x = vec.x;
			y = vec.y;
			z = vec.z;
		}

		Quaternion conjugate();
	};

	Quaternion operator*(const Quaternion& l, const Quaternion& r);
	void qrotate();
}