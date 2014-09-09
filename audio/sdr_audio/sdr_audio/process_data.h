//
//  process_data.h
//  sdr_audio
//
//  Created by Apple on 05.09.14.
//  Copyright (c) 2014 Apple. All rights reserved.
//

#ifndef sdr_audio_process_data_h
#define sdr_audio_process_data_h

#ifndef M_PI
#define M_PI		3.14159265358979323846
#endif

#define SAMPLE_RATE  (48000)

void processDataInit();
/*
 sampleBlockInput = 2 channel
 sampleBlockOutput = 1 channel
 */
void processData(float* sampleBlockInput, float* sampleBlockOutput, int frames);

#endif
