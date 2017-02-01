#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include "io.h"
using namespace std;


class Input
{
public:
	Input(int classNum);
	~Input(void);
	void readingFiles(string foldername, int class_flag, int beginIndex, int endIndex, int beginIndex1, int endIndex1);
	string getNextToken(istream &in);

public:
	vector<string> m_filelist;
	vector<string> m_total_filelist;
	vector<int> m_total_flags;
	vector<map<string,int>> m_classWords;
	map<string,int> m_words;
	vector<map<string,float>> m_probClassWord;

public:
	vector<int> m_numTokens;
	vector<int> m_docNum;
	int m_sizeVocabulary;
	int m_classNum;
};

