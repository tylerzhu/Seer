#pragma once
#include "Math/Vector3.h"
#include "Math/Matrix4.h"
#include "Math/Rect.h"

namespace Seer
{	

	class Camera
	{
	public:
		void SetLookAt(const Vector3& eye, const Vector3& lookat, const Vector3& up);
		void SetPerspective(real fovy, real aspect, real zNear, real zFar);
		void SetViewport(real x, real y, real width, real height);
		void SetAxes(const Vector3& rkDVector, const Vector3& rkUVector, const Vector3& rkRVector);

		Matrix4 GetView() const				{ return view; }
		Matrix4 GetProjection() const		{ return projection; }
		Matrix4 GetViewProj() const			{ return projection*view; };
		Rect GetScreenViewportRect() const	{ return viewport; };

		Vector3 GetPosition() const;
		Vector3 GetDVector() const;
		Vector3 GetUVector() const;
		Vector3 GetRVector() const;

		//////////////////////////////////////////////////////////////////////////
		// �޸����λ�á��Ƕ�
		//////////////////////////////////////////////////////////////////////////
		void SetPosition(const Vector3& position);
		void SetPosition(real x, real y, real z);
		
		/**
		  *  @brief  �������look����ƽ�ƾ���d������ʵ�֡�ǰ�����͡����ˡ�
		  *  @param[in]  inArgName input argument real name:purpose(Range)
		  *  @note   matters needing attention
		  *  @see    SetLookAt  
		  */
		void Walk(real d);

		/**
		*  @brief  �������right����ƽ�ƾ���d������ʵ�֡����󡿺͡����ҡ��ƶ�
		*  @param[in]  inArgName input argument real name:purpose(Range)
		*  @note   matters needing attention
		*  @see    SetLookAt
		*/
		void Strafe(real d);

		/**
		*  @brief  �������up����ƽ�ƾ���d������ʵ�֡����ϡ��͡����¡��ƶ�
		*  @param[in]  inArgName input argument real name:purpose(Range)
		*  @note   matters needing attention
		*  @see    SetLookAt
		*/
		void Jump(real d);

		/**
		*  @brief  �������right���������x�ᣩ��ת�Ƕ�angle������ʵ���ӽǡ����ϡ��͡����¡���
		*  @param[in]  inArgName input argument real name:purpose(Range)
		*  @note   matters needing attention
		*  @see    SetLookAt
		*/
		void Pitch(real angle);

		/**
		*  @brief  �������up���������y�ᣩ��ת�Ƕ�angle������ʵ���ӽǡ����󡿺͡����ҡ���
		*  @param[in]  inArgName input argument real name:purpose(Range)
		*  @note   matters needing attention
		*  @see    SetLookAt
		*/
		void Yaw(real angle);

		/**
		*  @brief  ������������ϵ��y����ת�Ƕ�angle������ʵ���ӽǡ����󡿺͡����ҡ���
		*  @param[in]  inArgName input argument real name:purpose(Range)
		*  @note   matters needing attention
		*  @see    SetLookAt
		*/
		void RotateY(float angle);
		
		/**
		  *  @brief  ���λ�á������ͱ仯֮�󣬸�����ͼ����
		  *  @note   matters needing attention
		  *  @see    other functions  
		  */
		void UpdateViewMatrix();

	protected:
		// The renderer to which this camera has been attached.  The camera is
		// considered to be active if this pointer is not null.  By necessity, a
		// camera cannot be attached to multiple renderers, but a camera may be
		// shared by renderers as long as only one renderer at a time uses the
		// camera.  The renderer is responsible for setting this Camera member.
		friend class Renderer;
		Renderer* m_pkRenderer;

	private:
		
		Vector3	m_kPosition;
		Vector3	m_kRight;
		Vector3	m_kUp;
		Vector3	m_kLook;

		real fovy;
		real aspect;
		real zNear;
		real zFar;

		Matrix4 view; ///< �������� -> ��������� �任����
		Matrix4 projection;
		Rect viewport;
		
		//		Matrix4 
	};

#include "Camera.inl"
}

