//
//  common.h
//  TestC
//
//  Created by Code New on 2019/10/26.
//  Copyright © 2019 Code New. All rights reserved.
//

#ifndef common_h
#define common_h

#include "wav.h"

size32_t array2binary(const unsigned char * const arr, int size);
char *bytearr2charstr(size32_t data);
size32_t little2big(const unsigned char * const arr, int size);
char *duration2time(float duration);

#endif /* common_h */
