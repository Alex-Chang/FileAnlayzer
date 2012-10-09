

class Convert
{
public:
	static int toUnsignedInt(string str)
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
};