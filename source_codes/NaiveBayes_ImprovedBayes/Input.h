#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include "io.h"
#include <math.h>
#include <algorithm>

using namespace std;

class Input
{
public:
	Input(int classNum);
	~Input(void);

	// Read files from a folder
	// Note:
	// (1) class_flag = 0 denotes the spam email, and class_flag = 1 denotes the non-spam email
	// (2) If you want to read consecutive files, then endIndex1 < beginIndex1. 
	void readingFiles(string foldername, int class_flag, int beginIndex, int endIndex, int beginIndex1, int endIndex1);
	string getNextToken(istream &in);

	/************************************************************************/
	/*
	* Naive Bayes Classifier
	*/
	// Train Naive Bayes Classifier
	void trainNaiveBayes();

	// Test Naive Bayes Classifier on testing data
	// Note:
	// class_flag = 0 denotes the spam email, and class_flag = 1 denotes the non-spam email
	void testNaiveBayes(string foldername, int class_flag, int beginIndex, int endIndex);

	// Read training model
	void readNaiveBayesTrainingModel(char* modelname);

	void clearTestingData();

public:
	vector<string> m_filelist;
	vector<map<string,int>> m_classWords;
	map<string,int> m_words;
	vector<map<string,double>> m_probClassWord;
	vector<double> m_probClass;	// probability for each class, i.e. p(c_i)

	vector<int> m_numTokens;	// number of tokens for each category
	vector<int> m_numDocs;		// number of documents for each category
	int m_sizeVocabulary;		// size of vocabulary
	int m_classNum;				// number of category
	int m_totalDocNum;			// total number of documents
	double accuracy;

	int m_totalTestDocNum;		
	int m_totalCorrectNum;	
};
