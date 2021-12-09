//
// Created by X3eRo0 on 12/08/2021
//

#include "bitmap.h"
#include <string.h>

#if defined(__cplusplus)
extern "C" {
#endif

/*
 * oprn_t
 * R W X B we need 4 bits to know which bot
 * performed which operation during 1 cycle
 *
 */

// global bitmap
u8 bitmap[0x200] = { 0 };
u8 bot_id = 0;

u8 get_oprn_at_idx(u32 idx)
{
    u8 bitmap_byte = bitmap[idx >> 1];
    u8 oprn = 0;

    if ((idx & 1) == 1) {
        oprn = (bitmap_byte >> 4) & 0xf;
    } else {
        oprn = bitmap_byte & 0xf;
    }

    return oprn;
}

void set_oprn_at_idx(u32 idx, u8 value)
{

    u8 bitmap_byte = bitmap[idx >> 1];
    if ((idx & 1) == 1) {
        bitmap_byte |= value << 4;
    } else {
        bitmap_byte |= value;
    }

    bitmap[idx >> 1] = bitmap_byte;
}

u8 get_current_bitmap_bot()
{
    return bot_id;
}

void set_current_bitmap_bot(u8 botid)
{
    bot_id = botid;
}

u8 check_oprn_valid(u8 oprn)
{
    return (oprn & 0x7) != 0;
}

void clear_bitmap()
{
    memset(bitmap, 0, sizeof(bitmap));
}

#if defined(__cplusplus)
}
#endif
