//
// Created by X3eRo0 on 12/08/2021
//

#ifndef BITMAP_H
#define BITMAP_H

#include "const.h"

enum oprn{
    r = 0,
    w = 1,
    x = 2,
    b = 4,
};

u8 get_oprn_at_idx(u32 idx); // return oprn at index in bitmap

#endif
