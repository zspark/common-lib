#pragma once

// this macro depends on configuration;
#if __CL_INTERNAL_DEBUG__
#include <iostream>
#define F_DBG_ASSERT(s) {if(!(s))throw "assertion failure";}
#define F_DBG_INFO(s) {std::cout<<"[INFO]"<<(s)<<std::endl;}
#define F_DBG_WARING(s) {std::cout<<"[WARN]"<<(s)<<std::endl;}
#define F_DBG_ERROR(s) {std::cout<<"[ERROR]"<<(s)<<std::endl;}
#else
#define F_DBG_ASSERT(s)
#define F_DBG_INFO(s)
#define F_DBG_WARNING(s)
#define F_DBG_ERROR(s)
#endif

#ifdef CL_API_IMPORTS
#define CL_API __declspec(dllimport)
#else
#define CL_API __declspec(dllexport)
#endif


#define CL_NAMESPACE_START namespace cl{
#define CL_NAMESPACE_END }