#pragma once

#define API_DECL			__stdcall		// Use C convention for API methods

typedef struct
{
	bool isCameraType208;
	int imageWidth;
	int imageHeight;
} CameraInfo;


bool  API_DECL GetCameraInfo(CameraInfo* cameraInfo);
