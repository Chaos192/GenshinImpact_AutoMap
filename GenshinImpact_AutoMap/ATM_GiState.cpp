#include "ATM_GiState.h"

bool ATM_GiState::isRun()
{
	giHandle = FindWindowA(giWndClass.c_str(), giName.c_str());/* 对原神窗口的操作 */
	isRunning = giHandle != NULL ? true : false;
	return isRunning;
}

void ATM_GiState::getHandle()
{
	giHandle = FindWindowA(giWndClass.c_str(), giName.c_str());
	getRect();
}

void ATM_GiState::getRect()
{
	if (giHandle != NULL)
	{
		GetWindowRect(giHandle, &giRect);
		GetClientRect(giHandle, &giClientRect);
		int x_offset = GetSystemMetrics(SM_CXDLGFRAME);
		int y_offset = GetSystemMetrics(SM_CYDLGFRAME) + GetSystemMetrics(SM_CYCAPTION);

		/*SetWindowPos(
			hwnd, 
			0, 
			margins_xy.cxLeftWidth + (isNoBorder ? 0 : x_offset), 
			margins_xy.cxRightWidth + (isNoBorder ? 0 : y_offset), 
			margins_size.cyTopHeight, 
			margins_size.cyBottomHeight, 
			SWP_NOACTIVATE | SWP_FRAMECHANGED
			);
		*/
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
Point ATM_GiState::getOffset()
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
			res.y = 82;
			break;
		}
		case W_1680x1050:
		{
			res.x = 250;
			res.y = 82;
			break;
		}
		
		default:
		{

			break;

		}
	}
	return res;
}

void ATM_GiState::getAllScreen()
{
	static HBITMAP	hBmp;
	BITMAP bmp;

	DeleteObject(hBmp);

	if (giHandle == NULL)return;

	//获取目标句柄的窗口大小RECT
	//GetWindowRect(giHandle, &giRect);/* 对原神窗口的操作 */

	//获取目标句柄的DC
	HDC hScreen = CreateDCA("DISPLAY", NULL, NULL, NULL);//GetDC(giHandle);/* 对原神窗口的操作 */
	//为屏幕设备描述表创建兼容的内存设备描述表   
	HDC hCompDC = CreateCompatibleDC(hScreen);

	giRect.left = 0;
	giRect.top = 0;
	giRect.right = GetDeviceCaps(hScreen, HORZRES);
	giRect.bottom = GetDeviceCaps(hScreen, VERTRES);

	//获取目标句柄的宽度和高度
	int	nWidth = giRect.right - giRect.left;
	int	nHeight = giRect.bottom - giRect.top;

	//创建Bitmap对象
	hBmp = CreateCompatibleBitmap(hScreen, nWidth, nHeight);//得到位图

	SelectObject(hCompDC, hBmp); //不写就全黑
	BitBlt(hCompDC, 0, 0, nWidth, nHeight, hScreen, 0, 0, SRCCOPY);

	//释放对象
	DeleteDC(hScreen);
	DeleteDC(hCompDC);

	//类型转换
	GetObject(hBmp, sizeof(BITMAP), &bmp);

	int nChannels = bmp.bmBitsPixel == 1 ? 1 : bmp.bmBitsPixel / 8;
	int depth = bmp.bmBitsPixel == 1 ? IPL_DEPTH_1U : IPL_DEPTH_8U;

	//mat操作
	giFrame.create(cv::Size(bmp.bmWidth, bmp.bmHeight), CV_MAKETYPE(CV_8U, nChannels));

	GetBitmapBits(hBmp, bmp.bmHeight*bmp.bmWidth*nChannels, giFrame.data);

}

