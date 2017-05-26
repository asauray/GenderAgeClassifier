#include "ageTrain.h"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <fstream>
using namespace std;
using namespace cv;
#define BWT03 0
#define BWT47 1
#define BWT814 2
#define BWT1520 3
#define BWT2145 4
#define BWT4660 5
#define BWT61 6
#define TAILLE_IMAGE 64

FindAge::FindAge()
{
}

FindAge::~FindAge()
{
}

void FindAge::setFindAge() {
	cout << "Please input the csv file name" << endl;
	cin >> fn_csv;
}

void FindAge::read_csv(const std::string&filename, std::vector<cv::Mat>&images, std::vector<int>&ageType, char separator) {
	ifstream file(filename.c_str(), ifstream::in);
	if (!file) {
		string error_message = "No valid input file was given, please check the given filename.";
		CV_Error(CV_StsBadArg, error_message);
	}
	string line, path, classlabel;
	while (getline(file, line)) {
		stringstream liness(line);
		getline(liness, path, separator);
		getline(liness, classlabel);
		if (!path.empty() && !classlabel.empty()) {
			images.push_back(imread(path, 0));
			ageType.push_back(atoi(classlabel.c_str()));
		}
	}
}

void FindAge::ageLearning() {
	vector<Mat> images;
	vector<int> ageTypes;
	try {
		read_csv(fn_csv, images, ageTypes);
	}
	catch (Exception&e) {
		cerr << "Error opening file :" << fn_csv << " Reason:" << e.msg << endl;
		exit(1);
	}
	if (images.size() <= 1) {
		string error_message = "This demo needs at least 2 images to work. Please add more images to your data set!";
		CV_Error(CV_StsError, error_message);
		exit(2);
	}
	resizeImage(images, TAILLE_IMAGE);
	cout << "images resized!" << endl;
	modelAge->train(images, ageTypes);
	modelAge->save("AgeInfo6000.xml");
	exit(0);
}

void FindAge::loadClassifier(const string&file) {
	modelAge->load(file);
}

void FindAge::resizeImage(vector<Mat>&images, const int & size) {
	vector<Mat>::iterator it;
	for (it = images.begin(); it != images.end(); it++) {
		resize(*(it), *(it), Size(size, size));
	}
}

void FindAge::noteAge(Mat&face) {
	Point position;
	Mat temp;
	position.x = 25;
	position.y = 25;
	face.copyTo(temp);
	cvtColor(temp, temp, CV_BGR2GRAY);
	resize(temp, temp, Size(TAILLE_IMAGE, TAILLE_IMAGE));
	result = modelAge->predict(temp);
	switch (result)
	{
	case BWT03:
		putText(face, "0-3", position, 1.5, 1.5, Scalar(255, 255, 255), 2);
		break;
	case BWT47:
		putText(face, "4-7", position, 1.5, 1.5, Scalar(255, 255, 255), 2);
		break;
	case BWT814:
		putText(face, "8-14", position, 1.5, 1.5, Scalar(255, 255, 255), 2);
		break;
	case BWT1520:
		putText(face, "15-20", position, 1.5, 1.5, Scalar(255, 255, 255), 2);
		break;
	case BWT2145:
		putText(face, "21-45", position, 1.5, 1.5, Scalar(255, 255, 255), 2);
		break;
	case BWT4660:
		putText(face, "46-60", position, 1.5, 1.5, Scalar(255, 255, 255), 2);
		break;
	case BWT61:
		putText(face, "+61", position, 1.5, 1.5, Scalar(255, 255, 255), 2);
		break;
	default:
		cout << "Age don't exist!" << endl;
		break;
	}
}

