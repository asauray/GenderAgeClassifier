#pragma once 
#include "faceDetection.h"
#include "genderTrain.h"
#include "ageTrain.h"
#include "opencv2/imgproc.hpp"
class Application
{
public:
	Application();
	~Application();
	void setApplication(int type,std::string source);
	void noteFace();
	void readCSV();
	void run(FindGender& genderClassifier,FindAge&ageClassifier);

private:
	std::vector<std::string> inPath;
	bool isImage = false;
	bool isVideo = false;
	std::string source = "";
	cv::Mat frameCourant;
	std::vector<cv::Rect> faces;
	std::vector<cv::Mat>ROI;
	FaceDetection m_det;
	int faceCount;
	int scale = 1;
};