void ATM_GiState::getGiScreen()
{
	static HBITMAP	hBmp;
	BITMAP bmp;

	DeleteObject(hBmp);

	if (giHandle == NULL)return;

	//获取目标句柄的窗口大小RECT
	GetWindowRect(giHandle, &giRect);/* 对原神窗口的操作 */

	//获取目标句柄的DC
	HDC hScreen = GetDC(giHandle);/* 对原神窗口的操作 */
	HDC hCompDC = CreateCompatibleDC(hScreen);

	//获取目标句柄的宽度和高度
	int	nWidth = giRect.right - giRect.left;
	int	nHeight = giRect.bottom - giRect.top;

	//创建Bitmap对象
	hBmp = CreateCompatibleBitmap(hScreen, nWidth, nHeight);//得到位图

	SelectObject(hCompDC, hBmp); //不写就全黑
	BitBlt(hCompDC, 0, 0, nWidth, nHeight, hScreen, 0, 0, SRCCOPY);

	//释放对象
	DeleteDC(hScreen);
	DeleteDC(hCompDC);

	//类型转换
	GetObject(hBmp, sizeof(BITMAP), &bmp);

	int nChannels = bmp.bmBitsPixel == 1 ? 1 : bmp.bmBitsPixel / 8;
	int depth = bmp.bmBitsPixel == 1 ? IPL_DEPTH_1U : IPL_DEPTH_8U;

	//mat操作
	giFrame.create(cv::Size(bmp.bmWidth, bmp.bmHeight), CV_MAKETYPE(CV_8U, nChannels));

	GetBitmapBits(hBmp, bmp.bmHeight*bmp.bmWidth*nChannels, giFrame.data);
}

void ATM_GiState::getGiFrame()
{
	if (giWndClass == "UnityWndClass")
	{
		getGiScreen();
	}
	else
	{
		getAllScreen();
	}
	getGiRectMode();
	if (giRectMode > 0)
	{
		getGiFramePaimon();
		getGiFrameMap();
		getGiFrameUID();
	}
}

void ATM_GiState::getGiFramePaimon()
{
	Rect PaimonRect;
	switch (giRectMode)
	{
		case F_1920x1080:
		case W_1920x1080:
		{
			PaimonRect = Rect(26, 12, 68, 77);
			resIdPaimon = 0;
			break;
		}
		case F_1680x1050:
		case W_1680x1050:
		{

			PaimonRect = Rect(23, 10, 59, 68);
			resIdPaimon = 1;
			break;
		}
		case F_1600x900:
		case W_1600x900:
		{

			PaimonRect = Rect(20, 9, 50, 58);//???
			break;
		}
		case F_1440x900:
		case W_1440x900:
		{

			PaimonRect = Rect(20, 9, 50, 58);
			resIdPaimon = 2;
			break;
		}
		case F_1400x1050:
		case W_1400x1050:
		{

			PaimonRect = Rect(20, 9, 59, 68);//???
			break;
		}
		case F_1366x768:
		case W_1366x768:
		{

			PaimonRect = Rect(19, 8, 48, 56);
			resIdPaimon = 3;
			break;
		}
		default:
		{
			PaimonRect = Rect(cvCeil(giSize.width*0.0135), cvCeil(giSize.width*0.006075), cvCeil(giSize.width*0.035), cvCeil(giSize.width*0.0406));
			resIdPaimon = 0;
			if (giSize.width / giSize.height == 64 / 27)
			{
				PaimonRect = Rect(cvCeil(giSize.width*0.038), cvCeil(giSize.height*0.012), cvCeil(giSize.height / 9 * 16 *0.035), cvCeil(giSize.height / 9 * 16 *0.0406));
			}
			break;
		}
	}
	giFrame(PaimonRect).copyTo(giFramePaimon);

}

void ATM_GiState::getGiFrameMap()
{
	Rect mapRect;
	switch (giRectMode)
	{
		case F_1920x1080:
		case W_1920x1080:
		{
			mapRect = Rect(62, 19, 212, 212);
			break;
		}
		case F_1680x1050:
		case W_1680x1050:
		{
			mapRect = Rect(54, 17, 185, 185);
			break;
		}
		default:
		{
			mapRect = Rect(cvCeil(giSize.width*0.032), cvCeil(giSize.width*0.01), cvCeil(giSize.width *0.11), cvCeil(giSize.width*0.11));
			if (giSize.width / giSize.height == 64 / 27)
			{
				mapRect = Rect(cvCeil(giSize.width*0.051), cvCeil(giSize.height / 9 * 16 *0.01), cvCeil(giSize.height/9*16 *0.11), cvCeil(giSize.height / 9 * 16 *0.11));
			}
			break;
		}
	}
	giFrame(mapRect).copyTo(giFrameMap);
}

