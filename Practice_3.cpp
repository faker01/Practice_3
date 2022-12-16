#include <iostream>
#include <fstream>
#include <string>


bool check_u(char c)
{
	return 'А' <= c <= 'Я';
}


bool check_l(char c)
{
	return 'а' <= c <= 'я';
}


char upper(char c)
{
	if (check_l(c))
	{
		return c - 32;
	}
	return c;
}


char lower(char c)
{
	if (check_u(c))
	{
		return c + 32;
	}
	return c;
}


bool check_let(char c)
{
	return check_u(c) or check_l(c);
}


bool check(std::string word, char max_l[])
{
	for (int i = 0; i < word.size(); i++)
	{
		if (strchr(max_l, lower(word[i])) == 0)
		{
			if (check_let(word[i]))
			{
				return true;
			}
		}
	}
	return false;
}


int main()
{
	setlocale(LC_ALL, "rus");

	std::string str;
	int max = 0, max_count = 0, count, len;
	char max_l[33], letters[33];

	std::ifstream file("input.txt", std::ios::in);

	while (!file.eof())
	{
		file >> str;

		count = 0;
		len = 0;
		for (int k = 0; k < 33; k++)
		{
			letters[k] = ' ';
		}

		for (int i = 0; i < str.size(); i++)
		{
			if (check_let(str[i]))
			{
				len++;
				if (strchr(letters, lower(str[i])) == 0)
				{
					letters[count] = lower(str[i]);
					count++;
				}
			}
		}
		if (len > max)
		{
			for (int i = 0; i < max_count; i++)
			{
				max_l[i] = ' ';
			}
			max = len;
			max_count = count;
			for (int i = 0; i < count; i++)
			{
				max_l[i] = letters[i];
			}
		}
		else if (len == max)
		{
			for (int i = 0; i < count; i++)
			{
				if (strchr(max_l, letters[i]) == 0)
				{
					max_l[max_count] = letters[i];
					max_count++;
				}
			}
		}
	}

	file.close();

	std::ifstream f_i("input.txt", std::ios::in);
	std::ofstream f_o("output.txt", std::ios::out);

	while (!f_i.eof())
	{
		f_i >> str;

		for (int k = 0; k < 33; k++)
		{
			letters[k] = ' ';
		}
		count = 0;

		if (check(str, max_l))
		{
			for (int i = 0; i < str.size(); i++)
			{
				if (strchr(max_l, lower(str[i])) == 0)
				{
					if (strchr(letters, upper(str[i])) == 0)
					{
						if (check_let(str[i]))
						{
							letters[count] = upper(str[i]);
							count++;
						}
					}
				}
				f_o << upper(str[i]);
			}
			f_o << "(";
			for (int i = 0; i < count; i++)
			{
				f_o << letters[i];
			}
			f_o << ") ";
		}
		else
		{
			f_o << str << " ";
		}
	}
	return 0;
}