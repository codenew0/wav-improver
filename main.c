//
//  wavwrite.c
//  TestC
//
//  Created by Code New on 2019/10/26.
//  Copyright © 2019 Code New. All rights reserved.
//

#include "wav.h"
#include "common.h"
#include "wavheader.h"

int main(int argc, char *argv[])
{
    WAVALL wavall;
    
    wavall.wav = (WAV *)malloc(sizeof(wavall.wav));
    WAV *wav = wavall.wav;
    FILE *input_file;
    FILE *output_file;
    char *filename = NULL;
    
    if (argc < 2)
    {
        filename = INPUT_FILE;
    }
    else
    {
        filename = argv[1];
    }
    input_file = fopen(filename, "rb");
    output_file = fopen(OUTPUT_FILE, "wb");
    
    wav_analyse(&wavall, input_file);
    print_wav(&wavall);
    
    printf("Time: %s\n", duration2time(wavall.duration));
    
    wav_write(output_file, input_file, wav);
    
    fclose(input_file);
    fclose(output_file);

    return 0;
}
