// | ESC  | F1   | F2     | F3    | F4   | F5    | F6     | F7   | F8   |
// | LGUI | 1    | 2      | 3     | 4    | 5     |        |      |      |
// | TAB  | QUOT | COMM   | DOT   | P    | Y     |        |      |      |
// | EQL  | A    | O      | E     | U    | I     |        |      |      |
// | LSFT | SCLN | Q      | J     | K    | X     |        |      |      |
// |      | GRV  | CAPS   | LEFT  | RGHT |       |        |      |      |
// |      |      |        |       |      |       | LALT   | LGUI |      |
// |      |      |        |       |      | /*ENT | LCTL*/ | HOME |      |
// |      |      |        |       |      | ENT   | LCTL   | END  |      |
// |      |      |        |       |      |       |        |      |      |
// | F9   | F10  | F11    | F12   | DEL  | SLCK  | PAUS   | FN0  | FN1  |
// |      |      |        | 6     | 7    | 8     | 9      | 0    | SLSH |
// |      |      |        | F     | G    | C     | R      | L    | BSLS |
// |      |      |        | D     | H    | T     | N      | S    | MINS |
// |      |      |        | B     | M    | W     | V      | Z    | RSFT |
// |      |      |        |       | UP   | DOWN  | LBRC   | RBRC |      |
// |      | BSPC | RCTL   |       |      |       |        |      |      |
// |      | PGUP | /*RALT | SPC*/ |      |       |        |      |      |
// |      | PGDN | RALT   | SPC   |      |       |        |      |      |
// |      |      |        |       |      |       |        |      |      |
static const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  KEYMAP(
  // layer 0 : default
  // left hand
  ESC , F1  , F2    , F3   , F4  , F5   , F6    , F7  , F8  ,
  LGUI, 1   , 2     , 3    , 4   , 5    ,
  TAB , QUOT, COMM  , DOT  , P   , Y    ,
  EQL , A   , O     , E    , U   , I    ,
  LSFT, SCLN, Q     , J    , K   , X    ,
        GRV , CAPS  , LEFT , RGHT,
                                          LALT  , LGUI,
                                   /*ENT, LCTL*/  HOME,
                                   ENT  , LCTL  , END ,
  // right hand
  F9  , F10 , F11   , F12  , DEL , SLCK , PAUS  , FN0 , FN1 ,
                      6    , 7   , 8    , 9     , 0   , SLSH,
                      F    , G   , C    , R     , L   , BSLS,
                      D    , H   , T    , N     , S   , MINS,
                      B    , M   , W    , V     , Z   , RSFT,
                             UP  , DOWN , LBRC  , RBRC,
        BSPC, RCTL  ,
        PGUP, /*RALT, SPC*/
        PGDN, RALT  , SPC
  ),
  // layer 1: mouse and media
  KEYMAP(
  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
  TRNS, TRNS, BTN1, MS_U, BTN2, WH_U,
  TRNS, TRNS, MS_L, MS_D, MS_R, WH_D,
  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
        TRNS, TRNS, TRNS, TRNS,
                                      TRNS, TRNS,
                                            WHOM,
                                TRNS, TRNS, MYCM,

  // right hand
  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
                    TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
                    VOLU, MPRV, MNXT, TRNS, TRNS, TRNS,
                    VOLD, MSTP, MPLY, TRNS, TRNS, TRNS, // don't use mute it does to work w pulseaudio
                    TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
                          TRNS, TRNS, TRNS, TRNS,
        TRNS, TRNS,
        TRNS,
        TRNS, TRNS, TRNS
  ),
  // layer 2: system, like sleep
  KEYMAP(
  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
        TRNS, TRNS, TRNS, TRNS,
                                      TRNS, TRNS,
                                            TRNS,
                                TRNS, TRNS, TRNS,

  // right hand
  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
                    TRNS, TRNS, TRNS, TRNS, TRNS, SLEP,
                    TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
                    TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
                    TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
                          TRNS, TRNS, TRNS, TRNS,
        TRNS, TRNS,
        TRNS,
        TRNS, TRNS, TRNS
  ),
};

const action_t fn_actions[] = {
    ACTION_LAYER_TOGGLE(1),
    ACTION_LAYER_MOMENTARY(2),
};
