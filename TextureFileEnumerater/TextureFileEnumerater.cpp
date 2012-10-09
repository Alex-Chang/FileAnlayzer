// TextureFileEnumerater.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "TextureFileEnumerater.h"
#include "../Common/FileHelper.h"

void TextureFileEmumerater::run()
{
	string currentPath = FileSystem::getCurrentPath();
	FileList fileList;
	StringList textureFileList;
	FileSystem::getAllFileInPath(fileList, currentPath, "material", FILE_ATTRIBUTE_ARCHIVE);
	for (FileIterator i = fileList.begin(); i != fileList.end(); i++)
	{
		string fileText = FileSystem::GetFileText(i->fileName);
		int start = 0, stop = 0;
		while(true)
		{
			start = fileText.find("texture ", start) + 8;
			if (start == 7) break;
			int spacestop = fileText.find(' ', start);
			if (spacestop == -1) spacestop = 999999999;
			int returnstop = fileText.find('\n', start);
			stop = spacestop < returnstop ? spacestop : returnstop;
			string textureFileName = fileText.substr(start, stop - start);
			textureFileList.push_back(textureFileName);
		}
	}
	sort(textureFileList.begin(), textureFileList.end());
	textureFileList.erase(unique(textureFileList.begin(), textureFileList.end()), textureFileList.end());
	for (StringIterator i = textureFileList.begin(); i != textureFileList.end(); i++)
	{
		cout << "\t" << *i << endl;
	}
}