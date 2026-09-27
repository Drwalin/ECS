#pragma once

#include <vector>

#include "types.hpp" // IWYU pragma: export

namespace ecs
{
class ObserverArray
{
public:
	struct ObserverEntry {
		void (*on)(Entity entity, ComponentManager *manager, void *component);
	};

	void add(ObserverArray entry);
	void execute_all_on(Entity entity, World *world, void *component);

private:
	std::vector<ObserverEntry> entries;
};

class ComponentManager
{
public:
	ComponentManager();
	virtual ~ComponentManager();

	void register_observer(ObserverType type, ObserverFunc observer);
	void call_observers(World *world, ObserverType type, Entity entity,
						void *component);

protected:
	TypeTraits traits;
	union {
		struct {
			ObserverArray add;
			ObserverArray set;
			ObserverArray remove;
		} on;
		ObserverArray array[3];
	} observers;
};
} // namespace ecs
