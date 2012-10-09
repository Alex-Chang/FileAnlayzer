// MaterialScriptChecker.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "MaterialScriptChecker.h"


void MaterialScriptChecker::run()
{
	string currentPath = FileSystem::getCurrentPath();
	FileList fileList;
	FileSystem::getAllFileInPath(fileList, currentPath, "material", FILE_ATTRIBUTE_ARCHIVE);
	for (FileIterator i = fileList.begin(); i != fileList.end(); i++)
	{
		checkFile(i->fileName);
	}
}
void MaterialScriptChecker::checkFile(string fileName)
{
	string text = FileSystem::GetFileText(fileName);
	int nLine = 0, nLastErrorLine = -1;

	for (int i = 0; i < (int)text.length(); i++)
	{
		if (text[i] == '\n')
		{
			nLine++;
		}
		if (text[i] < 0 || text[i] == '-' &&text[i+1]=='D' &&text[i+2]=='e' &&text[i+3]=='f')
		{
			if (nLastErrorLine == -1)
			{
				printf("\t%s\n", fileName.c_str());
			}
			if (text[i] < 0 && nLastErrorLine != nLine)
			{
				printf("\t\tLine %d\t包含unicode字符\n",nLine + 1);
			} 
			else
			{
				printf("\t\tLine %d\t材质未更名\n",nLine + 1);
			}
			nLastErrorLine = nLine;
		}
	}
}