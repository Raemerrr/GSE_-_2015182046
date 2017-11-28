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

int CheckObjectCount = (MAX_OBJECTS_COUNT/2); //������Ʈ ���� Ȯ��
float CharSpawnTime = 0;
float BuildSpawnTime = 0;
float BulleltSpawnTime = 0;
float ArrowSpawnTime = 0;
int DrawObjCheck = 0; //�׷����ִ��� üũ

using namespace std;

void RenderScene(void)
{

	DWORD currentTime = timeGetTime();
	DWORD updateTime = currentTime - g_prevTime;
	g_prevTime = currentTime;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.f);

	// Renderer Test
	//�׸����Լ�
	SceneManager->ObjectDraw(OBJECT_CHARACTER, CharSpawnTime);

	SceneManager->ObjectDraw(OBJECT_BUILDING, BuildSpawnTime);
	
	BulleltSpawnTime += (float)updateTime;
	//cout << BulleltSpawnTime << endl;
	SceneManager->ObjectDraw(OBJECT_BULLET, BulleltSpawnTime);	//���� 3��° ���ڰ� CheckObjectCount�� ArrowDraw �ø� �̿��
	//cout << "x�� : "<< SceneManager->getObject(0, OBJECT_BULLET)->getPosition().x << " y�� : " << SceneManager->getObject(0, OBJECT_BULLET)->getPosition().y << " s�� : " << SceneManager->getObject(0, OBJECT_BULLET)->getPosition().s <<endl;
	
	ArrowSpawnTime += (float)updateTime;
	//cout << ArrowSpawnTime << endl;
	SceneManager->ObjectDraw(OBJECT_ARROW, ArrowSpawnTime);	//���� 3��° ���ڰ� CheckObjectCount�� ArrowDraw �ø� �̿��
	//cout << "x�� : "<< SceneManager->getObject(0, OBJECT_ARROW)->getPosition().x << " y�� : " << SceneManager->getObject(0, OBJECT_ARROW)->getPosition().y << " s�� : " << SceneManager->getObject(0, OBJECT_ARROW)->getPosition().s <<endl;

	//�浹 üũ �� ������, ������ Ÿ�� ���� //������Ʈ
	//SceneManager->ObjectCollition(CheckObjectCount, (float)updateTime);
	SceneManager->ObjectCollition2((float)updateTime);
	SceneManager->ObjectCollition1((float)updateTime);
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
	x = (x - (MAX_SCREEN_WIDTH/2));
	y = ((MAX_SCEEN_HEIGHT / 2) - y);
	Data TEAM2CharColor = { 0.f,0.f, 255,255 };
	Data Red = { 255.f,0.f, 0.f,1.f }; //�������� 
	//DrawObjCheck = 0; //�׷����ִ��� üũ
	//int DrawArrCheck = 0; //ȭ�� �׷����ִ��� üũ
	//DrawObjCheck = CheckObjectCount;
	//DrawArrCheck = CheckArrowCount;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (!g_LButtonDown)
		{
			//cout << "DrawObjCheck : " << DrawObjCheck << " CheckObjectCount : " << CheckObjectCount << endl;
			if (CheckObjectCount > MAX_OBJECTS_COUNT)
			{
				return;
			}
			DrawObjCheck = 0; //�׷����ִ��� üũ
			for (int j = (MAX_OBJECTS_COUNT/2); j < MAX_OBJECTS_COUNT; ++j)
			{
				if (SceneManager->getObject(j, OBJECT_CHARACTER)->getPosition().s < 0.0f)
				{
					//cout << "SceneManager->getObject(" << j << ", OBJECT_CHARACTER)->getPosition().s < 0.0f ����" << endl;
					DrawObjCheck = CheckObjectCount;
					//cout << CheckObjectCount << endl;
					CheckObjectCount = j;
					//cout << "DrawObjCheck : " << DrawObjCheck << " CheckObjectCount : " << CheckObjectCount << endl;
					break;
				}
			}
			//std::cout << "Ŭ���Ǿ����ϴ�." << endl;
			//cout << "x : " << x << " y : " << y << " CheckObjCount : " << CheckObjectCount << " DrawObjCheck :" << DrawObjCheck << endl;
		}
		g_LButtonDown = true;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		if (g_LButtonDown)
		{
			//clicked
			//���� üũ
			//cout << "Ŭ�� �����Ǿ����ϴ�." << endl;
			Data temp1 = { (float)x,(float)y,0,MAX_OBJECTS_SIZE };
			SceneManager->getObject(CheckObjectCount, OBJECT_CHARACTER)->setPosition(temp1);
			/*SceneManager->getObject(DrawObjCheck, OBJECT_CHARACTER)->setObjLifeTime(100000.0f);*/
			SceneManager->getObject(CheckObjectCount, OBJECT_CHARACTER)->fixedObjLife(1.0f);
			SceneManager->getObject(CheckObjectCount, OBJECT_CHARACTER)->setRGB(TEAM2CharColor);
			SceneManager->getObject(CheckObjectCount, OBJECT_CHARACTER)->setTeamNum(2);
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

			if (DrawObjCheck != 0) 
			{
			CheckObjectCount = DrawObjCheck;
			}
			if (CheckObjectCount < (MAX_OBJECTS_COUNT-1) && DrawObjCheck == 0)
			{
				CheckObjectCount++;
			}
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
	glutInitWindowSize(MAX_SCREEN_WIDTH, MAX_SCEEN_HEIGHT);			//ȭ�� ũ�� ó��
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
	//SceneManager->ObjectCreate(OBJECT_CHARACTER); //ĳ���� ��ü����
	//SceneManager->ObjectCreate(OBJECT_BUILDING); //�ǹ� ��ü����
	//SceneManager->ObjectCreate(OBJECT_BULLET); //�Ѿ� ��ü����
	//SceneManager->ObjectCreate(OBJECT_ARROW); //ĳ���Ѿ� ��ü����
	for (int i = 1; i <= 4; ++i) // ARROW �߰��Ǹ� 4����
	{
		SceneManager->ObjectCreate(i);
	}
	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	g_prevTime = timeGetTime();

	glutMainLoop();

	//for (int i = 1; i <= 4; ++i) // ARROW �߰��Ǹ� 4����
	//{
	//	SceneManager->ObjectAllDelete(i);
	//}
	//SceneManager->RendererDelete();
	
	return 0;
}