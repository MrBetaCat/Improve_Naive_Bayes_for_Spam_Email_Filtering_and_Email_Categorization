#pragma once
#include"MultiInput.h"
#include <algorithm>
#define INSTANCES 367
#define NEIGHBORS 5

class MultiWeightedNaiveBayes
{
public:
	MultiWeightedNaiveBayes(int flag,string filename,int begin0, int end0, int begin1, int end1);
	~MultiWeightedNaiveBayes(void);
public:
	string getNextToken(istream &in);
	void readingSingleFile(string filename);
	void precomputeWeight();
	void precomputeDistance();
	void computeProbC();
	void computeProbAGivenC();
	void outputTestRes();

private:
	map<string,int> m_wordsForTest;
	vector<double> m_distance;
	vector<double> m_weight;
	MultiInput *m_input;
	int m_flag;
	string m_filename;
	int m_begin0;
	int m_end0;
	int m_begin1;
	int m_end1;

public:
	vector<double> m_prob_c;
	vector<double> m_prob_res;
	bool m_res;
	vector<map<string, double>> m_prob_a_given_c;
};

