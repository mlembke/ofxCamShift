#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "Poco/Random.h"
#include "ofxKernelType.h"
#include "ofxCamShiftWindow.h"
#include "ofxMatrix"

class ofxCamShift
{
public:
	ofxCamShift();
	ofxCamShift(unsigned char* pixels, int width, int height);
	ofxCamShift(ofxCvGrayscaleImage& image);
	~ofxCamShift();

	void update();
	void draw();
	void calculateMeanShift(ofxCamShiftWindow& window);
	int getWindowsCount();
	ofxCvFloatImage getHog();

private:
	unsigned char* pixels;
	ofxMatrix<unsigned char> pixMat;
	vector<ofxCamShiftWindow*> windows;
	ofxMatrix<float> HOG;
	ofxMatrix<int> ROI;
	ofxCvFloatImage HOGImage;
	ofVec2f meanShiftVector;
	KernelType kernelType;
	int width;
	int height;

	Poco::Random random;
};