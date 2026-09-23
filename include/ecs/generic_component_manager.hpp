#pragma once

#include <vector>

#include "ecs.hpp"

namespace ecs
{
template <typename T, ecs::Density D = T::_ecs_density>
class GenericComponentManager;

template <typename T>
class GenericComponentManager<T, ecs::Density::DENSE> : public ComponentManager
{
public:
	GenericComponentManager() {}
	virtual ~GenericComponentManager() override;

private:
	std::vector<bool> exists;
};

template <typename T>
class GenericComponentManager<T, ecs::Density::SPARSE> : public ComponentManager
{
public:
	GenericComponentManager() {}
	virtual ~GenericComponentManager() override;

private:
};
} // namespace ecs
