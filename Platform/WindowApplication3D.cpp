#include "WindowApplication3D.h"
#include "Math/Matrix3.h"



Seer::WindowApplication3D::WindowApplication3D(const char* acWindowTitle, int iXPosition, int iYPosition, int iWidth, int iHeight, const ColorRGBA& rkBackgroundColor)
	:WindowApplication(acWindowTitle, iXPosition, iYPosition, iWidth, iHeight, rkBackgroundColor)
{
	// camera motion
	m_akWorldAxis[0] = Vector3::ZERO;
	m_akWorldAxis[1] = Vector3::ZERO;
	m_akWorldAxis[2] = Vector3::ZERO;
	m_fTrnSpeed = 0.0f;
	m_fRotSpeed = 0.0f;
	m_bUArrowPressed = false;
	m_bDArrowPressed = false;
	m_bLArrowPressed = false;
	m_bRArrowPressed = false;
	m_bPgUpPressed = false;
	m_bPgDnPressed = false;
	m_bHomePressed = false;
	m_bEndPressed = false;
	m_bCameraMoveable = false;

	//// object motion
	//m_iDoRoll = 0;
	//m_iDoYaw = 0;
	//m_iDoPitch = 0;
	//m_spkMotionObject = 0;
	//m_fXTrack0 = 0.0f;
	//m_fYTrack0 = 0.0f;
	//m_fXTrack1 = 0.0f;
	//m_fYTrack1 = 0.0f;
	//m_bUseTrackBall = true;
	//m_bTrackBallDown = false;

	//// performance measurements
	//m_dLastTime = -1.0;
	//m_dAccumulatedTime = 0.0;
	//m_dFrameRate = 0.0;
	//m_iFrameCount = 0;
	//m_iAccumulatedFrameCount = 0;
	//m_iTimer = 30;
	//m_iMaxTimer = 30;
}

Seer::WindowApplication3D::~WindowApplication3D()
{

}

bool Seer::WindowApplication3D::OnInitialize()
{
	if (!WindowApplication::OnInitialize())
	{
		return false;
	}

	m_spkCamera = new Camera;
	m_pkRenderer->SetCamera(m_spkCamera);
	//m_spkMotionObject = 0;

	InitializeCameraMotion(0.01f, 0.01f);

	return true;
}

void Seer::WindowApplication3D::OnTerminate()
{
	m_pkRenderer->SetCamera(nullptr);
	m_spkCamera = 0;
	//m_spkMotionObject = 0;
	WindowApplication::OnTerminate();
}

void Seer::WindowApplication3D::OnDisplay()
{
	if (m_pkRenderer)
	{
		OnIdle();
	}
}

bool Seer::WindowApplication3D::OnKeyDown(unsigned char ucKey, int iX, int iY)
{
	if (WindowApplication::OnKeyDown(ucKey, iX, iY))
	{
		return true;
	}

	// standard keys
	switch (ucKey)
	{
	case 't':  // slower camera translation
		if (m_bCameraMoveable)
		{
			m_fTrnSpeed /= m_fTrnSpeedFactor;
		}
		return true;
	case 'T':  // faster camera translation
		if (m_bCameraMoveable)
		{
			m_fTrnSpeed *= m_fTrnSpeedFactor;
		}
		return true;
	case 'r':  // slower camera rotation
		if (m_bCameraMoveable)
		{
			m_fRotSpeed /= m_fRotSpeedFactor;
		}
		return true;
	case 'R':  // faster camera rotation
		if (m_bCameraMoveable)
		{
			m_fRotSpeed *= m_fRotSpeedFactor;
		}
		return true;
	case '?':  // reset the timer
		//ResetTime();
		return true;
	};

	return false;
}

