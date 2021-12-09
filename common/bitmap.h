//
// Created by X3eRo0 on 12/08/2021
//

#ifndef BITMAP_H
#define BITMAP_H

#include "const.h"

#if defined(__cplusplus)
extern "C" {
#endif

#define make_oprn(b, p) (b << oprn_b) | (1 << (p))

// 000, 000 - invalid
// 010 - valid
// 100 - valid
// 001 - valid

enum oprn {
    oprn_r = 0,
    oprn_w = 1,
    oprn_x = 2,
    oprn_b = 3,
};

u8 get_oprn_at_idx(u32 idx); // return oprn at index in bitmap
void set_oprn_at_idx(u32 idx, u8 value); // set oprn at index in bitmap

u8 get_current_bitmap_bot();
void set_current_bitmap_bot(u8 botid);

u8 check_oprn_valid(u8 oprn);

void clear_bitmap();

#if defined(__cplusplus)
}
#endif

#endif
