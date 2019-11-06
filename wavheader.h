//
//  wavheader.h
//  TestC
//
//  Created by Code New on 2019/10/27.
//  Copyright © 2019 Code New. All rights reserved.
//

#ifndef wavheader_h
#define wavheader_h
#include "wav.h"

enum WAVPOS
{
    FILELEN = 4,
    CHANNELS = 22,          // signable
    SAMPLERATE = 24,        // signable
    AVEBYTESRATE = 28,
    BLOCKALIGN = 32,
    BITSPERSAMPLE = 34,     // signable
    DATALEN = 40
};

typedef struct WAVHEADER
{
    size32_t fileId;
    size32_t fileLen;
    size32_t waveId;
    size32_t fmtId;
    size32_t fmtLen;
    size16_t compCode;
    size16_t nChannels;
    size32_t samplePreSec;
    size32_t aveBytePerSec;     // Sample Rate * Block Align
    size16_t blockAlign;        // Bytes per sample slice.(Bits per sample / 8 * channels)
    size16_t bitsPerSample;     // 8 | 16 | 24 | 32
    size32_t dataId;
    size32_t dataLen;
}WAVHEADER;

void create_wav_header(WAVHEADER *wav_header);
int wav_write(FILE *output_file, FILE *input_file, WAV *wav);
int parse_data(FILE *output_file, FILE *input_file, WAV *wav);
void print_wav_header(WAVHEADER *wav_header);

#endif /* wavheader_h */
