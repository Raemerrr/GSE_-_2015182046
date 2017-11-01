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
	//�׸����Լ�
	SceneManager->ObjectDraw(OBJECT_CHARACTER);
	SceneManager->ObjectDraw(OBJECT_BUILDING);
	SceneManager->ObjectDraw(OBJECT_BULLET);
	//�浹 üũ �� ������, ������ Ÿ�� ���� //������Ʈ
	SceneManager->ObjectCollition(CheckObjectCount, (float)updateTime);

	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
	/*for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		SceneManager->getObject(i, OBJECT_CHARACTER)->Update((float)updateTime);
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
			if (SceneManager->getObject(j, OBJECT_CHARACTER)->getPosition().s < 0.0f)
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
			SceneManager->getObject(DrawObjCheck, OBJECT_CHARACTER)->setPosition(temp1);
			/*SceneManager->getObject(DrawObjCheck, OBJECT_CHARACTER)->setObjLifeTime(100000.0f);
			SceneManager->getObject(DrawObjCheck, OBJECT_CHARACTER)->setObjLife(1000.0f);*/
			SceneManager->getObject(DrawObjCheck, OBJECT_CHARACTER)->setRGB(White);
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
			SceneManager->getObject(CheckObjectCount, OBJECT_CHARACTER)->setDirection(temp2);
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
	SceneManager->ObjectCreate(OBJECT_CHARACTER); //ĳ���� ��ü����
	SceneManager->ObjectCreate(OBJECT_BUILDING); //�ǹ� ��ü����
	SceneManager->ObjectCreate(OBJECT_BULLET); //�Ѿ� ��ü����

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	g_prevTime = timeGetTime();

	glutMainLoop();

	for (int i = 1; i <= 3; ++i) // ARROW �߰��Ǹ� 4����
	{
		SceneManager->ObjectAllDelete(i);
	}
	SceneManager->RendererDelete();
	
	return 0;
}