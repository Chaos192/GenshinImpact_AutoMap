// AutoTrackingDLL.cpp : 定义 DLL 的导出函数。
//

#include "pch.h"
#include "framework.h"
#include "AutoTrackingDLL.h"


// 这是导出变量的一个示例
AUTOTRACKINGDLL_API int nAutoTrackingDLL=0;

// 这是导出函数的一个示例。
AUTOTRACKINGDLL_API int fnAutoTrackingDLL(void)
{
    return 0;
}

AUTOTRACKINGDLL_API Point GetPos(void)
{
	return AUTOTRACKINGDLL_API Point();
}

AUTOTRACKINGDLL_API bool GetPos(Point & p)
{
	return AUTOTRACKINGDLL_API bool();
}

// 这是已导出类的构造函数。
CAutoTrackingDLL::CAutoTrackingDLL()
{
    return;
}
