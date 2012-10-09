

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
	virtual string getDiscribtion() {return "�оٳ���ǰĿ¼������Ŀ¼������material�ļ�����������ͻ���";}
	
	virtual void run();
};