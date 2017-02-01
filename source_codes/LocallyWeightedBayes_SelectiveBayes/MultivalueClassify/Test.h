#pragma once
#include "LocalWeightedNaiveBayes.h"
#include "SelectiveNaiveBayes.h"

class Test
{
public:
	Test(void);
	~Test(void);
public:
	void testLWNB();
	void testSNB();
private:
	vector<bool> m_res;
};

