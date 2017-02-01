#include "Test.h"


Test::Test(void)
{
}


Test::~Test(void)
{
}

void Test::testLWNB()
{
	WeightedNaiveBayes *pWNB;

	vector<string> m_filelist;
	_finddata_t file;
	long lf;
	string folder_path_name="spam\\*.*";
	const char* folder_path=folder_path_name.c_str();
    if((lf = _findfirst(folder_path, &file))==-1l)
		cout<<"no files!\n";
    else
    {
        while( _findnext( lf, &file ) == 0 )
        {
			m_filelist.push_back(file.name);//if(file.attrib == _A_SUBDIR)cout<<" subdir ";
		}	
	}
	_findclose(lf);

	m_res.resize(m_filelist.size());

	for(int i=183;i<(int)m_filelist.size();i++)
	{
		string str="spam\\"+m_filelist[i];
		pWNB=new WeightedNaiveBayes(0,str,0,14,15,46);
		pWNB->precomputeDistance();
		pWNB->precomputeWeight();
		pWNB->computeProbC();
		pWNB->computeProbAGivenC();
		pWNB->outputTestRes();
		m_res[i]=pWNB->m_res;
		cout<<pWNB->m_res<<endl;
	}


	float correct=0.0;
	for(int i=1;i<(int)m_res.size();i++)
	{
		if(m_res[i])
			correct+=1.0;
	}
	cout<<correct/(float)(m_res.size()-1)<<endl;
}

void Test::testSNB()
{
	SelectiveNaiveBayes *pSNB;

	vector<string> m_filelist;
	_finddata_t file;
	long lf;
	string folder_path_name="easy_ham\\*.*";
	const char* folder_path=folder_path_name.c_str();
    if((lf = _findfirst(folder_path, &file))==-1l)
		cout<<"no files!\n";
    else
    {
        while( _findnext( lf, &file ) == 0 )
        {
			m_filelist.push_back(file.name);//if(file.attrib == _A_SUBDIR)cout<<" subdir ";
		}	
	}
	_findclose(lf);

	m_res.resize(m_filelist.size());

	for(int i=1;i<(int)501;i++)
	{
		string str="easy_ham\\"+m_filelist[i];
		pSNB=new SelectiveNaiveBayes(1,str);
		pSNB->testResult();
		m_res[i]=pSNB->m_res;
		//cout<<"i:"<<pSNB->m_res<<endl;
	}


	float correct=0.0;
	for(int i=1;i<(int)501;i++)
	{
		if(m_res[i])
			correct+=1.0;
		if(i%50==0)
			cout<<correct/(float)(i)<<endl;
	}
	cout<<correct/(float)(500)<<endl;
}