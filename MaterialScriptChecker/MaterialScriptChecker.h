

class MaterialScriptChecker : public Plugin
{
public:
	virtual string getCommand() {return "check";}

	virtual string getTime() {return "2011-05-12 20:45";}

	virtual string getDiscribtion(){return "�оٳ���ǰĿ¼�°��������ַ���δ�������ʵ�material�ļ����к�";}

	virtual void run();

private:
	void checkFile(string fileName);
};

