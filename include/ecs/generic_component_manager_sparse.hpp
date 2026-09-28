#pragma once

#include <cassert>

#include <functional>

#include "ecs.hpp"
#include "generic_component_manager.hpp"

namespace ecs
{
template <typename T>
class GenericComponentManager<T, ecs::Density::SPARSE> : public ComponentManager
{
public:
	GenericComponentManager();
	virtual ~GenericComponentManager() override;

	void assure(Entity entity);
	T &access(Entity entity);
	T &add(Entity entity);
	T &set(Entity entity, const T &val);
	T &set(Entity entity, T &&mov_val);
	T *get(Entity entity) const;
	bool has(Entity entity) const;
	void remove(Entity entity);

	void for_each(const std::function<void(Entity, T &)> &fn);
	void for_each(const std::function<void(Entity, const T &)> &fn) const;

private:
};
} // namespace ecs
