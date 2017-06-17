#pragma once
#include "WindowApplication.h"

namespace Seer
{
	
	class WindowApplication3D: public WindowApplication
	{
		
	public:
		WindowApplication3D(const char* acWindowTitle, int iXPosition,
			int iYPosition, int iWidth, int iHeight,
			const ColorRGBA& rkBackgroundColor);

		~WindowApplication3D();

		// event callbacks
		virtual bool OnInitialize() override;
		virtual void OnTerminate() override;
		virtual void OnDisplay() override;
		virtual bool OnKeyDown(unsigned char ucKey, int iX, int iY) override;
		virtual bool OnSpecialKeyDown(int iKey, int iX, int iY) override;
		virtual bool OnSpecialKeyUp(int iKey, int iX, int iY) override;
		virtual bool OnMouseClick(int iButton, int iState, int iX, int iY,
			unsigned int uiModifiers) override;
		virtual bool OnMotion(int iButton, int iX, int iY,
			unsigned int uiModifiers) override;

	protected:
		// camera motion
		void InitializeCameraMotion(float fTrnSpeed, float fRotSpeed,
			float fTrnSpeedFactor = 2.0f, float fRotSpeedFactor = 2.0f);
		virtual bool MoveCamera();
		virtual void MoveForward();
		virtual void MoveBackward();
		virtual void MoveUp();
		virtual void MoveDown();
		virtual void TurnLeft();
		virtual void TurnRight();
		virtual void LookUp();
		virtual void LookDown();


		Camera* m_spkCamera;
		Vector3 m_akWorldAxis[3];
		float m_fTrnSpeed, m_fTrnSpeedFactor;
		float m_fRotSpeed, m_fRotSpeedFactor;
		bool m_bUArrowPressed;
		bool m_bDArrowPressed;
		bool m_bLArrowPressed;
		bool m_bRArrowPressed;
		bool m_bPgUpPressed;
		bool m_bPgDnPressed;
		bool m_bHomePressed;
		bool m_bEndPressed;
		bool m_bCameraMoveable;

		// object motion
		/*void InitializeObjectMotion(Spatial* pkMotionObject);
		bool MoveObject();
		void RotateTrackBall(float fX0, float fY0, float fX1, float fY1);
		SpatialPtr m_spkMotionObject;
		int m_iDoRoll, m_iDoYaw, m_iDoPitch;
		float m_fXTrack0, m_fYTrack0, m_fXTrack1, m_fYTrack1;
		Matrix3f m_kSaveRotate;
		bool m_bUseTrackBall, m_bTrackBallDown;*/
	};

}

