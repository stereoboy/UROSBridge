#pragma once
#include <chrono>  // for high_resolution_clock

/**
	Performance Analysis
*/

//#define _DBG_TIME_
#ifdef _DBG_TIME_
#define ROSDBG_TC_INIT()  \
	std::chrono::time_point<std::chrono::steady_clock> begin, end; \
	std::chrono::duration<double> elapsed; \

#define ROSDBG_TC_BEGIN() \
	begin = std::chrono::high_resolution_clock::now();\

#define ROSDBG_TC_END(L, SubModuleName, Msg) \
	end = std::chrono::high_resolution_clock::now(); \
	elapsed = end - begin; \
	UE_LOG(L, Log, TEXT("[ROS] [%s] %s elapsed time: %fs"), SubModuleName, TEXT(Msg), elapsed.count()); \

#else
#define ROSDBG_TC_INIT()

#define ROSDBG_TC_BEGIN()

#define ROSDBG_TC_END(L, SubModuleName, Msg)

#endif
