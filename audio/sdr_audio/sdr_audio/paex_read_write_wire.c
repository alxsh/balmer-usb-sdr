/** @file paex_read_write_wire.c
	@ingroup examples_src
	@brief Tests full duplex blocking I/O by passing input straight to output.
	@author Bjorn Roche. XO Audio LLC for Z-Systems Engineering.
    @author based on code by: Phil Burk  http://www.softsynth.com
    @author based on code by: Ross Bencina rossb@audiomulch.com
*/
/*
 * $Id: patest_read_record.c 757 2004-02-13 07:48:10Z rossbencina $
 *
 * This program uses the PortAudio Portable Audio Library.
 * For more information see: http://www.portaudio.com
 * Copyright (c) 1999-2000 Ross Bencina and Phil Burk
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * The text above constitutes the entire PortAudio license; however, 
 * the PortAudio community also makes the following non-binding requests:
 *
 * Any person wishing to distribute modifications to the Software is
 * requested to send the modifications to the original developer so that
 * they can be incorporated into the canonical version. It is also 
 * requested that these non-binding requests be included along with the 
 * license above.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mach/mach_time.h>

#include "portaudio.h"
#include "process_data.h"
#include "chebyshev_10KHz.h"

int pa_devs_main(void);
void profile();

#define FRAMES_PER_BUFFER (1024)
#define NUM_CHANNELS    (2)
#define NUM_SECONDS     (100)
/* #define DITHER_FLAG     (paDitherOff)  */
#define DITHER_FLAG     (0) /**/

/* @todo Underflow and overflow is disabled until we fix priming of blocking write. */
#define CHECK_OVERFLOW  (0)
#define CHECK_UNDERFLOW  (0)


/* Select sample format. */
#if 1
#define PA_SAMPLE_TYPE  paFloat32
#define SAMPLE_SIZE (4)
#define SAMPLE_SILENCE  (0.0f)
#define CLEAR(a) memset( (a), 0, FRAMES_PER_BUFFER * NUM_CHANNELS * SAMPLE_SIZE )
#define PRINTF_S_FORMAT "%.8f"
#elif 0
#define PA_SAMPLE_TYPE  paInt16
#define SAMPLE_SIZE (2)
#define SAMPLE_SILENCE  (0)
#define CLEAR(a) memset( (a), 0,  FRAMES_PER_BUFFER * NUM_CHANNELS * SAMPLE_SIZE )
#define PRINTF_S_FORMAT "%d"
#elif 0
#define PA_SAMPLE_TYPE  paInt24
#define SAMPLE_SIZE (3)
#define SAMPLE_SILENCE  (0)
#define CLEAR(a) memset( (a), 0,  FRAMES_PER_BUFFER * NUM_CHANNELS * SAMPLE_SIZE )
#define PRINTF_S_FORMAT "%d"
#elif 0
#define PA_SAMPLE_TYPE  paInt8
#define SAMPLE_SIZE (1)
#define SAMPLE_SILENCE  (0)
#define CLEAR(a) memset( (a), 0,  FRAMES_PER_BUFFER * NUM_CHANNELS * SAMPLE_SIZE )
#define PRINTF_S_FORMAT "%d"
#else
#define PA_SAMPLE_TYPE  paUInt8
#define SAMPLE_SIZE (1)
#define SAMPLE_SILENCE  (128)
#define CLEAR( a ) { \
    int i; \
    for( i=0; i<FRAMES_PER_BUFFER*NUM_CHANNELS; i++ ) \
        ((unsigned char *)a)[i] = (SAMPLE_SILENCE); \
}
#define PRINTF_S_FORMAT "%d"
#endif


