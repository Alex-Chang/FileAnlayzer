// FilesIncludeString.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "FilesIncludeString.h"
#include "../Common/FileHelper.h"


void FilesIncludeString::run()
{
	string stringToFind;
	cout << "input the sub string: ";
	cin >> stringToFind;
	string currentPath = FileSystem::getCurrentPath();
	FileList fileList;
	FileSystem::getAllFileInPath(fileList, currentPath, "material", FILE_ATTRIBUTE_ARCHIVE);
	for (FileIterator i = fileList.begin(); i != fileList.end(); i++)
	{
		string text = FileSystem::GetFileText(i->fileName);

		if (text.find(stringToFind) != -1)
			cout << "\t" + i->fileName << endl;
	}
}