#include "LocalWeightedNaiveBayes.h"


WeightedNaiveBayes::WeightedNaiveBayes(int flag,string filename,int begin0, int end0, int begin1, int end1)
{
	m_input=new MultiInput(2);
	m_flag=flag;
	m_filename=filename;
	m_begin0=begin0;
	m_end0=end0;
	m_begin1=begin1;
	m_end1=end1;
}


WeightedNaiveBayes::~WeightedNaiveBayes(void)
{
}

string WeightedNaiveBayes::getNextToken(istream &in)
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

void WeightedNaiveBayes::readingSingleFile(string filename)
{
	ifstream fin(filename.c_str());
	string s;
	string empty ="";
	while((s=getNextToken(fin))!=empty )
	{
		++m_wordsForTest[s];
	}
}

void WeightedNaiveBayes::precomputeDistance()
{
	m_input->readingFiles("spam_2",0,0,599,600,699);//1396
	m_input->readingFiles("easy_ham_2",1,0,599,600,699);
	readingSingleFile(m_filename);
	m_prob_c.resize(2);//0 for spam; and 1 for nonspam
	m_prob_a_given_c.resize(2);


	map<string,int>::iterator itr;
	for(int i=0;i<m_input->m_classNum;i++)
	{
		for(int j=0;j<INSTANCES;j++)
		{
			double sum=0.0; 
			for(itr=m_wordsForTest.begin();itr!=m_wordsForTest.end();itr++)
			{
				vector<float> dis;
				string cur_word=itr->first;
				int cur_freq=itr->second;
				int freq=m_input->m_classWords[i][j][cur_word];
				int cur_dis=abs(cur_freq-freq);
				sum+=(double)(cur_dis*cur_dis);
			}
			m_distance.push_back(sqrt(sum));
		}
	}
}

void WeightedNaiveBayes::precomputeWeight()
{
	m_weight.resize(m_distance.size());
	std::vector<float> myVec(m_distance.begin(), m_distance.end());
	std::sort(myVec.begin(),myVec.end());
	float dis_k=myVec[NEIGHBORS-1];
	for(int i=0;i<(int)m_distance.size();i++)
	{
		float w_i=m_distance[i]/dis_k;
		if(w_i>=1.0)
			m_weight[i]=0;
		else
			m_weight[i]=1.0-w_i;
	}


	//weight rescale
	float amount=0.0;
	float sum=0.0;
	for(int i=0;i<(int)m_weight.size();i++)
	{
		if(m_weight[i]>0.0)
			amount+=1.0;
		sum+=m_weight[i];
	}

	for(int i=0;i<(int)m_weight.size();i++)
	{
		if(m_weight[i]>0.0)
			m_weight[i]=m_weight[i]*amount/sum;
	}
}

void WeightedNaiveBayes::computeProbC()
{		
	double sum=0.0;
	for(int i=0;i<(int)m_weight.size();i++)
	{
		sum+=m_weight[i];
	}
	for(int i=0;i<m_input->m_classNum;i++)
	{
		double sum_label=0.0;
		for(int j=0;j<INSTANCES;j++)
		{
			int index=i*INSTANCES+j;
			sum_label+=m_weight[index];
		}
		m_prob_c[i]=(1.0+sum_label)/((double)m_input->m_classNum+sum);
		m_prob_c[i]=log10(m_prob_c[i]);
	}
}

void WeightedNaiveBayes::computeProbAGivenC()
{
	map<string,int>::iterator itr;
	for(int i=0;i<m_input->m_classNum;i++)
	{
		for(itr=m_wordsForTest.begin();itr!=m_wordsForTest.end();itr++)
		{
			string cur_word=itr->first;
			int a_i_j=itr->second;
			double w_numerator=0.0;
			double w_denominator=0.0;
			double prob=0.0;
			int c_word=0;
			int c_token=0;
			for(int j=0;j<INSTANCES;j++)
			{
				int index=i*INSTANCES+j;
				int c_cur_word=m_input->m_classWords[i][j][cur_word];
				c_word+=c_cur_word;
				c_token+=m_input->m_numTokens[i][j];
				if(c_cur_word==a_i_j)
					w_numerator+=m_weight[index];
			}
			for(int j=0;j<(int)m_weight.size();j++)
			{
				if(m_input->m_classWords[j/INSTANCES][j%INSTANCES][cur_word]==a_i_j)
					w_denominator+=m_weight[j];
			}
			m_prob_a_given_c[i][cur_word]=(1.0+(double)c_word+w_numerator)
									      /((double)m_input->m_sizeVocabulary+double(c_token)+w_denominator);
			m_prob_a_given_c[i][cur_word]=log10(m_prob_a_given_c[i][cur_word]);
		}
	}
}

void WeightedNaiveBayes::outputTestRes()
{
	m_prob_res.resize(2);
	for(int i=0;i<(int)m_prob_res.size();i++)
	{
		m_prob_res[i]=m_prob_c[i];
	}
	map<string,double>::iterator itr;

	for(int i=0;i<m_input->m_classNum;i++)
	{
		for(itr=m_prob_a_given_c[i].begin();itr!=m_prob_a_given_c[i].end();itr++)
		{
			m_prob_res[i]+=itr->second;
		}
	}

	if(m_prob_res[0]>m_prob_res[1])
	{
		if(m_flag==0)
			m_res=true;
		else
			m_res=false;
	}
	else
	{
		if(m_flag==1)
			m_res=true;
		else
			m_res=false;
	}
}