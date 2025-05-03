#ifndef SOUND_H
#define SOUND_H

#include <SDL2/SDL.h>

/** 
 * Initialize the audio device.  
 * Must be called after SDL_Init(SDL_INIT_AUDIO).  
 * Logs success or failure.
 */
void sound_init(void);

/** 
 * Queue a short square-wave “beep” onto the audio device.  
 * If you hear nothing, the device never opened.  
 */
void play_beep(void);

/** 
 * Close and clean up the audio device.  
 */
void sound_quit(void);

#endif // SOUND_H
