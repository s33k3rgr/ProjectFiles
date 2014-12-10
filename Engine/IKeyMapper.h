#ifndef ENGINE_IKEY_MAPPER_H
#define ENGINE_IKEY_MAPPER_H

namespace Input
{
	class IKeyMapper
	{
	public:
		virtual int getKeyFor(int action) const = 0;
	};
};

#endif