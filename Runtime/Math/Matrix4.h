#pragma once
#include "Precision.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "Vector4.h"

namespace Seer
{

	/*!
	 * \class Matrix4
	 *
	 * \ingroup GroupName
	 *
	 * \brief 
	 *
	 * ���� - ʹ������������ ����Ҳ��������
	 * ```math
	 * \begin{bmatrix}
	 * m{_1}{_1} & m{_1}{_2} & m{_1}{_3} & m{_1}{_4} \\
	 * m{_2}{_1} & m{_2}{_2} & m{_2}{_3} & m{_2}{_4} \\
	 * m{_3}{_1} & m{_3}{_2} & m{_3}{_3} & m{_3}{_4} \\
	 * m{_4}{_1} & m{_4}{_2} & m{_4}{_3} & m{_4}{_4}
	 * \end{bmatrix}
	 * ```
	 * 1. ������������ʱ���������󣬾������ң� v' = v * M
	 * 2. �������˵�˳���ǣ������ң��任��Ч��˳��Ҳ�Ǵ����ң� v' = v * T * R * S
	 * ���У�T��ʾƽ�ƾ���R��ʾ��ת����S��ʾ���ž���
	 *
	 * \note 
	 *
	 * \author tylerzhu
	 *
	 * \version 1.0
	 *
	 * \date ���� 2017
	 *
	 * Contact: user@company.com
	 *
	 */
	class Matrix4
	{
	public:
		real data[16];

		/**
		 * ��ʼ��Ϊ��λ����
		 */
		Matrix4()
		{
			SetIdentity();
		}

		/**
		* Creates a new matrix with explicit coefficients.
		*/
		Matrix4(
			real m00, real m01, real m02, real m03,
			real m10, real m11, real m12, real m13,
			real m20, real m21, real m22, real m23,
			real m30, real m31, real m32, real m33)
		{
			data[0]	= m00;	data[1] = m01;	data[2] = m02;	data[3] = m03;
			data[4] = m10;	data[5] = m11;	data[6] = m12;	data[7] = m13;
			data[8] = m20;	data[9] = m21;	data[10] = m22;	data[11] = m23;
			data[12] = m30;	data[13] = m31;	data[14] = m32;	data[15] = m33;
		}

		real& Get(int row, int column)            { return data[row + (column * 4)]; }
		const real& Get(int row, int column)const { return data[row + (column * 4)]; }

		//////////////////////////////////////////////////////////////////////////

		// 0����
		Matrix4& SetZero();

		// ��λ����
		Matrix4& SetIdentity();

		// ���ž���
		Matrix4& SetScale(const Vector3& scale);

		// ��ת����X
		Matrix4& SetRotateX(const real angle);

		// ��ת����Y
		Matrix4& SetRotateY(const real angle);

		// ��ת����Z
		Matrix4& SetRotateZ(const real angle);

		/**
		  *  @brief  ��ת����
		  *  @param[in]  inArgName input argument description.type name:purpose(Range)
		  *  @param[out] outArgName output argument description.
		  *  @Return:    SetRotate:description of the return value
		  *  - TRUE
		  *  - FALSE
		  *
		  *  @note   matters needing attention
		  *  @see    other functions
		  */
		Matrix4& SetRotate(Vector3& asix, const real angle);

		// ƽ�ƾ���
		Matrix4& SetTranslate(const Vector3& translate);

		/**
		  *  @brief  Thisis a brief description.
		  *  @param[in]  inArgName input argument description.type name:purpose(Range)
		  *  @param[out] outArgName output argument description.
		  *  @Return:    SetTR:description of the return value
		  *  - TRUE
		  *  - FALSE
		  *
		  *  @note   matters needing attention
		  *  @see    other functions
		  */
		Matrix4& SetTR(const Vector3& translate, Vector3& asix, const real angle);

		/**
		  *  @brief  Thisis a brief description.
		  *  @param[in]  inArgName input argument description.type name:purpose(Range)
		  *  @param[out] outArgName output argument description.
		  *  @Return:    SetTRS:description of the return value
		  *  - TRUE
		  *  - FALSE
		  *
		  *  @note   matters needing attention
		  *  @see    other functions
		  */
		Matrix4& SetTRS(const Vector3& translate, Vector3& asix, const real angle, const Vector3& scale);

		Matrix4& Translate(const Vector3& translate);
		Matrix4& Scale(const Vector3& scale);
		Matrix4& Transpose();

		//////////////////////////////////////////////////////////////////////////

		Vector4 MultiplyVector4(const Vector4& v) const;
		void MultiplyVector4(const Vector4& v, Vector4& output) const;

		Vector3 MultiplyVector3(const Vector3& v) const;
		void MultiplyVector3(const Vector3& v, Vector3& output) const;

		//////////////////////////////////////////////////////////////////////////

		Matrix4& View(const Vector3& eye, const Vector3& lookat, const Vector3& up);

		Matrix4& SetPerspective(real fovy, real aspect, real zNear, real zFar);

		//////////////////////////////////////////////////////////////////////////

		Matrix4 operator * (const Matrix4& o) const;

		Vector3 GetAxisX() const			{ return Vector3(Get(0, 0), Get(0, 1), Get(0, 2)); };
		Vector3 GetAxisY() const			{ return Vector3(Get(1, 1), Get(1, 1), Get(1, 2)); };
		Vector3 GetAxisZ() const			{ return Vector3(Get(2, 2), Get(2, 1), Get(2, 2)); };

		Vector4 GetRow(int row) const		{ return Vector4(Get(row, 0), Get(row, 1), Get(row, 2), Get(row, 3)); }
		Vector4 GetColumn(int col) const	{ return Vector4(Get(0, col), Get(1, col), Get(2, col), Get(3, col)); }
		//////////////////////////////////////////////////////////////////////////

	};

}