/* boards/yourboard/src/boot_image.c */

#include <stdint.h>

int board_boot_image(int slot)
{
    /* 根据 slot 启动 Primary/Secondary/Recovery */
    /* Stub 示例，返回 0 */
    return 0;
}

int board_reset_cause(void)
{
    /* 返回重启原因 */
    return 0;
}