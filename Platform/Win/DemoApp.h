#pragma once

#include "WindowApplication3D.h"
#include "MainMCR.h"
#include <SceneGraph/TriMesh.h>

using namespace Seer;

class DemoApp : public WindowApplication3D
{
	DECLARE_INITIALIZE;

public:
	DemoApp();

	virtual bool OnInitialize() override;
	virtual void OnTerminate() override;
	virtual void OnIdle() override;
	virtual bool OnKeyDown(unsigned char ucKey, int iX, int iY) override;


protected:
	void CreateScene();


	VertexBuffer* m_pkVBuffer;
	IndexBuffer* m_pkIBuffer;
	TriMesh* m_pkTriMesh;
};

REGISTER_INITIALIZE(DemoApp);
