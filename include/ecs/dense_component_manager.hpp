#pragma once

#include "types.hpp"
#include "ecs.hpp"
#include "paged_byte_array.hpp"

namespace ecs
{
/*
 * example dense components packaging:
 * Dense entry:
 * struct {
 *     DenseHeader header;
 *     uint8_t storage[storage_for_components_size];
 *     uint8_t padding[...];
 * };
 */

struct DenseHeader {
	void *componentsMap = 0;
	void *tagsMap = 0;
	uint32_t entityIdVersion = 0;
	uint32_t enabled = 0; // bit[31] -> entity presence
						  // bit[0..30] -> component presence
};

class DenseComponentManager
{
public:
	inline constexpr static uint32_t ENTITY_PRESENT_BIT = 31;
	inline constexpr static uint32_t ENTITY_PRESENT_MASK = 0x80000000u;
	inline constexpr static uint32_t COMPONENT_PRESENT_MASK = 0x7FFFFFFFu;

	DenseComponentManager();
	~DenseComponentManager();

	
	
private:
	ComponentManager *denseComponents[MAX_DENSE_COMPONENTS] = {nullptr};
	static DenseComponent componentsByteMeta[MAX_DENSE_COMPONENTS];

	uint32_t blockAlignement = 0;

	PagedByteArray storage;
};
} // namespace ecs
