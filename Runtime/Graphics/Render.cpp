#include "Render.h"
#include "stdio.h"
#include "stdlib.h"

Renderer::Renderer(void *fb)
{
	mesh[0] = { { 1, -1, 1, 1 }, { 1.0f, 0.2f, 0.2f }, 1 };
	mesh[1] = { { -1, -1, 1, 1 }, { 0.2f, 1.0f, 0.2f }, 1 };
	mesh[2] = { { -1, 1, 1, 1 }, { 0.2f, 0.2f, 1.0f }, 1 };
	mesh[3] = { { 1, 1, 1, 1 }, { 1.0f, 0.2f, 1.0f }, 1 };
	mesh[4] = { { 1, -1, -1, 1 }, { 1.0f, 1.0f, 0.2f }, 1 };
	mesh[5] = { { -1, -1, -1, 1 }, { 0.2f, 1.0f, 1.0f }, 1 };
	mesh[6] = { { -1, 1, -1, 1 }, { 1.0f, 0.3f, 0.3f }, 1 };
	mesh[7] = { { 1, 1, -1, 1 }, { 0.2f, 1.0f, 0.3f }, 1 };

	boxAngle = 1;
	model.SetRotate(Vector3(-1, -0.5, 1), boxAngle);

	int width = 800, height = 600;
	cameraPos = Vector3(3.5, 0, 0);
	camera.SetLookAt(cameraPos, Vector3(0, 0, 0), Vector3(0, 0, 1));
	camera.SetPerspective(3.1415926f * 0.5f, width / height, 1.0f, 500.0f);
	camera.SetViewport(0, 0, width, height);

	camera.GetView();

	int buff_array_head_size = sizeof(void*) * height;
	int texture_array_head_size = sizeof(void*) * 1024;
	int buff_size = width*height * 4;

	int total = buff_array_head_size * 2 + texture_array_head_size + buff_size * 2;
	char* ptr = (char*)malloc(total + 64);

	char *framebuf, *zbuf;

	frameBuffer = (unsigned int**)ptr;
	zBuffer = (float**)(ptr + sizeof(void*) * height);
	ptr += sizeof(void*) * height * 2;
	texture = (unsigned int**)ptr;
	ptr += sizeof(void*) * 1024;
	framebuf = (char*)ptr;
	zbuf = (char*)ptr + width*height * 4;
	ptr += width * height * 8;

	if (fb != NULL)
	{
		framebuf = (char*)fb;
	}

	for (int i = 0; i < height; i++)
	{
		frameBuffer[i] = (unsigned int*)(framebuf + width * 4 * i);
		zBuffer[i] = (float*)(zbuf + width * 4 * i);
	}

	texture[0] = (unsigned int*)ptr;
	texture[1] = (unsigned int*)ptr + 16;
}

Renderer::~Renderer()
{
}

