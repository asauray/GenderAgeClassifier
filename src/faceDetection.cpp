#include"faceDetection.h"
#include<iostream>
using namespace cv;

FaceDetection::FaceDetection()
{
	//use haar cascade detection, read the .xml file
	cascadeName = "data/haarcascade_frontalface_alt.xml";
	//initialiser the cascade classifier
	if (!cascade.load(cascadeName))
	{
		std::cerr << "ERROR: Could not load classifier cascade" << std::endl;
		exit(1);
	}
}

FaceDetection::~FaceDetection()
{
}

// The detection of the faces from input, and the results are storged in vector<Rect>faces
void FaceDetection::runDetection(Mat& input,std::vector<Rect>&faces,int& faceCount,int&scale) {
	Mat gray, smallImg;
	double fx = 1 / scale;
	if (input.channels() != 1)
		cvtColor(input, gray, cv::COLOR_BGR2GRAY);
	resize(gray, smallImg, Size(), fx, fx, INTER_LINEAR);
	equalizeHist(smallImg, smallImg);
	cascade.detectMultiScale(smallImg, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
}