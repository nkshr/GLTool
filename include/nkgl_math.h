#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <math.h>

using namespace std;

namespace nkgl
{
#define ToRadian(x) ((x) * M_PI / 180.0)
#define ToDegree(x) ((x) * 180.0 / M_PI) 

	template <typename T>
	struct Vec3
	{
		T x, y, z;

		Vec3()
		{
		};
		
		Vec3(T x, T y, T z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}
	};

	class Mat
	{
	public:
		virtual void transpose() = 0;
		virtual void print() = 0;
	};

	template <typename T>
	class Mat4x4 : public Mat
	{
	public:
		T m[4][4];
		
		void transpose(){}
		
		void  print()
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
		inline Mat4x4 operator*(Mat4x4& right)
		{
			Mat4x4 ret;
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

	};


}