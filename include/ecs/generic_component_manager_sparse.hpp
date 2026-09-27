#pragma once

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

	inline static void assure(Entity e, ComponentManager *cm);
	inline static T &access(Entity e, ComponentManager *cm);
	inline static T &add(Entity e, ComponentManager *cm);
	inline static T &set(Entity e, ComponentManager *cm, const T &val);
	inline static T &set(Entity e, ComponentManager *cm, T &&mov_val);
	inline static T *get(Entity e, const ComponentManager *cm);
	inline static bool has(Entity e, const ComponentManager *cm);
	inline static void remove(Entity e, ComponentManager *cm);

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
}
