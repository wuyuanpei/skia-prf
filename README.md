# skia-prf

This repo is a fork from Skia for the PRF project.
Skia is a complete 2D graphic library for drawing Text, Geometries, and Images.
See full details, and build instructions, at https://skia.org.

## 编译示例
- 用``clang``编译，性能更好
```
bin/gn gen out/Shared --args='is_official_build=false is_component_build=false cc="clang" cxx="clang++"'
ninja -C out/Shared
```

- 查看编译选项
```
bin/gn args --list out/Shared/
```

## 更新（之后需重新编译）
```
git pull
python tools/git-sync-deps
```

## 使用vulkan编译so
```
bin/gn gen out/Shared-Vk --args='is_official_build=true is_component_build=true skia_use_vulkan=true cc="clang" cxx="clang++" skia_pdf_subset_harfbuzz=false'
ninja -C out/Shared-Vk
```

## 使用vulkan和graphite编译so
```
bin/gn gen out/Shared-Vk-Graphite --args='is_official_build=true is_component_build=true skia_use_vulkan=true cc="clang" cxx="clang++" skia_pdf_subset_harfbuzz=false skia_enable_graphite=true'
ninja -C out/Shared-Vk-Graphite
```

## 最新版本的skia有个bug?
src/gpu/graphite/vk/VulkanBackendSemaphore.cpp需要加一行，否则外部链接的时候找不到这个函数symbol
```
#include "include/gpu/graphite/vk/VulkanGraphiteTypes.h"
```
