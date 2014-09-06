//
//  process_data.c
//  sdr_audio
//
//  Created by Apple on 05.09.14.
//  Copyright (c) 2014 Apple. All rights reserved.
//

#include <stdio.h>
#include <math.h>

#include "process_data.h"

#define LAST_MAX_SIZE 10

float lastMax[LAST_MAX_SIZE];

void processDataInit()
{
    for(int i=0; i<LAST_MAX_SIZE; i++)
    {
        lastMax[i] = 1.0f;
    }
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
    float mul = calcMul();
    
    for(int i=0; i<frames; i++)
    {
        float I = sampleBlockInput[i*2];
        float Q = sampleBlockInput[i*2+1];
        
        float mx = famax(I, Q);
        if(mx>curMax)
            curMax = mx;
        
        I *= mul;
        
        sampleBlockOutput[i] = I;
    }

    pushLastMax(curMax);
}
