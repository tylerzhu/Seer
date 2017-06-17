#include "Renderer.h"

using namespace Seer;


Seer::Renderer::Renderer(int iWidth, int iHeight):
m_iWidth(iWidth),
m_iHeight(iHeight),
m_kBackgroundColor(ColorRGBA::WHITE)
{
	m_pkCamera = nullptr;
}


Seer::Renderer::~Renderer()
{

}

void Seer::Renderer::Resize(int iWidth, int iHeight)
{	
	m_iWidth = iWidth;
	m_iHeight = iHeight;
	OnViewportChange();	
}

void Seer::Renderer::OnFrameChange()
{

}

void Seer::Renderer::OnFrustumChange()
{

}

void Seer::Renderer::DrawScene(/*VisibleSet& rkVisibleSet*/Geometry aGeometry[], int iSize)
{
	for (size_t i = 0; i < iSize; i++)
	{
		Draw(&aGeometry[i]);
	}
}

void Seer::Renderer::Draw(Geometry* pkGeometry)
{

	m_pkGeometry = pkGeometry;
	
	
	//(m_pkGeometry->View*m_pkGeometry->Local).MultiplyVector4();

	//m_pkGeometry
	//// ¶¥µã´¦Àí
	//vertex ver[3];
	//ver[0].pos = m_pkCamera->GetViewProj().MultiplyVector4(m_pVertex[iV0].pos);
	//ver[1].pos = m_pkCamera->GetViewProj().MultiplyVector4(m_pVertex[iV1].pos);
	//ver[2].pos = m_pkCamera->GetViewProj().MultiplyVector4(m_pVertex[iV2].pos);
	//// 
	//for (size_t i = 0; i < 3; i++)
	//{
	//	float rhw = (1 / ver[i].pos.w);
	//	ver[i].pos = ver[i].pos*rhw;
	//	ver[i].color = ver[i].color*rhw;
	//	ver[i].rhw = rhw;

	//	ver[i].pos =
	//	{
	//		(ver[i].pos.x + 1.0f) * m_pkCamera->GetScreenViewportRect().width * 0.5f,
	//		(1.0f - ver[i].pos.y) * m_pkCamera->GetScreenViewportRect().height * 0.5f,
	//		ver[i].pos.z,
	//		1.0f
	//	};
	//}

	DrawElements();

	// 
	m_pkGeometry = nullptr;



	//m_pkGeometry = pkGeometry;

	//SetGlobalState(m_pkGeometry->States);
	//SetWorldTransformation();

	//// Enable the index buffer.  The connectivity information is the same
	//// across all effects and all passes per effect.
	//EnableIBuffer();

	//// Lighting (if any) is applied first.  Effects are applied second.
	//bool bPrimaryEffect = true;
	//const int iMin = m_pkGeometry->GetStartEffect();
	//const int iMax = m_pkGeometry->GetEffectQuantity();
	//for (int i = iMin; i < iMax; i++)
	//{
	//	// The effect is necessarily a shader effect.  DrawScene bundles
	//	// together objects affected by a global effect.  The global effect's
	//	// Draw function should take care to call only Draw(Geometry*)
	//	// functions to avoid an infinite recursion.
	//	ShaderEffect* pkEffect =
	//		DynamicCast<ShaderEffect>(m_pkGeometry->GetEffect(i));
	//	assert(pkEffect);
	//	ApplyEffect(pkEffect, bPrimaryEffect);
	//}

	//// Disable the index buffer.
	//DisableIBuffer();

	//RestoreWorldTransformation();
	//RestoreGlobalState(m_pkGeometry->States);

	//m_pkGeometry = 0;
}

//----------------------------------------------------------------------------
void Renderer::SetCamera(Camera* pkCamera)
{
	if (m_pkCamera)
	{
		m_pkCamera->m_pkRenderer = nullptr;
	}

	if (pkCamera)
	{
		pkCamera->m_pkRenderer = this;
	}

	m_pkCamera = pkCamera;

	if (m_pkCamera)
	{
		OnFrustumChange();
		OnViewportChange();
		OnFrameChange();
	}
}

