//
//  process_data.c
//  sdr_audio
//
//  Created by balmer@inbox.ru on 05.09.14.
//  Copyright (c) 2014 balmer@inbox.ru. All rights reserved.
//

#include <math.h>

#include "process_data.h"
#include "chebyshev_10KHz.h"

#define LAST_MAX_SIZE 10

//FREQ_SAMPLES - подбирается так, чтобы достаточно точно попасть в период сигнала
#define FREQ 9900
#define FREQ_SAMPLES 480

float lastMax[LAST_MAX_SIZE];
static float freq_sin[FREQ_SAMPLES];
static float freq_cos[FREQ_SAMPLES];
static uint32_t freq_idx = 0;
bool upper_side_band = true;

IirData data_I;
IirData data_Q;

uint32_t quant_idx = 0;


void IQ_decoder_init();
float IQ_decoder(float I, float Q);

void processDataInit()
{
    for(int i=0; i<LAST_MAX_SIZE; i++)
    {
        lastMax[i] = 1.0f;
    }

    IQ_decoder_init();
}

float famax(float m1, float m2)
{
    m1 = fabsf(m1);
    m2 = fabsf(m2);
    return m1>m2?m1:m2;
}

void pushLastMax(float f)
{
    //process max
    for(int i=1; i<LAST_MAX_SIZE; i++)
    {
        lastMax[i-1] = lastMax[i];
    }
    lastMax[LAST_MAX_SIZE-1] = f;
}

float calcMul()
{
    float f = 0;
    for(int i=0; i<LAST_MAX_SIZE; i++)
    {
        f += lastMax[i];
    }
    
    f /= LAST_MAX_SIZE;
    
    
    if(f>0)
        return 0.5f/f;
    
    return 1.0f;
}

void processData(float* sampleBlockInput, float* sampleBlockOutput, int frames)
{
    float curMax = 0;
    float outMax = 0;
    float outMid = 0;
    float outDelta = 0;
    float mul = calcMul();
    
    for(int i=0; i<frames; i++)
    {
        float I = sampleBlockInput[i*2];
        float Q = sampleBlockInput[i*2+1];
        
        float mx = famax(I, Q);
        if(mx>curMax)
            curMax = mx;
        
        I *= mul;
        Q *= mul;
        
        float out = IQ_decoder(I,Q);
        
        float om = fabs(out);
        if(om>outMax)
            outMax = om;
        
        outMid += out;
        
        sampleBlockOutput[i] = out;
        //sampleBlockOutput[i] = I;
    }
    
    outMid /= frames;
    
    for(int i=0; i<frames; i++)
    {
        float d = sampleBlockOutput[i] - outMid;
        outDelta += d*d;
    }
    
    outDelta = sqrt(outDelta)/frames;
    
    pushLastMax(curMax);
}

void IQ_decoder_init()
{
    freq_idx = 0;
    float df = (2*M_PI*FREQ)/SAMPLE_RATE;
    for(int i=0; i<FREQ_SAMPLES; i++)
    {
        freq_sin[i] = sinf(df*i);
        freq_cos[i] = cosf(df*i);
    }
    iirInit(&data_I);
    iirInit(&data_Q);
}

float IQ_decoder(float I, float Q)
{
    //return I*1.1f+Q*1.2f;
    I = iir(I, &data_I);
    Q = iir(Q, &data_Q);
    //return Q;
    
    uint32_t idx = freq_idx%FREQ_SAMPLES;
    
    float out;
    if(upper_side_band)
        out = I*freq_cos[idx] + Q*freq_sin[idx];//SSB Upper Side Band
    else
        out = I*freq_cos[idx] - Q*freq_sin[idx];//SSB Lower Side Band
    
    freq_idx++;
    return out;
}

void setUpperSideBand(bool usb)
{
    upper_side_band = usb;
}