bool Seer::WindowApplication3D::OnSpecialKeyDown(int iKey, int iX, int iY)
{
	if (m_bCameraMoveable)
	{
		if (iKey == KEY_LEFT_ARROW)
		{
			m_bLArrowPressed = true;
			return true;
		}
		if (iKey == KEY_RIGHT_ARROW)
		{
			m_bRArrowPressed = true;
			return true;
		}
		if (iKey == KEY_UP_ARROW)
		{
			m_bUArrowPressed = true;
			return true;
		}
		if (iKey == KEY_DOWN_ARROW)
		{
			m_bDArrowPressed = true;
			return true;
		}
		if (iKey == KEY_PAGE_UP)
		{
			m_bPgUpPressed = true;
			return true;
		}
		if (iKey == KEY_PAGE_DOWN)
		{
			m_bPgDnPressed = true;
			return true;
		}
		if (iKey == KEY_HOME)
		{
			m_bHomePressed = true;
			return true;
		}
		if (iKey == KEY_END)
		{
			m_bEndPressed = true;
			return true;
		}
	}

	/*if (m_spkMotionObject)
	{
		if (iKey == KEY_F1)
		{
			m_iDoRoll = -1;
			return true;
		}
		if (iKey == KEY_F2)
		{
			m_iDoRoll = 1;
			return true;
		}
		if (iKey == KEY_F3)
		{
			m_iDoYaw = -1;
			return true;
		}
		if (iKey == KEY_F4)
		{
			m_iDoYaw = 1;
			return true;
		}
		if (iKey == KEY_F5)
		{
			m_iDoPitch = -1;
			return true;
		}
		if (iKey == KEY_F6)
		{
			m_iDoPitch = 1;
			return true;
		}
	}*/

	return false;
}

bool Seer::WindowApplication3D::OnSpecialKeyUp(int iKey, int iX, int iY)
{
	if (m_bCameraMoveable)
	{
		if (iKey == KEY_LEFT_ARROW)
		{
			m_bLArrowPressed = false;
			return true;
		}
		if (iKey == KEY_RIGHT_ARROW)
		{
			m_bRArrowPressed = false;
			return true;
		}
		if (iKey == KEY_UP_ARROW)
		{
			m_bUArrowPressed = false;
			return true;
		}
		if (iKey == KEY_DOWN_ARROW)
		{
			m_bDArrowPressed = false;
			return true;
		}
		if (iKey == KEY_PAGE_UP)
		{
			m_bPgUpPressed = false;
			return true;
		}
		if (iKey == KEY_PAGE_DOWN)
		{
			m_bPgDnPressed = false;
			return true;
		}
		if (iKey == KEY_HOME)
		{
			m_bHomePressed = false;
			return true;
		}
		if (iKey == KEY_END)
		{
			m_bEndPressed = false;
			return true;
		}
	}

	/*if (m_spkMotionObject)
	{
		if (iKey == KEY_F1)
		{
			m_iDoRoll = 0;
			return true;
		}
		if (iKey == KEY_F2)
		{
			m_iDoRoll = 0;
			return true;
		}
		if (iKey == KEY_F3)
		{
			m_iDoYaw = 0;
			return true;
		}
		if (iKey == KEY_F4)
		{
			m_iDoYaw = 0;
			return true;
		}
		if (iKey == KEY_F5)
		{
			m_iDoPitch = 0;
			return true;
		}
		if (iKey == KEY_F6)
		{
			m_iDoPitch = 0;
			return true;
		}
	}*/

	return false;
}

bool Seer::WindowApplication3D::OnMouseClick(int iButton, int iState, int iX, int iY, unsigned int uiModifiers)
{
	//if (!m_bUseTrackBall
	//	|| iButton != MOUSE_LEFT_BUTTON
	//	|| !m_spkMotionObject)
	//{
	//	return false;
	//}

	//float fMult = 1.0f / (m_iWidth >= m_iHeight ? m_iHeight : m_iWidth);

	//if (iState == MOUSE_DOWN)
	//{
	//	// get the starting point
	//	m_bTrackBallDown = true;
	//	m_kSaveRotate = m_spkMotionObject->Local.GetRotate();
	//	m_fXTrack0 = (2 * iX - m_iWidth)*fMult;
	//	m_fYTrack0 = (2 * (m_iHeight - 1 - iY) - m_iHeight)*fMult;
	//}
	//else
	//{
	//	m_bTrackBallDown = false;
	//}

	return true;
}

