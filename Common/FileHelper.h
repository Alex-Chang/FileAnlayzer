
struct File
{
	string fileName;
	string path;
	unsigned long fileAttribute;
};

typedef std::vector<File> FileList;
typedef FileList::iterator  FileIterator;
typedef std::vector<string> StringList;
typedef StringList::iterator StringIterator;

#define READ_BYTES_ONCE_TIME	1024

class FileSystem
{
public:
	static string getCurrentPath()
	{
		char szCurrentDic[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, szCurrentDic);
		return string(szCurrentDic);
	}

	static void getAllFileInPath(FileList& fileList, const string path, const string extention = "*", int mask = FILE_ATTRIBUTE_NORMAL)
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

	static string GetFileText(string fileName)
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
	
	static string getNativePath(const string& fullPath, const string& base)
	{
		return fullPath.substr(base.length(), fullPath.length() - base.length());
	}

	static bool runApplication(string appName)
	{
		STARTUPINFO info;
		memset(&info, 0, sizeof(STARTUPINFO));
		info.cb = sizeof(STARTUPINFO);
		info.dwFlags = STARTF_USESHOWWINDOW;
		info.wShowWindow = SW_SHOW;
		PROCESS_INFORMATION pi;
		return CreateProcess(appName.c_str(), NULL, NULL, NULL, FALSE, 0, NULL, NULL, &info, &pi) == TRUE;
	}
};