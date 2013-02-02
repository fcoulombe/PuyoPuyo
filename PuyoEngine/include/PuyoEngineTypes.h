#ifndef PUYOENGINETYPES_H
#define PUYOENGINETYPES_H

namespace PuyoEngine
{
	//here we defines our types since visual studio does not support stdint.h
	typedef long			int32_t;
	typedef unsigned long	uint32_t;

	typedef short			int16_t;
	typedef unsigned short	uint16_t;

	typedef char			int8_t;
	typedef unsigned char	uint8_t;

	//typedef the floats in case that we need to change between fix point or different float standard
	typedef float Real; 
}

#endif