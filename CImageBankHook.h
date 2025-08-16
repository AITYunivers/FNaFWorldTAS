#pragma once
#include "HookHelper.h"
#include "MMFGlobals.h"

CREATE_FUNC_STD(CIMAGEBANK_UnloadImages, 0x33240, void);
CREATE_FUNC_STD(CIMAGEBANK_UnloadImages2, 0x33310, void);

class CImageBankHook
{
public:
	// Callbacks
	static void __stdcall UnloadImages()
	{
		return CIMAGEBANK_UnloadImages();
	};

	static void __stdcall UnloadImages2()
	{
		return CIMAGEBANK_UnloadImages2();
	};
};