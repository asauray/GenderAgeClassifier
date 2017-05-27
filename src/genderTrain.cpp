#include"genderTrain.h"
#include"opencv2/highgui/highgui.hpp"
#include<fstream>
#include<iostream>
using namespace std;
using namespace cv;
#define TAILLE_IMAGE 128

static Mat norm_0_255(InputArray _src) {
	Mat src = _src.getMat();
	// Create and return normalized image:
	Mat dst;
	switch (src.channels()) {
	case 1:
		cv::normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC1);
		break;
	case 3:
		cv::normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC3);
		break;
	default:
		src.copyTo(dst);
		break;
	}
	return dst;
}

FindGender::FindGender()
{
}
void FindGender::setFindGender() {
	cout << "Input the path of file .csv for gender learning" << endl;
	cin >> fn_csv;
}
FindGender::~FindGender()
{
}

void FindGender::read_csv(const std::string& filename, std::vector<cv::Mat>& images, std::vector<int>& labels, char separator) {
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
			labels.push_back(atoi(classlabel.c_str()));
		}
	}
}


void FindGender::genderLearning() {
	vector<Mat> images;
	vector<int> labels;
	try {
		read_csv(fn_csv, images, labels);
	}
	catch (Exception&e) {
		cerr << "Error opening file \"" << fn_csv << "\". Reason: " << e.msg << endl;
		// nothing more we can do
		exit(1);
	}
	if (images.size() <= 1) {
		string error_message = "This demo needs at least 2 images to work. Please add more images to your data set!";
		CV_Error(CV_StsError, error_message);
		exit(2);
	}
	resizeImage(images, TAILLE_IMAGE);
	cout << "images resized!" << endl;
	model->train(images, labels);
	model->save("GenderInfoLBP.xml");
	exit(0);
};

void FindGender::loadClassifier(const string&file){
	model->load(file);
}


void FindGender::resizeImage(vector<Mat>&images,const int & size) {
	vector<Mat>::iterator it;
	for (it = images.begin(); it != images.end(); it++) {
		resize(*(it), *(it), Size(size, size));
	}
	
}

void FindGender::noteGender(Mat&face) {
	Point position;
	Mat temp;
	position.x = 30;
	position.y = 30;
	face.copyTo(temp);
	cvtColor(temp, temp, CV_BGR2GRAY);
	resize(temp, temp, Size(TAILLE_IMAGE, TAILLE_IMAGE));
	result = model->predict(temp);
	//cout << result << endl;
	if (result == 0) {
		putText(face, "M", position, 1.5, 1.5, Scalar(0, 255, 0), 2);
	}
	if(result == 1){
		putText(face, "F", position, 1.5, 1.5, Scalar(0, 0, 255), 2);
	}
}

void FindGender::showEigenFace() {
	// Here is how to get the eigenvalues of this Eigenfaces model:
	Mat eigenvalues = model->getEigenValues();
	// And we can do the same to display the Eigenvectors (read Eigenfaces):
	Mat W = model->getEigenVectors();
	// Get the sample mean from the training data
	Mat mean = model->getMean();

	imwrite("Wild_mean.png", norm_0_255(mean.reshape(1, 128)));
	for (int i = 0; i < min(16, W.cols); i++) {
		// get eigenvector #i
		Mat ev = W.col(i).clone();
		// Reshape to original size & normalize to [0...255] for imshow.
		Mat grayscale = norm_0_255(ev.reshape(1, 128));
		// Show the image & apply a Bone colormap for better sensing.
		Mat cgrayscale;
		applyColorMap(grayscale, cgrayscale, COLORMAP_BONE);
		// Display or save:
		imshow(format("Wild_fisherface_%d", i), cgrayscale);
		imwrite(format("Wild_fisherface_%d.png", i), norm_0_255(cgrayscale));
	}
}


