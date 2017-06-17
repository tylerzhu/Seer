#include "DemoApp.h"
#include "ApplicationMCR.h"
#include "tiny_obj_loader.h"
#include <iostream>

using namespace Seer;

WINDOW_APPLICATION(DemoApp);

const int g_iWidth = 800;
const int g_iHeight = 600;

DemoApp::DemoApp()
	: WindowApplication3D("DemoApp", 0, 0, g_iWidth, g_iHeight, ColorRGBA(1.0, 1.0, 1.0))
{

}

bool DemoApp::OnInitialize()
{
	if (!WindowApplication3D::OnInitialize())
	{
		return false;
	}

	// 设置相机信息
	Vector3 kCDir(0, 0, 0);
	Vector3 kCUp(0, 0, 1);
	Vector3 kCLoc(3.5, 0, 0);
	m_spkCamera->SetLookAt(kCLoc, kCDir, kCUp);
	m_spkCamera->SetPerspective(3.1415926f * 0.5f, g_iWidth / g_iHeight, 1.0f, 500.0f);
	m_spkCamera->SetViewport(0, 0, g_iWidth, g_iHeight);

	CreateScene();

	return true;
}

void DemoApp::OnTerminate()
{

}

bool DemoApp::OnKeyDown(unsigned char ucKey, int iX, int iY)
{
	switch (ucKey)
	{
	case 'a':
	case 'A':	
		// left ←
		m_spkCamera->Strafe(-0.05);
		return true;
	case 'd':
	case 'D':
		// right →
		m_spkCamera->Strafe(0.05);
		return true;
	case 'w':
	case 'W':
		// up ↑
		m_spkCamera->Walk(0.05);
		return true;
	case 's':
	case 'S':
		// down ↓
		m_spkCamera->Walk(-0.05);
		return true;
	}
	return false;
}


void DemoApp::OnIdle()
{
	if (MoveCamera())
	{ ///< 移动相机
	}

	///< 绘制场景
	m_pkRenderer->ClearBuffers();
	if (m_pkRenderer->BeginScene())
	{
		m_pkRenderer->DrawScene(m_pkTriMesh, 1);
		m_pkRenderer->EndScene();
	}
	m_pkRenderer->DisplayBackBuffer();
}

void DemoApp::CreateScene()
{
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string err;
//	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, "Models/mono.obj",
	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, "Models/cube.obj",
		"Models/", false);

	if (!err.empty()) {
		std::cerr << err << std::endl;
	}

	if (!ret) {
		printf("Failed to load/parse .obj.\n");	
		return;
	}

	Vertex* akVertex = new Vertex[attrib.vertices.size()];
	for (size_t v = 0; v < attrib.vertices.size() / 3; v++) {
		(akVertex+v)->Pos = {
			static_cast<const float>(attrib.vertices[3 * v + 0]),
			static_cast<const float>(attrib.vertices[3 * v + 1]),
			static_cast<const float>(attrib.vertices[3 * v + 2]),
			1 
		};
	}

	m_pkVBuffer = new VertexBuffer(akVertex, attrib.vertices.size());


	// For each shape
	for (size_t i = 0; i < shapes.size(); i++) {
		size_t index_offset = 0;
		int* aiIndex = new int[shapes[i].mesh.indices.size()];

		// For each face
		for (size_t f = 0; f < shapes[i].mesh.num_face_vertices.size(); f++) {
			size_t fnum = shapes[i].mesh.num_face_vertices[f];

			// For each vertex in the face
			for (size_t v = 0; v < fnum; v++) {
				tinyobj::index_t idx = shapes[i].mesh.indices[index_offset + v];
				*(aiIndex+index_offset + v) = idx.vertex_index;
			}
			index_offset += fnum;
		}	

		m_pkIBuffer = new IndexBuffer(shapes[i].mesh.indices.size());
		m_pkIBuffer->SetIndex(aiIndex, shapes[i].mesh.indices.size());

		m_pkTriMesh = new TriMesh(m_pkVBuffer, m_pkIBuffer);
		m_pkTriMesh->Local.SetRotate(Vector3(-1, -0.5, 1), 1);
	}
}



