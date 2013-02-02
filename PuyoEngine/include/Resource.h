#ifndef RESOURCE_H
#define RESOURCE_H

namespace PuyoEngine
{

	class Resource
	{
	public:
		Resource(): mRefCount(1) {}
		virtual ~Resource() {}
		size_t mRefCount;

	};


}
#endif