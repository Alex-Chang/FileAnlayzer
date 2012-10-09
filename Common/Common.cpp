
#include "Common.h"

#define READ_BYTES_ONCE_TIME	1024


string FileSystem::getCurrentPath()
{
	char szCurrentDic[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, szCurrentDic);
	return string(szCurrentDic);
}

void FileSystem::getAllFileInPath(FileList& fileList, const string path, const string extention /*= "*"*/, int mask /*= FILE_ATTRIBUTE_NORMAL*/)
{
	WIN32_FIND_DATA findData;
	HANDLE hFile = FindFirstFile((path + "\\*." + extention).c_str(), &findData);

	if (hFile == INVALID_HANDLE_VALUE)	return;
	do	
	if ((findData.dwFileAttributes & mask) == mask)
	{
		File file;
		file.fileName = findData.cFileName;
		file.path = path;
		file.fileAttribute = findData.dwFileAttributes;
		fileList.push_back(file);
	}
	while(FindNextFile(hFile, &findData));
}


string FileSystem::GetFileText(string fileName)
{
	string text;
	char szBuffer[READ_BYTES_ONCE_TIME + 1];
	DWORD nBytesRead = 0;
	HANDLE hFile = CreateFile(fileName.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE, NULL);

	do
	{
		ReadFile(hFile, szBuffer, READ_BYTES_ONCE_TIME, &nBytesRead, NULL);
		szBuffer[nBytesRead] = 0;
		text += szBuffer;
	}
	while((int)nBytesRead == READ_BYTES_ONCE_TIME);
	CloseHandle(hFile);
	return text;
}

string FileSystem::getNativePath(const string& source, const string& base)
{
	return source.substr(base.length(), source.length() - base.length());
}

bool FileSystem::runApplication(string appName)
{
	STARTUPINFO info;
	memset(&info, 0, sizeof(STARTUPINFO));
	info.cb = sizeof(STARTUPINFO);
	info.dwFlags = STARTF_USESHOWWINDOW;
	info.wShowWindow = SW_SHOW;
	PROCESS_INFORMATION pi;
	return CreateProcess(appName.c_str(), NULL, NULL, NULL, FALSE, 0, NULL, NULL, &info, &pi) == TRUE;
}

bool Text::findToken(const string& text, const string& token, int& start, int& stop)
{
	stop = start = text.find(token, start);
	int tokenLength = token.length();
	if (start == -1) return false;
	if (start == 0 || isBlank(text[start - 1]))
		if (isBlank(text[start + tokenLength]))
		{
			stop = start + tokenLength;
		}
		return true;
}

int Text::findTokenStop(const string& text, int start)
{
	if (isBlank(text[start]))
		while (start < (int)text.length() && isBlank(text[start]))
		{
			start++;
		}
	else
		while (start < (int)text.length() && !isBlank(text[start]))
		{
			start++;
		}
		return start;
}

bool Text::isBlank(char c)
{
	return c == ' ' || c == '\t' || c == 13 || c == 10;
}



int Convert::toUnsignedInt(string str)
{
	int length = str.length(), rusult = 0;
	for (int i = length - 1; i >= 0; i--)
	{
		if (str[i] < '0' || str[i] > '9')
			return 0;
		int temp = str[i] - 48, j = length - i - 1;
		while (j--)
		{
			temp *= 10;
		}
		rusult += temp;
	}
	return rusult;
}