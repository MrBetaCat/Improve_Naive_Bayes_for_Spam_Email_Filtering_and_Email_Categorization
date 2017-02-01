#pragma once
#pragma once
#include"Input.h"
#include"MultiInput.h"

class SelectiveNaiveBayes
{
public:
	SelectiveNaiveBayes(int flag, string filename);
	SelectiveNaiveBayes();
	~SelectiveNaiveBayes(void);
public:
	void preprocess();
	void selectFeature();
	double calcCorrectRate(string word);
	void readingSingleFile(string filename);
	string getNextToken(istream &in);
	bool testTrainingfile(int index,string word,int flag);
	double calcProb(string word,int flag);
	void outputModelFile();
	void testResult();
	double getProb(string word, int spam);
private:
	string m_filename;
	Input *m_input;
	MultiInput *m_multiInput;
	int m_flag;
	double probc0;
	double probc1;
	map<string,int> m_wordsForTest;
	vector<map<string,double>> m_prob_feature;
public:
	bool m_res;	
	vector<double> m_prob_res;
	vector<double> m_new_word;
	vector<map<string,double>> m_probModel;
	vector<double> m_probDocModel;
};

