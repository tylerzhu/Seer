#include "Matrix4.h"
#include <utility>

using namespace Seer;


Matrix4& Seer::Matrix4::SetIdentity()
{

	Get(0, 0) = 1.0;	Get(0, 1) = 0.0;	Get(0, 2) = 0.0;	Get(0, 3) = 0.0;
	Get(1, 0) = 0.0;	Get(1, 1) = 1.0;	Get(1, 2) = 0.0;	Get(1, 3) = 0.0;
	Get(2, 0) = 0.0;	Get(2, 1) = 0.0;	Get(2, 2) = 1.0;	Get(2, 3) = 0.0;
	Get(3, 0) = 0.0;	Get(3, 1) = 0.0;	Get(3, 2) = 0.0;	Get(3, 3) = 1.0;

	return *this;
}

Matrix4& Matrix4::SetZero()
{

	Get(0, 0) = 0.0;	Get(0, 1) = 0.0;	Get(0, 2) = 0.0;	Get(0, 3) = 0.0;
	Get(1, 0) = 0.0;	Get(1, 1) = 0.0;	Get(1, 2) = 0.0;	Get(1, 3) = 0.0;
	Get(2, 0) = 0.0;	Get(2, 1) = 0.0;	Get(2, 2) = 0.0;	Get(2, 3) = 0.0;
	Get(3, 0) = 0.0;	Get(3, 1) = 0.0;	Get(3, 2) = 0.0;	Get(3, 3) = 0.0;

	return *this;
}

Matrix4& Seer::Matrix4::SetScale(const Vector3& scale)
{
	Get(0, 0) = scale[0];		Get(0, 1) = 0.0;			Get(0, 2) = 0.0;			Get(0, 3) = 0.0;
	Get(1, 0) = 0.0;			Get(1, 1) = scale[1];		Get(1, 2) = 0.0;			Get(1, 3) = 0.0;
	Get(2, 0) = 0.0;			Get(2, 1) = 0.0;			Get(2, 2) = scale[2];		Get(2, 3) = 0.0;
	Get(3, 0) = 0.0;			Get(3, 1) = 0.0;			Get(3, 2) = 0.0;			Get(3, 3) = 1.0;

	return *this;
}

Matrix4& Seer::Matrix4::SetRotateX(const real angle)
{
	/*
	{ 1,	0,				0,				0 },
	{ 0,	cos(angle), 	sin(angle),		0 },
	{ 0,	-sin(angle),	cos(angle),		0 },
	{ 0,	0,				0,				1 }
	*/

	real c = real_cos(angle);
	real s = real_sin(angle);

	Get(0, 0) = 1.0;	Get(0, 1) = 0.0;	Get(0, 2) = 0.0;	Get(0, 3) = 0.0;
	Get(1, 0) = 0.0;	Get(1, 1) = c;		Get(1, 2) = s;		Get(1, 3) = 0.0;
	Get(2, 0) = 0.0;	Get(2, 1) = -s;		Get(2, 2) = c;		Get(2, 3) = 0.0;
	Get(3, 0) = 0.0;	Get(3, 1) = 0.0;	Get(3, 2) = 0.0;	Get(3, 3) = 1.0;

	return *this;
}

Matrix4& Seer::Matrix4::SetRotateY(const real angle)
{
	/*
	{ cos(angle),		0,			-sin(angle),			0 });
	{ 0,				1,			0,						0 });
	{ sin(angle),		0,			cos(angle),				0 });
	{ 0,				0,			0,						1 });
	*/

	real c = real_cos(angle);
	real s = real_sin(angle);

	Get(0, 0) = c;		Get(0, 1) = 0.0;	Get(0, 2) = -s;		Get(0, 3) = 0.0;
	Get(1, 0) = 0.0;	Get(1, 1) = 1.0;	Get(1, 2) = 0;		Get(1, 3) = 0.0;
	Get(2, 0) = s;		Get(2, 1) = 0.0;	Get(2, 2) = c;		Get(2, 3) = 0.0;
	Get(3, 0) = 0.0;	Get(3, 1) = 0.0;	Get(3, 2) = 0.0;	Get(3, 3) = 1.0;

	return *this;
}

Matrix4& Seer::Matrix4::SetRotateZ(const real angle)
{
	/*
	{ cos(angle),	sin(angle),				0,		0 });
	{ -sin(angle),	cos(angle),				0,		0 });
	{ 0,					0,				1,		0 });
	{ 0,					0,				0,		1 });
	*/

	real c = real_cos(angle);
	real s = real_sin(angle);

	Get(0, 0) = c;		Get(0, 1) = s;		Get(0, 2) = 0.0;	Get(0, 3) = 0.0;
	Get(1, 0) = -s;		Get(1, 1) = c;		Get(1, 2) = 0.0;	Get(1, 3) = 0.0;
	Get(2, 0) = 0.0;	Get(2, 1) = 0.0;	Get(2, 2) = 1.0;	Get(2, 3) = 0.0;
	Get(3, 0) = 0.0;	Get(3, 1) = 0.0;	Get(3, 2) = 0.0;	Get(3, 3) = 1.0;

	return *this;
}

