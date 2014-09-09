//
//  chebyshev_10KHz.h
//  sdr_audio
//
//  Created by Apple on 06.09.14.
//  Copyright (c) 2014 Apple. All rights reserved.
//

#ifndef sdr_audio_chebyshev_10KHz_h
#define sdr_audio_chebyshev_10KHz_h

#define NCoef 12
typedef struct IirData
{
    float y[NCoef+1]; //output samples
    float x[NCoef+1]; //input samples
} IirData;

void iirInit(IirData* data);
//Band pass filer 10-14 KHz
//48 KHz sample rate
float iir(float NewSample, IirData* data);


#endif