bool Seer::WindowApplication3D::OnMotion(int iButton, int iX, int iY, unsigned int uiModifiers)
{
	//if (!m_bUseTrackBall
	//	|| iButton != MOUSE_LEFT_BUTTON
	//	|| !m_bTrackBallDown
	//	|| !m_spkMotionObject)
	//{
	//	return false;
	//}

	//// get the ending point
	//float fMult = 1.0f / (m_iWidth >= m_iHeight ? m_iHeight : m_iWidth);
	//m_fXTrack1 = (2 * iX - m_iWidth)*fMult;
	//m_fYTrack1 = (2 * (m_iHeight - 1 - iY) - m_iHeight)*fMult;

	//// update the object's local rotation
	//RotateTrackBall(m_fXTrack0, m_fYTrack0, m_fXTrack1, m_fYTrack1);
	return true;
}

void Seer::WindowApplication3D::InitializeCameraMotion(float fTrnSpeed, float fRotSpeed, float fTrnSpeedFactor /*= 2.0f*/, float fRotSpeedFactor /*= 2.0f*/)
{
	m_bCameraMoveable = true;

	m_fTrnSpeed = fTrnSpeed;
	m_fRotSpeed = fRotSpeed;
	m_fTrnSpeedFactor = fTrnSpeedFactor;
	m_fRotSpeedFactor = fRotSpeedFactor;

	m_akWorldAxis[0] = m_spkCamera->GetDVector();
	m_akWorldAxis[1] = m_spkCamera->GetUVector();
	m_akWorldAxis[2] = m_spkCamera->GetRVector();
}

bool Seer::WindowApplication3D::MoveCamera()
{
	if (!m_bCameraMoveable)
	{
		return false;
	}

	bool bMoved = false;

	if (m_bUArrowPressed)
	{
		MoveForward();
		bMoved = true;
	}

	if (m_bDArrowPressed)
	{
		MoveBackward();
		bMoved = true;
	}

	if (m_bHomePressed)
	{
		MoveUp();
		bMoved = true;
	}

	if (m_bEndPressed)
	{
		MoveDown();
		bMoved = true;
	}

	if (m_bLArrowPressed)
	{
		TurnLeft();
		bMoved = true;
	}

	if (m_bRArrowPressed)
	{
		TurnRight();
		bMoved = true;
	}

	if (m_bPgUpPressed)
	{
		LookUp();
		bMoved = true;
	}

	if (m_bPgDnPressed)
	{
		LookDown();
		bMoved = true;
	}

	return bMoved;
}

void Seer::WindowApplication3D::MoveForward()
{
	m_spkCamera->Walk(m_fTrnSpeed);
}

void Seer::WindowApplication3D::MoveBackward()
{
	m_spkCamera->Walk(-m_fTrnSpeed);
}

void Seer::WindowApplication3D::MoveUp()
{
	m_spkCamera->Jump(m_fTrnSpeed);
}

void Seer::WindowApplication3D::MoveDown()
{
	m_spkCamera->Jump(-m_fTrnSpeed);
}

void Seer::WindowApplication3D::TurnLeft()
{	
	m_spkCamera->Yaw(m_fRotSpeed);
}

void Seer::WindowApplication3D::TurnRight()
{
	m_spkCamera->Yaw(-m_fRotSpeed);

}

void Seer::WindowApplication3D::LookUp()
{
	m_spkCamera->Pitch(m_fRotSpeed);
}

void Seer::WindowApplication3D::LookDown()
{
	m_spkCamera->Pitch(-m_fRotSpeed);
}
