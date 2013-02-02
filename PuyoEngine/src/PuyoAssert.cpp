#include "PuyoAssert.h"

#if defined(PUYOENGINE_CONFIG_DEBUG)

#include <Windows.h>
#include <DbgHelp.h>
#include <iostream>
using namespace PuyoEngine;

void PuyoEngine::PASSERT(bool condition) 
{
	if (!condition)
		DebugBreak();
	return;
}
void PuyoEngine::PASSERT_MSG(bool condition, const char *msg) 
{
	std::cout <<  msg <<std::endl;
	if (!condition)
		DebugBreak();
	return;
}
#endif