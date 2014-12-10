#ifndef ENGINE_MY_KEY_MAPPER_H
#define ENGINE_MY_KEY_MAPPER_H
#include <IKeyMapper.h>


namespace Input
{

	class MyKeyMapper : public IKeyMapper
	{
	public:
		int getKeyFor(int action) const;
	};

}

#endif