void Renderer::Loop()
{
	Clear();

//	printf("render loop\n");

	// step1. 获取模型数据
	// 顶点、颜色、贴图、法向量.....


	// step2. 将模型放置到世界坐标系中 (SRT - 缩放、旋转、位移)
	// 模型矩阵： 将模型坐标转换到世界坐标 
	vertex new_mesh_vertex[8];
	int len = sizeof(new_mesh_vertex) / (sizeof(Vector4) + sizeof(ColorRGBA) + sizeof(real));
	for (int i = 0; i < len; i++)
	{
		model.MultiplyVector4(mesh[i].pos, new_mesh_vertex[i].pos);
		new_mesh_vertex[i].color = mesh[i].color;
		new_mesh_vertex[i].rhw = mesh[i].rhw;

//		new_mesh_vertex[i] = { model.MultiplyVector4(mesh[i].pos), mesh[i].color, 1 };
	}	

//	// step3. 设置摄像机（观察点）- 位置 + 观察点（朝向） + 上方向
//	// 视图矩阵： 将世界坐标转换到相机坐标
//	for (int i = 0; i < len; i++)
//	{
//		new_mesh_vertex[i].pos = camera.GetView().MultiplyVector4(new_mesh_vertex[i].pos);
//	}
//	///< 经过模型变换、视图变换，此时w分量还是1
//
//	// step4. 透视投影
//	// 定义视锥体 - 视角fov + 近裁剪面 + 远裁剪面，投影屏幕：一般定义距离d=1 视口：屏幕宽高比aspect
//	// 透视投影矩阵： 裁剪掉视锥体之外的顶点，并将3D模型透视投影到2D视口
//	for (int i = 0; i < len; i++)
//	{
//		new_mesh_vertex[i].pos = camera.GetProjection().MultiplyVector4(new_mesh_vertex[i].pos);
//	}


	// step3 & step4
	for (int i = 0; i < len; i++)
	{
		new_mesh_vertex[i].pos = camera.GetViewProj().MultiplyVector4(new_mesh_vertex[i].pos);
	}


	///< 经过投影变换之后，此时w分量已经发生了变换，不在保持为1了
	///< 将齐次坐标转换为普通坐标（笛卡尔坐标）：Reciprocal of Homogeneous W - RHW
	///< 投影几何 -> 齐次坐标； 欧氏空间 -> 普通坐标（笛卡尔坐标）
	for (int i = 0; i < len; i++)
	{
		real rhw = (1 / new_mesh_vertex[i].pos.w);
		new_mesh_vertex[i].pos = new_mesh_vertex[i].pos*rhw;
		new_mesh_vertex[i].color = new_mesh_vertex[i].color*rhw;
		new_mesh_vertex[i].rhw = rhw;
	}
	
	// step5. 视口变换/屏幕映射
	// 视口变换矩阵： 将2D视口上的点转换为屏幕上的点 （这是一个缩放过程）
	for (int i = 0; i < len; i++)
	{
		new_mesh_vertex[i].pos =  
			{ 
				(new_mesh_vertex[i].pos.x + 1.0f) * camera.GetScreenViewportRect().width * 0.5f,
				(1.0f - new_mesh_vertex[i].pos.y) * camera.GetScreenViewportRect().height * 0.5f, 
				new_mesh_vertex[i].pos.z,
				1.0f
			};
	}


	// step6. 光栅化 - 绘制2D几何图元，将几何图元逐一光栅化为像素颜色并输出到屏幕（帧缓存）
	// 将矢量信息（由形状或基元构成）转换为光栅图像（由像素构成）

	// 0, 1, 2, 3
	DrawPrimitive(new_mesh_vertex[0], new_mesh_vertex[1], new_mesh_vertex[2]);
	DrawPrimitive(new_mesh_vertex[2], new_mesh_vertex[3], new_mesh_vertex[0]);
	// 4, 5, 6, 7
	DrawPrimitive(new_mesh_vertex[4], new_mesh_vertex[5], new_mesh_vertex[6]);
	DrawPrimitive(new_mesh_vertex[6], new_mesh_vertex[7], new_mesh_vertex[4]);
	// 0, 4, 5, 1
	DrawPrimitive(new_mesh_vertex[0], new_mesh_vertex[4], new_mesh_vertex[5]);
	DrawPrimitive(new_mesh_vertex[5], new_mesh_vertex[1], new_mesh_vertex[0]);
	// 1, 5, 6, 2
	DrawPrimitive(new_mesh_vertex[1], new_mesh_vertex[5], new_mesh_vertex[6]);
	DrawPrimitive(new_mesh_vertex[6], new_mesh_vertex[2], new_mesh_vertex[1]);
	// 2, 6, 7, 3
	DrawPrimitive(new_mesh_vertex[2], new_mesh_vertex[6], new_mesh_vertex[7]);
	DrawPrimitive(new_mesh_vertex[7], new_mesh_vertex[3], new_mesh_vertex[2]);
	// 3, 7, 4, 0
	DrawPrimitive(new_mesh_vertex[3], new_mesh_vertex[7], new_mesh_vertex[4]);
	DrawPrimitive(new_mesh_vertex[4], new_mesh_vertex[0], new_mesh_vertex[3]);
}

void Renderer::DrawLine(const Vector4& v1, const Vector4& v2)
{
	Vector4 v = v2 - v1;
	int distance = (int)v.Magnitude();

	if (distance < 1)
	{
		return;
	}

	//mid = p1 + (p2 - p1) / 2;
	v = v* 0.5;
	Vector4 mid = v1 + v;

	DrawPixel((int)mid.x, (int)mid.y, 0x000000);

	// Recursive  起點至中點，中點至終點
	DrawLine(v1, mid);
	DrawLine(mid, v2);
}

void Renderer::DrawPixel(int x, int y, unsigned int color)
{
	if (x<800 && x>=0 && y <600&&y>=0)
	{
		frameBuffer[y][x] = color;
	}
	
}

void Renderer::Clear()
{
	int y, x;

	//清理颜色缓冲区
	for (y = 0; y < 600; y++)
	{
		unsigned int* dst = frameBuffer[y];
		unsigned int cc = 0x555555;

		for (x = 800; x > 0; dst++, x--)
		{
			dst[0] = cc;
		}
	}

	//清理深度缓冲区
	for (y = 0; y < 600; y++)
	{
		float *dst = zBuffer[y];
		for (x = 800; x > 0; dst++, x--)
		{
			dst[0] = -1.f;
		}
	}
}


void Renderer::DrawPrimitive(vertex& v1, vertex& v2, vertex& v3)
{
	// 线框模式
//	DrawLine(v1.pos, v2.pos);
//	DrawLine(v1.pos, v3.pos);
//	DrawLine(v3.pos, v2.pos);

	// 颜色模式	
	Rasterize(&v1, &v2, &v3);
}

