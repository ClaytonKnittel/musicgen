
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "wav.h"


// Standard format codes for waveform data
#define WAVE_FORMAT_PCM         0x0001
#define WAVE_FORMAT_IEEE_FLOAT  0x0003


#define ptr_add(ptr, amt) \
    (((char*) (ptr)) + (amt))


typedef struct Header_T {
    // Chunk ID (always "RIFF")
    char ckID[4];

    // File size, minus 8 for ckID and WAVEID
    uint cksize;

    char WAVEID[4];
} Header;

typedef struct Format_T {
    // Chunk ID (always "fmt ")
    char ckID[4];

    // length of remainder of this chunk (16)
    uint cksize;

    // indicates audio format
    short wFormatTag;

    // Number of interleaved channels
    //  - 1 for mono
    //  - 2 for stereo
    //  - 6 for surround
    short nChannels;

    // Sampling rate (blocks per second)
    uint nSamplesPerSec;

    // Data rate (sample rate * sample size), used for
    // estimating memory requirement
    uint nAvgBytesPerSec;

    // Data block size
    short nBlockAlign;

    // Bits per sample
    short nBitsPerSample;
} Format;


typedef struct Data_T {
    // Chunk ID (always "data")
    char ckID[4];

    // Chunk size
    uint cksize;

    // Followed by "cksize" bytes of the sample data,
    // with 1-byte padding if "cksize" is odd
} Data;


void initHeader(Header *head, size_t fSize) {
    memcpy(((char*) head) + offsetof(Header, ckID), "RIFF", 4 * sizeof(char));
    head->cksize = fSize - 8;
    memcpy(((char*) head) + offsetof(Header, WAVEID), "WAVE", 4 * sizeof(char));
}

void initFormat(Format *fmt, size_t fSize, AudioFmt afmt) {
    memcpy(((char*) fmt) + offsetof(Format, ckID), "fmt ", 4 * sizeof(char));
    fmt->cksize = 16;
    fmt->wFormatTag = WAVE_FORMAT_PCM;
    fmt->nChannels = (short) afmt.nChannels;
    fmt->nSamplesPerSec = afmt.sample_rate;
    fmt->nAvgBytesPerSec = afmt.sample_rate * afmt.nChannels * (afmt.nBitsPerSample / 8);
    fmt->nBlockAlign = afmt.nChannels * (afmt.nBitsPerSample / 8);
    fmt->nBitsPerSample = afmt.nBitsPerSample;
}

void initData(Data *data, AudioFmt afmt) {
    memcpy(((char*) data) + offsetof(Data, ckID), "data", 4 * sizeof(char));
    data->cksize = afmt.nChannels * afmt.nSamples * (afmt.nBitsPerSample / 8);
}

size_t fileSize(AudioFmt afmt) {
    return sizeof(Header) + sizeof(Format) + sizeof(Data)
            + afmt.nChannels * afmt.nSamples * (afmt.nBitsPerSample / 8);
}


int audioWrite(const char* file, const short* audioData, AudioFmt afmt) {
    FILE *f = fopen(file, "wb");

    if (f == NULL) {
        printf("Unable to open file %s\n", file);
        return 1;
    }

    size_t fSize = fileSize(afmt);
    Header *head = (Header*) malloc(fSize);
    Format *fmt  = (Format*) ptr_add(head, sizeof(Header));
    Data   *data = (Data*)   ptr_add(fmt, sizeof(Format));
    initHeader(head, fSize);
    initFormat(fmt, fSize, afmt);
    initData(data, afmt);

    memcpy(ptr_add(data, sizeof(Data)), audioData, sizeof(short) * afmt.nSamples);

    fwrite(head, 1, fSize, f);

    free(head);
    fclose(f);

    return 0;
}
