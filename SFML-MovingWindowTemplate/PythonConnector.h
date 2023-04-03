#pragma once
#include "pyhelper.h"
#include <vector>

class PythonConnector
{
public:
	PythonConnector();
private:
	CPyInstance hInstance;
	CPyObject pythonClass;
	CPyObject object;
	bool ErrorCondition;
public:
	void createPopulation(int numberOfPopulation, bool loadPopulation = false);
	bool predictJump(int modelID, float distanceH, float distanceW, float velocity);
	void mutatePopulation(int bestParent1, int bestParent2);
	void savePopulation();
};