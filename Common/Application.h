
#include "Plugin.h"
#include <map>
#include "FileHelper.h"
using namespace std;

class Application
{
private:
	typedef		map<string, Plugin*>	PluginList;
	typedef		PluginList::iterator	PluginIterator;

	PluginList mPluginMap;
	FileList   mCurrentFileList;
	map<HINSTANCE, string> mDllList;

protected:
	void backDictionary();
	void enterDictionary(string subFolder);

public:
	void initialise();
	void shutdown();
	void run();
	void printAboutInfo();
	void printHelpInfo();
	void printMenu();
	void fillCurrentFileList();
	void printCurrentPath();
};