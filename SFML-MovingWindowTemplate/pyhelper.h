#pragma once

#include <Python.h>

class CPyInstance
{
public:
	CPyInstance()
	{
		// Set python path to all elements that are required to run python script. Also path to python script file is required to run it from c++ code.
		Py_SetPath(L"C:\\Users\\SSSS\\miniconda3\\python38.zip;C:\\Users\\SSSS\\miniconda3\\lib;C:\\Users\\SSSS\\AppData\\miniconda3\\DLLs;F:\\Cleared Projects\\AI\\FlappyBirdAi\\SFML-MovingWindowTemplate\\Python;C:\\Users\\SSSS\\miniconda3\\envs\\tensorflow\\lib\\site-packages;C:\\Users\\SSSS\\AppData\\Roaming\\Python\\Python38\\site-packages;C:\\Users\\SSSS\\miniconda3\\envs\\tensorflow;C:\\Users\\SSSS\\miniconda3\\envs\\tensorflow\\lib;C:\\Users\\SSSS\\miniconda3\\envs\\tensorflow\\DLLs");
		Py_Initialize();
	}
	~CPyInstance()
	{
		Py_Finalize();
	}
};

// RAII helps control python object by autmatic construction and deletion
class CPyObject
{
private:
	PyObject* p;
public:
	CPyObject() : p(nullptr) {}
	CPyObject(PyObject* _p) : p(_p) {}

	~CPyObject()
	{
		Release();
	}

	PyObject* getObject()
	{
		return p;
	}

	PyObject* setObject(PyObject* _p)
	{
		return (p = _p);
	}

	PyObject* AddRef()
	{
		if (p)
		{
			Py_INCREF(p);
		}
		return p;
	}

	void Release()
	{
		if (p)
		{
			Py_DECREF(p);
		}

		p = NULL;
	}

	PyObject* operator ->()
	{
		return p;
	}

	bool is()
	{
		return p ? true : false;
	}

	operator PyObject* ()
	{
		return p;
	}

	PyObject* operator = (PyObject* pp)
	{
		p = pp;
		return p;
	}

	operator bool()
	{
		return p ? true : false;
	}
};