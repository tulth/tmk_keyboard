/*
  Copyright 2013 Oleg Kostyuk <cub.uanic@gmail.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <stdint.h>
#include <stdbool.h>
#include "keycode.h"
#include "action.h"
#include "action_util.h"
#include "action_code.h"
#include "action_macro.h"
#include "action_layer.h"
#include "report.h"
#include "host.h"
#include "keymap.h"

/* keymap definition macro, based on ergodox */
#define KEYMAP(                                                                                \
  /* left side */                                                                              \
  k02 , k42 , k82  , k01  , k41 , k81   , k00  , k40 , k80 ,                                   \
  k10 , kE0 , k60  , kA0  , k20 , kC0   ,                                                      \
  k11 , kE1 , k61  , kA1  , k21 , kC1   ,                                                      \
  k12 , kE2 , k62  , kA2  , k22 , kC2   ,                                                      \
  k13 , kE3 , k63  , kA3  , k23 , kC3   ,                                                      \
        kE4 , k64  , kA4  , kC4 ,                                                              \
                                          kC6  , kC5 ,                                         \
                                  /*BSPC, DEL*/  kA5 ,                                         \
                                  kA6   , k26  , kE5 ,                                         \
  /* right side */                                                                             \
  k03 , k43 , k83  , k04  , k44 , k84   , k05  , k08 , k09 ,                                   \
                     k94  , k54 , kD4   , kB4  , k74 , kF4 ,                                   \
                     k95  , k55 , kD5   , kB5  , k75 , kF5 ,                                   \
                     k96  , k56 , kD6   , kB6  , k76 , kF6 ,                                   \
                     k97  , k57 , kD7   , kB7  , k77 , kF7 ,                                   \
                            k93 , kD3   , kB3  , k73 ,                                         \
        k27 , k66  ,                                                                           \
        k67 , /*ENT, SPC*/                                                                     \
        k17 , kE6  , k16                                                                       \
  )                                                                                            \
  /* matrix positions k<row_hex><col_hex> */                                                   \
  {                                                                                            \
  {KC_##k00,KC_##k01,KC_##k02,KC_##k03,KC_##k04,KC_##k05,KC_NO   ,KC_NO   ,KC_##k08,KC_##k09}, \
  {KC_##k10,KC_##k11,KC_##k12,KC_##k13,KC_NO   ,KC_NO   ,KC_##k16,KC_##k17,KC_NO   ,KC_NO   }, \
  {KC_##k20,KC_##k21,KC_##k22,KC_##k23,KC_NO   ,KC_NO   ,KC_##k26,KC_##k27,KC_NO   ,KC_NO   }, \
  {KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   }, \
  {KC_##k40,KC_##k41,KC_##k42,KC_##k43,KC_##k44,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   }, \
  {KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_##k54,KC_##k55,KC_##k56,KC_##k57,KC_NO   ,KC_NO   }, \
  {KC_##k60,KC_##k61,KC_##k62,KC_##k63,KC_##k64,KC_NO   ,KC_##k66,KC_##k67,KC_NO   ,KC_NO   }, \
  {KC_NO   ,KC_NO   ,KC_NO   ,KC_##k73,KC_##k74,KC_##k75,KC_##k76,KC_##k77,KC_NO   ,KC_NO   }, \
  {KC_##k80,KC_##k81,KC_##k82,KC_##k83,KC_##k84,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   }, \
  {KC_NO   ,KC_NO   ,KC_NO   ,KC_##k93,KC_##k94,KC_##k95,KC_##k96,KC_##k97,KC_NO   ,KC_NO   }, \
  {KC_##kA0,KC_##kA1,KC_##kA2,KC_##kA3,KC_##kA4,KC_##kA5,KC_##kA6,KC_NO   ,KC_NO   ,KC_NO   }, \
  {KC_NO   ,KC_NO   ,KC_NO   ,KC_##kB3,KC_##kB4,KC_##kB5,KC_##kB6,KC_##kB7,KC_NO   ,KC_NO   }, \
  {KC_##kC0,KC_##kC1,KC_##kC2,KC_##kC3,KC_##kC4,KC_##kC5,KC_##kC6,KC_NO   ,KC_NO   ,KC_NO   }, \
  {KC_NO   ,KC_NO   ,KC_NO   ,KC_##kD3,KC_##kD4,KC_##kD5,KC_##kD6,KC_##kD7,KC_NO   ,KC_NO   }, \
  {KC_##kE0,KC_##kE1,KC_##kE2,KC_##kE3,KC_##kE4,KC_##kE5,KC_##kE6,KC_NO   ,KC_NO   ,KC_NO   }, \
  {KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_##kF4,KC_##kF5,KC_##kF6,KC_##kF7,KC_NO   ,KC_NO   }, \
  }


#if defined(KEYMAP_DVORAK)
#include "keymap_dvorak.h"
#elif defined(KEYMAP_COLEMAK)
#include "keymap_colemak.h"
#elif defined(KEYMAP_WORKMAN)
#include "keymap_workman.h"
#elif defined(KEYMAP_MICRO)
#include "keymap_micro.h"
#elif defined(KEYMAP_CUB)
#include "keymap_cub.h"
#else
// | ESC  | F1   | F2    | F3    | F4   | F5     | F6    | F7   | F8   |
// | EQL  | 1    | 2     | 3     | 4    | 5      |       |      |      |
// | TAB  | Q    | W     | E     | R    | T      |       |      |      |
// | CAPS | A    | S     | D     | F    | G      |       |      |      |
// | LSFT | Z    | X     | C     | V    | B      |       |      |      |
// |      | GRV  | BSLS  | LEFT  | RGHT |        |       |      |      |
// |      |      |       |       |      |        | LCTL  | LALT |      |
// |      |      |       |       |      | /*BSPC | DEL*/ | HOME |      |
// |      |      |       |       |      | BSPC   | DEL   | END  |      |
// |      |      |       |       |      |        |       |      |      |
// | F9   | F10  | F11   | F12   | PSCR | SLCK   | PAUS  | FN0  | FN1  |
// |      |      |       | 6     | 7    | 8      | 9     | 0    | MINS |
// |      |      |       | Y     | U    | I      | O     | P    | BSLS |
// |      |      |       | H     | J    | K      | L     | SCLN | QUOT |
// |      |      |       | N     | M    | COMM   | DOT   | SLSH | RSFT |
// |      |      |       |       | UP   | DOWN   | LBRC  | RBRC |      |
// |      | RGUI | RCTL  |       |      |        |       |      |      |
// |      | PGUP | /*ENT | SPC*/ |      |        |       |      |      |
// |      | PGDN | ENT   | SPC   |      |        |       |      |      |
static const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  KEYMAP(
  // layer 0 : default
  // left hand
  ESC , F1  , F2   , F3   , F4  , F5    , F6   , F7  , F8  ,
  EQL , 1   , 2    , 3    , 4   , 5     ,
  TAB , Q   , W    , E    , R   , T     ,
  CAPS, A   , S    , D    , F   , G     ,
  LSFT, Z   , X    , C    , V   , B     ,
        GRV , BSLS , LEFT , RGHT,
                                          LCTL , LALT,
                                  /*BSPC, DEL*/  HOME,
                                  BSPC  , DEL  , END ,
  
  // right hand
  F9  , F10 , F11  , F12  , PSCR, SLCK  , PAUS , FN0 , FN1 ,
                     6    , 7   , 8     , 9    , 0   , MINS,
                     Y    , U   , I     , O    , P   , BSLS,
                     H    , J   , K     , L    , SCLN, QUOT,
                     N    , M   , COMM  , DOT  , SLSH, RSFT,
                            UP  , DOWN  , LBRC , RBRC,
        RGUI, RCTL ,
        PGUP, /*ENT, SPC*/
        PGDN, ENT  , SPC
  ),
};

/*
 * Fn action definition
 */
const action_t fn_actions[] = {};

#endif


/* translates key to keycode */
#define KEYMAPS_SIZE    (sizeof(keymaps) / sizeof(keymaps[0]))
uint8_t keymap_key_to_keycode(uint8_t layer, keypos_t key)
{
  if (layer < KEYMAPS_SIZE) {
    return keymaps[(layer)][(key.row)][(key.col)];
  } else {
    // fall back to layer 0
    return keymaps[0][(key.row)][(key.col)];
  }
}

/* translates Fn keycode to action */
action_t keymap_fn_to_action(uint8_t keycode)
{
    return fn_actions[FN_INDEX(keycode)];
}
