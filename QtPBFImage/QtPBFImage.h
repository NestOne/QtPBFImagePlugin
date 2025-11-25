#if !defined(__UGC_GRAPHICSW_H__)
#define __UGC_GRAPHICSW_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "../Graphics/Graphics.h"

#ifdef _DEBUG
	#pragma message("自动连接动态库 SuGraphicsQTd.uge ...")
	#pragma comment(lib,"SuGraphicsQTd.lib") 

#else
	#pragma message("自动连接动态库 SuGraphicsQT.uge ...") 
	#pragma comment(lib,"SuGraphicsQT.lib") 
#endif

#endif //__UGC_GRAPHICSW_H__