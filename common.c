//
//  common.c
//  TestC
//
//  Created by Code New on 2019/10/26.
//  Copyright © 2019 Code New. All rights reserved.
//

#include "wav.h"
#include "common.h"

size32_t array2binary(const unsigned char * const arr, int size)
{
    size32_t n = 0;
    
    for (int i = 0; i < size; i++)
    {
        n |= arr[i] << (8 * i);
    }
    
    return n;
}

char *bytearr2charstr(size32_t data)
{
    char *str = (char *)malloc(sizeof(char) * 10);
    memset(str, 0, 10);
    
    for (int i = 0; i < 4; i++)
    {
        str[i] = data >> 8 * i;
    }
    
    return str;
}

size32_t little2big(const unsigned char * const arr, int size)
{
    size32_t n = 0;
    
    for (int i = 0; i < size; i++)
    {
        n |= arr[size - 1 - i] << (8 * (size - 1 - i));
    }
    
    return n;
}

char *duration2time(float duration)
{
    char *time = (char *)malloc(sizeof(char) * 100);
    
    int hour = duration / 3600;
    int min = (int)duration % 3600 / 60;
    int sec = (int)duration % 60;
    
    sprintf(time, "%d:%d:%d", hour, min, sec);
    
    return time;
}
