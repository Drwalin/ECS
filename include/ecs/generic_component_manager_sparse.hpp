#pragma once

#include "ecs.hpp"
#include "component_registry.hpp"
#include "generic_component_manager.hpp"

namespace ecs
{
template <typename T>
class GenericComponentManager<T, ecs::Density::SPARSE> : public ComponentManager
{
public:
	GenericComponentManager() {}
	virtual ~GenericComponentManager() override;

	inline static void assure(Entity e, ComponentManager *cm);
	inline static T &access(Entity e, ComponentManager *cm);
	inline static T &add(Entity e, ComponentManager *cm);
	inline static T &set(Entity e, ComponentManager *cm, const T &val);
	inline static T &set(Entity e, ComponentManager *cm, T &&mov_val);
	inline static T *get(Entity e, const ComponentManager *cm);
	inline static void remove(Entity e, ComponentManager *cm);

private:
};
}
