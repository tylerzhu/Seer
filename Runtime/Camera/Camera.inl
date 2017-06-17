#pragma once

inline Vector3 Seer::Camera::GetPosition() const
{
	return m_kPosition;
}

inline Vector3 Camera::GetDVector() const
{
	return m_kLook;
}

inline Vector3 Camera::GetUVector() const
{
	return m_kUp;
}

inline Vector3 Camera::GetRVector() const
{
	return m_kRight;
}



