


class TextureFileEmumerater : public Plugin
{
public:
	virtual string getCommand() {return "enum";}
	virtual string getTime() {return "2011-09-26 16:10";}
	virtual string getDiscribtion()	{return "列举出当前文件夹下所有material文件包含的所有texture文件";}
	virtual void run();
};
