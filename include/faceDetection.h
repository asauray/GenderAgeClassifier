#pragma once
#include"opencv2/core.hpp"
#include"opencv2/highgui.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/imgproc.hpp"
#include<string>

class FaceDetection
{
public:
	FaceDetection();
	~FaceDetection();
	void runDetection(cv::Mat& iput,std::vector<cv::Rect>&faces,int& faceCount,int &scale);
	
private:
	cv::CascadeClassifier cascade;
	std::string cascadeName;
	std::vector<cv::Rect> faces;
};