Matrix4& Seer::Matrix4::SetRotate(Vector3& axis, const real angle)
{
	/*
	u  旋转轴x分量
	v  旋转轴y分量
	w  旋转轴z分量
	| uu+(1-uu)cos		uv(1-cos)+wsin		uw(1-cos)-vsin       0 |
	| uv(1-cos)-wsin	vv+(1-vv)cos		vw(1-cos)+usin       0 |
	| uw(1-cos)+vsin	vw(1-cos)-usin		ww+(1-ww)cos		 0 |
	| 0					0					0				     1 |
	*/

	axis.Normalise();
	float u = axis.x;
	float v = axis.y;
	float w = axis.z;

	real c = real_cos(angle);
	real s = real_sin(angle);

	Get(0, 0) = c + (u * u) * (1 - s);		Get(0, 1) = u * v * (1 - c) + w * s;	Get(0, 2) = u * w * (1 - c) - v * s;	Get(0, 3) = 0.0;
	Get(1, 0) = u * v * (1 - c) - w * s;	Get(1, 1) = c + v * v * (1 - s);		Get(1, 2) = w * v * (1 - c) + u * s;	Get(1, 3) = 0.0;
	Get(2, 0) = u * w * (1 - c) + v * s;	Get(2, 1) = v * w * (1 - c) - u * s;	Get(2, 2) = c + w * w * (1 - s);		Get(2, 3) = 0.0;
	Get(3, 0) = 0.0;						Get(3, 1) = 0.0;						Get(3, 2) = 0.0;						Get(3, 3) = 1.0;

	return *this;
}

Matrix4& Seer::Matrix4::SetTranslate(const Vector3& translate)
{
	SetIdentity();
	
	Get(3, 0) = translate[0];
	Get(3, 1) = translate[1];
	Get(3, 2) = translate[2];

	return *this;
}

Matrix4& Seer::Matrix4::SetTR(const Vector3& translate, Vector3& asix, const real angle)
{	
	SetRotate(asix, angle);

	Get(3, 0) = translate[0];
	Get(3, 1) = translate[1];
	Get(3, 2) = translate[2];

	return *this;
}

Matrix4& Seer::Matrix4::SetTRS(const Vector3& translate, Vector3& asix, const real angle, const Vector3& scale)
{
	SetTR(translate, asix, angle).Scale(scale);

	return *this;
}

Matrix4& Seer::Matrix4::Translate(const Vector3& translate)
{
	Get(3, 0) = Get(0, 0) * translate[0] + Get(1, 0) * translate[1] + Get(2, 0) * translate[2] + Get(3, 0);
	Get(3, 1) = Get(0, 1) * translate[0] + Get(1, 1) * translate[1] + Get(2, 1) * translate[2] + Get(3, 1);
	Get(3, 2) = Get(0, 2) * translate[0] + Get(1, 2) * translate[1] + Get(2, 2) * translate[2] + Get(3, 2);
	Get(3, 3) = Get(0, 3) * translate[0] + Get(1, 3) * translate[1] + Get(2, 3) * translate[2] + Get(3, 3);
	return *this;
}

Matrix4& Seer::Matrix4::Scale(const Vector3& scale)
{
	Get(0, 0) *= scale[0];
	Get(1, 0) *= scale[0];
	Get(2, 0) *= scale[0];
	Get(3, 0) *= scale[0];

	Get(0, 1) *= scale[1];
	Get(1, 1) *= scale[1];
	Get(2, 1) *= scale[1];
	Get(3, 1) *= scale[1];

	Get(0, 2) *= scale[2];
	Get(1, 2) *= scale[2];
	Get(2, 2) *= scale[2];
	Get(3, 2) *= scale[2];
	return *this;
}

Matrix4& Seer::Matrix4::Transpose()
{
	std::swap(Get(0, 1), Get(1, 0));
	std::swap(Get(0, 2), Get(2, 0));
	std::swap(Get(0, 3), Get(3, 0));
	std::swap(Get(1, 2), Get(2, 1));
	std::swap(Get(1, 3), Get(3, 1));
	std::swap(Get(2, 3), Get(3, 2));
	return *this;
}

Seer::Vector4 Seer::Matrix4::MultiplyVector4(const Vector4& v) const
{
	Vector4 res;
	MultiplyVector4(v, res);
	return res;
}

void Seer::Matrix4::MultiplyVector4(const Vector4& v, Vector4& output) const
{
	output.x = Get(0, 0) * v.x + Get(1, 0) * v.y + Get(2, 0) * v.z + Get(3, 0) * v.w;
	output.y = Get(0, 1) * v.x + Get(1, 1) * v.y + Get(2, 1) * v.z + Get(3, 1) * v.w;
	output.z = Get(0, 2) * v.x + Get(1, 2) * v.y + Get(2, 2) * v.z + Get(3, 2) * v.w;
	output.w = Get(0, 3) * v.x + Get(1, 3) * v.y + Get(2, 3) * v.z + Get(3, 3) * v.w;
}

Seer::Vector3 Seer::Matrix4::MultiplyVector3(const Vector3& v) const
{
	Vector3 res;
	MultiplyVector3(v, res);
	return res;
}

