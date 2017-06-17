#pragma once

#include "Math/ColorRGBA.h"
#include "Camera/Camera.h"
#include "SceneGraph/Geometry.h"

namespace Seer
{

	class Renderer
	{
	public:
		Renderer(int iWidth, int iHeight);
		virtual ~Renderer();

		// Run-time type information.
		enum
		{
			OPENGL,
			DIRECTX,
			SOFTWARE,
			MAX_RENDERER_TYPES
		};
		virtual int GetType() const = 0;

		// camera access and support
		void SetCamera(Camera* pkCamera);
		Camera* GetCamera() const;

		// window parameters
		int GetWidth() const;
		int GetHeight() const;
		virtual void Resize(int iWidth, int iHeight);
		virtual void ToggleFullscreen();

		// background color access
		virtual void SetBackgroundColor(const ColorRGBA& rkColor);
		const ColorRGBA& GetBackgroundColor() const;

		// pre- and postdraw semantics
		virtual bool BeginScene();
		virtual void EndScene();

		// full window buffer operations
		virtual void ClearBackBuffer() = 0;
		//virtual void ClearZBuffer() = 0;
		//virtual void ClearStencilBuffer() = 0;
		virtual void ClearBuffers() = 0;
		virtual void DisplayBackBuffer() = 0;

		// object drawing
		void DrawScene(/*VisibleSet& rkVisibleSet*/Geometry aGeometry[], int iSize);
		void Draw(Geometry* pkGeometry);
	protected:
		// The main entry point to drawing in the derived-class renderers.
		virtual void DrawElements() = 0;

	protected:
		// Support for camera access and transformation setting.
		friend class Camera;
		void OnFrameChange();
		void OnFrustumChange();
		virtual void OnViewportChange() = 0;

	protected:
		int m_iWidth, m_iHeight;
		ColorRGBA m_kBackgroundColor;

		// The camera for establishing the view frustum.
		Camera* m_pkCamera;

		// Current Geometry object for drawing.
		Geometry* m_pkGeometry;

		// Transformations used in the geometric pipeline.  These matrices are
		// stored to support 1x4 row vectors times 4x4 matrices.
		Matrix4 m_kWorldMatrix;
		Matrix4 m_kViewMatrix;
		Matrix4 m_kProjectionMatrix;

		// Toggle for fullscreen/window mode.
		bool m_bFullscreen;
	};

#include "Renderer.inl"

}

