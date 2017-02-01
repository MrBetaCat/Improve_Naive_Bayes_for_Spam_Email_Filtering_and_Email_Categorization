#include "Input.h"
#include "ImprovedBayes.h"

int main()
{

	////////////////////////////////////////////////////////////////////
	Input *m_input=new Input(2);
	// Read the spam emails
	m_input->readingFiles("../data/spam_2",0,0,1395,1396,1395);

	// Read the non-spam emails
	m_input->readingFiles("../data/easy_ham_2", 1, 0, 1399, 1400, 1399);

	// Train Naive Bayes Classifier
	m_input->trainNaiveBayes();

	m_input->readNaiveBayesTrainingModel("model.txt");

	cout<<"Naive Bayes:"<<endl;
	//m_input->testNaiveBayes("../data/spam", 0, 0, 499);
	//cout<<(double)(m_input->m_totalCorrectNum)/(m_input->m_totalTestDocNum)<<endl;

	//m_input->clearTestingData();
	//m_input->testNaiveBayes("../data/easy_ham", 1, 0, 499);
	//cout<<(double)(m_input->m_totalCorrectNum)/(m_input->m_totalTestDocNum)<<endl;

	m_input->clearTestingData();
	//m_input->testNaiveBayes("../data/spam", 0, 0, 499);
	m_input->testNaiveBayes("../data/easy_ham", 1, 0, 499);
	cout<<(double)(m_input->m_totalCorrectNum)/(m_input->m_totalTestDocNum)<<endl;

	delete m_input;


	////////////////////////////////////////////////////////////////////
	// Training Improved Naive Bayes Classifier
	ImprovedBayes *impBayes = new ImprovedBayes(2);
	impBayes->readingFiles("../data/spam_2",0,0,1395);
	impBayes->readingFiles("../data/easy_ham_2", 1, 0, 1399);

	impBayes->trainImprovedBayes("model_ImprovedBayes.txt");

	// Testing Improved Naive Bayes Classifier
	impBayes->readImprovedBayesTrainingModel("model_ImprovedBayes.txt");

	cout<<"Improved Bayes:"<<endl;
	//impBayes->clearTestingData();
	//impBayes->testImprovedBayes("../data/spam", 0, 0, 499);
	//cout<<(double)(impBayes->m_totalCorrectNum)/(impBayes->m_totalTestDocNum)<<endl;

	//impBayes->clearTestingData();
	//impBayes->testImprovedBayes("../data/easy_ham", 1, 0, 499);
	//cout<<(double)(impBayes->m_totalCorrectNum)/(impBayes->m_totalTestDocNum)<<endl;

	impBayes->clearTestingData();
	//impBayes->testImprovedBayes("../data/spam", 0, 0, 499);
	impBayes->testImprovedBayes("../data/easy_ham", 1, 0, 499);
	cout<<(double)(impBayes->m_totalCorrectNum)/(impBayes->m_totalTestDocNum)<<endl;
	
	
	//impBayes->testImprovedBayes("../data/hard_ham", 1, 0, 249);
	//cout<<"  Accuracy for hard_ham:"<<impBayes->accuracy<<endl;

	delete impBayes;




	//////////////////////////////////////////////////////////////////////
	// Email Categorization

	// Categorization
	// Calender: 0
	// discussion_threads: 1
	// personal: 2
	// university: 3
	//const int classNum = 4;

	////
	//Input *m_input=new Input(classNum);

	//// Read Training Data...
	//// calender
	//m_input->readingFiles("../data/multiclass/calendar-beck-s",0,0,125,126,125);
	//m_input->readingFiles("../data/multiclass/calendar-corman-s",0,0,95,126,125);
	//m_input->readingFiles("../data/multiclass/calendar-haedicke-m",0,0,40,126,125);
	//m_input->readingFiles("../data/multiclass/calendar-kaminski-v",0,0,61,126,125);
	//m_input->readingFiles("../data/multiclass/calendar-lavorato-j",0,0,166,126,125);
	//m_input->readingFiles("../data/multiclass/calendar-mccarty-d",0,0,67,126,125);
	//// discussion_threads
	//m_input->readingFiles("../data/multiclass/discussion_threads-beck-s",1,0,1000,126,125);
	//m_input->readingFiles("../data/multiclass/discussion_threads-lokay-m",1,0,912,126,125);
	//m_input->readingFiles("../data/multiclass/discussion_threads-mann-k",1,0,1000,126,125);
	//// personal
	//m_input->readingFiles("../data/multiclass/personal-kaminski-v",2,0,280,126,125);
	//m_input->readingFiles("../data/multiclass/personal-farmer-d",2,0,320,126,125);
	//m_input->readingFiles("../data/multiclass/personal-griffith-j",2,0,24,126,125);
	//m_input->readingFiles("../data/multiclass/personal-williams-w3",2,0,15,126,125);
	//// university
	//m_input->readingFiles("../data/multiclass/university-kaminski-v",3,0,366,126,125);

	//////Training
	//m_input->trainNaiveBayes();

	//// Read model
	//m_input->readNaiveBayesTrainingModel("model.txt");

	//// Testing...
	//m_input->clearTestingData();
	//string str = "../data/multiclass/";
	//str += "calendar-whalley-g";
	//m_input->testNaiveBayes(str, 0, 0, 148);
	//cout<<(double)(m_input->m_totalCorrectNum)/(m_input->m_totalTestDocNum)<<endl;

	//str.clear();
	//m_input->clearTestingData();
	//str = "../data/multiclass/";
	//str += "calendar-white-s";
	//m_input->testNaiveBayes(str, 0, 0, 142);
	//cout<<(double)(m_input->m_totalCorrectNum)/(m_input->m_totalTestDocNum)<<endl;
	//
	//str.clear();
	//m_input->clearTestingData();
	//str = "../data/multiclass/";
	//str += "discussion_threads-mcconnell-m";
	//m_input->testNaiveBayes(str, 1, 0, 696);
	//cout<<(double)(m_input->m_totalCorrectNum)/(m_input->m_totalTestDocNum)<<endl;

	//m_input->clearTestingData();
	//str.clear();
	//str = "../data/multiclass/";
	//str += "discussion_threads-love-p";
	//m_input->testNaiveBayes(str, 1, 0, 577);
	//cout<<(double)(m_input->m_totalCorrectNum)/(m_input->m_totalTestDocNum)<<endl;

	//m_input->clearTestingData();
	//str.clear();
	//str = "../data/multiclass/";
	//str += "personal-beck-s";
	//m_input->testNaiveBayes(str, 2, 0, 47);
	//cout<<(double)(m_input->m_totalCorrectNum)/(m_input->m_totalTestDocNum)<<endl;

	//m_input->clearTestingData();
	//str.clear();
	//str = "../data/multiclass/";
	//str += "personal-davis-d";
	//m_input->testNaiveBayes(str, 2, 0, 40);
	//cout<<(double)(m_input->m_totalCorrectNum)/(m_input->m_totalTestDocNum)<<endl;

	//m_input->clearTestingData();
	//str.clear();
	//str = "../data/multiclass/";
	//str += "university-rogers-b-kean-s";
	//m_input->testNaiveBayes(str, 3, 0, 35);
	//cout<<(double)(m_input->m_totalCorrectNum)/(m_input->m_totalTestDocNum)<<endl;

	//delete m_input;

	//ImprovedBayes *impBayes = new ImprovedBayes(classNum);
	//// Read Training Data...
	//// calender
	//impBayes->readingFiles("../data/multiclass/calendar-beck-s",0,0,125);
	//impBayes->readingFiles("../data/multiclass/calendar-corman-s",0,0,95);
	//impBayes->readingFiles("../data/multiclass/calendar-haedicke-m",0,0,40);
	//impBayes->readingFiles("../data/multiclass/calendar-kaminski-v",0,0,61);
	//impBayes->readingFiles("../data/multiclass/calendar-lavorato-j",0,0,166);
	//impBayes->readingFiles("../data/multiclass/calendar-mccarty-d",0,0,67);
	//// discussion_threads
	//impBayes->readingFiles("../data/multiclass/discussion_threads-beck-s",1,0,1000);
	//impBayes->readingFiles("../data/multiclass/discussion_threads-lokay-m",1,0,912);
	//impBayes->readingFiles("../data/multiclass/discussion_threads-mann-k",1,0,1000);
	//// personal
	//impBayes->readingFiles("../data/multiclass/personal-kaminski-v",2,0,280);
	//impBayes->readingFiles("../data/multiclass/personal-farmer-d",2,0,320);
	//impBayes->readingFiles("../data/multiclass/personal-griffith-j",2,0,24);
	//impBayes->readingFiles("../data/multiclass/personal-williams-w3",2,0,15);
	//// university
	//impBayes->readingFiles("../data/multiclass/university-kaminski-v",3,0,366);

	//impBayes->trainImprovedBayes("model_ImprovedBayes_categorization.txt");

	//impBayes->readImprovedBayesTrainingModel("model_ImprovedBayes_categorization.txt");

	//// Testing...
	//impBayes->clearTestingData();
	//str = "../data/multiclass/";
	//str += "calendar-whalley-g";
	//impBayes->testImprovedBayes(str, 0, 0, 148);
	//cout<<(double)(impBayes->m_totalCorrectNum)/(impBayes->m_totalTestDocNum)<<endl;

	//impBayes->clearTestingData();
	//str.clear();
	//str = "../data/multiclass/";
	//str += "calendar-white-s";
	//impBayes->testImprovedBayes(str, 0, 0, 142);
	//cout<<(double)(impBayes->m_totalCorrectNum)/(impBayes->m_totalTestDocNum)<<endl;
	//
	//impBayes->clearTestingData();
	//str.clear();
	//str = "../data/multiclass/";
	//str += "discussion_threads-mcconnell-m";
	//impBayes->testImprovedBayes(str, 1, 0, 696);
	//cout<<(double)(impBayes->m_totalCorrectNum)/(impBayes->m_totalTestDocNum)<<endl;

	//impBayes->clearTestingData();
	//str.clear();
	//str = "../data/multiclass/";
	//str += "discussion_threads-love-p";
	//impBayes->testImprovedBayes(str, 1, 0, 577);
	//cout<<(double)(impBayes->m_totalCorrectNum)/(impBayes->m_totalTestDocNum)<<endl;

	//impBayes->clearTestingData();
	//str.clear();
	//str = "../data/multiclass/";
	//str += "personal-beck-s";
	//impBayes->testImprovedBayes(str, 2, 0, 47);
	//cout<<(double)(impBayes->m_totalCorrectNum)/(impBayes->m_totalTestDocNum)<<endl;

	//impBayes->clearTestingData();
	//str.clear();
	//str = "../data/multiclass/";
	//str += "personal-davis-d";
	//impBayes->testImprovedBayes(str, 2, 0, 40);
	//cout<<(double)(impBayes->m_totalCorrectNum)/(impBayes->m_totalTestDocNum)<<endl;

	//impBayes->clearTestingData();
	//str.clear();
	//str = "../data/multiclass/";
	//str += "university-rogers-b-kean-s";
	//impBayes->testImprovedBayes(str, 3, 0, 35);
	//cout<<(double)(impBayes->m_totalCorrectNum)/(impBayes->m_totalTestDocNum)<<endl;

	//delete impBayes;

	return 0;
}