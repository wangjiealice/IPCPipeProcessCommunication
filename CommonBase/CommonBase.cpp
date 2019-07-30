#define Camera208
#include "stdafx.h"
#include "CommonBase.h"

bool API_DECL GetCameraInfo(CameraInfo * cameraInfo)
{
#ifdef Camera208
	cameraInfo->isCameraType208 = true;
	cameraInfo->imageWidth = 3840;
	cameraInfo->imageHeight = 2160;

#else
	cameraInfo->isCameraType208 = false;
	cameraInfo->imageWidth = 1920;
	cameraInfo->imageHeight = 1080;

#endif // Camera208
	return false;
}
