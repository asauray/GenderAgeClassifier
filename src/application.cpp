#include"application.h"
#include<iostream>
#include<fstream>
using namespace std;
using namespace cv;

Application::Application() {
}
Application::~Application() {
}

void Application::setApplication(int type,string source) {
	if (type == 0) {
		isImage = true;
		this->source = source;
	}
	if (type == 1) {
		isVideo = true;
		this->source = source;
	}
}

void Application::noteFace() {
	//cout << "Face nombre:"<<faces.size() <<endl;
	for (size_t i = 0; i < faces.size(); i++)
	{
		Rect r = faces[i];
		Point center;
		Scalar color = Scalar(255,0,0);
		int radius;
		//cout << "Position " << i << ":" << faces[i] << endl;
		double aspect_ratio = (double)r.width / r.height;
		if (0.75 < aspect_ratio && aspect_ratio < 1.3)
		{
			center.x = cvRound((r.x + r.width*0.5)*scale);
			center.y = cvRound((r.y + r.height*0.5)*scale);
			radius = cvRound((r.width + r.height)*0.25*scale);
			circle(frameCourant, center, radius, color, 3, 8, 0);
		}
		else
			rectangle(frameCourant, cvPoint(cvRound(r.x*scale), cvRound(r.y*scale)),
				cvPoint(cvRound((r.x + r.width - 1)*scale), cvRound((r.y + r.height - 1)*scale)),
				color, 3, 8, 0);
	}
}

void Application::readCSV() {
	ifstream file(source.c_str(), ifstream::in);
	if (!file) {
		string error_message = "No valid input CSV file was given, please check the given filename.";
		CV_Error(CV_StsBadArg, error_message);
	}
	string line;
	while (getline(file, line)) {
		if(!line.empty())
			inPath.push_back(line);
	}
}

void Application::run(FindGender&genderClassifier,FindAge&ageClassfier) {
	vector<Rect>::iterator it;
	vector<string>::iterator itS;
	if (isImage) {
		readCSV();
		for (itS = inPath.begin(); itS != inPath.end(); itS++) {
			try
			{
				frameCourant = imread(*(itS));
			}
			catch (cv::Exception& e)
			{
				cerr << "Error opening file:" << source
					<< " Rasion: " << e.msg << endl;
				exit(1);
			}
			//Detect the faces
			m_det.runDetection(frameCourant, faces, faceCount, scale);
			//Find and note the gender in the faces
			for (it = faces.begin(); it != faces.end(); it++) {
				auto frame = frameCourant(*(it));
				genderClassifier.noteGender(frame);
				ageClassfier.noteAge(frame);
			}
			//note the face in the video or images
			noteFace();
			//write the results in the same images
			imwrite(*(itS), frameCourant);
		}
	}
	if (isVideo) {
		VideoCapture capture;
		if (isVideo) {
			try
			{
				capture.open(atoi(source.c_str()));
			}
			catch (cv::Exception& e)
			{
				cerr << "Error opening camera:" << source
					<< " Rasion: " << e.msg << endl;
				exit(1);
			}
		}
		cvNamedWindow("Resultat", 1);
		capture >> frameCourant;
		//Boucle when the capture is not empty
		while (!frameCourant.empty())
		{
			m_det.runDetection(frameCourant, faces, faceCount,scale);
			//for each faces finded, note the gender
			for (it = faces.begin(); it != faces.end(); it++) {
				auto frame = frameCourant(*(it));
				genderClassifier.noteGender(frame);
				ageClassfier.noteAge(frame);
			}
			//note the face in the video or images
			noteFace();
			//Display the results in real time
			imshow("Resultat", frameCourant);
			//push ESC to exit
			if (waitKey(1) == 27)
				break;
			capture >> frameCourant;	
		}
	}
}