void ATM_GiState::getGiFrameUID()
{
	Rect uidRect;
	switch (giRectMode)
	{
		case F_1920x1080:
		{
			uidRect = Rect(giFrame.cols - 240, giFrame.rows - 25, 180, 18);
			break;
		}
		case W_1920x1080:
		{
			uidRect = Rect(giFrame.cols - 240, giFrame.rows - 25, 180, 18);
			uidRect.x = uidRect.x - 16;
			uidRect.y = uidRect.y - 29;
			break;
		}
		case F_1680x1050:
		{
			uidRect = Rect(giFrame.cols - 207, giFrame.rows - 23, 155, 18);
			break;
		}
		case W_1680x1050:
		{
			uidRect = Rect(giFrame.cols - 207, giFrame.rows - 23, 155, 18);
			uidRect.x = uidRect.x - 16;
			uidRect.y = uidRect.y - 29;
			break;
		}
		case F_1600x900:
		{
			uidRect = Rect(giFrame.cols - 207, giFrame.rows - 23, 155, 18);
			break;
		}
		case W_1600x900:
		{
			uidRect = Rect(giFrame.cols - 207, giFrame.rows - 23, 155, 18);
			uidRect.x = uidRect.x - 16;
			uidRect.y = uidRect.y - 29;
			break;
		}
		case F_1440x900:
		{
			uidRect = Rect(giFrame.cols - 207, giFrame.rows - 23, 155, 18);
			break;
		}
		case W_1440x900:
		{
			uidRect = Rect(giFrame.cols - 207, giFrame.rows - 23, 155, 18);
			uidRect.x = uidRect.x - 16;
			uidRect.y = uidRect.y - 29;
			break;
		}
		case F_1400x1050:
		{
			uidRect = Rect(giFrame.cols - 207, giFrame.rows - 23, 155, 18);
			break;
		}
		case W_1400x1050:
		{
			uidRect = Rect(giFrame.cols - 207, giFrame.rows - 23, 155, 18);
			uidRect.x = uidRect.x - 16;
			uidRect.y = uidRect.y - 29;
			break;
		}
		case F_1366x768:
		{
			uidRect = Rect(giFrame.cols - 207, giFrame.rows - 23, 155, 18);
			break;
		}
		case W_1366x768:
		{
			uidRect = Rect(giFrame.cols - 207, giFrame.rows - 23, 155, 18);
			uidRect.x = uidRect.x - 16;
			uidRect.y = uidRect.y - 29;
			break;
		}
		default:
		{
			uidRect = Rect(giFrame.cols - 240, giFrame.rows - 25, 180, 18);
			break;
		}
	}
	giFrame(uidRect).copyTo(giFrameUID);
}

void ATM_GiState::setGiNameClass(LANGID SystemLanguageID)
{
	switch (SystemLanguageID)
	{
		case 0X0804:
		{                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
			giName = "原神";
			break;
		}
		case 0x0409:
		{
			giName = "GenshinImpact";
			break;     
		}
		default:
		{
			giName = "GenshinImpact";//GenshinImpact.
			break;
		}
	}
}

void ATM_GiState::setGiHandle(HWND GiHandle)
{
	if (GiHandle != NULL)
	{
		char classNameLis[256];
		char nameLis[256];
		giHandle = GiHandle;
		GetClassNameA(GiHandle, classNameLis, 256);
		giWndClass = classNameLis;
		GetWindowTextA(GiHandle, nameLis, 256);
		giName = nameLis;
	}
}
