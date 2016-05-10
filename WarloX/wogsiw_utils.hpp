#pragma once
#include <stdio.h>
#include <iostream>

using namespace std;

bool ReadFile(const string& path,string& source);

static float deltaTimeStart;
static float deltaTime;


float calcDeltaTime();
float calcGameTime();

#define NULL_MEMORY(x) memset(x,0,sizeof(x));
#define ARRAY_SIZE(x) sizeof(x)/sizeof(x[0]);
#define DEL_MEMORY(x) if(x) {delete x; x = NULL;}
