#pragma once

#include "components_header.hpp"

struct ExamplePosition {
	float x, y, z;
	
	ECS_TYPE_TRAITS_HEADER(ExamplePosition, "EP", 3, true, 4);
};

struct ExampleTagPlayer {
	ECS_TAG_TRAITS(ExampleTagPlayer, "ETP", 4);
};

