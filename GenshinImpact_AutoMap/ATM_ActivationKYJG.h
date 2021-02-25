#pragma once
#include <Windows.h>
class ATM_ActivationKYJG
{
	//C:\Users\aymb0\AppData\LocalLow\¿ÕÓ«¾Æ¹Ý\¡¸¿ÕÓ«¾Æ¹Ý¡¹Ô­ÉñµØÍ¼

	//¿ÕÓ«¾Æ¹Ý´°¿Ú¾ä±ú
	HWND kyHandle;

public:
	bool isRunKYJG = false;
	bool isActivationMap = false;

	void getKYJGHandle();
	
	void setState(HWND giHandle);

	void setActivation();
	void setUnActivation(HWND giHandle);

};

