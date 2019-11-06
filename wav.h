//
//  wav.h
//  TestC
//
//  Created by Code New on 2019/10/26.
//  Copyright © 2019 Code New. All rights reserved.
//

#ifndef wav_h
#define wav_h

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define BYTE_4 4
#define BYTE_2 2
#define LIST_VALUE 1414744396
#define INPUT_FILE "test3.wav"
#define OUTPUT_FILE "new.wav"

typedef unsigned int size32_t;
typedef unsigned short size16_t;

enum COMPRESS_CODE
{
    UNKNOWN = 0,
    PCM = 1,
    ADPCM = 2,
    IEEE_FLOATING_POINT = 3,
    A_LAW = 6,
    Au_LAW = 7,
    IMA_ADPCM = 17,
    YAMAHA_ADPCM = 20,
    GSM = 49,
    G721_ADPCM = 64,
    MPEG = 80,
    EXPERIMENTAL = 65536
};

typedef struct RIFF
{
    size32_t fileId;            // "RIFF"
    size32_t fileLen;           // File size - 8
}RIFF;

typedef struct SIGNLD
{
    size32_t waveId;            // "WAVE"
}SIGNID;

typedef struct FORMAT_BLOCK
{
    size32_t chkId;             // "fmt "
    size32_t chkLen;            // Length of format data(16)
    size16_t wFormatTag;        // Type of format(PCM: 1, A-law: 6, Mu-law: 7)
    size16_t wChannels;         // Number of Channels(2)
    size32_t dwSampleRate;      // Sample Rate(CD: 44100, DAT: 48000)
    size32_t dwAvgBytesRate;    // (Sample Rate * BitsPerSample * Channels) / 8
    size16_t wBlockAlign;       // wChannels * (dwBitsPerSample / 8)
    size16_t wBitsPerSample;    // Bits per sample
    size16_t wExtSize;          // the number of bytes in a frame
    char *extraInfo;
}FORMAT;

typedef struct DATA_BLOCK
{
    size32_t chkId;             // "data"
    size32_t chkLen;            // Size of the data section
}DATA;

typedef struct LIST_BLOCK
{
    size32_t chkId;             // "data"
    size32_t chkLen;            // Size of the data section
    size32_t typeId;
    char *text;
}LIST;

typedef struct WAV
{
    RIFF riff;
    SIGNID signId;
    FORMAT format;
    DATA data;
    LIST *list;
}WAV;

typedef struct WAVALL
{
    WAV *wav;
    size32_t fileSize;
    size32_t dataPosition;    
    size32_t numOfSample;
    float duration;
}WAVALL;

int wav_analyse(WAVALL *wavall, FILE *file);
void print_wav(WAVALL *wavall);

#endif /* wav_h */
