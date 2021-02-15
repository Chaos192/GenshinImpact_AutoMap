#include "ATM_GiState.h"

bool ATM_GiState::isRun()
{
	giHandle = FindWindowA(NULL, "原神");/* 对原神窗口的操作 */
	if (giHandle != NULL)
	{
		isRunning = true;
	}
	else
	{
		isRunning = false;
	}
	return isRunning;
}

void ATM_GiState::getHandle()
{
	giHandle = FindWindowA(NULL, "原神");
	if (giHandle != NULL)
	{
		GetWindowRect(giHandle, &giRect);
	}
}
