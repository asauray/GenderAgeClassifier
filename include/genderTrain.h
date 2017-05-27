#pragma once
#include<vector>
#include"opencv2/core.hpp"
#include <opencv2/face.hpp>
#include <opencv2/imgproc.hpp>

class Application;
class FindGender
{
public:
	FindGender();
	~FindGender();
	void setFindGender();
	void genderLearning();
	void noteGender(cv::Mat& face);
	void showEigenFace();
	void loadClassifier(const std::string &file);
private:
	int result = -1;
	void read_csv(const std::string& filename, std::vector<cv::Mat>& images, std::vector<int>& labels, char separator = ';');
	cv::Ptr<cv::face::BasicFaceRecognizer> model = cv::face::createFisherFaceRecognizer();
	//cv::Ptr<cv::FaceRecognizer>model = cv::createLBPHFaceRecognizer();
	std::string fn_csv = "F:/ProjetMultimedia/CreatCSV/CreatCSV/CreatCSV/GenreTrain.csv";
	void resizeImage(std::vector<cv::Mat>&image,const int& imageSize);
};

