#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <math.h>



class Node
{
	std::string key;
public:

	Node(const char* str)
	{
		key = std::string(str);
	}

	Node(std::string str)
	{
		key = str;
	}

	std::string getKey()
	{
		return key;
	}
};




int hash(std::string key)
{
	int h = 1;
	for (int i = 0; i < key.size(); i++)
	{
		h = (256 * h + key[i]) % 1000;
		std::cout << h << '\n';
	}
	return abs(h);
}




class HashTable
{
	std::vector<std::list<Node>> hashT;
	int size;
	Node none = Node("None");

public:

	HashTable(int Size)
	{
		size = Size;
		hashT.resize(Size);
	}

	bool addElem(Node& node)
	{
		int location = hash(node.getKey()) % size;
		if (this->isElemInList(node.getKey(), location))
		{
			return false;
		}
		hashT[location].push_back(node);
		return true;
	}

	Node findElem(std::string key)
	{
		int location = hash(key) % size;
		std::list<Node>::iterator it;
		it = hashT[location].begin();
		while (it != hashT[location].end())
		{
			if ((*it).getKey() == key)
				return *it;
			++it;
		}
		return none;
	}

private:
	bool isElemInList(std::string key, int location)
	{
		//int location = hash(key) % size;
		std::list<Node>::iterator it;
		it = hashT[location].begin();
		while (it != hashT[location].end())
		{
			if ((*it).getKey() == key)
				return true;
			++it;
		}
		return false;
	}

public:
	bool deleteElem(std::string key)
	{
		int location = hash(key) % size;
		std::list<Node>::iterator it;
		it = hashT[location].begin();
		while (it != hashT[location].end())
		{
			if ((*it).getKey() == key)
			{
				hashT[location].erase(it);
				return true;
			}
			++it;
		}
		return false;
	}

	std::vector<int> getStatistic()
	{
		std::vector<int> stat;
		stat.resize(size);
		for (int i = 0; i < size; i++)
		{
			stat[i] = hashT[i].size();
		}
		return stat;
	}
};
