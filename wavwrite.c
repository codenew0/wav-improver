//
//  wavwrite.c
//  TestC
//
//  Created by Code New on 2019/10/26.
//  Copyright © 2019 Code New. All rights reserved.
//

#include "wavheader.h"
#include "common.h"

int wav_write(FILE *output_file, FILE *input_file, WAV *wav)
{
    char choice[20];
    WAVHEADER wav_header;
    printf("Use default header? (Yes) ");
    fgets(choice, 19, stdin);
    
    if (choice[0] == 'Y' || choice[0] == 'y' || choice[0] == 10)       //new line or Y
    {
        create_wav_header(&wav_header);
        wav_header.fileLen = wav->data.chkLen + 36;
        wav_header.dataLen = wav->data.chkLen;
    }
    else if (choice[0] == 'N' || choice[0] == 'n')
    {
        printf("\nNum of channels: ");
        scanf("%hu", &wav_header.nChannels);    // Channels
        printf("Sample rate: ");
        scanf("%u", &wav_header.samplePreSec);  // Sample rate
        printf("Bits per sample: ");
        scanf("%hu", &wav_header.bitsPerSample);// Bits per sample
        wav_header.fileId = 1179011410;         // "RIFF"
        wav_header.fileLen = wav->data.chkLen + 36;
                                                // Changeable
        wav_header.waveId = 1163280727;         // "WAVE"
        wav_header.fmtId = 544501094;           // "fmt "
        wav_header.fmtLen = 16;                 // No extented info
        wav_header.compCode = 1;                // PCM
        wav_header.blockAlign = wav_header.nChannels * wav_header.bitsPerSample / 8;
                                                // nChans * bytes-per-sample
        wav_header.aveBytePerSec = wav_header.samplePreSec * wav_header.blockAlign;
                                                // nChans * sampleRate * bytes-per-sample
        wav_header.dataId = 1635017060;         // "data"
        wav_header.dataLen = wav->data.chkLen;  // Changeable
    }
    
    print_wav_header(&wav_header);
    
    fwrite(&wav_header, sizeof(wav_header), 1, output_file);
    parse_data(output_file, input_file, wav);
    
    return 0;
}

int parse_data(FILE *output_file, FILE *input_file, WAV *wav)
{
    char *chunk = (char *)malloc(sizeof(char) * wav->format.wBlockAlign);
    
    size32_t numOfSample = wav->data.chkLen * 8 /
                      (wav->format.wBitsPerSample * wav->format.wChannels);
    
    for (int i = 0; i < numOfSample; i++)
    {
        fread(chunk, 1, wav->format.wBlockAlign, input_file);
//        char zero = 0;
        fwrite(chunk, 1, wav->format.wBlockAlign, output_file);
//        fwrite(&zero, 1, wav->format.wBlockAlign / 4, output_file);
//        fwrite(chunk + 1, 1, wav->format.wBlockAlign / 4, output_file);
//        fwrite(&zero, 1, wav->format.wBlockAlign / 4, output_file);
//        fwrite(chunk + 1, 1, wav->format.wBlockAlign / 4, output_file);
        for(int xchannel = 0; xchannel < wav->format.wChannels; xchannel++)
        {
            
           // printf(" Channel#%d  ", xchannel + 1);
          //  printf("%d  ", chunk[xchannel * 2] | chunk[xchannel * 2 + 1] << 8);
            //fwrite(chunk, 1, wav->format.wBlockAlign, output_file);
            //putchar('|');
        }
     //   putchar('\n');
    }
//    fseek(output_file, 0, DATALEN);
//    fwrite(&wav->data.chkLen, sizeof(wav->data.chkLen), 1, output_file);
//
//    size32_t fileLen = 36 + wav->data.chkLen;
//    fseek(output_file, 0, FILELEN);
//    fwrite(&fileLen, sizeof(fileLen), 1, output_file);
    
    printf("\nOver\n");
    fclose(output_file);
    
    return 0;
}

void create_wav_header(WAVHEADER *wav_header)
{
    wav_header->fileId = 1179011410;         // "RIFF"
    wav_header->fileLen = -1;                // UNKNOWN
    wav_header->waveId = 1163280727;         // "WAVE"
    wav_header->fmtId = 544501094;           // "fmt "
    wav_header->fmtLen = 16;                 // No extented info
    wav_header->compCode = 1;                // PCM
    wav_header->nChannels = 2;               // 2 Channels
    wav_header->samplePreSec = 48000;        // Digital Audio Tape (DAT).
    wav_header->aveBytePerSec = wav_header->samplePreSec * sizeof(size32_t);
                                             // nChans * sampleRate * bytes-per-sample
    wav_header->blockAlign = sizeof(size32_t);
                                             // nChans * bytes-per-sample
    wav_header->bitsPerSample = 16;          // Bits per sample
    wav_header->dataId = 1635017060;         // "data"
    wav_header->dataLen = -1;                // UNKNOWN
}

void print_wav_header(WAVHEADER *wav_header)
{
    
    printf("--------------RIFF----------------\n");
    printf("fileId: %u, value: \"%s\"\n", wav_header->fileId, bytearr2charstr(wav_header->fileId));
    printf("fileLen: %u\n", wav_header->fileLen);
    printf("--------------SIGN----------------\n");
    printf("waveId: %u, value: \"%s\"\n", wav_header->waveId, bytearr2charstr(wav_header->waveId));
    printf("--------------FORMAT--------------\n");
    printf("chkId: %u, value: \"%s\"\n", wav_header->fmtId, bytearr2charstr(wav_header->fmtId));
    printf("chkLen: %u\n", wav_header->fmtLen);
    printf("wFormatTag: %hu\n", wav_header->compCode);
    printf("wChannels: %hu\n", wav_header->nChannels);
    printf("dwSampleRate: %u\n", wav_header->samplePreSec);
    printf("dwAvgBytesRate: %u\n", wav_header->aveBytePerSec);
    printf("wBlockAlign: %hu\n", wav_header->blockAlign);
    printf("wBitsPerSample: %hu\n", wav_header->bitsPerSample);
    printf("--------------DATA----------------\n");
    printf("chkId: %u, value: \"%s\"\n", wav_header->dataId, bytearr2charstr(wav_header->dataId));
    printf("chkLen: %u\n", wav_header->dataLen);
    printf("----------------------------------\n");
}
