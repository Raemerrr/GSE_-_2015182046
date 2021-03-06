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

#define MAX_SKYOBJECTS_COUNT 6
#define MAX_SKYOBJECTS_SIZE 50
#define MAX_SKYOBJECTS_LIFE 50

#define MAX_OBJECTS_COUNT 300
#define MAX_OBJECTS_SIZE 30
#define MAX_OBJECTS_LIFE 100

#define MAX_BUILDING_COUNT 6
#define MAX_BUILDING_SIZE 100
#define MAX_BUILDING_LIFE 500

#define MAX_BULLET_COUNT (MAX_BUILDING_COUNT*100)
#define MAX_BULLET_SIZE 4
#define MAX_BULLET_LIFE 15

#define MAX_ARROW_COUNT (MAX_OBJECTS_COUNT*100)
#define MAX_ARROW_SIZE 4
#define MAX_ARROW_LIFE 10

#define LEVEL_GOD 0				//빌딩 눈.비
#define LEVEL_SKY 0.1			//캐릭터
#define LEVEL_GROUND 0.2		//에로우, 불렛
#define LEVEL_UNDERGROUND 0.3	//배경이미지


enum OBJECT { OBJECT_CHARACTER = 1, OBJECT_BUILDING, OBJECT_BULLET, OBJECT_ARROW, OBJECT_SKYCHARACTER };

//글자체
#define  GLUT_STROKE_ROMAN
#define  GLUT_STROKE_MONO_ROMAN
#define  GLUT_BITMAP_9_BY_15   
#define  GLUT_BITMAP_8_BY_13
#define  GLUT_BITMAP_TIMES_ROMAN_10
#define  GLUT_BITMAP_TIMES_ROMAN_24
#define  GLUT_BITMAP_HELVETICA_10
#define  GLUT_BITMAP_HELVETICA_12
#define  GLUT_BITMAP_HELVETICA_18
