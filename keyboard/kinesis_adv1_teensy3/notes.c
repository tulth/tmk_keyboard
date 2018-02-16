#include <printf.h>
#include "notes.h"
#include "kinesis_adv1_teensy3.h"

static bool busy = false;
static int note_num = 0;
static bool gap = false;
typedef struct note_t {
    int pitch;
    int duration;
} note_t;
static note_t notes[] = {
  {NOTE_NONE, QUARTER_NOTE},
  {NOTE_E4, EIGHTH_NOTE},
  {NOTE_E4, 1.5*EIGHTH_NOTE},
  {NOTE_NONE, 0.5*EIGHTH_NOTE},
  {NOTE_E4, QUARTER_NOTE},
  {NOTE_C4, EIGHTH_NOTE},
  {NOTE_E4, QUARTER_NOTE},
  {NOTE_G4, QUARTER_NOTE},
  {NOTE_NONE, QUARTER_NOTE},
  {NOTE_G3, QUARTER_NOTE}};

void notes_start(void)
{
  busy = true;
  note_num = 0;
  gap = false;
}

void notes_update(void)
{
  /* printf("note_num: %d\n", note_num); */
  /* printf("kinesis_buzzer_busy(): %d\n", kinesis_buzzer_busy()); */
  int total_notes = sizeof(notes) / sizeof(note_t);
  if (note_num < total_notes) {
    if (!kinesis_buzzer_busy()) {
      if (gap) {
        kinesis_start_buzzer(GAP_TIME, NOTE_NONE);
        gap = false;
      } else {
        kinesis_start_buzzer(notes[note_num].duration-GAP_TIME, notes[note_num].pitch);
        note_num++;
        gap = true;
      }
    }
  } else {
    busy = kinesis_buzzer_busy();
  }
    
}

bool notes_busy(void)
{
  return busy;
}
