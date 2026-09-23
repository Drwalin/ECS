#pragma once

#include "types.hpp"
#include "paged_byte_array.hpp"

namespace ecs
{
struct DenseHeader {
	void *componentsMap = 0;
	void *tagsMap = 0;
	uint32_t entityIdVersion = 0;
	uint32_t enabled = 0; // bit[31] -> entity presence
						  // bit[0..30] -> component presence
};

class DenseComponentManager {
public:
	DenseComponentManager();
	~DenseComponentManager();

	
	
private:
	ComponentManager *denseComponents[MAX_DENSE_COMPONENTS] = {nullptr};
	static DenseComponent componentsByteMeta[MAX_DENSE_COMPONENTS];
	
	uint32_t blockAlignement;
	
	PagedByteArray storage;
};
}
