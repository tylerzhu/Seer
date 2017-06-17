#pragma once
#include "Mesh.h"
#include "Math/Matrix4.h"
#include "Camera/Camera.h"

class Renderer
{
public:
	Renderer(void *fb);
	~Renderer();

	void Loop();
	
public:
	void RotateBox(float deltaAngle);
	void Walk(float delta);
	void Strafe(float delta);
	void Pitch(float delta);
	void RotateY(float delta);

public:
	void SetCameraPos(const Vector3& pos);
	void LeftCameraPos();
	void RightCameraPos();

public:
	void Clear();
	void DrawPrimitive(vertex& v1, vertex& v2, vertex& v3);
	void DrawLine(const Vector4& v1, const Vector4& v2);
	void DrawPixel(int x, int y, unsigned int color);

	void Rasterize(vertex* v1, vertex* v2, vertex* v3);
	void DrawScanLine(float param1, vertex* va, vertex* vb, vertex* vc, vertex* vd);


private:

	vertex mesh[8];
	Matrix4 model;	
	Camera camera;

	unsigned int** frameBuffer;
	float** zBuffer;
	unsigned int** texture;

	Vector3 cameraPos;
	float boxAngle;
};



