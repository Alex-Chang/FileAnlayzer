

class MaterialScriptChecker : public Plugin
{
public:
	virtual string getCommand() {return "check";}

	virtual string getTime() {return "2011-05-12 20:45";}

	virtual string getDiscribtion(){return "列举出当前目录下包含汉字字符或未命名材质的material文件和行号";}

	virtual void run();

private:
	void checkFile(string fileName);
};

