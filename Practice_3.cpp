#include <iostream>
#include <fstream>
#include <string>



bool is_up(char c) {
	return c >= 'А' && c <= 'Я';
}

bool is_low(char c) {
	return c >= 'а' && c <= 'я';
}

bool is_l(char c) {
	return is_up(c) || is_low(c);
}

char up(char c) {
	if (is_low(c) && is_l(c)) {
		return c - 32;
	}
	return c;
}

char low(char c) {
	if (is_up(c) && is_l(c)) {
		return c + 32;
	}
	return c;
}

bool check(std::string word, char max_l[]) {
	for (int i = 0; i < word.size(); i++) {
		if (strchr(max_l, low(word[i])) == 0) {
			if (is_l(word[i])) {
				return true;
			}
		}
	}
	return false;
}



int main()
{
	setlocale(LC_ALL, "Russian");
	std::string str;
	std::ifstream file("input.txt");
	int max_len = 0;
	int max_count = 0;
	char max_l[33];
	for (int i = 0; i < 33; i++)
	{
		max_l[i] = ' ';
	}
	char let[33];
	while (!file.eof())
	{
		file >> str;
		for (int i = 0; i < 33; i++)
		{
			let[i] = ' ';
		}
		int count = 0;
		int len = 0;
		for (int i = 0; i < str.size(); i++)
		{
			if (is_l(str[i]))
			{
				len++;
				if (strchr(let, low(str[i])) == 0)
				{
					let[count] = low(str[i]);
					count++;
				}
			}
		}
		if (len > max_len)
		{
			for (int i = 0; i < max_count; i++)
			{
				max_l[i] = ' ';
			}
			max_len = len;
			max_count = count;
			for (int i = 0; i < count; i++)
			{
				max_l[i] = let[i];
			}
		}
		else if (len == max_len)
		{
			for (int i = 0; i < count; i++)
			{
				if (strchr(max_l, let[i]) == 0)
				{
					max_l[max_count] = let[i];
					max_count++;
				}
			}
		}
	}
	file.close();
	file.open("input.txt");
	std::ofstream out("output.txt");
	while (!file.eof())
	{
		file >> str;
		for (int i = 0; i < 33; i++)
		{
			let[i] = ' ';
		}
		int count = 0;
		if (check(str, max_l))
		{
			for (int i = 0; i < str.size(); i++)
			{
				if (strchr(max_l, low(str[i])) == 0)
				{
					if (strchr(let, up(str[i])) == 0)
					{
						if (is_l(str[i]))
						{
							let[count] = up(str[i]);
							count++;
						}
					}
				}
				out << up(str[i]);
			}
			out << "(";
			for (int i = 0; i < count; i++)
			{
				out << let[i];
			}
			out << ") ";
		}
		else
		{
			out << str << " ";
		}
	}
}
