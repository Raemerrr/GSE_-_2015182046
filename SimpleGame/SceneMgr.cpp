#include "stdafx.h"
#include "SceneMgr.h"

using namespace std;

SceneMgr::SceneMgr()
{
	obj = NULL;
	obj_BUILDING = NULL;
	obj_BULLET = NULL;
	obj_ARROW = NULL;
	g_Renderer = NULL;
	bulletCount = 0;
	arrowCount = 0;
	bulletTimeSet = 0;
	arrowTimeSet = 0;
	pngNum = g_Renderer->CreatePngTexture("./Resource/building_set.png");
}

SceneMgr::~SceneMgr()
{
}

void SceneMgr::ObjectCreate(int Object_Type)
{

	if (Object_Type == OBJECT_CHARACTER)
	{
		obj = new Object[MAX_OBJECTS_COUNT]();
		/*for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		{
			obj[i] = NULL;
		}*/
	}
	else if (Object_Type == OBJECT_BUILDING)
	{
		obj_BUILDING = new Object[MAX_BUILDING_COUNT]();
		for (int i = 0; i < MAX_BUILDING_COUNT; ++i) //�ǹ� �ʱ�ȭ
		{
			Data temp1 = { 0.0f,0.0f,0.0f,MAX_BUILDING_SIZE };
			obj_BUILDING[i].setPosition(temp1);
		}
	}
	else if (Object_Type == OBJECT_BULLET)
	{
		obj_BULLET = new Object[MAX_BULLET_COUNT]();
		for (int i = 0; i < MAX_BULLET_COUNT; ++i)	//�Ѿ� �ʱ�ȭ
		{
			float checkX = 1;
			float checkY = 1;

			if (rand() % 2 == 1)
			{
				checkX *= -1;
			}if (rand() % 2 == 1)
			{
				checkY *= -1;
			}
			Data temp3 = { checkX,checkY,0.0f,0.0f };
			obj_BULLET[i].setDirection(temp3);

			/*Data temp2 = { 0.0f,0.0f,0.0f,0.0f };
			obj_BULLET[i].setPosition(temp2);*/
			Data RGB = { 0.0f,0.0f,255.0f,1.0f };
			obj_BULLET[i].setRGB(RGB);
			obj_BULLET[i].fixedObjLife(10.0f);
		}
	}
	else if (Object_Type == OBJECT_ARROW)
	{
		obj_ARROW = new Object[MAX_ARROW_COUNT]();
		for (int i = 0; i < MAX_ARROW_COUNT; ++i)	//�Ѿ� �ʱ�ȭ
		{
			float checkX = 1;
			float checkY = 1;

			if (rand() % 2 == 1)
			{
				checkX *= -1;
			}if (rand() % 2 == 1)
			{
				checkY *= -1;
			}
			Data temp3 = { checkX,checkY,0.0f,0.0f };
			obj_ARROW[i].setDirection(temp3);

			/*Data temp2 = { 0.0f,0.0f,0.0f,0.0f };
			obj_BULLET[i].setPosition(temp2);*/
			Data RGB = { 0.0f,255.0f,255.0f,1.0f };
			obj_ARROW[i].setRGB(RGB);
			obj_ARROW[i].fixedObjLife(10.0f);
		}
	}
}

void SceneMgr::ObjectAllDelete(int Object_Type)
{
	if (Object_Type == OBJECT_CHARACTER)
	{
		delete[] obj;
	}
	else if (Object_Type == OBJECT_BUILDING)
	{
		delete[] obj_BUILDING;
	}
	else if (Object_Type == OBJECT_BULLET)
	{
		delete[] obj_BULLET;
	}
	else if (Object_Type == OBJECT_ARROW)
	{
		delete[] obj_ARROW;
	}
}

Object* SceneMgr::getObject(int i, int Object_Type)
{
	if (Object_Type == OBJECT_CHARACTER)
	{
		return &obj[i];
	}
	else if (Object_Type == OBJECT_BUILDING)
	{
		return &obj_BUILDING[i];
	}
	else if (Object_Type == OBJECT_BULLET)
	{
		return &obj_BULLET[i];
	}
	else
	{
		return &obj_ARROW[i];
	}
}

void SceneMgr::setObject(Object pos)
{
}

void SceneMgr::RendererCreate() {
	g_Renderer = new Renderer(500, 500);
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
}

void SceneMgr::RendererDelete() {
	delete g_Renderer;
}

