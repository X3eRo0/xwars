//
// Created by X3eRo0 on 12/08/2021
//

#include "bitmap.h"

/*
 * oprn_t
 * R W X B we need 4 bits to know which bot
 * performed which operation during 1 cycle
 *
 */

// global bitmap
u8 bitmap[0x200] = { 0 };

u8 get_oprn_at_idx(u32 idx)
{

    u8 bitmap_byte = bitmap[idx >> 1];
    u8 oprn = 0;

    if (idx & 1 == 1) {
        oprn = (bitmap_byte >> 4) & 0xf;
    } else {
        oprn = bitmap_byte & 0xf;
    }
}
