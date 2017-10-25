/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)
This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"
#include "SceneMgr.h"

#define MAX_OBJECTS_SIZE 10
#define MAX_OBJECTS_COUNT 10

SceneMgr *SceneManager = new SceneMgr();

bool g_LButtonDown = false; //���콺 Ŭ�� Ȯ��
DWORD g_prevTime = 0;	//���� �ð� Ȯ�� ����
int CheckObjectCount = 0; //������Ʈ ���� Ȯ��

using namespace std;


void RenderScene(void)
{
	DWORD currentTime = timeGetTime();
	DWORD updateTime = currentTime - g_prevTime;
	g_prevTime = currentTime;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	// Renderer Test
	for (int i = 0; i < CheckObjectCount; ++i)
	{
		Data pos = SceneManager->getObject(i)->getPosition();
		Data rgb = SceneManager->getObject(i)->getRGB();
		SceneManager->getRenderer()->DrawSolidRect(pos.x, pos.y, pos.z, pos.s, rgb.x, rgb.y, rgb.z, rgb.s);
	}

	for (int i = 0; i < CheckObjectCount; ++i)	//Life Time���� ��ü ���ֱ�
	{
		if (SceneManager->getObject(i)->getObjLifeTime() <= 0.0f)
		{
			Data temp = { 0.0,0.0,0.0,-1.0 };
			SceneManager->getObject(i)->setPosition(temp); //����� -1�̴� False���·� ������
			CheckObjectCount--;
		}
	}

	for (int i = 0; i < CheckObjectCount; ++i) //�浹üũ�� ���� -1������ �Ѵ�.
	{
		Data White = { 255,255, 255,1.0 };
		SceneManager->getObject(i)->setRGB(White);
		SceneManager->ObjectCollition(i, CheckObjectCount, MAX_OBJECTS_SIZE);
	}

	for (int i = 0; i < CheckObjectCount; ++i)
	{
		SceneManager->getObject(i)->Update((float)updateTime);
	}
	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
	/*for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		SceneManager->getObject(i)->Update();
	}*/
}

void MouseInput(int button, int state, int x, int y)
{
	x = x - 250;
	y = 250 - y;
	Data White = { 255,255, 255,1.0 };
	Data Red = { 255,0, 0,1.0 }; //�������� 
	int DrawObjCheck = 0; //�׷����ִ��� üũ
	DrawObjCheck = CheckObjectCount;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		for (int j = 0; j < MAX_OBJECTS_SIZE; ++j)
		{
			if (SceneManager->getObject(j)->getPosition().s < 0.0f)
			{
				DrawObjCheck = j;
			}
		else if (CheckObjectCount >= MAX_OBJECTS_COUNT)
			{
				return;
			}
		}
		std::cout << "Ŭ���Ǿ����ϴ�." << endl;
		std::cout << "x : " << x << " y : " << y << " CheckObjCount : " << CheckObjectCount << endl;
		g_LButtonDown = true;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		if (g_LButtonDown)
		{
			//clicked
			//���� üũ
			std::cout << "Ŭ�� �����Ǿ����ϴ�." << endl;
			Data temp1 = { (float)x,(float)y,0,MAX_OBJECTS_SIZE };
			SceneManager->getObject(DrawObjCheck)->setPosition(temp1);
			SceneManager->getObject(DrawObjCheck)->setObjLifeTime(100000.0f);
			SceneManager->getObject(DrawObjCheck)->setObjLife(1000.0f);
			SceneManager->getObject(DrawObjCheck)->setRGB(White);
			float checkX = 1;
			float checkY = 1;

			if (rand() % 2 == 1)
			{
				checkX *= -1;
			}if (rand() % 2 == 1)
			{
				checkY *= -1;
			}
			Data temp2 = { checkX,checkY,0.0f,0.0f };
			SceneManager->getObject(CheckObjectCount)->setDirection(temp2);
			CheckObjectCount++;
		}

		g_LButtonDown = false;
	}
	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}

int main(int argc, char **argv)
{
	srand((unsigned)time(NULL));  //�ѹ��� ������ ��.
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	SceneManager->RendererCreate();
	SceneManager->ObjectCreate(MAX_OBJECTS_COUNT, MAX_OBJECTS_SIZE); //��ü����
	
	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	g_prevTime = timeGetTime();

	glutMainLoop();

	SceneManager->RendererDelete();
	SceneManager->ObjectDelete();

	return 0;
}