Renderer* SceneMgr::getRenderer() {
	return g_Renderer;
}

void SceneMgr::setRenderer(Renderer p) {
}

void SceneMgr::ObjectCollition(int& MAX, float updateTime)
{
	//Data Red = { 255,0, 0,1.0 }; //�������� 
	//Data White = { 255,255, 255,1.0 };
	//Data Blue = { 0.0,0.0,255,1.0 };
	//for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	//{
	//	obj[i].setRGB(White);
	//	if (obj[i].getPosition().s > 0.0f)
	//	{
	//		int Size = MAX_OBJECTS_SIZE / 2;

	//		Data charRect = obj[i].getPosition();
	//		for (int j = 0; j < MAX_OBJECTS_COUNT; ++j)
	//		{
	//			if (i == j)
	//			{
	//				continue;
	//			}
	//			Data buildRect = obj[j].getPosition();
	//			if ((charRect.x - Size) < (buildRect.x + Size) && (charRect.x + Size) > (buildRect.x - Size) && (charRect.y - Size) < (buildRect.y + Size) && (charRect.y + Size) > (buildRect.y - Size))
	//			{
	//				obj[i].setRGB(Red);
	//				obj[i].setObjLife((-1.0));
	//			}
	//		}
	//		if (obj[i].getObjLife() <= 0.0 || obj[i].getObjLifeTime() < 0.0f)
	//		{
	//			Data temp = { 0.0,0.0,0.0,-1.0 };
	//			obj[i].setPosition(temp); //����� -1 �̴� False ���¶� ��
	//			MAX--;
	//			//delete &obj[i];
	//			//obj[i] = nullptr;
	//		}
	//		else
	//		{
	//			obj[i].Update((float)updateTime);

	//		}
	//	}
	//}
	//-------------------OBJECT_CHARACTER ���� �浹 ��� �ּ�ó��
	Data Red = { 255,0, 0,1.0 }; //�������� 
	Data White = { 255,255, 255,1.0 };
	Data Blue = { 0.0,0.0,255,1.0 };

	int obj_Character_Size = MAX_OBJECTS_SIZE / 2;
	int obj_Bulidong_Size = MAX_BUILDING_SIZE / 2;
	int obj_Bullet_Size = MAX_BULLET_SIZE / 2;
	int obj_Arrow_Size = MAX_ARROW_SIZE / 2;


	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (obj[i].getPosition().s < 0.0f || obj[i].getObjLifeTime() < 0.0)	//�̹� 0.0f�� ���� ó���� ������ �浹 üũ�� ���� �ʴ´�.
		{
			continue;
		}
		obj[i].setRGB(White);

		Data charRect = obj[i].getPosition();
		Data arrowRect = obj_ARROW[i].getPosition();
		for (int j = 0; j < MAX_BUILDING_COUNT; ++j)
		{
			Data buildRect = obj_BUILDING[j].getPosition();
			//cout << "������ ü�� : " << obj_BUILDING[j].getObjLife() << endl;
			/*if (i == j)
			{
				continue;
			}*/

			if (obj_BUILDING[j].getObjLife() < 0.0f || obj_BUILDING[j].getPosition().s < 0.0)
			{
				continue;
			}
			if (((charRect.x - obj_Character_Size) < (buildRect.x + obj_Bulidong_Size) && (charRect.x + obj_Character_Size) > (buildRect.x - obj_Bulidong_Size) && (charRect.y - obj_Character_Size) < (buildRect.y + obj_Bulidong_Size) && (charRect.y + obj_Character_Size) > (buildRect.y - obj_Bulidong_Size)) )
			{
				cout << "������ ü�� : " << obj_BUILDING[j].getObjLife() << endl;
				obj[i].setRGB(Red);
				obj_BUILDING[j].setObjLife((-100.00f));
				obj[i].setObjLife(-5.0f);
			}
			/*if ((arrowRect.x - obj_Arrow_Size) < (buildRect.x + obj_Bulidong_Size) && (arrowRect.x + obj_Arrow_Size) > (buildRect.x - obj_Bulidong_Size) && (arrowRect.y - obj_Arrow_Size) < (buildRect.y + obj_Bulidong_Size) && (arrowRect.y + obj_Arrow_Size) > (buildRect.y - obj_Bulidong_Size)) 
			{
				cout << "������ ü�� : " << obj_BUILDING[j].getObjLife() << endl;
				obj_ARROW[i].setRGB(Red);
				obj_BUILDING[j].setObjLife((-100.00f));
				obj_ARROW[i].setObjLife(-5.0f);
			}*/


			if (obj[i].getObjLife() <= 0.0f)
			{
				Data temp2 = { 0.0,0.0,0.0,-1.0 };
				obj[i].setPosition(temp2);			//����� -1 �̴� False ���¶� ��
				//obj[i].fixedObjLife(-1.0f);			//-1�� �������� �����ϸ� �浹üũ, ��߻� �� ���� ���� ����.
				MAX--;
			}
			//if (obj_ARROW[i].getObjLife() <= 0.0f)
			//{
			//	Data temp2 = { 0.0,0.0,0.0,-1.0 };
			//	obj_ARROW[i].setPosition(temp2);			//����� -1 �̴� False ���¶� ��
			//										//obj[i].fixedObjLife(-1.0f);			//-1�� �������� �����ϸ� �浹üũ, ��߻� �� ���� ���� ����.
			//	
			//}
			if (obj_BUILDING[j].getObjLife() <= 0.0)//|| obj_BUILDING[i].getObjLifeTime() < 0.0f
			{
				Data temp = { 0.0,0.0,0.0,-1.0 };
				obj_BUILDING[j].setPosition(temp); //����� -1 �̴� False ���¶� ��
												   //delete &obj_BUILDING[i];
												   //obj[i] = nullptr;
				for (int r = 0; r < MAX_BULLET_COUNT; ++r)
				{
					Data temp2 = { 0.0,0.0,0.0,-1.0 };
					obj_BULLET[r].setPosition(temp2);			//����� -1 �̴� False ���¶� ��
					obj_BULLET[r].fixedObjLife(-1.0f);			//-1�� �������� �����ϸ� �浹üũ, ��߻� �� ���� ���� ����.
				}
			}
		}
		for (int q = 0; q < MAX_BULLET_COUNT; ++q)
		{
			Data bulletRect = obj_BULLET[q].getPosition();
			if (obj_BULLET[q].getObjLife() < 0.0f)
			{
				continue;
			}
			if ((charRect.x - obj_Character_Size) < (bulletRect.x + obj_Bullet_Size) && (charRect.x + obj_Character_Size) > (bulletRect.x - obj_Bullet_Size) && (charRect.y - obj_Character_Size) < (bulletRect.y + obj_Bullet_Size) && (charRect.y + obj_Character_Size) > (bulletRect.y - obj_Bullet_Size))
			{
				//cout << "�Ѿ��� ü�� : " << obj_BULLET[q].getObjLife() << endl;
				obj[i].setRGB(Red);
				obj_BULLET[q].setObjLife((-10.00f));
			}
			if (obj_BULLET[q].getObjLife() < 0.0)//|| obj_BUILDING[i].getObjLifeTime() < 0.0f
			{
				Data temp = { 0.0,0.0,0.0,-1 };
				obj_BULLET[q].setPosition(temp);			//����� -1 �̴� False ���¶� ��
				obj_BULLET[q].fixedObjLife(10.0f);			//delete &obj_BUILDING[i];
															//obj[i] = nullptr;
				float checkX = 1;
				float checkY = 1;

				if (rand() % 2 == 1)
				{
					checkX *= -1;
				}if (rand() % 2 == 1)
				{
					checkY *= -1;
				}
				Data temp3 = { checkX,checkY,0.0f,0.0f };
				obj_BULLET[q].setDirection(temp3);

			}
			else
			{
				obj_BULLET[q].Update((float)updateTime, OBJECT_BULLET);
			}
		}
		obj[i].Update((float)updateTime, OBJECT_CHARACTER);
		//obj_ARROW[i].Update((float)updateTime, OBJECT_ARROW);
	}
}
void SceneMgr::ObjectDraw(int Object_Type, float& timeSet) {
	//bulletTimeSet += timeSet;
	//bulletTimeSet += 1;
	//cout << timeSet << endl;

	//arrowTimeSet += timeSet;
	//arrowTimeSet += 1;
	if (Object_Type == OBJECT_CHARACTER)
	{
		for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		{
			Data pos = obj[i].getPosition();
			Data rgb = obj[i].getRGB();
			g_Renderer->DrawSolidRect(pos.x, pos.y, pos.z, pos.s, rgb.x, rgb.y, rgb.z, rgb.s);
		}
	}
	else if (Object_Type == OBJECT_BUILDING)
	{
		for (int i = 0; i < MAX_BUILDING_COUNT; ++i)
		{
			//Data BUILDINGPOS = { 0.0f,0.0f,0.0f,MAX_BUILDING_SIZE };
			//obj_BUILDING[i].setPosition(BUILDINGPOS);  //�ʱⰪ�� ����� 0�̱⶧���� �������� ����. �׷��� �ǹ� ũ�⸸ ŭ���� ����
			//obj_BUILDING[i].setObjLife((1.0f));
			//�̰����� ���Ͱ��� �� �۾��� �ϰԵǸ� ���� ���������� ��� ���� �����ְų�, ���ڸ��� ��ġ�ϰ� ����� ������ ��.

			Data pos = obj_BUILDING[i].getPosition();
			Data rgb = obj_BUILDING[i].getRGB();
			//g_Renderer->DrawSolidRect(pos.x, pos.y, pos.z, pos.s, rgb.x, rgb.y, rgb.z, rgb.s);
			g_Renderer->DrawTexturedRect(pos.x, pos.y, pos.z, pos.s, rgb.x, rgb.y, rgb.z, rgb.s, pngNum);
			
		}
	}
	else if (Object_Type == OBJECT_BULLET)
	{
		for (int i = 0; i < MAX_BULLET_COUNT; ++i)
		{
			/*if (obj_BULLET[i].getPosition().s < MAX_BULLET_SIZE)
			{
				bulletCount = i;
			}*/
			Data pos = obj_BULLET[i].getPosition();
			Data rgb = obj_BULLET[i].getRGB();
			g_Renderer->DrawSolidRect(pos.x, pos.y, pos.z, pos.s, rgb.x, rgb.y, rgb.z, rgb.s);

			if (timeSet > 300)
			{
				/*Data temp2 = { 0.0f,0.0f,0.0f,MAX_BULLET_SIZE };
				obj_BULLET[bulletCount].setPosition(temp2);
				Data pos = obj_BUILDING[bulletCount].getPosition();
				Data rgb = obj_BUILDING[bulletCount].getRGB();
				if (bulletCount > MAX_BULLET_COUNT)
				{

				}*/
				//cout << "bulletCount : " << bulletCount << endl;
				float checkX = 1;
				float checkY = 1;

				if (rand() % 2 == 1)
				{
				checkX *= -1;
				}if (rand() % 2 == 1)
				{
				checkY *= -1;
				}

				Data temp3 = { checkX,checkY,0.0f,0.0f };
				obj_BULLET[bulletCount].setDirection(temp3);

				Data temp2 = { 0.0f,0.0f,0.0f,MAX_BULLET_SIZE };
				obj_BULLET[bulletCount].setPosition(temp2);
				bulletCount++;
				if (bulletCount > MAX_BULLET_COUNT)
				{
					bulletCount = 0;
				}
				timeSet = 0;
			}
		}
	}
	else
	{
		for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		{
			Data pos = obj_ARROW[i].getPosition();
			Data rgb = obj_ARROW[i].getRGB();
			g_Renderer->DrawSolidRect(pos.x, pos.y, pos.z, pos.s, rgb.x, rgb.y, rgb.z, rgb.s);
		}

		for (int i = 0; i < MAX_ARROW_COUNT; ++i)
		{
			/*if (obj_BULLET[i].getPosition().s < MAX_BULLET_SIZE)
			{
			bulletCount = i;
			}*/
			Data pos = obj_ARROW[i].getPosition();
			Data rgb = obj_ARROW[i].getRGB();
			g_Renderer->DrawSolidRect(pos.x, pos.y, pos.z, pos.s, rgb.x, rgb.y, rgb.z, rgb.s);

			if (timeSet > 500)
			{
				float checkX = 1;
				float checkY = 1;

				if (rand() % 2 == 1)
				{
					checkX *= -1;
				}if (rand() % 2 == 1)
				{
					checkY *= -1;
				}

				Data temp3 = { checkX,checkY,0.0f,0.0f };
				obj_ARROW[arrowCount].setDirection(temp3);

				Data temp2 = { 100.0f,0.0f,0.0f,MAX_ARROW_SIZE };
				obj_ARROW[arrowCount].setPosition(temp2);
				arrowCount++;
				if (arrowCount > MAX_ARROW_COUNT)
				{
					arrowCount = 0;
				}
				timeSet = 0;
			}
		}
	}
}