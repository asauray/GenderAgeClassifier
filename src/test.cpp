#include<iostream>
#include"application.h"
#include"genderTrain.h"
#include"ageTrain.h"
using namespace std;
#define DONT_TRAINING_GENDER
#define DONT_TRAINING_AGE
void help() {
	cout << "Executer:" << "xxx.exe -video source || xxx.exe -image path" << endl;
}

int main(int argc, const char*argv[]) {
	Application m_app;
	FindGender m_gender;
	FindAge m_age;
#ifndef DONT_TRAINING_GENDER
	// input the csv file name from console, if not, use the csv default
	//m_gender.setFindGender(); 

	cout << "Gender Training..." << endl;
	//training the gender classifier
	m_gender.genderLearning();
#else
	//Do not train the classifier but load from the .yaml file
	m_gender.loadClassifier("data/genderTrained2000.yaml");
#endif // !DONT_TRAINING_GENDER

#ifndef DONT_TRAINING_AGE
	cout << "Age Trainig..." << endl;
	m_age.ageLearning();
#else
	m_age.loadClassifier("data/AgeInfo.xml");
#endif // !DONT_TRAINING_AGE

	

	/*switch (argc)
	{
	case 1:
	case 2: help(); break;
	case 3:
		if (strcmp(argv[1], "-video")) {
			m_app.setApplication(1, argv[1]);
			m_app.run();
		}
		else if (strcmp(argv[1], "-image")) {
			m_app.setApplication(0, argv[1]);
			m_app.run();
		}
		else help();
		break;
	default:
		help();
		break;
	}*/
	//Write the eigenFace mean etc.
	//m_gender.showEigenFace();

	//First argument is type of input: 1 for video and 0 for images
	//Second argument is the source of the input, for video is 0, for images is the file csv which include the path of images
	//m_app.setApplication(0, "data/TestMan.csv");
	m_app.setApplication(1, "0");
	m_app.run(m_gender,m_age);

	return 0;
}