void Renderer::Rasterize(vertex* v1, vertex* v2, vertex* v3)
{
	//对三角形顶点排序，坐标系为屏幕坐标系，原点在左上角
	//使得顺序为 P1-P2-P3, P1在离屏幕顶端最近，p3最远，P2在中间，
	if (v1->pos.y > v2->pos.y)
	{
		vertex* temp = v2;
		v2 = v1;
		v1 = temp;
	}
	if (v2->pos.y > v3->pos.y)
	{
		vertex* temp = v2;
		v2 = v3;
		v3 = temp;
	}
	if (v1->pos.y > v2->pos.y)
	{
		vertex* temp = v2;
		v2 = v1;
		v1 = temp;
	}

	//求两边的斜率倒数
	//12 =  p1-p2的直线
	//13 =  p1-p3的直线
	float invSlop_12, invSlop_13;
	if (v2->pos.y - v1->pos.y > 0)
	{
		invSlop_12 = (v2->pos.x - v1->pos.x) / (v2->pos.y - v1->pos.y);
	}
	else
	{
		invSlop_12 = 0;
	}
	if (v3->pos.y - v1->pos.y > 0)
	{
		invSlop_13 = (v3->pos.x - v1->pos.x) / (v3->pos.y - v1->pos.y);
	}
	else
	{
		invSlop_13 = 0;
	}

	//p2位于右边的情况
	if (invSlop_12 > invSlop_13)
	{
		//遍历三角形Y轴
		for (int y = (int)(v1->pos.y + 1.f); y < (int)(v3->pos.y + 1.f); y++)
		{
			//第一阶段，渲染平底三角形
			if (y < v2->pos.y)
			{
				DrawScanLine(y + 1.f, v1, v3, v1, v2);
			}
			else //第一阶段，渲染平顶三角形
			{
				DrawScanLine(y + 1.f, v1, v3, v2, v3);
			}
		}
	}
	//p2位于左边的情况
	else
	{
		//遍历三角形Y轴
		for (int y = (int)(v1->pos.y + 1.f); y < (int)(v3->pos.y + 1.f); y++)
		{
			//第一阶段，渲染平底三角形
			if (y < v2->pos.y)
			{
				DrawScanLine(y + 1.f, v1, v2, v1, v3);
			}
			else //第一阶段，渲染平顶三角形
			{
				DrawScanLine(y + 1.f, v2, v3, v1, v3);
			}
		}
	}
}

void Renderer::DrawScanLine(float y, vertex* va, vertex* vb, vertex* vc, vertex* vd)
{
	//求插值的t
	float gradient1 = (float)va->pos.y != vb->pos.y ? (y - va->pos.y) / (vb->pos.y - va->pos.y) : 1;
	float gradient2 = (float)vc->pos.y != vd->pos.y ? (y - vc->pos.y) / (vd->pos.y - vc->pos.y) : 1;

	vertex svx, evx, step;
	svx.Lerp(va, vb, gradient1);
	evx.Lerp(vc, vd, gradient2);

	float scanlinewidth = evx.pos.x - svx.pos.x;

	step.GetStep(&svx, &evx, scanlinewidth);

	int sx = (int)(svx.pos.x + 1.f);
	int ex = (int)(evx.pos.x + 1.f);
	int width = 800;
	float* zbuffer = zBuffer[(int)y];

	for (int x = sx; x < ex; x++)
	{
		if (x >= 0 && x < width)
		{
			//Z深度测试
			float rhw = svx.rhw;
			if (rhw >= zbuffer[x])
			{
				zbuffer[x] = rhw;
				//片元处理
				float w = 1.0f / rhw;
				ColorRGBA color = svx.color;
				color *= w;
				DrawPixel(x, y, color.GetHexIngoreA());
//				DrawPixel(x, y, color.GetHex());
			}
		}

		svx.pos += step.pos;
		svx.rhw += step.rhw;
		svx.color += step.color;

		if (x >= width) break;
	}
}

void Renderer::SetCameraPos(const Vector3& pos)
{
	cameraPos = pos;
//	camera.SetLookAt(cameraPos, Vector3(0, 0, 0), Vector3(0, 0, 1));
	camera.SetPosition(cameraPos);
}

void Renderer::RightCameraPos()
{
	cameraPos.x += 0.1f;
	SetCameraPos(cameraPos);
}

void Renderer::LeftCameraPos()
{
	cameraPos.x -= 0.1f;
	SetCameraPos(cameraPos);
}

void Renderer::RotateBox(float deltaAngle)
{
	boxAngle += deltaAngle;
	model.SetRotate(Vector3(-1, -0.5, 1), boxAngle);
}

void Renderer::Walk(float delta)
{
	camera.Walk(delta);
}

void Renderer::Strafe(float delta)
{
	camera.Strafe(delta);
}

void Renderer::Pitch(float delta)
{
	camera.Pitch(delta);
}

void Renderer::RotateY(float delta)
{
	camera.RotateY(delta);
}


