#include "stdafx.h"
#include "ImageProcessing.h"

#include <opencv2/core/core.hpp>//OpenCV包含头文件  
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/imgcodecs/imgcodecs_c.h>

#include <time.h>
#include <vector>//容器头文件 
#include <stack>
#include <math.h>
#include <bitset>
#include <stdio.h>  
#include <stdlib.h>  
#include <windows.h>

using namespace std;
using namespace cv;

const int ImageSize = 1920 * 1080;

string saveImageFileFolder = "C:\\Users\\zcalwang\\Desktop\\CameraTestFolder\\AxiocamApplication\\";

typedef long LONG;
typedef unsigned long DWORD;
typedef unsigned short WORD;
#define SaveYonlyBmpImage

typedef struct {
	WORD    bfType;
	DWORD   bfSize;
	WORD    bfReserved1;
	WORD    bfReserved2;
	DWORD   bfOffBits;
} BMPFILEHEADER_T;

typedef struct {
	DWORD      biSize;
	LONG       biWidth;
	LONG       biHeight;
	WORD       biPlanes;
	WORD       biBitCount;
	DWORD      biCompression;
	DWORD      biSizeImage;
	LONG       biXPelsPerMeter;
	LONG       biYPelsPerMeter;
	DWORD      biClrUsed;
	DWORD      biClrImportant;
} BMPINFOHEADER_T;

class colorobj
{
public:
	int value;
	Scalar mycolor;
};

vector<colorobj> setcolor;//收集需要上色的灰度对象

