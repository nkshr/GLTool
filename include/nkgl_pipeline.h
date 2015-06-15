#include "nkgl_math.h"

using namespace nkgl;

struct PpmInfo
{
	float fov, height, width, znear, zfar;
};

class Pipeline
{
private:
	Mat4x4<float> tmat, rmat, smat, ppmat, final;
public:
	Pipeline();
	void translate(float x, float y, float z);
	void rotate(float x, float y, float z);
	void set_ppm(PpmInfo ppm_info);	//set perspective projection matrix.
	void do_scaling(float scale);
	const float* get_transformation();
};
