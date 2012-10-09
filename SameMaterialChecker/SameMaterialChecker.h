

#include "../Common/Plugin.h"
#include "../Common/FileHelper.h"


class SameMaterialCheck : public Plugin
{
private:
	struct FileIncluedMaterial {string materialName; FileList fileList;};
	vector<FileIncluedMaterial> mMaterialFileList;

protected:
	void getMaterialFiles(FileList& fileList, string path);
	void checkFile(const File& file);
	void checkResult();

public:
	virtual string getCommand() {return "same";}
	virtual string getTime() {return "2011-09-28 14:13";}
	virtual string getDiscribtion() {return "列举出当前目录及其子目录下所有material文件材质重名冲突情况";}
	
	virtual void run();
};