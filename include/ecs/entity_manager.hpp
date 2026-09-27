#pragma once

#include <vector>
#include <map>

#include "types.hpp" // IWYU pragma: export

namespace ecs
{
class EntityManager
{
public:
	Entity add();
	void remove(Entity entity);
	void clear();

private:
	std::vector<uint32_t> entityVersion;
	std::vector<uint32_t> emptyEntityIds;
	std::vector<std::map<ComponentId, uint32_t>> componentsOffsets;
};
} // namespace ecs