/*******************************************************************/
int main(void);
int main(void)
{
//    return pa_devs_main();
    
    PaStreamParameters inputParameters, outputParameters;
    PaStream *stream = NULL;
    PaError err;
    
    int i;
    processDataInit();
    
    
    printf("patest_read_write_wire.c\n"); fflush(stdout);

    int numBytesInput = FRAMES_PER_BUFFER * NUM_CHANNELS * SAMPLE_SIZE ;
    int numBytesOutput = FRAMES_PER_BUFFER * SAMPLE_SIZE ;
    char *sampleBlockInput = (char *) malloc( numBytesInput );
    char *sampleBlockOutput = (char *) malloc( numBytesOutput );
    
    if( sampleBlockInput == NULL )
    {
        printf("Could not allocate record array.\n");
        exit(1);
    }
    
    memset( sampleBlockInput, 0, numBytesInput );
    memset( sampleBlockOutput, 0, numBytesOutput );

    err = Pa_Initialize();
    if( err != paNoError ) goto error;
    
    //profile();

    //inputParameters.device = Pa_GetDefaultInputDevice(); /* default input device */
    inputParameters.device = 4;//USB Asus
    if(inputParameters.device>=Pa_GetDeviceCount())
    {
        printf( "Bad Input device # %d.\n", inputParameters.device );
        exit(1);
    }
    
    printf( "Input device # %d.\n", inputParameters.device );
    printf( "Input LL: %g s\n", Pa_GetDeviceInfo( inputParameters.device )->defaultLowInputLatency );
    printf( "Input HL: %g s\n", Pa_GetDeviceInfo( inputParameters.device )->defaultHighInputLatency );
    inputParameters.channelCount = NUM_CHANNELS;
    inputParameters.sampleFormat = PA_SAMPLE_TYPE;
    inputParameters.suggestedLatency = Pa_GetDeviceInfo( inputParameters.device )->defaultHighInputLatency ;
    inputParameters.hostApiSpecificStreamInfo = NULL;

    outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
    printf( "Output device # %d.\n", outputParameters.device );
    printf( "Output LL: %g s\n", Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency );
    printf( "Output HL: %g s\n", Pa_GetDeviceInfo( outputParameters.device )->defaultHighOutputLatency );
    outputParameters.channelCount = 1;
    outputParameters.sampleFormat = PA_SAMPLE_TYPE;
    outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultHighOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;

    /* -- setup -- */

   err = Pa_OpenStream(
              &stream,
              &inputParameters,
              &outputParameters,
              SAMPLE_RATE,
              FRAMES_PER_BUFFER,
              paClipOff,      /* we won't output out of range samples so don't bother clipping them */
              NULL, /* no callback, use blocking API */
              NULL ); /* no callback, so no callback userData */
    if( err != paNoError ) goto error;

    err = Pa_StartStream( stream );
    if( err != paNoError ) goto error;
    printf("Wire on. Will run %d seconds.\n", NUM_SECONDS); fflush(stdout);

    for( i=0; i<(NUM_SECONDS*SAMPLE_RATE)/FRAMES_PER_BUFFER; ++i )
    {
        err = Pa_WriteStream( stream, sampleBlockOutput, FRAMES_PER_BUFFER );
        if( err && CHECK_UNDERFLOW ) goto xrun;
        processData((float*)sampleBlockInput, (float*)sampleBlockOutput, FRAMES_PER_BUFFER);
        err = Pa_ReadStream( stream, sampleBlockInput, FRAMES_PER_BUFFER );
        if( err && CHECK_OVERFLOW ) goto xrun;
    }
    err = Pa_StopStream( stream );
    if( err != paNoError ) goto error;

    memset( sampleBlockInput, 0, numBytesInput );
    memset( sampleBlockOutput, 0, numBytesOutput );
    free( sampleBlockInput );
    free( sampleBlockOutput );

    Pa_Terminate();
    return 0;

xrun:
    if( stream ) {
       Pa_AbortStream( stream );
       Pa_CloseStream( stream );
    }
    free( sampleBlockInput );
    free( sampleBlockOutput );
    Pa_Terminate();
    if( err & paInputOverflow )
       fprintf( stderr, "Input Overflow.\n" );
    if( err & paOutputUnderflow )
       fprintf( stderr, "Output Underflow.\n" );
    return -2;

error:
    if( stream ) {
       Pa_AbortStream( stream );
       Pa_CloseStream( stream );
    }
    free( sampleBlockInput );
    free( sampleBlockOutput );
    Pa_Terminate();
    fprintf( stderr, "An error occured while using the portaudio stream\n" );
    fprintf( stderr, "Error number: %d\n", err );
    fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( err ) );
    return -1;
}

static double machSecondsConversionScaler_ = 0.0;

static void InitializeClock( void )
{
    mach_timebase_info_data_t info;
    kern_return_t err = mach_timebase_info( &info );
    if( err == 0  )
        machSecondsConversionScaler_ = 1e-9 * (double) info.numer / (double) info.denom;
}


static double GetTime( void )
{
    return mach_absolute_time() * machSecondsConversionScaler_;
}

void profile()
{
    InitializeClock();
    IirData data;
    iirInit(&data);
#define COUNT 100000
    float input[COUNT];
    float output[COUNT];
    for(int i=0; i<COUNT; i++)
        input[i] = rand()*1e-5;
    PaTime start = GetTime();
    for(int i=0; i<COUNT; i++)
        output[i] = iir(input[i], &data);
    PaTime end = GetTime();
    printf("profile time=%e\n", end-start);
    printf("scale=%e\n", machSecondsConversionScaler_);
}