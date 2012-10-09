

class Text
{
public:
	static bool findToken(const string& text, const string& token, int& start, int& stop)
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

	static int findTokenStop(const string& text, int start)
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

	static bool isBlank(char c)
	{
		return c == ' ' || c == '\t' || c == 13 || c == 10;
	}
};