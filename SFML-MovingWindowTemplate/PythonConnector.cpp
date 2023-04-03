#include "PythonConnector.h"
#include <iostream>
#include <chrono>

PythonConnector::PythonConnector()
{
	// Python script name without .py
	CPyObject pName = PyUnicode_FromString("flappyBirdAI");
	// Import module
	CPyObject pModule = PyImport_Import(pName);

	CPyObject dict;

	ErrorCondition = false;
	if (pModule)
	{
		//Get dictionary object that implements module's namespace (__dict__)
		dict = PyModule_GetDict(pModule);
		if (dict == nullptr) {
			PyErr_Print();
			std::cerr << "Fails to get the dictionary.\n";
			ErrorCondition = true;
		}
		else
		{
			// Loading python class
			pythonClass = PyDict_GetItemString(dict, "GeneticAlgorithm");
			if (pythonClass == nullptr) {
				PyErr_Print();
				std::cerr << "Fails to get the Python class.\n";
				ErrorCondition = true;
			}
			else
			{
				//Check if it is callable
				if (PyCallable_Check(pythonClass)) {
					object = PyObject_CallObject(pythonClass, nullptr);
				}
				else {
					std::cerr << "Cannot instantiate the Python class" << std::endl;
					ErrorCondition = true;
				}
			}
		}
	}
	else
	{
		std::cerr << "ERROR: Module not imported\n" << std::endl;
		ErrorCondition = true;
	}
}

void PythonConnector::createPopulation(int populationNumber, bool loadPopulation)
{
	// Set number of birds in each population
	PyObject_CallMethod(object, "setNumberOfModels", "(i)", populationNumber);
	// Create new population
	PyObject_CallMethod(object, "buildModel", NULL);
	// Load population from file
	if (loadPopulation)
	{
		PyObject_CallMethod(object, "loadModels", NULL);
	}
}

bool PythonConnector::predictJump(int modelID, float distanceH, float distanceW, float velocity)
{
	CPyObject value = PyObject_CallMethod(object, "predictMove", "(i,f,f,f)", modelID, distanceH, distanceW, velocity);
	return (bool)PyLong_AsLong(value);
}

void PythonConnector::mutatePopulation(int bestParent1, int bestParent2)
{
	PyObject_CallMethod(object, "modifyPopulation", "(i,i)", bestParent1, bestParent2);
}

void PythonConnector::savePopulation()
{
	PyObject_CallMethod(object, "saveModels", NULL);
}
