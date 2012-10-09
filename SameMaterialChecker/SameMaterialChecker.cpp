// SameMaterialChecker.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "SameMaterialChecker.h"
#include "../Common/Parser.h"

void SameMaterialCheck::getMaterialFiles(FileList& fileList, string path)
{
	FileSystem::getAllFileInPath(fileList, path, "material", FILE_ATTRIBUTE_ARCHIVE);
	FileList folderList;
	FileSystem::getAllFileInPath(folderList, path, "*", FILE_ATTRIBUTE_DIRECTORY);
	folderList.erase(folderList.begin(), folderList.begin() + 2);
	for (FileIterator i = folderList.begin(); i != folderList.end(); i++)
	{
		getMaterialFiles(fileList, path + "\\" + i->fileName);
	}
}

void SameMaterialCheck::run()
{
	FileList materialFileList;
	getMaterialFiles(materialFileList, FileSystem::getCurrentPath());

	for (FileIterator i = materialFileList.begin(); i != materialFileList.end(); i++)
	{
		checkFile(*i);
	}
	checkResult();

	mMaterialFileList.clear();
}

void SameMaterialCheck::checkFile(const File& file)
{
	string text = FileSystem::GetFileText(file.path + "\\" + file.fileName);
	int begin = 0, end = 0;
	for(;;)
	{
		if(!Text::findToken(text, string("material"), begin, end))
			break;
		begin = end;
		end = Text::findTokenStop(text, end); // 过滤掉material关键字后面的空白字符
		begin = end;
		end = Text::findTokenStop(text, end); 
		string sub = text.substr(begin, end - begin);
		vector<FileIncluedMaterial>::iterator i;
		for (i = mMaterialFileList.begin(); i != mMaterialFileList.end(); i++)
		{
			if (i->materialName == sub)
			{
				i->fileList.push_back(file);
				break;
			}
		}
		if (i == mMaterialFileList.end())
		{
			FileIncluedMaterial pFile;
			pFile.materialName = sub;
			pFile.fileList.push_back(file);
			mMaterialFileList.push_back(pFile);
		}
	}
}

void SameMaterialCheck::checkResult()
{
	string currentPath = FileSystem::getCurrentPath();
	for (vector<FileIncluedMaterial>::iterator i = mMaterialFileList.begin(); i != mMaterialFileList.end(); i++)
	{
		if ((*i).fileList.size() > 1)
		{
			string materal = i->materialName;
			cout << "\t材质名" + materal + "在文件 ";
			for (FileIterator j = i->fileList.begin(); j != i->fileList.end(); j++)
			{
				cout << FileSystem::getNativePath(j->path + "\\" + j->fileName, currentPath) + ", ";
			}
			cout << "中存在\n";
		}
	}
}