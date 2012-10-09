
#include <Windows.h>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
#pragma once;

#define		DLL_EXPORT_API			extern "C" __declspec(dllexport)
#define		DEFAULT_AUTHOR_NAME		"����ɺ�"

class Plugin
{
public:
	virtual string getCommand() = 0;

	virtual string getAuthor() {return DEFAULT_AUTHOR_NAME;}

	virtual string getTime() = 0;
	
	virtual string getDiscribtion() = 0;

	virtual void   printfInformation()
	{
		cout << "�������ߣ�" + getAuthor() + "\n";
		cout << "����ʱ�䣺" + getTime() + "\n";
		cout << "����������" + getDiscribtion() + "\n\n";
	}

	virtual void run(){}

	void go() {printfInformation();run(); system("pause");}
};

