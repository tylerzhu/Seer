#pragma once

namespace Seer
{
	class Renderer;

	class FrameBuffer
	{
	public: // static
		// Abstract base class.  The FrameBuffer::Create and FrameBuffer::Destroy
		// functions form a factory.  The input pkTarget must be a SAMPLER_2D
		// target.  The frame buffer is 2D and has width and height of the target
		// texture.
		static FrameBuffer* Create(Renderer* pkRenderer);
		static void Destroy(FrameBuffer* pkBuffer);

	public:
		FrameBuffer(Renderer* pkRenderer);
		virtual ~FrameBuffer();

	protected:
		Renderer* m_pkRenderer;

		// The frame buffer factory.  Each derived class implements a Creator and
		// a Destroyer and assigns the function pointers to the static data
		// members declared here.
		typedef FrameBuffer* (*Creator)(Renderer*);
		typedef void(*Destroyer)(FrameBuffer*);
		static Creator ms_aoCreate[];
		static Destroyer ms_aoDestroy[];
	};
}

