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

class ImprovedBayes
{
public:
	ImprovedBayes(int classNum);
	~ImprovedBayes();

	// Read files from a folder
	// Note:
	// (1) class_flag = 0 denotes the spam email, and class_flag = 1 denotes the non-spam email
	// (2) If you want to read consecutive files, then endIndex1 < beginIndex1. 
	void readingFiles(string foldername, int class_flag, int beginIndex, int endIndex);
	string getNextToken(istream &in);

	// Train Improved Bayes
	void trainImprovedBayes(char *modelname);

	// Read training model
	void readImprovedBayesTrainingModel(char* modelname);

	// Test Improved Bayes Classifier on testing data
	// Note:
	// class_flag = 0 denotes the spam email, and class_flag = 1 denotes the non-spam email
	void testImprovedBayes(string foldername, int class_flag, int beginIndex, int endIndex);

	void clearTestingData();


public:
	vector<string> m_filelist;
	map<string,int> m_words;
	vector<map<string,int>> m_classWords;
	vector<map<string,double>> m_probClassWord;
	vector<int> m_numDocs;		// number of documents for each category
	vector<double> m_probClass;	// probability for each class, i.e. p(c_i)
	vector<double> m_numTokens;	// number of documents containing all words for each category

	int m_totalDocNum;			// total number of documents
	int m_sizeVocabulary;		// size of vocabulary
	double accuracy;			// accuracy
	int m_classNum;				// number of category

	int m_totalTestDocNum;		
	int m_totalCorrectNum;	
};