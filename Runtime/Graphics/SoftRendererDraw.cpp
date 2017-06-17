#include "SoftRenderer.h"

using namespace Seer;


//----------------------------------------------------------------------------
void SoftRenderer::DrawElements()
{
	//ApplyVertexShader();

	// ==> DrawPolypoint、 DrawPolylineDisjoint、 DrawPolylineContiguous、 DrawTriMesh
	(this->*m_aoDrawFunction[m_pkGeometry->Type])();
}
//----------------------------------------------------------------------------
void SoftRenderer::DrawPolypoint()
{
	/*int iIQuantity = m_pkIBResource->IQuantity;
	const int* piIndex = m_pkIBResource->Index;
	for (int i = 0; i < iIQuantity; i++)
	{
		RasterizePoint(*piIndex++);
	}*/
}
//----------------------------------------------------------------------------
void SoftRenderer::DrawPolylineDisjoint()
{
	/*int iSQuantity = m_pkIBResource->IQuantity / 2;
	const int* piIndex = m_pkIBResource->Index;
	int iQuantity, aiEnd[2];
	for (int i = 0; i < iSQuantity; i++)
	{
		iQuantity = 2;
		aiEnd[0] = *piIndex++;
		aiEnd[1] = *piIndex++;
		ClipSegment(iQuantity, aiEnd);
		if (iQuantity == 2)
		{
			RasterizeEdge(aiEnd[0], aiEnd[1]);
		}
	}*/
}
//----------------------------------------------------------------------------
void SoftRenderer::DrawPolylineContiguous()
{
	/*int iSQuantity = m_pkIBResource->IQuantity - 1;
	const int* aiIndex = m_pkIBResource->Index;
	int iQuantity, aiEnd[2];
	for (int i = 0; i < iSQuantity; i++)
	{
		iQuantity = 2;
		aiEnd[0] = aiIndex[i];
		aiEnd[1] = aiIndex[i + 1];
		ClipSegment(iQuantity, aiEnd);
		if (iQuantity == 2)
		{
			RasterizeEdge(aiEnd[0], aiEnd[1]);
		}
	}*/
}
//----------------------------------------------------------------------------
void SoftRenderer::DrawTriMesh()
{
	Matrix4 mvp = m_pkCamera->GetViewProj()*m_pkGeometry->Local;
	std::vector<Vertex> kVertex(m_pkGeometry->VBuffer->GetVertexQuantity());

	for (size_t i = 0; i < m_pkGeometry->VBuffer->GetVertexQuantity(); i++)
	{
		kVertex[i].Pos = (*m_pkGeometry->VBuffer)[i].Pos;
		kVertex[i].Color = (*m_pkGeometry->VBuffer)[i].Color;
		kVertex[i].Rhw = (*m_pkGeometry->VBuffer)[i].Rhw;

		kVertex[i].Pos = mvp.MultiplyVector4(kVertex[i].Pos);

		float rhw = 1 / kVertex[i].Pos.w;
		kVertex[i].Pos = kVertex[i].Pos*rhw;
		kVertex[i].Color = kVertex[i].Color*rhw;
		kVertex[i].Rhw = rhw;

		kVertex[i].Pos = { 
			(kVertex[i].Pos.x + 1.0f) * m_pkCamera->GetScreenViewportRect().width * 0.5f,
			(1.0f - kVertex[i].Pos.y) * m_pkCamera->GetScreenViewportRect().height * 0.5f,
			kVertex[i].Pos.z,
			1.0f };
	}

	int j = 1;

	for (size_t i = 0; i < m_pkGeometry->IBuffer->GetIndexQuantity(); )
	{
		
		int v0 = (*m_pkGeometry->IBuffer)[i], v1 = (*m_pkGeometry->IBuffer)[i+1], v2 = (*m_pkGeometry->IBuffer)[i+2];
		//printf("%d %d %d\n", v0, v1, v2);
//		RasterizeEdge(&kVertex[v0], &kVertex[v1]);
//		RasterizeEdge(&kVertex[v1], &kVertex[v2]);
//		RasterizeEdge(&kVertex[v2], &kVertex[v0]);

		RasterizeTriangle(&kVertex[v0], &kVertex[v1], &kVertex[v2]);

		i += 3;
	}

	//// Process the triangles to discard back-facing ones, clipping and
	//// drawing the front-facing ones.
	//int iTQuantity = m_pkIBResource->IQuantity / 3;
	//const int* piIndex = m_pkIBResource->Index;
	//CullState* pkCullState = GetCullState();
	//WireframeState* pkWireframeState = GetWireframeState();
	//for (int i = 0; i < iTQuantity; i++)
	//{
	//	// Get the triangle vertices.
	//	int iV0 = *piIndex++;
	//	int iV1 = *piIndex++;
	//	int iV2 = *piIndex++;

	//	// Cull the triangles based on culling state.
	//	if (pkCullState->Enabled)
	//	{
	//		// Get the clip-space coordinates (r'[i],u'[i],d'[i],w'[i]).
	//		const float* afV0 = GetOutputVertex(iV0);
	//		const float* afV1 = GetOutputVertex(iV1);
	//		const float* afV2 = GetOutputVertex(iV2);

	//		// The visibility test is applied to clip-space coordinates
	//		// (r'[i],u'[i],w'[i]).  The d'[i] term cannot be used as the
	//		// third component since it contains a translation from the
	//		// projection matrix that maps view coordinates to clip
	//		// coordinates.  The normal vector is fine to compute with the
	//		// d'[i] term, but the dot product of the normal with one of the
	//		// vertices is not
	//		Vector3f kE1(afV1[0] - afV0[0], afV1[1] - afV0[1], afV1[3] - afV0[3]);
	//		Vector3f kE2(afV2[0] - afV0[0], afV2[1] - afV0[1], afV2[3] - afV0[3]);
	//		Vector3f kN = kE1.Cross(kE2);

	//		// NOTE:  The camera coordinates are E+r*R+u*U+d*D, but {R,U,D}
	//		// is a left-handed system.  The visibility test must be computed
	//		// accordingly.  The handedness is absorbed into the computation
	//		// of m_iCullSignAdjust.  The default sign adjustment is +1 for
	//		// counterclockwise triangles and back face culling.
	//		float fVisibility = m_iCullSignAdjust*(kN[0] * afV0[0] +
	//			kN[1] * afV0[1] + kN[2] * afV0[3]);
	//		if (fVisibility <= 0.0f)
	//		{
	//			// The triangle is potentially back facing, but an incorrect
	//			// classification can occur due to round-off errors.  Try a
	//			// more detailed test to decide if the triangle really should
	//			// be rejected.

	//			// The visibility test is applied to the window coordinates of
	//			// the points.  If any of the w-components of the points are
	//			// negative, the points are behind the viewer.  Triangles
	//			// with any such vertices are sent to the clipper because
	//			// parts of the triangle are potentially visible.
	//			if (afV0[3] > 0.0f && afV1[3] > 0.0f && afV2[3] > 0.0f)
	//			{
	//				int aiX[3], aiY[3];
	//				ClipToWindowXY(afV0, aiX[0], aiY[0]);
	//				ClipToWindowXY(afV1, aiX[1], aiY[1]);
	//				ClipToWindowXY(afV2, aiX[2], aiY[2]);
	//				int iVisibility = m_iCullSignAdjust*(
	//					(aiX[2] - aiX[0])*(aiY[1] - aiY[0]) -
	//					(aiX[1] - aiX[0])*(aiY[2] - aiY[0]));

	//				if (iVisibility <= 0)
	//				{
	//					// The triangle is back facing.
	//					continue;
	//				}
	//			}
	//		}
	//	}

	//	// The triangle is visible.  Clip it against the view frustum.
	//	int aiIndex[SOFT_MAX_CLIP_INDICES];
	//	int aiEdge[SOFT_MAX_CLIP_INDICES];
	//	int iQuantity = 3;
	//	aiIndex[0] = iV0;
	//	aiIndex[1] = iV1;
	//	aiIndex[2] = iV2;
	//	aiEdge[0] = 0;
	//	aiEdge[1] = 1;
	//	aiEdge[2] = 2;
	//	ClipPolygon(iQuantity, aiIndex, aiEdge);
	//	if (iQuantity < 3)
	//	{
	//		// The entire triangle was outside the view frustum.
	//		continue;
	//	}

	//	// Rasterize the triangles and call the pixel shaders.
	//	int iVQuantity = m_pkVBResource->VQuantity;
	//	if (pkWireframeState->Enabled)
	//	{
	//		// Draw only the polygon boundary edges, but not any diagonals
	//		// generated by clipping or edges whose end points are both clip
	//		// vertices.
	//		for (int j0 = iQuantity - 1, j1 = 0; j1 < iQuantity; j0 = j1++)
	//		{
	//			if (aiIndex[j0] < iVQuantity
	//				|| aiIndex[j1] < iVQuantity
	//				|| aiEdge[j0] == aiEdge[j1])
	//			{
	//				RasterizeEdge(aiIndex[j0], aiIndex[j1]);
	//			}
	//		}
	//	}
	//	else
	//	{
	//		int iNumTriangles = iQuantity - 2;
	//		for (int j = 1; j <= iNumTriangles; j++)
	//		{
	//			RasterizeTriangle(aiIndex[0], aiIndex[j], aiIndex[j + 1]);
	//		}
	//	}
	//}
}
//----------------------------------------------------------------------------
void SoftRenderer::RasterizePoint(int iV0)
{
	//// Get the output vertex from the vertex shader.
	//const float* afVertex0 = GetOutputVertex(iV0);

	//// Test for containment in the view frustum.

	//// constraint:  W - 1 >= 0  (W >= 1)
	//float fW = afVertex0[3];
	//if (fW - 1.0f < 0.0f)
	//{
	//	return;
	//}

	//// constraint:  F - N*W >= 0 (W <= F/N)
	//float fDMin = m_pkCamera->GetDMin();
	//float fDMax = m_pkCamera->GetDMax();
	//if (fDMax - fDMin*fW < 0.0f)
	//{
	//	return;
	//}

	//// constraint:  W + X >= 0
	//float fX = afVertex0[0];
	//if (fW + fX < 0.0f)
	//{
	//	return;
	//}

	//// constraint:  W - X >= 0
	//if (fW - fX < 0.0f)
	//{
	//	return;
	//}

	//// constraint:  W + Y >= 0
	//float fY = afVertex0[1];
	//if (fW + fY < 0.0f)
	//{
	//	return;
	//}

	//// constraint:  W - Y >= 0
	//if (fW - fY < 0.0f)
	//{
	//	return;
	//}

	//// Get the screen-space coordinates for the vertex.
	//float fDepth, fInverseW;
	//ClipToWindow(afVertex0, fX, fY, fDepth, fInverseW);
	//int iX0 = RoundfToIntPos(fX);
	//int iY0 = RoundfToIntPos(fY);
	//if (iX0 >= m_iWidth)
	//{
	//	iX0 = m_iWidth - 1;
	//}
	//if (iY0 >= m_iHeight)
	//{
	//	iY0 = m_iHeight - 1;
	//}

	//// Draw the pixel.
	//int iIndex = iX0 + m_iWidth*iY0;
	////SetColorBuffer(iX0, iY0, iIndex, )
}
//----------------------------------------------------------------------------
void SoftRenderer::RasterizeEdge(Vertex* kV0, Vertex* kV1)
{
	Vector4 v = kV1->Pos - kV0->Pos;
	int distance = (int)v.Magnitude();

	if (distance < 1)
	{
		return;
	}

	//mid = p1 + (p2 - p1) / 2;
	v = v* 0.5;
	Vertex mid;
	mid.Pos = kV0->Pos + v;

	//RasterizeEdge((int)mid.x, (int)mid.y, 0x000000);
	int iIndex = (int)mid.Pos.x + m_iWidth*(int)mid.Pos.y;
	SetColorBuffer((int)mid.Pos.x, (int)mid.Pos.y, iIndex, ColorRGBA::BLACK);

	// Recursive 起点至中点，中点至终点
	RasterizeEdge(kV0, &mid);
	RasterizeEdge(&mid, kV1);
}
//----------------------------------------------------------------------------
void SoftRenderer::RasterizeTriangle(Vertex* kV0, Vertex* kV1, Vertex* kV2)
{
	//对三角形顶点排序，坐标系为屏幕坐标系，原点在左上角
	//使得顺序为 P1-P2-P3, P1在离屏幕顶端最近，p3最远，P2在中间，
	if (kV0->Pos.y > kV1->Pos.y)
	{
		Vertex* temp = kV1;
		kV1 = kV0;
		kV0 = temp;
	}
	if (kV1->Pos.y > kV2->Pos.y)
	{
		Vertex* temp = kV1;
		kV1 = kV2;
		kV2 = temp;
	}
	if (kV0->Pos.y > kV1->Pos.y)
	{
		Vertex* temp = kV1;
		kV1 = kV0;
		kV0 = temp;
	}

	//求两边的斜率倒数
	//12 =  p1-p2的直线
	//13 =  p1-p3的直线
	float invSlop_12, invSlop_13;
	if (kV1->Pos.y - kV0->Pos.y > 0)
	{
		invSlop_12 = (kV1->Pos.x - kV0->Pos.x) / (kV1->Pos.y - kV0->Pos.y);
	}
	else
	{
		invSlop_12 = 0;
	}
	if (kV2->Pos.y - kV0->Pos.y > 0)
	{
		invSlop_13 = (kV2->Pos.x - kV0->Pos.x) / (kV2->Pos.y - kV0->Pos.y);
	}
	else
	{
		invSlop_13 = 0;
	}

	//p2位于右边的情况
	if (invSlop_12 > invSlop_13)
	{
		//遍历三角形Y轴
		for (int y = (int)(kV0->Pos.y + 1.f); y < (int)(kV2->Pos.y + 1.f); y++)
		{
			//第一阶段，渲染平底三角形
			if (y < kV1->Pos.y)
			{
				RasterizeScanLine(y + 1.f, kV0, kV2, kV0, kV1);
			}
			else //第一阶段，渲染平顶三角形
			{
				RasterizeScanLine(y + 1.f, kV0, kV2, kV1, kV2);
			}
		}
	}
	//p2位于左边的情况
	else
	{
		//遍历三角形Y轴
		for (int y = (int)(kV0->Pos.y + 1.f); y < (int)(kV2->Pos.y + 1.f); y++)
		{
			//第一阶段，渲染平底三角形
			if (y < kV1->Pos.y)
			{
				RasterizeScanLine(y + 1.f, kV0, kV1, kV0, kV2);
			}
			else //第一阶段，渲染平顶三角形
			{
				RasterizeScanLine(y + 1.f, kV1, kV2, kV0, kV2);
			}
		}
	}
}
//----------------------------------------------------------------------------
void Seer::SoftRenderer::RasterizeScanLine(float y, Vertex* kVa, Vertex* kVb, Vertex* kVc, Vertex* kVd)
{
	//RasterizeEdge();

	if (y<0 || y>=m_iHeight)
	{
		return;
	}

	//求插值的t
	float gradient1 = kVa->Pos.y != kVb->Pos.y ? (y - kVa->Pos.y) / (kVb->Pos.y - kVa->Pos.y) : 1;
	float gradient2 = kVc->Pos.y != kVd->Pos.y ? (y - kVc->Pos.y) / (kVd->Pos.y - kVc->Pos.y) : 1;

	Vertex svx, evx, step;
	svx.Lerp(kVa, kVb, gradient1);
	evx.Lerp(kVc, kVd, gradient2);

	float scanlinewidth = evx.Pos.x - svx.Pos.x;

	step.GetStep(&svx, &evx, scanlinewidth);

	int sx = (int)(svx.Pos.x + 1.f);
	int ex = (int)(evx.Pos.x + 1.f);

	for (int x = sx; x < ex; x++)
	{
		if (x >= 0 && x < m_iWidth)
		{
			//Z深度测试
			float rhw = svx.Rhw;
			if (rhw >= m_afDepthBuffer[(int)y*m_iWidth + x])
			{
				m_afDepthBuffer[(int)y*m_iWidth + x] = rhw;
				//片元处理
				float w = 1.0f / rhw;
				ColorRGBA color = svx.Color;
				color *= w;
				SetColorBuffer(x, (int)y, x + m_iWidth*(int)y, color);
			}
		}

		svx.Pos += step.Pos;
		svx.Rhw += step.Rhw;
		svx.Color += step.Color;

		if (x >= m_iWidth) break;
	}
}
//----------------------------------------------------------------------------