


class FilesIncludeString : public Plugin
{
public:
	virtual string getCommand() {return "sub";}

	virtual string getTime() {return "2011-09-26 20:11";}

	virtual string getDiscribtion(){return "列举出当前目录下包含输入串的所有material文件";}

	virtual void run();
};
