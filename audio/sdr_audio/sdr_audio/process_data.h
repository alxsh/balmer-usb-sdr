//
//  process_data.h
//  sdr_audio
//
//  Created by Apple on 05.09.14.
//  Copyright (c) 2014 Apple. All rights reserved.
//

#ifndef sdr_audio_process_data_h
#define sdr_audio_process_data_h

/*
 sampleBlockInput = 2 channel
 sampleBlockOutput = 1 channel
 */
void processData(float* sampleBlockInput, float* sampleBlockOutput, int frames);

#endif
