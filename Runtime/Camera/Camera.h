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
		// 修改相机位置、角度
		//////////////////////////////////////////////////////////////////////////
		void SetPosition(const Vector3& position);
		void SetPosition(real x, real y, real z);
		
		/**
		  *  @brief  相机沿着look方向平移距离d，可以实现【前进】和【后退】
		  *  @param[in]  inArgName input argument real name:purpose(Range)
		  *  @note   matters needing attention
		  *  @see    SetLookAt  
		  */
		void Walk(real d);

		/**
		*  @brief  相机沿着right方向平移距离d，可以实现【向左】和【向右】移动
		*  @param[in]  inArgName input argument real name:purpose(Range)
		*  @note   matters needing attention
		*  @see    SetLookAt
		*/
		void Strafe(real d);

		/**
		*  @brief  相机沿着up方向平移距离d，可以实现【向上】和【向下】移动
		*  @param[in]  inArgName input argument real name:purpose(Range)
		*  @note   matters needing attention
		*  @see    SetLookAt
		*/
		void Jump(real d);

		/**
		*  @brief  相机绕着right方向（相机的x轴）旋转角度angle，可以实现视角【向上】和【向下】看
		*  @param[in]  inArgName input argument real name:purpose(Range)
		*  @note   matters needing attention
		*  @see    SetLookAt
		*/
		void Pitch(real angle);

		/**
		*  @brief  相机绕着up方向（相机的y轴）旋转角度angle，可以实现视角【向左】和【向右】看
		*  @param[in]  inArgName input argument real name:purpose(Range)
		*  @note   matters needing attention
		*  @see    SetLookAt
		*/
		void Yaw(real angle);

		/**
		*  @brief  绕着世界坐标系的y轴旋转角度angle，可以实现视角【向左】和【向右】看
		*  @param[in]  inArgName input argument real name:purpose(Range)
		*  @note   matters needing attention
		*  @see    SetLookAt
		*/
		void RotateY(float angle);
		
		/**
		  *  @brief  相机位置、方向发送变化之后，更新视图矩阵
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

		Matrix4 view; ///< 世界坐标 -> 摄像机坐标 变换矩阵
		Matrix4 projection;
		Rect viewport;
		
		//		Matrix4 
	};

#include "Camera.inl"
}

