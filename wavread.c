//
//  wavread.c
//  TestC
//
//  Created by Code New on 2019/10/26.
//  Copyright © 2019 Code New. All rights reserved.
//

#include "wav.h"
#include "common.h"

int wav_analyse(WAVALL *wavall, FILE *file)
{
    WAV *wav = wavall->wav;
    
    unsigned char *data4, *data2;

    if (file == NULL)
    {
        perror("Open failed\n");
        return 1;
    }
    
    fseek(file, 0, SEEK_END);
    wavall->fileSize = (size32_t)ftell(file);
    rewind(file);
    printf("Size: %u\n", wavall->fileSize);

    data4 = (unsigned char *)malloc(sizeof(unsigned char) * BYTE_4);
    data2 = (unsigned char *)malloc(sizeof(unsigned char) * BYTE_2);
    
    //fileId
    fread(data4, 1, BYTE_4, file);
    wav->riff.fileId = array2binary(data4, BYTE_4);
    //fileLen
    fread(data4, 1, BYTE_4, file);
    wav->riff.fileLen = little2big(data4, BYTE_4);
    //size32_t tmp = (wav->riff.fileLen - 36) / 2 + 36;
    size32_t tmp = wav->riff.fileLen;
    //waveId
    fread(data4, 1, BYTE_4, file);
    wav->signId.waveId = array2binary(data4, BYTE_4);
    //chkId
    fread(data4, 1, BYTE_4, file);
    wav->format.chkId = array2binary(data4, BYTE_4);
    //chkLen
    fread(data4, 1, BYTE_4, file);
    wav->format.chkLen = array2binary(data4, BYTE_4);
    //wFormatTag
    fread(data2, 1, BYTE_2, file);
    wav->format.wFormatTag = (size16_t)array2binary(data2, BYTE_2);
    //wChannels
    fread(data2, 1, BYTE_2, file);
    wav->format.wChannels = (size16_t)array2binary(data2, BYTE_2);
    //dwSampleRate
    fread(data4, 1, BYTE_4, file);
    wav->format.dwSampleRate = little2big(data4, BYTE_4);
    //dwAvgBytesRate
    fread(data4, 1, BYTE_4, file);
    wav->format.dwAvgBytesRate = little2big(data4, BYTE_4);
    //wBlockAlign
    fread(data2, 1, BYTE_2, file);
    wav->format.wBlockAlign = (size16_t)little2big(data2, BYTE_2);
    //wBitsPerSample
    if (wav->format.wFormatTag == PCM)
    {
        fread(data2, 1, BYTE_2, file);
        wav->format.wBitsPerSample = (size16_t)array2binary(data2, BYTE_2);
    }
    else
    {
        wav->format.wBitsPerSample = 0;
    }

    //wExtSize
    if (wav->format.chkLen == 16)
    {
        wav->format.wExtSize = 0;
        wav->format.extraInfo = NULL;
    }
    else
    {
        fread(data2, 1, BYTE_2, file);
        wav->format.wExtSize = (size16_t)array2binary(data4, BYTE_4);
        //extraInfo
        wav->format.extraInfo = (char *)malloc(sizeof(char) * wav->format.wExtSize);
        fread(wav->format.extraInfo, 1, wav->format.wExtSize, file);
    }
    //chkId
    fread(data4, 1, BYTE_4, file);
    size32_t tmp_id = array2binary(data4, BYTE_4);
    
    //list chunk
    if (tmp_id == LIST_VALUE)
    {
        wav->list = (LIST *)malloc(sizeof(LIST));
        wav->list->chkId = LIST_VALUE;
        //list len
        fread(data4, 1, BYTE_4, file);
        wav->list->chkLen = little2big(data4, BYTE_4);
        //typeId
        fread(data4, 1, BYTE_4, file);
        wav->list->typeId = array2binary(data4, BYTE_4);
        //text
        wav->list->text = (char *)malloc(sizeof(char) * (wav->list->chkLen - 4));
        fread(wav->list->text, 1, wav->list->chkLen - 4, file);
        fread(data4, 1, BYTE_4, file);
    }
    else
    {
        wav->list = NULL;
    }
    wav->data.chkId = array2binary(data4, BYTE_4);
    //chkLen
    fread(data4, 1, BYTE_4, file);
    wav->data.chkLen = little2big(data4, BYTE_4);
    //tmp = wav->data.chkLen / 2;
    tmp = wav->data.chkLen;
    //data (x)
//    wav->data.x = (char *)malloc(sizeof(char) * wav->data.chkLen);
//    fread(wav->data.x, 1, wav->data.chkLen, file);
    wavall->dataPosition = (size32_t)ftell(file);
    wavall->duration = wav->riff.fileLen * 1.0 / wav->format.dwAvgBytesRate;
    wavall->numOfSample = wav->data.chkLen * 8 / (wav->format.wBitsPerSample * wav->format.wChannels);
    
    return 0;
}

void print_wav(WAVALL *wavall)
{
    WAV *wav = wavall->wav;
    
    printf("--------------RIFF----------------\n");
    printf("fileId: %u, value: \"%s\"\n", wav->riff.fileId, bytearr2charstr(wav->riff.fileId));
    printf("fileLen: %u\n", wav->riff.fileLen);
    printf("--------------SIGN----------------\n");
    printf("waveId: %u, value: \"%s\"\n", wav->signId.waveId, bytearr2charstr(wav->signId.waveId));
    printf("--------------FORMAT--------------\n");
    printf("chkId: %u, value: \"%s\"\n", wav->format.chkId, bytearr2charstr(wav->format.chkId));
    printf("chkLen: %u\n", wav->format.chkLen);
    printf("wFormatTag: %hu\n", wav->format.wFormatTag);
    printf("wChannels: %hu\n", wav->format.wChannels);
    printf("dwSampleRate: %u\n", wav->format.dwSampleRate);
    printf("dwAvgBytesRate: %u\n", wav->format.dwAvgBytesRate);
    if (wav->format.wBitsPerSample != 0)
    {
        printf("wBlockAlign: %hu\n", wav->format.wBlockAlign);
    }
    if (wav->format.wBitsPerSample != 0)
    {
        printf("wBitsPerSample: %hu\n", wav->format.wBitsPerSample);
    }
    if (wav->format.wExtSize != 0)
    {
        printf("wExtSize: %hu\n", wav->format.wExtSize );
        printf("extraInfo: %s\n", wav->format.extraInfo);
    }
    printf("--------------DATA----------------\n");
    printf("chkId: %u, value: \"%s\"\n", wav->data.chkId, bytearr2charstr(wav->data.chkId));
    printf("chkLen: %u\n", wav->data.chkLen);
    printf("data position: %u\n", wavall->dataPosition);
    printf("--------------SAMPLE--------------\n");
    printf("file size: %u\n", wavall->fileSize);
    printf("num of sample: %u\n", wavall->numOfSample);
    printf("duration: %f\n", wavall->duration);
    printf("----------------------------------\n");
}
