#include "ofxCamShift.h"

using namespace::std;

ofxCamShift::ofxCamShift()
{
	random.seed();
	pixels = nullptr;
	meanShiftVector = ofVec2f(-1, -1);
	kernelType = NONE;
	height = -1;
	width = -1;
}

ofxCamShift::ofxCamShift(unsigned char* pixels, int width, int height)
{
	random.seed();
	this->pixels = pixels;
	this->width = width;
	this->height = height;
	kernelType = UNIFORM;

	windows.push_back(new ofxCamShiftWindow(ofVec2f(width / 2.0, height / 2.0)));
}

ofxCamShift::ofxCamShift(ofxCvGrayscaleImage& image)
{
	random.seed();
	this->pixels = image.getPixels();
	this->width = image.width;
	this->height = image.height;
	kernelType = UNIFORM;
	HOGImage.allocate(width, height);
	pixMat = ofxMatrix<unsigned char>(height, width, pixels);
	ROI = ofxMatrix<int>(height, width);
	windows.push_back(new ofxCamShiftWindow(ofVec2f(width / 2.0, height / 2.0)));
}

ofxCamShift::~ofxCamShift()
{
	pixels = nullptr;
	meanShiftVector = ofVec2f(-1, -1);
	kernelType = NONE;
	height = -1;
	width = -1;
}

void ofxCamShift::calculateMeanShift(ofxCamShiftWindow& window)
{
	double sumX = 0.0;
	double sumY = 0.0;
	double totalLuminance = 0.0;
	int analysisWindowSize = static_cast<int>(1.25 * window.getSize());
	int yMin = window.getCenter().y - analysisWindowSize / 2 < 0 ? 0 : window.getCenter().y - analysisWindowSize / 2;
	int yMax = window.getCenter().y + analysisWindowSize / 2 > height ? height : window.getCenter().y + analysisWindowSize / 2;

	int xMin = window.getCenter().x - analysisWindowSize / 2 < 0 ? 0 : window.getCenter().x - analysisWindowSize / 2;
	int xMax = window.getCenter().x + analysisWindowSize / 2 > width ? width : window.getCenter().x + analysisWindowSize / 2;
	unsigned char maxLuminance = 0;

	switch (kernelType)
	{
	default:
	case GAUSSIAN:
		break;
	case UNIFORM:
		for (auto y = yMin; y < yMax; ++y)
		{
			double distY = (y - window.getCenter().y);
			for (auto x = xMin; x < xMax; ++x)
			{
				double distX = (x - window.getCenter().x);
				sumX += pixels[y * width + x] * distX;
				sumY += pixels[y * width + x] * distY;
				totalLuminance += pixels[y * width + x];
				maxLuminance = max(maxLuminance, pixels[y * width + x]);
			}
		}
		break;
	}
	if (totalLuminance > 0.0)
	{
		window.setColor(ofColor::orange);
		meanShiftVector = ofVec2f(sumX / totalLuminance, sumY / totalLuminance);
		window.setSize(1.5 * static_cast<int>(ceil(sqrt(totalLuminance / static_cast<double>(maxLuminance)))));
		window.setLuminanceDensity(totalLuminance / pow(window.getSize(), 2));
	}
	else
	{
		window.setColor(ofColor::blue);
		meanShiftVector = ofVec2f(0.f, 0.f);
		window.setDeafultSize();
		window.setLuminanceDensity(0);
	}
}

void ofxCamShift::update()
{
	if (windows.size() > 0)
	{
		for (auto*& window : windows)
		{
			calculateMeanShift(*window);
			window->shiftWindow(meanShiftVector);
		}
	}
}

void ofxCamShift::draw()
{
	for (auto*& window : windows)
	{
		window->draw();
	}
}


int ofxCamShift::getWindowsCount()
{
	return windows.size();
}

ofxCvFloatImage ofxCamShift::getHog()
{
	return HOGImage;
}