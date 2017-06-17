#pragma once



//----------------------------------------------------------------------------
inline Camera* Renderer::GetCamera() const
{
	return m_pkCamera;
}

//----------------------------------------------------------------------------
inline int Renderer::GetWidth() const
{
	return m_iWidth;
}
//----------------------------------------------------------------------------
inline int Renderer::GetHeight() const
{
	return m_iHeight;
}
//----------------------------------------------------------------------------
inline void Renderer::ToggleFullscreen()
{
	m_bFullscreen = !m_bFullscreen;
}
//----------------------------------------------------------------------------
inline void Renderer::SetBackgroundColor(const ColorRGBA& rkColor)
{
	m_kBackgroundColor = rkColor;
}
//----------------------------------------------------------------------------
inline const ColorRGBA& Renderer::GetBackgroundColor() const
{
	return m_kBackgroundColor;
}
//----------------------------------------------------------------------------
inline bool Renderer::BeginScene()
{
	// stub for derived classes
	return true;
}
//----------------------------------------------------------------------------
inline void Renderer::EndScene()
{
	// stub for derived classes
}