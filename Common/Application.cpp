
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
	cout << "\tback"			<< "\t\t返回到上一级目录" << endl;
	cout << "\tenter disk:"		<< "\t进入disk盘符. 如enter D:" << endl;
	cout << "\tenter subpath"	<< "\t进入当前目录下的subpath目录. 如enter myfolder" << endl;
	cout << "\tenter index"		<< "\t进入当前目录下第index个目录. 如enter 3" << endl;
	cout << "\tenter .."		<< "\t返回到上一级目录" << endl;
	cout << "\tpath"			<< "\t\t显示当前目录" << endl;
	cout << "\texit"			<< "\t\t退出mytools工具" << endl;
	cout << "\tabout"			<< "\t\t显示系统和各功能的关于信息" << endl;
	cout << "\ttieba"			<< "\t\t启动贴吧监听器" << endl;
	cout << "\thelp"			<< "\t\t显示帮助信息" << endl;
	cout << endl;
}

void Application::printAboutInfo()
{
	cout << "\tmytools v1.0 developed by 剑起飞虹 , 2011-09-26 21:47\n";
	cout << "\tincludes :\n";
	int index = 1;
	for (PluginIterator i = mPluginMap.begin(); i != mPluginMap.end(); i++)
	{
		Plugin* p = i->second;
		cout << "\t\tsubsystem" << index++ << "\n" ;
		cout << "\t\t开发作者：" + p->getAuthor() + "\n";
		cout << "\t\t开发时间：" + p->getTime() + "\n";
		cout << "\t\t功能描述：" + p->getDiscribtion() + "\n\n";
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
	cout << "\t当前目录为 " + FileSystem::getCurrentPath() + "\n";
	int index = 1;
	if (mCurrentFileList.size() == 0)
		cout << "\t当前目录没有子目录。\n";

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