
#include "Application.h"
#include <strstream>
#include "Converter.h"


void Application::initialise()
{
	string currentPath = FileSystem::getCurrentPath();
	FileList dllList;
	srand(0);
	FileSystem::getAllFileInPath(dllList, "D:\\MyDocument\\Visual Studio 2008\\Projects\\FileAnlayzer\\Debug", "dll", FILE_ATTRIBUTE_ARCHIVE);
	for (FileIterator i = dllList.begin(); i != dllList.end(); i++)
	{
		HINSTANCE hDllHandle = LoadLibrary(i->fileName.c_str());
		Plugin* plugin = *(Plugin**)GetProcAddress(hDllHandle, "plugin");
		mPluginMap[plugin->getCommand()] = plugin;
		mDllList[hDllHandle] = i->fileName;
		Sleep(rand() % 2000);
		cout << "load " + i->fileName + " successfully.\n";
	}
	cout << "OK\n";
}

void Application::shutdown()
{
	for (map<HINSTANCE, string>::iterator i = mDllList.begin(); i != mDllList.end(); i++)
	{
		FreeLibrary(i->first);
		Sleep(rand() % 2000);
		cout << "unload " + i->second + " successfully.\n";
	}
}

void Application::printHelpInfo()
{
	for (PluginIterator i = mPluginMap.begin(); i != mPluginMap.end(); i++)
	{
		Plugin* plugin = i->second;
		cout << "\t" << plugin->getCommand() << "\t\t" << plugin->getDiscribtion() << endl;
	}
	cout << "\tback"			<< "\t\t���ص���һ��Ŀ¼" << endl;
	cout << "\tenter disk:"		<< "\t����disk�̷�. ��enter D:" << endl;
	cout << "\tenter subpath"	<< "\t���뵱ǰĿ¼�µ�subpathĿ¼. ��enter myfolder" << endl;
	cout << "\tenter index"		<< "\t���뵱ǰĿ¼�µ�index��Ŀ¼. ��enter 3" << endl;
	cout << "\tenter .."		<< "\t���ص���һ��Ŀ¼" << endl;
	cout << "\tpath"			<< "\t\t��ʾ��ǰĿ¼" << endl;
	cout << "\texit"			<< "\t\t�˳�mytools����" << endl;
	cout << "\tabout"			<< "\t\t��ʾϵͳ�͸����ܵĹ�����Ϣ" << endl;
	cout << "\ttieba"			<< "\t\t�������ɼ�����" << endl;
	cout << "\thelp"			<< "\t\t��ʾ������Ϣ" << endl;
	cout << endl;
}

void Application::printAboutInfo()
{
	cout << "\tmytools v1.0 developed by ����ɺ� , 2011-09-26 21:47\n";
	cout << "\tincludes :\n";
	int index = 1;
	for (PluginIterator i = mPluginMap.begin(); i != mPluginMap.end(); i++)
	{
		Plugin* p = i->second;
		cout << "\t\tsubsystem" << index++ << "\n" ;
		cout << "\t\t�������ߣ�" + p->getAuthor() + "\n";
		cout << "\t\t����ʱ�䣺" + p->getTime() + "\n";
		cout << "\t\t����������" + p->getDiscribtion() + "\n\n";
	}
}

void Application::printMenu()
{
	cout << "\nMENU: ";
	for (PluginIterator i = mPluginMap.begin(); i != mPluginMap.end(); i++)
	{
		cout << " [" + i->second->getCommand() + "]";
	}
	cout << " [enter] [back] [path] [exit] [about] [tieba] [help/?]\n";
}

void Application::fillCurrentFileList()
{
	string currentPath = FileSystem::getCurrentPath();
	mCurrentFileList.clear();
	FileSystem::getAllFileInPath(mCurrentFileList, currentPath, "*", FILE_ATTRIBUTE_DIRECTORY);
	mCurrentFileList.erase(mCurrentFileList.begin(), mCurrentFileList.begin() + 2);
}

void Application::backDictionary()
{
	SetCurrentDirectory("..\\");
	cout << FileSystem::getCurrentPath() << endl;
	fillCurrentFileList();
	printCurrentPath();
}

void Application::enterDictionary(string subFolder)
{
	int num = 0;
	string newPath;
	if (subFolder.length() == 2 && (subFolder[0] >= 'A' && subFolder[0] <= 'Z') && subFolder[1] == ':')
	{
		newPath = subFolder + "\\";
	}
	else if ((num = Convert::toUnsignedInt(subFolder)) && num <= (int)mCurrentFileList.size()) // must be '=', not '=='
	{
		subFolder = mCurrentFileList[num - 1].fileName;
		newPath = FileSystem::getCurrentPath() + "\\" + subFolder;
	}
	else
	{
		newPath = FileSystem::getCurrentPath() + "\\" + subFolder;
	}
	SetCurrentDirectory(newPath.c_str());
	
	fillCurrentFileList();
	
	printCurrentPath();
}

void Application::printCurrentPath()
{
	cout << "\t��ǰĿ¼Ϊ " + FileSystem::getCurrentPath() + "\n";
	int index = 1;
	if (mCurrentFileList.size() == 0)
		cout << "\t��ǰĿ¼û����Ŀ¼��\n";

	for (FileIterator i = mCurrentFileList.begin(); i != mCurrentFileList.end(); i++)
	{
		cout << "\t" << index++ << "\t\b\b" << i->fileName << endl;
	}
}

void Application::run()
{
	while (1)
	{
		try
		{
			printMenu();
			string cmd;
			cout << "mytools > ";
			cin >> cmd;
			PluginIterator i = mPluginMap.find(cmd);
			if (i != mPluginMap.end()) i->second->run();
			else if (cmd == "help" || cmd == "?") printHelpInfo();
			else if (cmd == "back")  backDictionary();
			else if (cmd == "enter") {string subFolder; cin >> subFolder; enterDictionary(subFolder);}
			else if (cmd == "path") enterDictionary(".");
			else if (cmd == "about") printAboutInfo();
			else if (cmd == "exit") break;
			else if (cmd == "tieba") 
			{
				if(!FileSystem::runApplication("D:\\MyDocument\\Visual Studio 2008\\Projects\\tiebarlistner\\tiebarlistner\\bin\\Release\\tiebarlistner.exe"))
				{
					cout << "\tapplication not found.\n";
					continue;
				}
			}
			else cout << "\terror: \"" + cmd + "\" is an unknown command\n";

			cout << "\tdone.\n";
		}
		catch (exception* e)
		{
			cout << "an error occored just." << e->what() << endl;
		}
	}
}