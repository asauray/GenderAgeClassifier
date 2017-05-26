#pragma once
#include <vector>
#include "opencv2/core/core.hpp"
#include "opencv2/contrib/contrib.hpp"
class FindAge
{
public:
	FindAge();
	~FindAge();
	void setFindAge();
	void ageLearning();
	void noteAge(cv::Mat& face);
	void loadClassifier(const std::string &file);

private:
	int result = -1;
	void read_csv(const std::string&filename, std::vector<cv::Mat>&images, std::vector<int>&ageType, char separator = ';');
	std::string fn_csv = "F:/ProjetMultimedia/CreatCSV/CreatCSV/CreatCSV/AgeTrain.csv";
	void resizeImage(std::vector<cv::Mat>&images, const int& imageSize);
	cv::Ptr<cv::FaceRecognizer> modelAge = cv::createLBPHFaceRecognizer();
};


