#pragma once
#include "Geometry.h"

namespace Seer
{
	
	class Polyline : public Geometry
	{
	public:
		// construction and destruction
		Polyline(VertexBuffer* pkVBuffer, bool bClosed, bool bContiguous);
		virtual ~Polyline();

		// member access
		void SetActiveQuantity(int iActiveQuantity);
		int GetActiveQuantity() const;

		void SetClosed(bool bClosed);
		bool GetClosed() const;

		void SetContiguous(bool bContiguous);
		bool GetContiguous() const;

	protected:
		Polyline();
		void SetGeometryType();

		// Allow application to specify fewer than the maximum number of vertices
		// to draw.
		int m_iActiveQuantity;

		// polyline is open or closed, contiguous or disjoint segments
		bool m_bClosed, m_bContiguous;
	};

#include "Polyline.inl"

}

