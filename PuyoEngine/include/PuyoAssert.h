#ifndef PUYO_ASSERT_H
#define PUYO_ASSERT_H

namespace PuyoEngine
{
//assert functions that should get optimized out in release
//TODO: this will still evaluate the arguments. need to make it a macro to get rid of the arguments
#if defined(PUYOENGINE_CONFIG_DEBUG)
void PASSERT(bool condition) ;
void PASSERT_MSG(bool condition, const char *msg) ;
#else
	inline void PASSERT(bool ) 
	{
		return;
	}
	inline void PASSERT_MSG(bool , const char *) 
	{
		return;
	}

#endif


}
#endif