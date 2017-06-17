#include "Camera.h"

using namespace Seer;

void Seer::Camera::SetPosition(real x, real y, real z)
{
	m_kPosition.x = x;
	m_kPosition.y = y;
	m_kPosition.z = z;

	UpdateViewMatrix();
}

void Seer::Camera::SetPosition(const Vector3& position)
{
	this->m_kPosition = position;

	UpdateViewMatrix();
}

void Camera::SetLookAt(const Vector3& cameraPosition, const Vector3& lookat, const Vector3& up)
{
	view.View(cameraPosition, lookat, up);

	this->m_kPosition = cameraPosition;
	this->m_kRight = view.GetColumn(0).ToVector3();
	this->m_kUp = view.GetColumn(1).ToVector3();
	this->m_kLook = view.GetColumn(2).ToVector3();
}

void Seer::Camera::SetPerspective(real fovy, real aspect, real zNear, real zFar)
{
	this->fovy = fovy;
	this->aspect = aspect;
	this->zNear = zNear;
	this->zFar = zFar;

	projection.SetPerspective(fovy, aspect, zNear, zFar);
}

void Seer::Camera::SetViewport(real x, real y, real width, real height)
{
	viewport.Set(x, y, width, height);
}

void Seer::Camera::UpdateViewMatrix()
{
	m_kRight.Normalise();
	m_kUp.Normalise();
	m_kLook.Normalise();

	view.Get(0, 0) = m_kRight.x;				view.Get(0, 1) = m_kUp.x;				view.Get(0, 2) = m_kLook.x;				view.Get(0, 3) = 0.0;
	view.Get(1, 0) = m_kRight.y;				view.Get(1, 1) = m_kUp.y;				view.Get(1, 2) = m_kLook.y;				view.Get(1, 3) = 0.0;
	view.Get(2, 0) = m_kRight.z;				view.Get(2, 1) = m_kUp.z;				view.Get(2, 2) = m_kLook.z;				view.Get(2, 3) = 0.0;
	view.Get(3, 0) = -m_kRight.Dot(m_kPosition);	view.Get(3, 1) = -m_kUp.Dot(m_kPosition);	view.Get(3, 2) = -m_kLook.Dot(m_kPosition);	view.Get(3, 3) = 1.0;
}

void Seer::Camera::Walk(real d)
{
	// Move the camera along its look vector to move forwards and backwards. 
	// This can be implemented by translating the camera position along its look vector
	m_kPosition += m_kLook*d;

	SetLookAt(m_kPosition, m_kLook, m_kUp);
}

void Seer::Camera::Strafe(real d)
{
	// Move the camera along its right vector to strafe right and left. 
	// This can be implemented by translating the camera position along its right vector.
	m_kPosition += m_kRight*d;

	SetLookAt(m_kPosition, m_kLook, m_kUp);
}

void Seer::Camera::Jump(real d)
{
	// Move the camera along its right vector to strafe right and left. 
	// This can be implemented by translating the camera position along its right vector.
	m_kPosition += m_kUp*d;

	SetLookAt(m_kPosition, m_kLook, m_kUp);
}

void Seer::Camera::Pitch(real angle)
{
	// Rotate the camera around its right vector to ¡¸ look up and down ¡¹.
	// Rotate up and look vector about the right vector.

	Matrix4 matrix;
	matrix.SetRotate(m_kRight, angle);

	m_kUp = matrix.MultiplyVector3(m_kUp);
	m_kLook = matrix.MultiplyVector3(m_kLook);

	UpdateViewMatrix();
}


void Seer::Camera::Yaw(real angle)
{
	// Rotate the camera around its right vector to ¡¸ look left and right ¡¹.
	// Rotate up and look vector about the right vector.

	Matrix4 matrix;
	matrix.SetRotate(m_kUp, angle);

	m_kRight = matrix.MultiplyVector3(m_kRight);
	m_kLook = matrix.MultiplyVector3(m_kLook);

	UpdateViewMatrix();
}


void Seer::Camera::RotateY(float angle)
{
	// Rotate the basis vectors about the world y-axis.
	
	Matrix4 matrix;
	matrix.SetRotateY(angle);

	m_kRight = matrix.MultiplyVector3(m_kRight);
	m_kUp = matrix.MultiplyVector3(m_kUp);
	m_kLook = matrix.MultiplyVector3(m_kLook);

	UpdateViewMatrix();
}

void Seer::Camera::SetAxes(const Vector3& rkDVector, const Vector3& rkUVector, const Vector3& rkRVector)
{
	m_kRight = rkDVector;
	m_kUp = rkUVector;
	m_kLook = rkRVector;

	UpdateViewMatrix();
}





