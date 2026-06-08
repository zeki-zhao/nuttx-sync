/****************************************************************************
 * boards/arm/stm32/mystm32f429igt6/src/stm32_dma_alloc.c
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <nuttx/kmalloc.h>

#if defined(CONFIG_FAT_DMAMEMORY)

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: fat_dma_alloc
 *
 * Description:
 *   Allocate DMA-capable memory for FAT I/O buffers.  Guarantees sufficient
 *   alignment for SDIO DMA burst transfers.
 *
 ****************************************************************************/

void *fat_dma_alloc(size_t size)
{
  return kmm_memalign(16, size);
}

/****************************************************************************
 * Name: fat_dma_free
 *
 * Description:
 *   Free memory previously allocated by fat_dma_alloc.
 *
 ****************************************************************************/

void fat_dma_free(FAR void *memory, size_t size)
{
  kmm_free(memory);
}

#endif /* CONFIG_FAT_DMAMEMORY */
