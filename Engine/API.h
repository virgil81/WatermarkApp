#pragma once
#ifdef _DV_EXPORTS 
#define DLLEXP __declspec(dllexport)
#else
#define DLLEXP __declspec(dllimport)
#endif // _DV_EXPORTS

