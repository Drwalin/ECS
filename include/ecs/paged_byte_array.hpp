#pragma once

#include <cstdint>
#include <cstdlib>
#include <cstring>

namespace ecs
{
class PagedByteArray
{
public:
	~PagedByteArray();

	void init(uint32_t element_size, uint32_t page_elements);

	void *access(uint32_t element_id);
	void *try_get(uint32_t element_id);
	const void *try_get(uint32_t element_id) const;

	uint32_t page_id_from_element_id(uint32_t element_id) const;
	uint32_t first_element_in_page(uint32_t page_id) const;
	bool is_page_present(uint32_t page_id) const;

	void remove_page(uint32_t page_id);

	size_t get_memory_usage();

public:
	bool memset_zero = false;
	uint32_t element_size = 0;
	uint32_t page_elements = 0;			   // must be power of 2
	uint32_t page_elements_bit_offset = 0; // = log2(page_elements)
	uint32_t page_mask = 0;		// = (~0u) << page_elements_bit_offset
	uint32_t elements_mask = 0; // = ~page_mask

private:
	uint8_t **pages = nullptr;
	uint32_t pages_count = 0;
	uint32_t pages_capacity = 0;
	uint32_t present_pages_count = 0;
};
} // namespace ecs
