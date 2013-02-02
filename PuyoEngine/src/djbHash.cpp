#include "djbHash.h"

using namespace PuyoEngine;

uint32_t PuyoEngine::DJBHash(const char* str, size_t len)
{
	uint32_t hash = 5381;

	for(size_t i = 0; i < len; str++, i++)
	{
		hash = ((hash << 5) + hash) + (*str);
	}

	return hash;
}