#include "Input.h"
#include "MultiInput.h"
#include "Test.h"
#include "SelectiveNaiveBayes.h"

int main()
{
	//Test *pTest=new Test();
	//pTest->testLWNB();

	SelectiveNaiveBayes *pSNB=new SelectiveNaiveBayes();
	pSNB->preprocess();
	pSNB->selectFeature();
	pSNB->outputModelFile();

	//Test *pTest=new Test();
	//pTest->testSNB();

	system("pause");
	return 0;
}