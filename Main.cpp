#define _CRT_SECURE_NO_WARNINGS

#include "HeshTable.h"
#include <cassert>
#include <stdio.h>


int FileLen(FILE* file)
{
	assert(file);          //??????
	fseek(file, 0, SEEK_END);
	int lenf = ftell(file);
	fseek(file, 0, SEEK_SET);
	return lenf;
}


bool isLetter(char ch)
{
	char st[2];
	st[0] = ch;
	st[1] = '\0';
	std::string str(st);
	std::string A("A");
	std::string Z("Z");
	std::string a("a");
	std::string z("z");
	//std::cout << st << "  :   " << (st >= A) << '\n';
	if (((st >= A) && (st <= Z)) || ((st >= a) && (st <= z)))
		return true;
	return false;
}


int main()
{
	HashTable set(1000);

	FILE* text = fopen("Test text.txt", "r");
	int sizeText = FileLen(text);

	char* buffer = new char[sizeText];
	int pointer = 0;
	int a = fread(buffer, sizeof(char), sizeText, text);
	fclose(text);

	std::string word("");
	int i = 0;
	while (i < sizeText)
	{
		//std::cout << buffer[i] << "  :  " << isLetter(buffer[i]) << '\n';
		if (isLetter(buffer[i]))
			word = word + buffer[i];
		else
		{
			Node* n = new Node(word);
			set.addElem(*n);
			//std::cout << word << '\n';
			word = std::string("");
		}
		//std::cout << i << '\n';
		i++;
	}

	std::vector<int> stat = set.getStatistic();

	std::string data("");
	for (int i = 0; i < stat.size(); i++)
	{
		data = data + std::string(" ") + std::to_string(stat[i]);
	}

	//std::cout << data << '\n';
	FILE* dat = fopen("data.txt", "w");

	fwrite(data.c_str(), sizeof(char), data.size(), dat);
}