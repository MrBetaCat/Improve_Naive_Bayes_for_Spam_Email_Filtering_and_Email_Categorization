#include "Test.h"


Test::Test(void)
{
}


Test::~Test(void)
{
}

void Test::testLWNB()
{
	MultiWeightedNaiveBayes *pWNB;

	vector<string> m_filelist;
	_finddata_t file;
	long lf;
	string folder_path_name="university-rogers-b-kean-s\\*.*";
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

	for(int i=1;i<(int)m_filelist.size();i++)
	{
		string str="university-rogers-b-kean-s\\"+m_filelist[i];
		pWNB=new MultiWeightedNaiveBayes(3,str,0,14,15,46);
		pWNB->precomputeDistance();
		pWNB->precomputeWeight();
		pWNB->computeProbC();
		pWNB->computeProbAGivenC();
		pWNB->outputTestRes();
		m_res[i]=pWNB->m_res;
		cout<<pWNB->m_res<<endl;
	}


	float correct=0.0;
	for(int i=0;i<(int)m_res.size();i++)
	{
		if(m_res[i])
			correct+=1.0;
	}
	cout<<correct/(float)m_res.size()<<endl;
}

void Test::testSNB()
{
	SelectiveNaiveBayes *pSNB;

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

	for(int i=1;i<(int)m_filelist.size();i++)
	{
		string str="spam\\"+m_filelist[i];
		pSNB=new SelectiveNaiveBayes(str);
		pSNB->testResult();
		m_res[i]=pSNB->m_res;
		cout<<"i:"<<pSNB->m_res<<endl;
	}


	float correct=0.0;
	for(int i=0;i<(int)m_res.size();i++)
	{
		if(m_res[i])
			correct+=1.0;
	}
	cout<<correct/(float)m_res.size()<<endl;
}