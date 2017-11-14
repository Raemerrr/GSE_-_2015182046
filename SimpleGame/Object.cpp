#include "stdafx.h"
#include "Object.h"

using namespace std;

Object::Object()
{
	//srand((unsigned)time(NULL));  //�ѹ��� ������ ��.
	Position.x = 999.0;		//��ġ�� �ʴ� ��ġ���� �����ϱ� ����.(�ʻ� ���� ���ϴ� �� ó��)
	Position.y = 999.0;		//��ġ�� �ʴ� ��ġ���� �����ϱ� ����.
	Position.z = 999.0;		//��ġ�� �ʴ� ��ġ���� �����ϱ� ����.
	Position.s = 0.0;
	Rgb.x = 0.0;
	Rgb.y = 0.0;
	Rgb.z = 0.0;
	Rgb.s = 1.0;
	vX = 0.0; //X�� ����
	vY = 0.0; //Y�� ����

	Direction.x = 0.0;
	Direction.y = 0.0;
	Direction.z = 0.0;//���� ����
	Direction.s = 0.0;//���� ����
	objLife = 1000.0; //������
	lifeTime = 1000.0; //������
}
//Object::Object(const Object& other) {
//	Position.x = other.Position.x;		//��ġ�� �ʴ� ��ġ���� �����ϱ� ����.(�ʻ� ���� ���ϴ� �� ó��)
//	Position.y = 999.0;		//��ġ�� �ʴ� ��ġ���� �����ϱ� ����.
//	Position.z = 999.0;		//��ġ�� �ʴ� ��ġ���� �����ϱ� ����.
//	Position.s = 0.0;
//	Rgb.x = 0.0;
//	Rgb.y = 0.0;
//	Rgb.z = 0.0;
//	Rgb.s = 1.0;
//	vX = 0.0; //X�� ����
//	vY = 0.0; //Y�� ����
//
//	Direction.x = 0.0;
//	Direction.y = 0.0;
//	Direction.z = 0.0;//���� ����
//	Direction.s = 0.0;//���� ����
//	objLife = 1000.0; //������
//	lifeTime = 1000.0; //������
//}
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

void Object::Update(float elapsedTime, int OBJECT_TYPE)
{
	float objSpeed = 0.0f;
	if (OBJECT_TYPE == OBJECT_CHARACTER)
	{
		objSpeed = 100.0f;
	}
	else if (OBJECT_TYPE == OBJECT_BULLET)
	{
		objSpeed = 3.0f;
	}
	else if (OBJECT_TYPE == OBJECT_ARROW)
	{
		objSpeed = 5.0f;
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
		if (Position.x > 250) {
			vX = -vX;
			vY = (float)(rand() % 2);
		}
		if (Position.x < -250) {
			vX = -vX;
			vY = (float)(rand() % 2);
		}
		if (Position.y > 250) {
			vY = -vY;
			vX = (float)(rand() % 2);
		}
		if (Position.y < -250) {
			vY = -vY;
			vX = (float)(rand() % 2);
		}
	}
	else if (OBJECT_TYPE == OBJECT_BULLET) {
		Position.x = Position.x + vX * elapsedTime * objSpeed;	//�̵�����
		Position.y = Position.y + vY * elapsedTime * objSpeed;	//�̵�����
		//cout << Position.x << endl;
		//Position.s = MAX_BULLET_SIZE;
		//if (Position.x > 250 || Position.x < -250 || Position.y > 250 || Position.y < -250)
		//{
		//	/*float checkX = 1;
		//	float checkY = 1;

		//	if (rand() % 2 == 1)
		//	{
		//		checkX *= -1;
		//	}if (rand() % 2 == 1)
		//	{
		//		checkY *= -1;
		//	}
		//	vX = checkX;
		//	vY = checkY;*/
		//	Position.s = 0.0f;
		//	Position.x = 0.0f;
		//	Position.y = 0.0f;
		//	//cout << "��� ��Ż" << endl;
		//}

		/*float checkX = 1;
		float checkY = 1;

		if (rand() % 2 == 1)
		{
			checkX *= -1;
		}if (rand() % 2 == 1)
		{
			checkY *= -1;
		}

		if (Position.x > 250) {
			vX = checkX;
			vY = (float)(rand() % 2);
		}
		if (Position.x < -250) {
			vX = checkX;
			vY = (float)(rand() % 2);
		}
		if (Position.y > 250) {
			vX = (float)(rand() % 2);
			vY = checkY;
		}
		if (Position.y < -250) {
			vX = (float)(rand() % 2);
			vY = checkY;
		}*/
		if (Position.x > 250) {
			vX = -vX;
			vY = (float)(rand() % 2);
		}
		if (Position.x < -250) {
			vX = -vX;
			vY = (float)(rand() % 2);
		}
		if (Position.y > 250) {
			vY = -vY;
			vX = (float)(rand() % 2);
		}
		if (Position.y < -250) {
			vY = -vY;
			vX = (float)(rand() % 2);
		}
	}
	else if (OBJECT_TYPE == OBJECT_ARROW) {
		Position.x = Position.x + vX * elapsedTime * objSpeed;	//�̵�����
		Position.y = Position.y + vY * elapsedTime * objSpeed;	//�̵�����		
		if (Position.x > 250) {
			vX = -vX;
			vY = (float)(rand() % 2);
		}
		if (Position.x < -250) {
			vX = -vX;
			vY = (float)(rand() % 2);
		}
		if (Position.y > 250) {
			vY = -vY;
			vX = (float)(rand() % 2);
		}
		if (Position.y < -250) {
			vY = -vY;
			vX = (float)(rand() % 2);
		}
	}
}
