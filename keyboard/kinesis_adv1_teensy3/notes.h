#ifndef NOTES_H
#define NOTES_H

#include <stdbool.h>

#define NOTE_E4 1516
#define NOTE_E4 1516
#define NOTE_C4 1911 /* middle C */
#define NOTE_G4 1275
#define NOTE_G3 2551
#define NOTE_NONE 1000000
#define EIGHTH_NOTE 110
#define QUARTER_NOTE (2 * EIGHTH_NOTE)
#define GAP_TIME 15

void notes_start(void);

void notes_update(void);

bool notes_busy(void);

#endif
