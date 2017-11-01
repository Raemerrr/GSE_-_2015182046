#include "stdafx.h"
#include "Object.h"

using namespace std;

Object::Object()
{
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

float Object::getObjLifeTime()
{
	return lifeTime;
}

void Object::setObjLifeTime(float p)
{
	lifeTime = p;
}

void Object::Update(float elapsedTime)
{
	elapsedTime = elapsedTime / 1000.f;
	if (!(lifeTime <= 0.0f))
	{
		lifeTime -= 1.0;
	}
	float objSpeed = 100;
	Position.x = Position.x + vX * elapsedTime * objSpeed;
	Position.y = Position.y + vY * elapsedTime * objSpeed;
	if (Position.x > 250) {
		vX = -vX;
		vY = rand() % 2;
	}
	if (Position.x < -250) {
		vX = -vX;
		vY = rand() % 2;
	}
	if (Position.y > 250) {
		vY = -vY;
		vX = rand() % 2;
	}
	if (Position.y < -250) {
		vY = -vY;
		vX = rand() % 2;
	}
}
