#pragma once

#include <string>

#include "../../include/ecs/header_macros.hpp"

struct Position {
	float x, y, z;
	ECS_TYPE_TRAITS_HEADER_DENSE(Position, "pos", 1, 4, {24, 0, 4, 1, 3, 16, 48})
};

struct HealthPoints {
	int hp;
	ECS_TYPE_TRAITS_HEADER_DENSE(HealthPoints, "hp", 2, 4, {36, 1, 4, 1, 3, 16, 48})
};

struct MaxHealthPoints {
	int hp;
	ECS_TYPE_TRAITS_HEADER_DENSE(MaxHealthPoints, "maxhp", 3, 4, {40, 2, 4, 1, 3, 16, 48})
};

struct CharacterSheet {
	std::string name;
	int mana;
	ECS_TYPE_TRAITS_HEADER_SPARSE(CharacterSheet, "cs", 4, 4)
};

struct TagPlayer {
	ECS_TAG_TRAITS(TagPlayer, "tp", 1)
};
