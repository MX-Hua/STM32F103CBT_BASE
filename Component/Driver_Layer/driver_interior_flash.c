/*
 * driver_interior_flash.c
 *
 *  Created on: Mar 9, 2026
 *      Author: hea
 */


#include "driver_interior_flash.h"
#include "string.h"






/*
* 函数名：void ReadFlash(uint32_t startAddr, uint32_t *pdata, uint32_t length)
* 输入参数：startAddr-> 读首地址; pdata -> 读出的数据指针; length -> 读的字节个数
* 输出参数：无
* 返回值：无
* 函数作用：读内部 flash
*/
void Driver_Read_Flash_Word(uint32_t startAddr, uint32_t *pdata, uint32_t length)
{
        #if 1
        // 方式一:使用指针获取数据
        uint16_t i = 0;

        for(i=0; i<length; i++) // 读取 length 个数据
        {
        pdata[i]=*(uint32_t*)startAddr; // 将指定地址数据保存到 pata
        startAddr = startAddr + 4; // 地址加 4,即下一个 32 位数据位置
        }
        #else
        // 方式二:使用 C 库的内存拷贝函数获取数据
        memcpy((uint32_t*)pdata, (uint32_t*)startAddr, sizeof(uint32_t)*length);
        #endif
}






// 安全写入函数（带中断保护）
HAL_StatusTypeDef Driver_Flash_Write_Safe_Word(uint32_t addr, uint32_t *data, uint32_t len_words)
{
    FLASH_EraseInitTypeDef EraseCfg = {0};
    uint32_t page_error = 0;
    uint32_t i;
    HAL_StatusTypeDef status = HAL_OK;

    // 1. 禁用全局中断（关键！防止操作中触发HardFault）
    __disable_irq();

    // 2. 解锁Flash
    if (HAL_FLASH_Unlock() != HAL_OK) {
        __enable_irq();
        return HAL_ERROR;
    }

    // 3. 擦除整页（必须！）
    EraseCfg.TypeErase = FLASH_TYPEERASE_PAGES;
    EraseCfg.PageAddress = USER_PAGE_ADDR; // 必须页对齐
    EraseCfg.NbPages = 1;

    if (HAL_FLASHEx_Erase(&EraseCfg, &page_error) != HAL_OK) {
        status = HAL_ERROR;
        goto cleanup;
    }

    // 4. 写入数据（按字写入，地址4字节对齐）
    for (i = 0; i < len_words; i++) {
        if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,
                             addr + (i * 4),
                             data[i]) != HAL_OK) {
            status = HAL_ERROR;
            break;
        }
        // 可选：写入后校验
        if (*(__IO uint32_t*)(addr + i*4) != data[i]) {
            status = HAL_ERROR;
            break;
        }
    }

cleanup:
    HAL_FLASH_Lock(); // 5. 上锁
    __enable_irq();   // 6. 恢复中断
    return status;
}

void Driver_write_flash_HalfWord(uint32_t addr, uint16_t *data, uint16_t len)
{
        __disable_irq();
    HAL_FLASH_Unlock();

    // 擦除一页
    FLASH_EraseInitTypeDef erase = {0};
    erase.TypeErase = FLASH_TYPEERASE_PAGES;
    erase.PageAddress = addr;
    erase.NbPages = 1;

    uint32_t pageError = 0;
    HAL_FLASHEx_Erase(&erase, &pageError);

    // 写入半字数组
    for (uint16_t i = 0; i < len; i++) {
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,
                          addr + i*2,
                          data[i]);
    }

    HAL_FLASH_Lock();
    __enable_irq();   // 6. 恢复中断
}

void Driver_read_flash_HalfWord(uint32_t addr, uint16_t *buf, uint16_t len)
{
    for (uint16_t i = 0; i < len; i++) {
        buf[i] = *(uint16_t*)(addr + i*2);
    }
}

