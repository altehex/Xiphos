# Change log for versions 2.3-2.4
---
*New info will be added.*

- Memory dedicated to kernel initialization is freed for later use.
- Fixes for xiphos_std_free_list_malloc:
  - The lists are unlocked if no free regions are found.
  - memory_init() now parses memory map to get available free regions.
