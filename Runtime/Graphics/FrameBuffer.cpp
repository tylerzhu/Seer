#include "FrameBuffer.h"
#include "Renderer.h"

using namespace Seer;

FrameBuffer::Creator FrameBuffer::ms_aoCreate[Renderer::MAX_RENDERER_TYPES];
FrameBuffer::Destroyer FrameBuffer::ms_aoDestroy[Renderer::MAX_RENDERER_TYPES];

Seer::FrameBuffer::FrameBuffer(Renderer* pkRenderer)
{
	
}

Seer::FrameBuffer::~FrameBuffer()
{

}

FrameBuffer* Seer::FrameBuffer::Create(Renderer* pkRenderer)
{
	Creator oCreator = ms_aoCreate[pkRenderer->GetType()];
	if (oCreator)
	{
		return oCreator(pkRenderer);
	}
	return nullptr;
}

void Seer::FrameBuffer::Destroy(FrameBuffer* pkBuffer)
{
	
}