bool equal255or0(int &value)//判断元素是否等于255或者0
{
	if (value == 255 || value == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void compare(int &value, int &minimun)//比较大小
{
	if (value != 0 && value != 255)
	{
		if (minimun >= value)
		{
			minimun = value;
		}
	}
}

Scalar GetRandomColor()//彩色显示
{
	uchar r = (uchar)(255 * (rand() / (1.0 + RAND_MAX)));
	uchar g = (uchar)(255 * (rand() / (1.0 + RAND_MAX)));
	uchar b = (uchar)(255 * (rand() / (1.0 + RAND_MAX)));
	return cv::Scalar(b, g, r);
}

int ImageProcessing::GetCVMatPointValue(const cv::Mat& labelImg, int row, int column)
{
	int imageWidth = labelImg.cols;
	int imageHeight = labelImg.rows;

	//int value1 = labelImg.at<int>(row, column);
	int value2 = labelImg.data[row*imageWidth + column];
	printf("Coordinate X : %d, Y : %d, value is : %d \n", row, column, value2);

	return 0;
}

void LabelColor(const cv::Mat& labelImg, cv::Mat& colorLabelImg)
{
	if (labelImg.empty() ||
		labelImg.type() != CV_32SC1)
	{
		return;
	}


	std::map<int, cv::Scalar> colors;

	int rows = labelImg.rows;
	int cols = labelImg.cols;

	colorLabelImg.release();
	colorLabelImg.create(rows, cols, CV_8UC3);
	colorLabelImg = cv::Scalar::all(0);

	for (int i = 0; i < rows; i++)
	{
		const int* data_src = (int*)labelImg.ptr<int>(i);
		uchar* data_dst = colorLabelImg.ptr<uchar>(i);
		for (int j = 0; j < cols; j++)
		{
			int pixelValue = data_src[j];
			if (pixelValue > 1)
			{
				if (colors.count(pixelValue) <= 0)
				{
					colors[pixelValue] = GetRandomColor();
				}

				cv::Scalar color = colors[pixelValue];
				*data_dst++ = (uchar)color[0];
				*data_dst++ = (uchar)color[1];
				*data_dst++ = (uchar)color[2];
			}
			else
			{
				data_dst++;
				data_dst++;
				data_dst++;
			}
		}
	}
}

void ImageProcessing::CalculateMeanVarianceValue(const cv::Mat& inputImage, float& mean, float& variance)
{
	Scalar     meanScalar;
	Scalar     devScalar;

	meanStdDev(inputImage, meanScalar, devScalar);
	mean = (float)meanScalar.val[0];
	variance = (float)devScalar.val[0];
	std::cout << "Image mean value is: " << mean << ",\t" << "Image variance is: "<< variance << "\n";
}

void ImageProcessing::TransferImageBuffer2Mat(unsigned char *grayImageData, cv::Mat& image, int height, int width)
{
	image = cv::Mat(height, width, CV_8UC1, grayImageData, 0);

	imwrite(saveImageFileFolder + "imageMat.jpg", image);
}

void ImageProcessing::TransferImageBuffer2Mat(cv::Mat& image)
{
	//  CV_<bit_depth>(S | U | F)C<number_of_channels>
	//	
	//	1--bit_depth-- - 比特数-- - 代表8bite, 16bites, 32bites, 64bites-- - 举个例子吧--比如说, 如
	//	如果你现在创建了一个存储--灰度图片的Mat对象, 这个图像的大小为宽100, 高100, 那么, 现在这张
	//	灰度图片中有10000个像素点，它每一个像素点在内存空间所占的空间大小是8bite, 8位--所以它对
	//	应的就是CV_8
	//
	//	2--S | U | F--S--代表-- - signed int-- - 有符号整形
	//	U--代表--unsigned int--无符号整形
	//	F--代表--float-------- - 单精度浮点型
	//
	//	3--C<number_of_channels>----代表-- - 一张图片的通道数, 比如:
	//  1--灰度图片--grayImg-- - 是--单通道图像
	//	2--RGB彩色图像-------- - 是--3通道图像
	//	3--带Alph通道的RGB图像--是--4通道图像
	//CV_8UC1---则可以创建----8位无符号的单通道---灰度图片------grayImg

	image = cv::Mat(imageHeight, imageWidth, CV_8UC1, grayImageData, 0);

	imwrite(saveImageFileFolder + "imageMat.jpg", image);
}

bool ImageProcessing::YUV420spToBGR24(unsigned char* pYUV, unsigned char*& pBGR24, int width, int height)
{
	/*unsigned long bufsize = width * height;
	pBGR24 = (unsigned char *)malloc(bufsize * 3);*/

	if (width < 1 || height < 1 || pYUV == NULL || pBGR24 == NULL)
		return false;

	Mat yuvImg(height + height / 2, width, CV_8UC1, pYUV);

	//只有Y分量的Mat，保存出来的图是8bit的灰度图
	//即检测坏点的基本矩阵
	cv::Mat saveYuvImg(height, width, CV_8UC1, pYUV);

	Mat dst(height, width, CV_8UC3, pBGR24);
	cv::cvtColor(yuvImg, dst, COLOR_YUV2RGB_NV21);

	//Mat reverseDst(height, width, CV_8UC3, pBGR24);
	//cv::cvtColor(dst, reverseDst, COLOR_RGB2BGR);

	//cv::imshow("yuv", yuvImg);
	//cv::imwrite("C:\\Users\\zcalwang\\Desktop\\CameraTestFolder\\PixelCorrection\\outputRGB.bmp", dst);

	return true;
}

static inline uint8_t clamp(int c)
{
	if (c < 0) {
		return 0;
	}
	else if (c > 255) {
		return 255;
	}
	else {
		return (uint8_t)c;
	}
}

void ImageProcessing::ReverseMatrix(unsigned char* origial, unsigned char*& des, int width, int height)
{
	if (width < 1 || height < 1 || origial == NULL || des == NULL)
		return;

	//unsigned long bufsize = width * height;
	//des = (unsigned char *)malloc(bufsize * 3);

	Mat src(height, width, CV_8UC3, origial);
	Mat dest(height, width, CV_8UC3, des);

	cv::cvtColor(src, dest, COLOR_RGB2BGR);
}

//from https://en.wikipedia.org/wiki/YCbCr
void ImageProcessing::YuvToRgb(const uint8_t *yuvRawData, uint8_t *rgbData, int width, int height)
{
	const uint8_t *pYBits = NULL;
	const uint8_t *pUBits = NULL;
	const uint8_t *pVBits = NULL;
	const uint8_t *pURowBits = NULL;

	int yDataSize = width * height;
	pYBits = (const uint8_t *)yuvRawData;
	pURowBits = (const uint8_t *)yuvRawData + yDataSize;
	uint8_t *pDestBits = rgbData;

	for (int y = 0; y < height; y++) {
		pUBits = pURowBits;
		pVBits = pUBits + 1;//yDataSize / 4;
		for (int x = 0; x < width; x++, pYBits++, pDestBits += 3) {
			// YUV to RGB formula from https://en.wikipedia.org/wiki/YCbCr
			int Y = (int)pYBits[0];
			// int C = (int)pYBits[0] - 16;
			int E = (int)pUBits[0] - 128;  // Cr
			int D = (int)pVBits[0] - 128;  // Cb

										   // const double scale = 219.0 / 255.0;  // scale to [16, 235] range, for video;

										   // BT 601
										   // int rTmp = (1.164 * C + 1.596 * E) * scale + 16.5;
										   // int gTmp = (1.164 * C - 0.392*D-0.813 * E) * scale + 16.5;
										   // int bTmp = (1.164 * C + 2.017 * D) * scale + 16.5;

										   // BT 709
										   // int rTmp = (1.164 * C + 1.793 * E) * scale + 16.5;
										   // int gTmp = (1.164 * C - 0.213 * D - 0.533 * E) * scale + 16.5;
										   // int bTmp = (1.164 * C + 2.112 * D) * scale + 16.5;

										   // JPEG
										   // int rTmp = Y + 1.402f * E + 0.5f;
										   // int gTmp = Y - 0.344136f * D - 0.714136f * E + 0.5f;
										   // int bTmp = Y + 1.772f * D + 0.5f;

										   // JPEG (Int)
			int rTmp = ((Y << 8) + 359 * E + 128) >> 8;
			int gTmp = ((Y << 8) - 88 * D - 183 * E + 128) >> 8;
			int bTmp = ((Y << 8) + 454 * D + 128) >> 8;

			pDestBits[0] = clamp(rTmp);
			pDestBits[1] = clamp(gTmp);
			pDestBits[2] = clamp(bTmp);

			if ((x % 2) == 1) {
				pUBits += 2;
				pVBits += 2;
			}
		}

		if ((y % 2) == 1) {
			pURowBits += width;
		}
	}
}

void ImageProcessing::SaveBmpFromRGB(uchar * pdata, char * bmp_file, int width, int height)
{      //分别为rgb数据，要保存的bmp文件名，图片长宽  
	int size = width*height * 3 * sizeof(char); // 每个像素点3个字节  
												// 位图第一部分，文件信息  
	BMPFILEHEADER_T bfh;
	bfh.bfType = (WORD)0x4d42;  //bm  
	bfh.bfSize = size  // data size  
		+ sizeof(BMPFILEHEADER_T) // first section size  
		+ sizeof(BMPINFOHEADER_T) // second section size  
		;
	bfh.bfReserved1 = 0; // reserved  
	bfh.bfReserved2 = 0; // reserved  
	bfh.bfOffBits = sizeof(BMPFILEHEADER_T) + sizeof(BMPINFOHEADER_T);//真正的数据的位置  

																	  // 位图第二部分，数据信息  
	BMPINFOHEADER_T bih;
	bih.biSize = sizeof(BMPINFOHEADER_T);
	bih.biWidth = width;
	bih.biHeight = -height;//BMP图片从最后一个点开始扫描，显示时图片是倒着的，所以用-height，这样图片就正了  
	bih.biPlanes = 1;//为1，不用改  
	bih.biBitCount = 24;
	bih.biCompression = 0;//不压缩  
	bih.biSizeImage = size;
	bih.biXPelsPerMeter = 2835;//像素每米  
	bih.biYPelsPerMeter = 2835;
	bih.biClrUsed = 0;//已用过的颜色，24位的为0  
	bih.biClrImportant = 0;//每个像素都重要  
	FILE * fp = fopen(bmp_file, "wb");
	if (!fp) return;

	fwrite(&bfh, 8, 1, fp);//由于linux上4字节对齐，而信息头大小为54字节，第一部分14字节，第二部分40字节，所以会将第一部分补齐为16自己，直接用sizeof，打开图片时就会遇到premature end-of-file encountered错误  
	fwrite(&bfh.bfReserved2, sizeof(bfh.bfReserved2), 1, fp);
	fwrite(&bfh.bfOffBits, sizeof(bfh.bfOffBits), 1, fp);
	fwrite(&bih, sizeof(BMPINFOHEADER_T), 1, fp);
	fwrite(pdata, size, 1, fp);
	fclose(fp);
}

//Example:
//  ImageProcessing imageProcess;
//	imageProcess.CreateImagebufferFromLocalYUVImage("C:\\Users\\Test\\Desktop\\TWAIN\\Test_image\\208_1",imageWidth, imageHeight, yuvImageBuffer, true); 

bool ImageProcessing::CreateImagebufferFromLocalYUVImage(string yuv_file_path, int width, int height, unsigned char*& yuvImageBuffer,bool isCamera208)
{
	if (yuvImageBuffer == NULL) return false;
	printf("yuv file w: %d, h: %d \n", width, height);

	FILE* pFileIn = fopen(yuv_file_path.c_str(), "rb+");

	if (fseek(pFileIn, 0, SEEK_END) != 0) return false;
	int frame_count = (int)((int)ftell(pFileIn) / (width * height));  // ftell 用于求文件大小

	printf("frame num is %d \n", frame_count);
	if(fseek(pFileIn, 0, SEEK_SET) != 0) return false;

	int bufLen = 0;
	if (isCamera208)
	{
		bufLen = width * height * 3 / 2;
	}
	else
	{
		bufLen = width * height;
	}

	for (int i = 0; i < frame_count; i++)
	{
		int readResult = fread(yuvImageBuffer, bufLen * sizeof(unsigned char), 1, pFileIn);
		if (readResult == 0)
		{
			return false;
		}
	}

	if (fclose(pFileIn) != 0) return false;

	return true;
}

int ImageProcessing::GetPixelCorrectionPixelNumber(
	uchar* bufferMemory,
	int imageHeight,
	int imageWidth,
	int thresh,
	bool isCheckLightPoint)
{
	int badPointNumber = 0;

	//Simple get pixel count
	for (int i = 0; i < imageHeight*imageWidth; i++)
	{
		uchar pointY = bufferMemory[i];
		if (isCheckLightPoint)
		{
			if (pointY > thresh)
			{
				/*qDebug() << "Exist light point:";

				qDebug() << "i number is " + QString::number(i);
				qDebug() << "pointY is " + QString::number(pointY);*/

				++badPointNumber;
			}
		}
		else
		{
			if (pointY < thresh)
			{
				/*qDebug() << "Exist dark point:";

				qDebug() << "i number is " + QString::number(i);
				qDebug() << "pointY is " + QString::number(pointY);*/

				++badPointNumber;
			}
		}
	}

	return badPointNumber;
}

ImageProcessing::ImageProcessing()
{
//Test case 1
	//int width = 3840;
	//int height = 2160;
	//FILE* pFileIn = fopen("C:\\Camera\\YUVImageViewer\\Samples\\208_color2.yuv", "rb+");

	//fseek(pFileIn, 0, SEEK_END);
	//int frame_count = 0;

	//frame_count = (int)((int)ftell(pFileIn) / ((width * height * 3) / 2));  // ftell 用于求文件大小
	//printf("frame num is %d \n", frame_count);
	//fseek(pFileIn, 0, SEEK_SET);//文件内位置定位到文件头

	//int bufLen = width * height * 3 / 2;
	//unsigned char* pYuvBuf = new unsigned char[bufLen];

	//for (int i = 0; i < frame_count; i++)
	//{
	//	fread(pYuvBuf, bufLen * sizeof(unsigned char), 1, pFileIn);
	//}

	//unsigned char* outputBuffer = nullptr;
	//unsigned long bufsize = width * height;
	//outputBuffer = (unsigned char *)malloc(bufsize * 3);

	//YUV420spToBGR24(pYuvBuf, outputBuffer,width,height);
	////SaveBmpFromRGB(outputBuffer, "C:\\Users\\zcalwang\\Desktop\\CameraTestFolder\\PixelCorrection\\Yuv420sp2Rgb.bmp",width,height);


	//Mat rgbImg(height, width, CV_8UC3, outputBuffer);
	////cv::Mat rgbImg;
	////memcpy(rgbImg.data, outputBuffer, 3 * bufLen * sizeof(unsigned char));

	//cv::imwrite("C:\\Users\\zcalwang\\Desktop\\CameraTestFolder\\PixelCorrection\\Yuv420sp2Rgb.bmp", rgbImg);

//Test case 2
	//ReadYUVImage("C:\\Camera\\YUVImageViewer\\Samples\\red.yuv", 3840, 2160);

	//printf("This is only for test, do not use it in real BL.\n");
}

ImageProcessing::ImageProcessing(int width, int height, unsigned char *data, unsigned long bufsize)
{
	imageWidth = width;
	imageHeight = height;
	grayImageData = (unsigned char *)malloc(bufsize);
	memcpy(grayImageData, data, bufsize);

#pragma region[Transfer byte[] to Mat]

	//int width = 1920;
	//int height = 1080;
	//int grayValue = 255;
	//unsigned char *_data = new unsigned char[width*height]();

	//for (int i = 0; i < width*height; i++)
	//{
	//	++grayValue;
	//	if (grayValue >= 255)
	//	{
	//		grayValue = 0;
	//	}
	//	_data[i] = grayValue;
	//}

	//Mat imageMat = cv::Mat(height, width, CV_8UC1, _data, 0);

	//imwrite("C:\\Users\\zcalwang\\Desktop\\CameraTestFolder\\PixelCorrection\\imageMat.jpg", imageMat);
	//printf("End");

#pragma endregion[Transfer byte[] to Mat]


#pragma region[Test light&&dark point pass]

	//cv::Mat lightPointImage = cv::imread("C:\\Users\\zcalwang\\Desktop\\CameraTestFolder\\PixelCorrection\\6numberBlackBG.jpg", 0);
	//int lightPointNumber = GetBadRegionNumber(true, 50, lightPointImage);
	//printf("lightPointNumber %d\n", lightPointNumber);


	//cv::Mat darkPointImage = cv::imread("C:\\Users\\zcalwang\\Desktop\\CameraTestFolder\\PixelCorrection\\6numberRegion.jpg", 0);
	//int darkPointNumber = GetBadRegionNumber(false, 50, darkPointImage);
	//printf("darkPointNumber %d\n", darkPointNumber);

#pragma endregion[Test light&&dark point pass]


#pragma region[Seed_Filling]
	//cv::Mat binImage = cv::imread("C:\\Users\\zcalwang\\Desktop\\CameraTestFolder\\PixelCorrection\\6numberRegion.jpg", 0);
	//cv::threshold(binImage, binImage, 50, 1, CV_THRESH_BINARY_INV);
	////imwrite("2.bmp", binImage);

	//cv::Mat labelImg;
	//Seed_Filling(binImage, labelImg);
	////彩色显示
	//cv::Mat colorLabelImg;
	//LabelColor(labelImg, colorLabelImg);
	//cv::imshow("colorImg", colorLabelImg);
#pragma endregion[Seed_Filling]


#pragma region[Two_Pass]
	//CallImageTransferFunction();
	//printf("发现的亮点数目为%d\n", badPointCount);

#pragma endregion[Two_Pass]


}

ImageProcessing::~ImageProcessing()
{
	//printf("ImageProcessing析构函数调用\n");

	if (grayImageData != nullptr)
	{
		delete grayImageData;
		grayImageData = NULL;
	}
}