void Seer::Matrix4::MultiplyVector3(const Vector3& v, Vector3& output) const
{
	output.x = Get(0, 0) * v.x + Get(1, 0) * v.y + Get(2, 0) * v.z;
	output.y = Get(0, 1) * v.x + Get(1, 1) * v.y + Get(2, 1) * v.z;
	output.z = Get(0, 2) * v.x + Get(1, 2) * v.y + Get(2, 2) * v.z;
}

Matrix4& Seer::Matrix4::View(const Vector3& eye, const Vector3& lookat, const Vector3& up)
{
	/*
	r 对应向右方向基向量 相当于x轴
	u 对应向上方向基向量 相当于y轴
	d 对应向前方向基向量 相当于z轴
	p 对应Eye位置
	| r.x	u.x		d.x       0 |
	| r.y	u.y		d.y       0 |
	| r.z	u.z		d.z		 0 |
	| -P*R	-P*U	-P*D     1 |
	*/

	Vector3 r, u, d;

	//计算向前向量
	d = lookat - eye;
	d.Normalise();

	//计算向右向量
	r = up.Cross(d);
	r.Normalise();

	//计算向上向量
	u = d.Cross(r);

	Get(0, 0) = r.x;			Get(0, 1) = u.x;			Get(0, 2) = d.x;			Get(0, 3) = 0.0;
	Get(1, 0) = r.y;			Get(1, 1) = u.y;			Get(1, 2) = d.y;			Get(1, 3) = 0.0;
	Get(2, 0) = r.z;			Get(2, 1) = u.z;			Get(2, 2) = d.z;			Get(2, 3) = 0.0;
	Get(3, 0) = -r.Dot(eye);	Get(3, 1) = -u.Dot(eye);	Get(3, 2) = -d.Dot(eye);	Get(3, 3) = 1.0;

	return *this;
}

Matrix4& Seer::Matrix4::SetPerspective(real fovy, real aspect, real zNear, real zFar)
{
	/*
	cot fovy的半角余切
	aspect 屏幕宽高比
	f,n   远近裁面距离
	| cot/aspect  0      0        0 |
	| 0			  cot	 0        0 |
	| 0           0      f/(f-n)  1 |
	| 0           0      fn/(n-f) 0 |
	*/

	SetZero();
	
	real cot = 1.0 / real_tan(fovy * 0.5f);	
	Get(0, 0) = cot / aspect;
	Get(1, 1) = cot;
	Get(2, 2) = zFar / (zFar - zNear);
	Get(2, 3) = 1.0;
	Get(3, 2) = (zNear * zFar) / (zNear - zFar);

	return *this;
}

Matrix4 Matrix4::operator*(const Matrix4& o) const
{
//	data[0] = m00;	data[1] = m01;	data[2] = m02;	data[3] = m03;
//	data[4] = m10;	data[5] = m11;	data[6] = m12;	data[7] = m13;
//	data[8] = m20;	data[9] = m21;	data[10] = m22;	data[11] = m23;
//	data[12] = m30;	data[13] = m31;	data[14] = m32;	data[15] = m33;
	return Matrix4(
		data[0] * o.data[0] + data[1] * o.data[4] + data[2] * o.data[8] + data[3] * o.data[12],
		data[0] * o.data[1] + data[1] * o.data[5] + data[2] * o.data[9] + data[3] * o.data[13],
		data[0] * o.data[2] + data[1] * o.data[6] + data[2] * o.data[10] + data[3] * o.data[14],
		data[0] * o.data[3] + data[1] * o.data[7] + data[2] * o.data[11] + data[3] * o.data[15],

		data[4] * o.data[0] + data[5] * o.data[4] + data[6] * o.data[8] + data[7] * o.data[12],
		data[4] * o.data[1] + data[5] * o.data[5] + data[6] * o.data[9] + data[7] * o.data[13],
		data[4] * o.data[2] + data[5] * o.data[6] + data[6] * o.data[10] + data[7] * o.data[14],
		data[4] * o.data[3] + data[5] * o.data[7] + data[6] * o.data[11] + data[7] * o.data[15],

		data[8] * o.data[0] + data[9] * o.data[4] + data[10] * o.data[8] + data[11] * o.data[12],
		data[8] * o.data[1] + data[9] * o.data[5] + data[10] * o.data[9] + data[11] * o.data[13],
		data[8] * o.data[2] + data[9] * o.data[6] + data[10] * o.data[10] + data[11] * o.data[14],
		data[8] * o.data[3] + data[9] * o.data[7] + data[10] * o.data[11] + data[11] * o.data[15],

		data[12] * o.data[0] + data[13] * o.data[4] + data[14] * o.data[8] + data[15] * o.data[12],
		data[12] * o.data[1] + data[13] * o.data[5] + data[14] * o.data[9] + data[15] * o.data[13],
		data[12] * o.data[2] + data[13] * o.data[6] + data[14] * o.data[10] + data[15] * o.data[14],
		data[12] * o.data[3] + data[13] * o.data[7] + data[14] * o.data[11] + data[15] * o.data[15]
		);
}



