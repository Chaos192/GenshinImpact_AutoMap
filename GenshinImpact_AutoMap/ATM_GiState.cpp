#include "ATM_GiState.h"

bool ATM_GiState::isRun()
{
	giHandle = FindWindowA(NULL, "原神");/* 对原神窗口的操作 */
	isRunning = giHandle != NULL ? true : false;
	return isRunning;
}

void ATM_GiState::getHandle()
{
	giHandle = FindWindowA(NULL, "原神");
	getRect();
}

void ATM_GiState::getRect()
{
	if (giHandle != NULL)
	{
		GetWindowRect(giHandle, &giRect);
		giSize.width = giRect.right - giRect.left;//+6
		giSize.height = giRect.bottom - giRect.top;//+29
		getGiRectMode();
	}
	else
	{
		giRect.left = 100;
		giRect.top = 100;
		giRectMode = RectMode::FW_MINIMIZE;
	}
}

int ATM_GiState::getGiRectMode()
{
	static const cv::Size size1920x1080(1920, 1080);
	static const cv::Size size1680x1050(1680, 1050);
	static const cv::Size size1440x900(1440, 900);
	static const cv::Size size1366x768(1366, 768);
	static const cv::Size size1920x1080uf(1929, 1106);
	static const cv::Size size1680x1050uf(1689, 1079);
	static const cv::Size size1440x900uf(1449, 929);
	static const cv::Size size1366x768uf(1375, 797);
	if (giHandle != NULL)
	{

		if (giSize == size1920x1080)
		{
			isFullScreen = true;
			giSize = size1920x1080;
			giRectMode = RectMode::F_1920x1080;
			return giRectMode;
		}
		if (giSize == size1920x1080uf)
		{
			isFullScreen = false;
			giSize = size1920x1080;
			giRectMode = RectMode::F_1920x1080;
			return giRectMode;
		}

		if (giSize == size1680x1050)
		{
			isFullScreen = true;
			giSize = size1680x1050;
			giRectMode = RectMode::F_1680x1050;
			return giRectMode;
		}
		if (giSize == size1680x1050uf)
		{
			isFullScreen = false;
			giSize = size1680x1050uf;
			giRectMode = RectMode::F_1680x1050;
			return giRectMode;
		}

		if (giSize == size1440x900)
		{
			isFullScreen = true;
			giSize = size1440x900;
			giRectMode = RectMode::F_1440x900;
			return giRectMode;
		}
		if (giSize == size1440x900uf)
		{
			isFullScreen = false;
			giSize = size1440x900uf;
			giRectMode = RectMode::F_1440x900;
			return giRectMode;
		}
		if (giSize == size1366x768)
		{
			isFullScreen = true;
			giSize = size1366x768;
			giRectMode = RectMode::F_1366x768;
			return giRectMode;
		}
		if (giSize == size1366x768uf)
		{
			isFullScreen = false;
			giSize = size1366x768uf;
			giRectMode = RectMode::F_1366x768;
			return giRectMode;
		}
		isFullScreen = true;
		//giSize = cv::Size(0,0);
		giRectMode = RectMode::FW_UNDIFINDE;
	}
	else
	{
		giRectMode = RectMode::FW_MINIMIZE;
	}
	return giRectMode;
}

int ATM_GiState::getGiState()
{
	isRun() ? getHandle() : giRectMode = RectMode::FW_MINIMIZE;
	return giRectMode;
}

cv::Point ATM_GiState::getOffset()
{
	cv::Point res;
	switch (giRectMode)
	{
		case F_1920x1080:
		{
			res.x = 288;
			res.y = 82;
			break;
		}
		case W_1920x1080:
		{
			res.x = 288;
			res.y = 82;
			break;
		}
		case F_1680x1050:
		{
			res.x = 250;
			res.y = 100;
			break;
		}
		case W_1680x1050:
		{
			res.x = 250;
			res.y = 100;
			break;
		}
		
		default:
			break;
	}
	return cv::Size();
}
