#include "ImprovedBayes.h"

ImprovedBayes::ImprovedBayes(int classNum)
{
	accuracy = 0;
	m_totalTestDocNum = 0;
	m_totalCorrectNum = 0;
	m_classNum = classNum;
	m_classWords.resize(classNum);
	m_probClassWord.resize(classNum);
	m_probClass.resize(classNum);
	m_numDocs.resize(classNum);
	m_numTokens.resize(classNum);
}

ImprovedBayes::~ImprovedBayes()
{
	if(!m_classWords.empty())
		m_classWords.clear();
	if(!m_probClassWord.empty())
		m_probClassWord.clear();
	if (!m_numDocs.empty())
	{
		m_numDocs.clear();
	}
	if (!m_probClass.empty())
	{
		m_probClass.clear();
	}
	if (!m_numTokens.empty())
	{
		m_numTokens.clear();
	}
}

string ImprovedBayes::getNextToken(istream &in)
{
	char c;
	string ans="";
	c=in.get();

	while(!in.eof())//cleaning non letter charachters
	{
		if(c>=-1&&c<=255)
		{
			if(!isalpha(c))
				c=in.get();
			else
				break;
		}
		else
			c=in.get();
	}
	while(true)
	{
		if(c>=-1&&c<=255)
		{
			if(isalpha(c))
			{
				ans.push_back(tolower(c));
				c=in.get();
			}
			else
				break;
		}
		else
			c=in.get();

	}
	return ans;
}

void ImprovedBayes::readingFiles(string foldername, int class_flag, int beginIndex, int endIndex)
{
	//the first file name of filelist is always ".."
	_finddata_t file;
	long lf;
	string folder_path_name=foldername+"\\*.*";
	const char* folder_path=folder_path_name.c_str();
	if((lf = _findfirst(folder_path, &file))==-1l)
	{
		cout<<"no files!\n";
	}
	else
	{
		while( _findnext( lf, &file ) == 0 )
		{
			m_filelist.push_back(file.name);//if(file.attrib == _A_SUBDIR)cout<<" subdir ";
		}	
	}
	_findclose(lf);

	//read all files
	for(int i=beginIndex+1;i<=endIndex+1;i++)
	{
		string filename=foldername+"\\"+m_filelist[i];
		ifstream fin(filename.c_str());
		string s;
		string empty ="";
		while((s=getNextToken(fin))!=empty )
		{
			if(m_words[s] == 0)
			{
				++m_classWords[class_flag][s];
			}
			m_words[s] = 1;			
		}
		fin.close();
		for (map<string,int>::iterator iter = m_words.begin(); iter != m_words.end(); ++iter)
		{
			iter->second = 0;
		}
	}

	if(!m_filelist.empty())
		m_filelist.clear();

	m_sizeVocabulary = m_words.size();
	m_numDocs[class_flag] = endIndex - beginIndex + 1;
	m_totalDocNum += m_numDocs[class_flag];
}

void ImprovedBayes::trainImprovedBayes(char* modelname)
{
	for (int i = 0; i != m_classWords.size(); ++i)
	{
		m_probClass[i] = log((double)(m_numDocs[i])/m_totalDocNum);
		double n = 0;
		for (map<string,int>::iterator iter = m_classWords[i].begin(); iter != m_classWords[i].end(); ++iter)
		{
			n += iter->second;
		}
		m_numTokens[i] = n;
		for (map<string,int>::iterator iter = m_classWords[i].begin(); iter != m_classWords[i].end(); ++iter)
		{
			double prob = log((double)(1+iter->second)/(m_sizeVocabulary + n));
			m_probClassWord[i].insert(map<string,double>::value_type(iter->first, prob));
		}
	}

	// Save the training model
	ofstream writeout;
	writeout.open(modelname, ios::trunc);
	writeout<<"Class Number"<<endl;
	writeout<<m_classNum<<endl;
	writeout<<"Vocabulary Number"<<endl;
	writeout<<m_sizeVocabulary<<endl;
	writeout<<"Token Number"<<endl;
	for (int i = 0; i != m_classNum; ++i)
	{
		writeout<<i<<" "<<m_numTokens[i]<<endl;
	}
	writeout<<"Class Probability"<<endl;
	for (int i = 0; i != m_classWords.size(); ++i)
	{
		writeout<<i<<" "<<m_probClass[i]<<endl;
	}
	writeout<<"Word Probability"<<endl;
	for (int i = 0; i != m_classWords.size(); ++i)
	{
		for (map<string,double>::iterator iter = m_probClassWord[i].begin(); iter != m_probClassWord[i].end(); ++iter)
		{
			writeout<<i<<" "<<iter->first<<" "<<iter->second<<endl;
		}
	}

	writeout.close();
}

