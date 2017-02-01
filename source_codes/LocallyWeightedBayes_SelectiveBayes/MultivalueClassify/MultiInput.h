#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include "io.h"
using namespace std;


class MultiInput
{
public:
	MultiInput(int classNum);
	~MultiInput(void);
	void readingFiles(string foldername, int class_flag, int beginIndex, int endIndex, int beginIndex1, int endIndex1);
	string getNextToken(istream &in);

public:
	vector<string> m_filelist;
	vector<vector<map<string,int>>> m_classWords;
	map<string,int> m_words;

public:
	vector<vector<int>> m_numTokens;
	int m_sizeVocabulary;
	int m_classNum;

};

