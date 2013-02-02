#ifndef DJBHASH_H
#define DJBHASH_H
#include "PuyoEngineTypes.h"

namespace PuyoEngine
{
	//just a quick hash function for string
	uint32_t DJBHash(const char* str, size_t len);
}
#endif