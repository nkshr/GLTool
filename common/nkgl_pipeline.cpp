#include "nkgl_pipeline.h"

void Pipeline::translate(float x, float y, float z)
{
	tmat.m[0][0] = 1.0f, tmat.m[0][1] = 0.0f, tmat.m[0][2] = 0.0f, tmat.m[0][3] = x;
	tmat.m[1][0] = 0.0f, tmat.m[1][1] = 1.0f, tmat.m[1][2] = 0.0f, tmat.m[1][3] = y;
	tmat.m[2][0] = 0.0f, tmat.m[2][1] = 0.0f, tmat.m[2][2] = 1.0f, tmat.m[2][3] = z;
	tmat.m[3][0] = 0.0f, tmat.m[3][1] = 0.0f, tmat.m[3][2] = 0.0f, tmat.m[3][3] = 1.0f;
}

void Pipeline::rotate(float xdeg, float ydeg, float zdeg)
{
	const float x = (float)ToRadian(xdeg);
	const float y = (float)ToRadian(ydeg);
	const float z = (float)ToRadian(zdeg);

	Mat4x4<float> rx, ry, rz;
	rx.m[0][0] = 1.0f; rx.m[0][1] = 0.0f; rx.m[0][2] = 0.0f; rx.m[0][3] = 0.0f;
	rx.m[1][0] = 0.0f; rx.m[1][1] = cosf(x); rx.m[1][2] = -sinf(x); rx.m[1][3] = 0.0f;
	rx.m[2][0] = 0.0f; rx.m[2][1] = sinf(x); rx.m[2][2] = cosf(x); rx.m[2][3] = 0.0f;
	rx.m[3][0] = 0.0f; rx.m[3][1] = 0.0f; rx.m[3][2] = 0.0f; rx.m[3][3] = 1.0f;

	ry.m[0][0] = cosf(y); ry.m[0][1] = 0.0f; ry.m[0][2] = -sinf(y); ry.m[0][3] = 0.0f;
	ry.m[1][0] = 0.0f; ry.m[1][1] = 1.0f; ry.m[1][2] = 0.0f; ry.m[1][3] = 0.0f;
	ry.m[2][0] = sinf(y); ry.m[2][1] = 0.0f; ry.m[2][2] = cosf(y); ry.m[2][3] = 0.0f;
	ry.m[3][0] = 0.0f; ry.m[3][1] = 0.0f; ry.m[3][2] = 0.0f; ry.m[3][3] = 1.0f;

	rz.m[0][0] = cosf(z); rz.m[0][1] = -sinf(z); rz.m[0][2] = 0.0f; rz.m[0][3] = 0.0f;
	rz.m[1][0] = sinf(z); rz.m[1][1] = cosf(z); rz.m[1][2] = 0.0f; rz.m[1][3] = 0.0f;
	rz.m[2][0] = 0.0f; rz.m[2][1] = 0.0f; rz.m[2][2] = 1.0f; rz.m[2][3] = 0.0f;
	rz.m[3][0] = 0.0f; rz.m[3][1] = 0.0f; rz.m[3][2] = 0.0f; rz.m[3][3] = 1.0f;

	rmat = rz * ry * rx;
}

void Pipeline::do_scaling(float scale)
{
	smat.m[0][0] = scale, smat.m[0][1] = 0.0f, smat.m[0][2] = 0.0f, smat.m[0][3] = 0.0f;
	smat.m[1][0] = 0.0f, smat.m[1][1] = scale, smat.m[1][2] = 0.0f, smat.m[1][3] = 0.0f;
	smat.m[2][0] = 0.0f, smat.m[2][1] = 0.0f, smat.m[2][2] = scale, smat.m[2][3] = 0.0f;
	smat.m[3][0] = 0.0f, smat.m[3][1] = 0.0f, smat.m[3][2] = 0.0f, smat.m[3][3] = 1.0f;
}

const float* Pipeline::get_transformation()
{
	final = ppmat * smat * tmat * rmat;
	return &final.m[0][0];
}

void Pipeline::set_ppm(PpmInfo ppm_info)
{
	const float ar = ppm_info.width / ppm_info.height;
	const float tan_half_fov = tanf(ToRadian(ppm_info.fov) / 2.0f);

	ppmat.m[0][0] = 1.0f / (ar * tan_half_fov);
	ppmat.m[0][1] = 0.0f;
	ppmat.m[0][2] = 0.0f;
	ppmat.m[0][3] = 0.0f;

	ppmat.m[1][0] = 0.0f;
	ppmat.m[1][1] = 1.0f / tan_half_fov;
	ppmat.m[1][2] = 0.0f;
	ppmat.m[1][3] = 0.0f;

	ppmat.m[2][0] = 0.0f;
	ppmat.m[2][1] = 0.0f;
	ppmat.m[2][2] = (-ppm_info.znear - ppm_info.zfar) / (ppm_info.znear - ppm_info.zfar);
	ppmat.m[2][3] = (2 * ppm_info.zfar * ppm_info.znear) / (ppm_info.znear - ppm_info.zfar);

	ppmat.m[3][0] = 0.0f;
	ppmat.m[3][1] = 0.0f;
	ppmat.m[3][2] = 1.0f;
	ppmat.m[3][3] = 0.0f;
}

Pipeline::Pipeline()
{
	translate(0.0f, 0.0f, 0.0f);
	rotate(0.0f, 0.0f, 0.0f);
	do_scaling(1.0f);

	PpmInfo ppm_info;
	ppm_info.fov = 60;
	ppm_info.width = 640;
	ppm_info.height = 480;
	ppm_info.znear = 1;
	ppm_info.zfar = 1000;
	set_ppm(ppm_info);
}