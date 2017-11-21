#pragma once

#include "targetver.h"
#include "Windows.h"

#include <stdio.h>
#include <tchar.h>
#include <random>
#include <ctime>
#include <iostream>

#define MAX_SCREEN_WIDTH 500
#define MAX_SCEEN_HEIGHT 800

#define MAX_OBJECTS_SIZE 10
#define MAX_OBJECTS_COUNT 10

#define MAX_BUILDING_COUNT 6
#define MAX_BUILDING_SIZE 30

#define MAX_BULLET_COUNT 120	//6���� �ǹ��� ����� ��� (MAX_BULLET_COUNT/6)�߾� ��� ���̴�.
#define MAX_BULLET_SIZE 5

#define MAX_ARROW_COUNT 100
#define MAX_ARROW_SIZE 5



enum OBJECT { OBJECT_CHARACTER = 1, OBJECT_BUILDING, OBJECT_BULLET, OBJECT_ARROW };


//srand((unsigned)time(NULL));

