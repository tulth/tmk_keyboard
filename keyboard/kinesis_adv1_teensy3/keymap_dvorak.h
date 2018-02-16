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
};

const action_t fn_actions[] = {};
