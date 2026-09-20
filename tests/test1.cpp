#include <cstdio>

// #include "../include/ecs/ecs.hpp"
#include "../include/ecs/example_usage.hpp"

int main()
{
	using T = ExamplePosition;
	printf("Done: {%s %i}, %s, %s %s!\n", T::_ecs_short_name.s.c_str(),
			T::_ecs_short_name.i,
			T::_ecs_type_name,
			T::_ecs_poco?"POCO":"COMPLEX"
			, T::_ecs_name.s.c_str()
			);
}
