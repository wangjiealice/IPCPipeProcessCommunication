#pragma once
//#include <QtWidgets/QMainWindow>
#include <opencv2/opencv.hpp>

using namespace std;

class ImageProcessing
{
public:
	ImageProcessing();
	ImageProcessing(int width, int height, unsigned char *data, unsigned long bufsize);
	~ImageProcessing();
	
	bool YUV420spToBGR24(unsigned char* pYUV, unsigned char*& pBGR24, int width, int height);
	void SaveBmpFromRGB(uchar * pdata, char * bmp_file, int width, int height);
	void ReverseMatrix(unsigned char* origial, unsigned char*& des, int width, int height);
	void YuvToRgb(const uint8_t *yuvRawData, uint8_t *rgbData, int width, int height);
	bool CreateImagebufferFromLocalYUVImage(string yuv_file_path, int width, int height, unsigned char*& yuvImageBuffer, bool isCamera208);
	int GetPixelCorrectionPixelNumber(
		uchar* bufferMemory,
		int imageHeight,
		int imageWidth,
		int thresh,
		bool isCheckLightPoint);

private:
	void TransferImageBuffer2Mat(cv::Mat& image);
	void TransferImageBuffer2Mat(unsigned char *grayImageData, cv::Mat& image, int height, int width);
	int GetCVMatPointValue(const cv::Mat& labelImg, int row, int column);
	void CalculateMeanVarianceValue(const cv::Mat& inputImage, float& mean, float& variance);

private:
	int badPointCount = 0;
	int imageWidth = 0;
	int imageHeight = 0;
	//Gray image data
	unsigned char *grayImageData = nullptr;
	unsigned long imageBufsize = 0;

};