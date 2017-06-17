#include "Polyline.h"




void Seer::Polyline::SetActiveQuantity(int iActiveQuantity)
{
	int iVQuantity = VBuffer->GetVertexQuantity();
	if (0 <= iActiveQuantity && iActiveQuantity <= iVQuantity)
	{
		m_iActiveQuantity = iActiveQuantity;
	}
	else
	{
		m_iActiveQuantity = iVQuantity;
	}

	IBuffer->SetIndexQuantity(m_iActiveQuantity);
}

void Seer::Polyline::SetClosed(bool bClosed)
{
	m_bClosed = bClosed;
	SetGeometryType();
}

void Seer::Polyline::SetContiguous(bool bContiguous)
{
	m_bContiguous = bContiguous;
	SetGeometryType();
}

void Seer::Polyline::SetGeometryType()
{
	if (m_bContiguous)
	{
		if (m_bClosed)
		{
			if (Type != GT_POLYLINE_CLOSED)
			{
				// Increase the index quantity to account for closing the
				// polyline.
				IBuffer->SetIndexQuantity(IBuffer->GetIndexQuantity() + 1);
				//IBuffer->Release();
			}
			Type = GT_POLYLINE_CLOSED;
		}
		else
		{
			if (Type == GT_POLYLINE_CLOSED)
			{
				// Decrease the index quantity to account for closing the
				// polyline.
				IBuffer->SetIndexQuantity(IBuffer->GetIndexQuantity() - 1);
				//IBuffer->Release();
			}
			Type = GT_POLYLINE_OPEN;
		}
	}
	else
	{
		if (Type == GT_POLYLINE_CLOSED)
		{
			// Decrease the index quantity to account for closing the
			// polyline.
			IBuffer->SetIndexQuantity(IBuffer->GetIndexQuantity() - 1);
			//IBuffer->Release();
		}
		Type = GT_POLYLINE_SEGMENTS;
	}
}

Seer::Polyline::Polyline(VertexBuffer* pkVBuffer, bool bClosed, bool bContiguous)
	:Geometry(pkVBuffer, nullptr)
{
	int iVQuantity = VBuffer->GetVertexQuantity();

	m_iActiveQuantity = iVQuantity;
	m_bClosed = bClosed;
	m_bContiguous = bContiguous;

	// One extra slot is allocated for the indices to allow for closed
	// polylines.  In that case, aiIndex[iVQuantity] is set to aiIndex[0].
	IBuffer = new IndexBuffer(iVQuantity + 1);
	int* aiIndex = IBuffer->GetData();
	for (int i = 0; i < iVQuantity; i++)
	{
		aiIndex[i] = i;
	}
	aiIndex[iVQuantity] = 0;

	if (!m_bContiguous || !m_bClosed)
	{
		// If the curve starts out not closed, reduce the index quantity so
		// that the renderer ignores the extra index.
		IBuffer->SetIndexQuantity(iVQuantity);
	}

	SetGeometryType();
}

Seer::Polyline::Polyline()
{
	m_iActiveQuantity = 0;
	m_bClosed = false;
	m_bContiguous = false;
	SetGeometryType();

}

Seer::Polyline::~Polyline()
{

}
