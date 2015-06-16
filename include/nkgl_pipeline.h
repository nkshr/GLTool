#include "nkgl_math.h"

using namespace nkgl;

struct PpmInfo
{
	float fov, height, width, znear, zfar;
};

class Pipeline
{
private:
	Mat4x4f tmat, rmat, smat, ppmat, final, cam_tmat_;
public:
	Pipeline();
	void translate_obj(float x, float y, float z);
	void rotate_obj(float xdeg, float ydeg, float zdeg);
	void set_ppm(PpmInfo ppm_info);	//set perspective projection matrix.
	void do_scaling(float scale);
	const float* get_transformation();
	void rotate_cam();
	void translate_cam(Vec3f position);
};