void ImprovedBayes::readImprovedBayesTrainingModel(char* modelname)
{
	ifstream readin;
	readin.open(modelname, ios::in);
	if (readin.fail())
	{
		cout<<"Cannot open the model file."<<endl;
		return;
	}
	string str;
	int classNo = 0;
	double prob = 0;
	while (!readin.eof())
	{
		readin>>str;
		if (readin.fail())
		{
			break;
		}
		if (str == "Class")
		{
			readin>>str;
			if (str == "Number")
			{
				readin>>m_classNum;
			}
			else if (str == "Probability")
			{
				for (int i = 0; i != m_classNum; ++i)
				{
					readin>>classNo;
					readin>>m_probClass[classNo];
				}				 
			}
		}
		else if (str == "Vocabulary")
		{
			readin>>str;
			readin>>m_sizeVocabulary;
		}
		else if (str == "Token")
		{
			readin>>str;
			for (int i = 0; i != m_classNum; ++i)
			{
				readin>>classNo;
				readin>>m_numTokens[classNo];
			}
		}
		else if (str == "Word")
		{
			readin>>str;
			while (!readin.eof())
			{
				readin>>classNo>>str>>prob;
				if (readin.fail())
				{
					break;
				}
				m_probClassWord[classNo].insert(map<string,double>::value_type(str, prob));
			}
		}
	}
	readin.close();
}

void ImprovedBayes::testImprovedBayes(string foldername, int class_flag, int beginIndex, int endIndex)
{
	//the first file name of filelist is always ".."
	_finddata_t file;
	long lf;
	string folder_path_name=foldername+"\\*.*";
	const char* folder_path=folder_path_name.c_str();
	if((lf = _findfirst(folder_path, &file))==-1l)
	{
		cout<<"no files!\n";
	}
	else
	{
		while( _findnext( lf, &file ) == 0 )
		{
			m_filelist.push_back(file.name);//if(file.attrib == _A_SUBDIR)cout<<" subdir ";
		}
	}
	_findclose(lf);

	//read all files
	vector<double> probs;
	int correctNum = 0;
	for(int i=beginIndex+1;i<=endIndex+1;i++)
	{
		string filename=foldername+"\\"+m_filelist[i];
		ifstream fin(filename.c_str());
		string s;
		string empty ="";

		probs.clear();
		probs.resize(m_classNum, 0);
		while((s=getNextToken(fin))!=empty)
		{
			for (int j = 0; j != m_classNum; ++j)
			{
				map<string,double>::iterator iter = m_probClassWord[j].find(s);
				if (iter != m_probClassWord[j].end())
				{// saved word for this category
					probs[j] += iter->second;
				}
				else
				{// new word for this category
					probs[j] -= log(m_numTokens[j] + m_sizeVocabulary);
				}
			}
		}
		fin.close();

		for (int j = 0; j != m_classNum; ++j)
		{
			probs[j] += m_probClass[j];
		}

		// Test if the data is classified correctly
		double temp = probs[0];
		int test_flag = 0;
		for (int j = 1; j != m_classNum; ++j)
		{
			if (probs[j] > temp)
			{
				test_flag = j;
				temp = probs[j];
			}
		}
		if (test_flag == class_flag)
		{
			correctNum++;
		}
		int tempNum = m_totalTestDocNum + i-beginIndex+1; 
		if (tempNum%50 == 0)
		{
			cout<<tempNum<<"\t"<<(double)(correctNum+m_totalCorrectNum)/tempNum<<endl;
		}
	}

	m_totalTestDocNum += endIndex-beginIndex+1;
	m_totalCorrectNum += correctNum;
	if(!m_filelist.empty())
		m_filelist.clear();
}

void ImprovedBayes::clearTestingData()
{
	m_totalCorrectNum = 0;
	m_totalTestDocNum = 0;
}