#include "Input.h"

Input::Input(int classNum)
{
	m_classNum=classNum;
	m_sizeVocabulary=0;
	m_classWords.resize(classNum);
	m_probClassWord.resize(classNum);
	m_numTokens.resize(classNum);
	m_docNum.resize(classNum);
}

Input::~Input(void)
{
	if(!m_filelist.empty())
		m_filelist.clear();
	if(!m_classWords.empty())
		m_classWords.clear();
	if(!m_probClassWord.empty())
		m_probClassWord.clear();
	if(!m_words.empty())
		m_words.clear();
}

string Input::getNextToken(istream &in)
{
    char c;
    string ans="";
    c=in.get();

    //while(!isalpha(c) && !in.eof())//cleaning non letter charachters
    //{
    //    c=in.get();
    //}
    //while(isalpha(c))
    //{
    //    ans.push_back(tolower(c));
    //    c=in.get();
    //}

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

void Input::readingFiles(string foldername, int class_flag, int beginIndex, int endIndex, int beginIndex1, int endIndex1)
{
	//the first file name of filelist is always ".."
    _finddata_t file;
	long lf;
	string folder_path_name=foldername+"\\*.*";
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

	//read all files
	m_docNum[class_flag]=endIndex+1-beginIndex+endIndex1+1-beginIndex1;
	for(int i=beginIndex+1;i<=endIndex+1;i++)
	{
		string filename=foldername+"\\"+m_filelist[i];
		m_total_filelist.push_back(filename);
		m_total_flags.push_back(class_flag);
		ifstream fin(filename.c_str());
		string s;
		string empty ="";
		while((s=getNextToken(fin))!=empty )
		{
				++m_classWords[class_flag][s];
				++m_words[s];
				m_numTokens[class_flag]++;
		}
	}
	for(int i=beginIndex1+1;i<=endIndex1+1;i++)
	{
		string filename=foldername+"\\"+m_filelist[i];
		m_total_filelist.push_back(filename);
		m_total_flags.push_back(class_flag);
		ifstream fin(filename.c_str());
		string s;
		string empty ="";
		while((s=getNextToken(fin))!=empty )
		{
				++m_classWords[class_flag][s];
				++m_words[s];
				m_numTokens[class_flag]++;
		}
	}
	if(!m_filelist.empty())
		m_filelist.clear();

	m_sizeVocabulary=m_words.size();
}