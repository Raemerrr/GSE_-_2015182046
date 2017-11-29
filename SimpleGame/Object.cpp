#include "stdafx.h"
#include "Object.h"

using namespace std;

Object::Object()
{
	//srand((unsigned)time(NULL));  //�ѹ��� ������ ��.
	Position.x = 999.0f;		//��ġ�� �ʴ� ��ġ���� �����ϱ� ����.(�ʻ� ���� ���ϴ� �� ó��)
	Position.y = 999.0f;		//��ġ�� �ʴ� ��ġ���� �����ϱ� ����.
	Position.z = 999.0f;		//��ġ�� �ʴ� ��ġ���� �����ϱ� ����.
	Position.s = 1.0f;
	Rgb.x = 0.0;
	Rgb.y = 0.0;
	Rgb.z = 0.0;
	Rgb.s = 0.0;
	vX = 0.0; //X�� ����
	vY = 0.0; //Y�� ����
	teamNum = 0;

	Direction.x = 0.f;
	Direction.y = 0.f;
	Direction.z = 0.f;//���� ����
	Direction.s = 0.f;//���� ����
	objLife = 0.f; //������
	lifeTime = 1000.f; //������
}

Object::~Object()
{
}

Data Object::getPosition()
{
	return Position;
}

void Object::setPosition(Data pos)
{
	Position.x = pos.x;
	Position.y = pos.y;
	Position.z = pos.z;
	Position.s = pos.s;
}

Data Object::getRGB()
{
	return Rgb;
}

void Object::setRGB(Data rgb)
{
	Rgb.x = rgb.x;
	Rgb.y = rgb.y;
	Rgb.z = rgb.z;
	Rgb.s = rgb.s;
}

Data Object::getDirection()
{
	Direction.x = vX;
	Direction.y = vY;
	return Direction;
}

void Object::setDirection(Data p)
{
	vX = p.x;
	vY = p.y;
}

float Object::getObjLife()
{
	return objLife;
}

void Object::setObjLife(float p)
{
	objLife += p;
}

void Object::fixedObjLife(float p)
{
	objLife = p;
}

float Object::getObjLifeTime()
{
	return lifeTime;
}

void Object::setObjLifeTime(float p)
{
	lifeTime = p;
}

int Object::getTeamNum() 
{
	return teamNum;
}

void Object::setTeamNum(int a) 
{
	teamNum = a;
}

void Object::Update(float elapsedTime, int OBJECT_TYPE)
{
	int screenX = MAX_SCREEN_WIDTH / 2;
	int screenY = MAX_SCEEN_HEIGHT / 2;

	float objSpeed = 0.0f;
	if (OBJECT_TYPE == OBJECT_CHARACTER)
	{
		objSpeed = 300.f;
	}
	else if (OBJECT_TYPE == OBJECT_BULLET)
	{
		objSpeed = 600.f;
	}
	else if (OBJECT_TYPE == OBJECT_ARROW)
	{
		objSpeed = 100.f;
	}

	elapsedTime = elapsedTime / 1000.f;
	//cout << bulletSpawnTime << endl; 

	//ĳ���� ������Ÿ�� ��� �ּ�ó��
	/*if (!(lifeTime <= 0.0f) && OBJECT_TYPE == OBJECT_CHARACTER)
	{
		lifeTime -= 1.0;
	}*/

	if (OBJECT_TYPE == OBJECT_CHARACTER)
	{
		Position.x = Position.x + vX * elapsedTime * objSpeed;  //�̵�����
		Position.y = Position.y + vY * elapsedTime * objSpeed;	//�̵�����
		if (Position.x > screenX) {
			vX = -vX;
			vY = (float)(rand() % 2);
		}
		if (Position.x < (-screenX)) {
			vX = -vX;
			vY = (float)(rand() % 2);
		}
		if (Position.y > screenY) {
			vY = -vY;
			vX = (float)(rand() % 2);
		}
		if (Position.y < (-screenY)) {
			vY = -vY;
			vX = (float)(rand() % 2);
		}/*if (Position.x > screenX || Position.x < (-screenX) || Position.y > screenY || Position.y < (-screenY))
		{
			objLife = (-1.f);
		}*/
	}
	else if (OBJECT_TYPE == OBJECT_BULLET) {
		Position.x = Position.x + vX * elapsedTime * objSpeed;	//�̵�����
		Position.y = Position.y + vY * elapsedTime * objSpeed;	//�̵�����
		//cout << "BULLET x : " << Position.x <<  endl;
		//cout << Position.x << endl;
		//Position.s = MAX_BULLET_SIZE;
		if (Position.x > screenX || Position.x < (-screenX) || Position.y > screenY || Position.y < (-screenY))
		{
			/*vX = 0;
			vY = 0;
			Position.s = -1.0f;
			Position.x = 999.0f;
			Position.y = 999.0f;*/
			objLife = (-1.f);

			//cout << "��� ��Ż" << endl;
		}

		//��� ��Ż ��.
		/*if (Position.x > screenX) {
			vX = -vX;
			vY = (float)(rand() % 2);
		}
		if (Position.x < (-screenX)) {
			vX = -vX;
			vY = (float)(rand() % 2);
		}
		if (Position.y > screenY) {
			vY = -vY;
			vX = (float)(rand() % 2);
		}
		if (Position.y < (-screenY)) {
			vY = -vY;
			vX = (float)(rand() % 2);
		}*/
	}
	else if (OBJECT_TYPE == OBJECT_ARROW) {
		Position.x = Position.x + vX * elapsedTime * objSpeed;	//�̵�����
		Position.y = Position.y + vY * elapsedTime * objSpeed;	//�̵�����		
		if (Position.x > screenX || Position.x < (-screenX) || Position.y > screenY || Position.y < (-screenY))
		{
			/*vX = 0;
			vY = 0;
			Position.s = -1.0f;
			Position.x = 999.0f;
			Position.y = 999.0f;*/
			objLife = (-1.f);

			//cout << "��� ��Ż" << endl;
		}
																
		//��� ��Ż ��.													
		/*if (Position.x > screenX) {
			vX = -vX;
			vY = (float)(rand() % 2);
		}
		if (Position.x < (-screenX)) {
			vX = -vX;
			vY = (float)(rand() % 2);
		}
		if (Position.y > screenY) {
			vY = -vY;
			vX = (float)(rand() % 2);
		}
		if (Position.y < (-screenY)) {
			vY = -vY;
			vX = (float)(rand() % 2);
		}*/
	}
}
