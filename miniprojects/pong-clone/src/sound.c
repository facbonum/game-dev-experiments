#include "sound.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SAMPLE_RATE 44100
#define BLIP_DURATION_MS 100
#define BLIP_FREQ 440  // Hz

static SDL_AudioDeviceID device_id = 0;
static Uint8 *blip_buffer = NULL;
static Uint32 blip_length = 0;

void sound_init() {
    SDL_AudioSpec spec;
    SDL_zero(spec);
    spec.freq = SAMPLE_RATE;
    spec.format = AUDIO_U8;
    spec.channels = 1;
    spec.samples = 512;
    spec.callback = NULL;

    device_id = SDL_OpenAudioDevice(NULL, 0, &spec, NULL, 0);
    if (device_id == 0) {
        printf("Failed to open audio device: %s\n", SDL_GetError());
        return;
    }

    // Generate square wave blip
    int samples = (SAMPLE_RATE * BLIP_DURATION_MS) / 1000;
    blip_buffer = (Uint8 *)malloc(samples);
    if (!blip_buffer) {
        printf("Failed to allocate blip buffer\n");
        return;
    }

    for (int i = 0; i < samples; i++) {
        float t = (float)i / SAMPLE_RATE;
        float cycle = fmodf(t * BLIP_FREQ, 1.0f);
        blip_buffer[i] = cycle < 0.5f ? 255 : 0;  // Square wave: full or none
    }

    blip_length = samples;
}

void sound_play_hit() {
    if (device_id == 0 || blip_buffer == NULL) return;

    SDL_ClearQueuedAudio(device_id);
    SDL_QueueAudio(device_id, blip_buffer, blip_length);
    SDL_PauseAudioDevice(device_id, 0);
}

void sound_quit() {
    if (device_id) SDL_CloseAudioDevice(device_id);
    if (blip_buffer) free(blip_buffer);
}
