
#include QMK_KEYBOARD_H

// Layers
#define _QW			    0
#define _LOWER		  1
#define _RAISE		  2
#define _FN			    3
#define _LWL0 		  4
#define _LWL1		    5

// Macro keycodes
  enum custom_keycodes {
  INSR = SAFE_RANGE,
  DELR,
  INSC,
  DELC
};

typedef struct {
  bool is_press_action;
  int state;
} xtap;

enum {
  SINGLE_TAP =      1,
  SINGLE_HOLD =     2,
  DOUBLE_TAP =      3,
  DOUBLE_HOLD =     4,
  DOUBLE_SINGLE_TAP = 5, // Send two single taps
  TRIPLE_TAP =      6,
  TRIPLE_HOLD =     7
};

// Tap dance enums
enum {
  // Simple 
  LCRLY = 0,
  RCRLY,
  PIPE,
  TILDE,
  // Complex
  MAKE1,
  MAKE2,
  EMAIL,
  LBKTS,
  RBKTS
};

// Tap dance dance states
// To activate SINGLE_HOLD, you will need to hold for 200ms first.
// This tap dance favors keys that are used frequently in typing like 'f'
int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    //If count = 1, and it has been interrupted - it doesn't matter if it is pressed or not: Send SINGLE_TAP
    if (state->interrupted) {
      //     if (!state->pressed) return SINGLE_TAP;
      //need "permissive hold" here.
      //     else return SINsGLE_HOLD;
      //If the interrupting key is released before the tap-dance key, then it is a single HOLD
      //However, if the tap-dance key is released first, then it is a single TAP
      //But how to get access to the state of the interrupting key????
      return SINGLE_TAP;
    }
    else {
      if (!state->pressed) return SINGLE_TAP;
      else return SINGLE_HOLD;
    }
  }
  // If count = 2, and it has been interrupted - assume that user is trying to type the letter associated
  // with single tap.
  else if (state->count == 2) {
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  else if ((state->count == 3) && ((state->interrupted) || (!state->pressed))) return TRIPLE_TAP;
  else if (state->count == 3) return TRIPLE_HOLD;
  else return 8; //magic number. At some point this method will expand to work for more presses
}

// This works well if you want this key to work as a "fast modifier". It favors being held over being tapped.
int hold_cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted) {
      if (!state->pressed) return SINGLE_TAP;
      else return SINGLE_HOLD;
    }
    else {
      if (!state->pressed) return SINGLE_TAP;
      else return SINGLE_HOLD;
    }
  }
  // If count = 2, and it has been interrupted - assume that user is trying to type the letter associated
  // with single tap.
  else if (state->count == 2) {
    if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  else if (state->count == 3) {
    if (!state->pressed) return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return 8; // Magic number. At some point this method will expand to work for more presses
}

// For complex tap dances. Put it here so it can be used in any keymap
void make_therick48_finished (qk_tap_dance_state_t *state, void *user_data);
void make_therick48_reset (qk_tap_dance_state_t *state, void *user_data);

void make_nori_finished (qk_tap_dance_state_t *state, void *user_data);
void make_nori_reset (qk_tap_dance_state_t *state, void *user_data);

void email_finished (qk_tap_dance_state_t *state, void *user_data);
void email_reset (qk_tap_dance_state_t *state, void *user_data);

void lbkts_finished (qk_tap_dance_state_t *state, void *user_data);
void lbkts_reset (qk_tap_dance_state_t *state, void *user_data);

void rbkts_finished (qk_tap_dance_state_t *state, void *user_data);
void rbkts_reset (qk_tap_dance_state_t *state, void *user_data);

// Tap dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [PIPE]    = ACTION_TAP_DANCE_DOUBLE(KC_BSLS, KC_PIPE),
  [TILDE]   = ACTION_TAP_DANCE_DOUBLE(KC_GRAVE, KC_TILDE),
  [MAKE1]    = ACTION_TAP_DANCE_FN_ADVANCED(NULL, make_therick48_finished, make_therick48_reset),
  [MAKE2]    = ACTION_TAP_DANCE_FN_ADVANCED(NULL, make_nori_finished, make_nori_reset),
  [EMAIL]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, email_finished, email_reset),
  [LBKTS]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lbkts_finished, lbkts_reset),
  [RBKTS]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rbkts_finished, rbkts_reset),
};

// Readability keycodes
#define _______		  KC_TRNS

// Layer codes
#define LOWER 		  MO(_LOWER)
#define RAISE 		  MO(_RAISE)
#define FN 		  	  MO(_FN)

#define LWR_BS 		  LT(_LOWER, KC_BSPC)
#define RSE_SPC 	  LT(_RAISE, KC_SPC)
#define FN_TAB		  LT(_FN, KC_TAB)
#define FN_ESC		  LT(_FN, KC_ESC)
#define LWL0_TAB	  LT(_LWL0, KC_TAB)
#define LWL0_ESC	  LT(_LWL0, KC_ESC)
#define LWL0_SPC 	  LT(_LWL0, KC_SPC)
#define LWL1_PSLS	  LT(_LWL1, KC_PSLS)
#define LWL1_PENT	  LT(_LWL1, KC_PENT)
#define LWL1_BS		  LT(_LWL1, KC_BSPC)
#define LWR_P0      LT(_LWL1, KC_P0)

// Dual key codes
#define CTL_A 		  CTL_T(KC_A)
#define CTL_F 		  CTL_T(KC_F)
#define CTL_J		    CTL_T(KC_J)
#define CTL_Z		    CTL_T(KC_Z)
#define CTL_LEFT	  CTL_T(KC_LEFT)
#define CTL_RGHT 	  CTL_T(KC_RIGHT)
#define CTL_HOME	  CTL_T(KC_HOME)
#define CTL_END		  CTL_T(KC_END)
#define CTL_SLS		  CTL_T(KC_SLSH)

#define SFT_S 		  SFT_T(KC_S)
#define SFT_X		    SFT_T(KC_X)
#define SFT_SPC		  SFT_T(KC_SPC)
#define SFT_ENT		  SFT_T(KC_ENT)
#define SFT_DOT		  SFT_T(KC_DOT)
#define SFT_QUOT	  SFT_T(KC_QUOT)
#define SFT_DOWN	  SFT_T(KC_DOWN)
#define SFT_UP 		  SFT_T(KC_UP)
#define SFT_PGDN	  SFT_T(KC_PGDN)
#define SFT_PGUP	  SFT_T(KC_PGUP)
#define SFT_CAPS	  SFT_T(KC_CAPSLOCK)

#define ALT_LEFT    ALT_T(KC_LEFT)
#define ALT_RGHT    ALT_T(KC_RIGHT)
#define ALT_UP      ALT_T(KC_UP)

#define WIN_BS		  LGUI_T(KC_BSPC)

#define SA_BS 		  MT(MOD_LSFT | MOD_LALT, KC_BSPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QW QWERTY
  .-----------------------------------------------------------------------------------------------------------------------------------------------.    .-----------------------------------------------.
  |    Esc    |     Q     |     W     |     E     |     R     |     T     |     Y     |     U     |     I     |     O     |     P     |    Del    |    |     7     |     8     |     9     |     -     | 
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|    |-----------+-----------+-----------+-----------|
  |  Fn Tab   |     A     |     S     |     D     |     F     |     G     |     H     |     J     |     K     |     L     |     ;     |     '     |    |     4     |     5     |     6     |     +     |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|    |-----------+-----------+-----------+-----------|
  |   Shift   |     Z     |     X     |     C     |     V     |     B     |     N     |     M     |     ,     |     .     |     /     |   Enter   |    |     3     |     2     |     1     |   Enter   |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|    |-----------+-----------+-----------+-----------|
  |    Ctrl   |   Shift   |    GUI    |    Alt    |  Lwr BS   |    BS     |   Space   |  Rse Spc  |   Left    |   Down    |     Up    |   Right   |    |     0     |     .     |     *     |     /     |
  '-----------------------------------------------------------------------------------------------------------------------------------------------'    '-----------------------------------------------'
*/

  [_QW] = LAYOUT_ortho_4x12_4x4(
    KC_ESC,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_DEL,          KC_P7,     KC_P8,      KC_P9,      KC_PMNS,
    FN_TAB,     CTL_A,      SFT_S,      KC_D,       CTL_F,      KC_G,       KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    SFT_QUOT,        KC_P4,     KC_P5,      KC_P6,      KC_PPLS,
    KC_LSFT,    CTL_Z,      SFT_X,      KC_C,       KC_V,       KC_B,       KC_N,       KC_M,       KC_COMM,    KC_DOT,     CTL_SLS,    SFT_ENT,         KC_P1,     KC_P2,      KC_P3,      KC_PENT,
    KC_LCTL,    KC_LSFT,    KC_LGUI,    KC_LALT,    LWR_BS,     WIN_BS,     SFT_SPC,    RSE_SPC,    CTL_LEFT,   SFT_DOWN,   SFT_UP,     CTL_RGHT,        LWR_P0,    KC_PDOT,    KC_PAST,    LWL1_PSLS
  ),

/* Lower
  .-----------------------------------------------------------------------------------------------------------------------------------------------.    .-----------------------------------------------.
  |           |     (     |     )     |     -     |     =     |    ***    |    ***    |    BS     |     7     |     8     |     9     |     -     |    |    BS     |     /     |     *     |    Del    |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|    |-----------+-----------+-----------+-----------|
  |   LWL0    |   Home    |   Pg Dn   |   Pg Up   |    End    |  BS LWL1  |    F4     |    F2     |     4     |     5     |     6     |     +     |    |   Left    |   Down    |     Up    |   Right   |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|    |-----------+-----------+-----------+-----------|
  |           |   Left    |    Down   |    Up     |   Right   |    ***    |   Raise   |   Calc    |     1     |     2     |     3     |   Enter   |    |   Pg Dn   |   Pg Up   |    End    |           |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|    |-----------+-----------+-----------+-----------|
  |           |           |           |           |   Lower   |           |           |   LWL0    |     0     |     .     |     *     |   / LWL1  |    |           |           |           |   LWL1    |
  '-----------------------------------------------------------------------------------------------------------------------------------------------'    '-----------------------------------------------'
*/

  [_LOWER] = LAYOUT_ortho_4x12_4x4(
    _______,    KC_LPRN,    KC_RPRN,    KC_MINS,    KC_EQL,     KC_NO,      KC_NO,      KC_BSPC,     KC_P7,     KC_P8,      KC_P9,      KC_PMNS,         KC_BSPC,    KC_PSLS,    KC_PAST,    KC_DEL,
    LWL0_TAB,   CTL_HOME,   SFT_PGDN,   SFT_PGUP,   CTL_END,    LWL1_BS,    KC_F4,      KC_F2,       KC_P4,     KC_P5,      KC_P6,      KC_PPLS,         CTL_LEFT,   SFT_DOWN,   SFT_UP,     KC_RIGHT,
    _______,    ALT_LEFT,   SFT_DOWN,   SFT_UP,     ALT_RGHT,   KC_NO,      MO(2),      KC_CALC,     KC_P1,     KC_P2,      KC_P3,      KC_PENT,         CTL_HOME,   SFT_PGDN,   SFT_PGUP,   CTL_END,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    LWL0_SPC,    KC_P0,     KC_PDOT,    KC_PAST,    LWL1_PSLS,       _______,    _______,    _______,    _______
  ),

    /* LWL0
      .-----------------------------------------------------------------------------------------------------------------------------------------------.    .-----------------------------------------------.
      |           |           |    F13    |    F14    |           |           |           |           |    BS     |     /     |     *     |    Del    |    |           |           |           |           |
      |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|    |-----------+-----------+-----------+-----------|
      |   LWL0    |   Ctrl    |   Shift   |    Del    |    F2     |           |           |           |   Left    |   Down    |     Up    |   Right   |    |           |           |           |           |
      |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|    |-----------+-----------+-----------+-----------|
      |           |           |           |           |           |           |           |           |   Home    |   Pg Dn   |   Pg Up   |    End    |    |           |           |           |           |
      |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|    |-----------+-----------+-----------+-----------|
      |           |           |           |           |           |           |           |   LWL0    |           |           |           |   LWL1    |    |           |           |           |           |
      '-----------------------------------------------------------------------------------------------------------------------------------------------'    '-----------------------------------------------'
    */

      [_LWL0] = LAYOUT_ortho_4x12_4x4(
        _______,    _______,    KC_F13,     KC_F14,     _______,    _______,    _______,    _______,    KC_BSPC,    KC_PSLS,    KC_PAST,    KC_DEL,          _______,    _______,    _______,    _______,
        _______,    KC_LCTL,    KC_LSFT,    KC_DEL,     KC_F2,      _______,    _______,    _______,    CTL_LEFT,   SFT_DOWN,   SFT_UP,     KC_RIGHT,        _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    CTL_HOME,   SFT_PGDN,   SFT_PGUP,   CTL_END,         _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,    _______,    _______,    TG(1),	    _______,    _______,    _______,    _______,    _______,         _______,    _______,    _______,    _______
      ),

    /* LWL1
      .-----------------------------------------------------------------------------------------------------------------------------------------------.    .-----------------------------------------------.
      |    F1     |    F2     |    F3     |    F4     |    F5     |    F6     |    F7     |    F8     |    F9     |   F10     |   F11     |   F12     |    |           |           |           |           |
      |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|    |-----------+-----------+-----------+-----------|
      |   RESET   |           |           |           |           |   LWL1    |           |           |     $     |     ,     |     %     |           |    |           |           |           |           |
      |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|    |-----------+-----------+-----------+-----------|
      |           |           |           |           |           |           |           |           |           |           |           |           |    |           |           |           |           |
      |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|    |-----------+-----------+-----------+-----------|
      |           |           |           |           |           |           |           |           |           |           |  NumLock  |   LWL1    |    |           |           |           |           |
      '-----------------------------------------------------------------------------------------------------------------------------------------------'    '-----------------------------------------------'
    */

      [_LWL1] = LAYOUT_ortho_4x12_4x4(
        KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,     KC_F12,          _______,    _______,    _______,    _______,
        RESET,      _______,    _______,    _______,    _______,    _______,    _______,    _______,    KC_DLR,     KC_COMM,    KC_PERC,    _______,         _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,         _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    KC_NLCK,    _______,         _______,    _______,    _______,    _______
      ),

/* Raise
  .-----------------------------------------------------------------------------------------------------------------------------------------------.    .-----------------------------------------------.
  |     1     |     2     |     3     |     4     |     5     |     6     |     7     |     8     |     9     |     0     |     -     |     =     |    |           |           |           |           |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|    |-----------+-----------+-----------+-----------|
  |     !     |     @     |     #     |     $     |     %     |     ^     |     &     |     *     |     (     |     )     |     _     |     +     |    |           |           |           |           |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|    |-----------+-----------+-----------+-----------|
  |   Caps    |           |     `     |           |           |           |  Insert   |   Pr Scr  |     [     |     ]     |     \     |           |    |           |           |           |           |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|    |-----------+-----------+-----------+-----------|
  |           |           |           |           |           |           |  TG(Lwr)  |   Raise   |   Play    |   Vol-    |   Vol+    |   Mute    |    |           |           |           |           |
  '-----------------------------------------------------------------------------------------------------------------------------------------------'    '-----------------------------------------------'
*/

  [_RAISE] = LAYOUT_ortho_4x12_4x4(
    KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_MINS,    KC_EQL,          _______,    _______,    _______,    _______,
    KC_EXLM,    KC_AT,      KC_HASH,    KC_DLR,     KC_PERC,    KC_CIRC,    KC_AMPR,    KC_ASTR,    KC_LPRN,    KC_RPRN,    KC_UNDS,    KC_PLUS,         _______,    _______,    _______,    _______,
    SFT_CAPS,   _______,    KC_GRAVE,   _______,    _______,    _______,    KC_INS,     KC_PSCR,    KC_LBRC,    KC_RBRC,    KC_BSLS,    _______,         _______,    _______,    _______,    _______,
    _______,    _______,    _______,    _______,    _______,    _______,    TG(1),      _______,    KC_MPLY,    KC_VOLD,    KC_VOLU,    KC_MUTE,         _______,    _______,    _______,    _______
  ),

/* FN
  .-----------------------------------------------------------------------------------------------------------------------------------------------.    .-----------------------------------------------.
  |    F13    |    F14    |    F15    |    F16    |    F17    |    F18    |    F19    |    F20    |    F21    |   F22     |   F23     |    BS     |    |           |           |           |           |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|    |-----------+-----------+-----------+-----------|
  |    Fn     |   Ctrl    |   Shift   |    Del    |    F2     |           |    F2     |   Left    |    Down   |    Up     |   Right   |   Enter   |    |           |           |           |           |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|    |-----------+-----------+-----------+-----------|
  |           |           |           |           |           |           |           |   Home    |   Pg Dn   |   Pg Up   |    End    |           |    |           |           |           |           |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|    |-----------+-----------+-----------+-----------|
  |           |           |           |           |   Enter   |           |           |           |   Home    |   Pg Dn   |   Pg Up   |    End    |    |           |           |           |           |
  '-----------------------------------------------------------------------------------------------------------------------------------------------'    '-----------------------------------------------'
*/

  [_FN] = LAYOUT_ortho_4x12_4x4(
    KC_F13,     KC_F14,     KC_F15,     KC_F16,     KC_F17,     KC_F18,     KC_F19,     KC_F20,     KC_F21,     KC_F22,     KC_F23,     KC_BSPC,         _______,    _______,    _______,    _______,
    _______,    KC_LCTL,    KC_LSFT,    KC_DEL,     KC_F2,      _______,    KC_F2,      ALT_LEFT,   KC_DOWN,    KC_UP,      ALT_RGHT,   KC_ENT,          _______,    _______,    _______,    _______,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    CTL_HOME,   SFT_PGDN,   SFT_PGUP,   CTL_END,    _______,         _______,    _______,    _______,    _______,
    _______,    _______,    _______,    _______,    KC_ENT,     _______,    _______,    _______,    KC_HOME,    KC_PGDN,    KC_PGUP,    KC_END,          _______,    _______,    _______,    _______
  )

};


const uint16_t PROGMEM fn_actions[] = {

};


/*uint16_t get_tapping_term(uint16_t keycode) {
  switch (keycode) {
    case CTL_T(KC_A):
 	 return 500;
	case SFT_T(KC_S):
	 return 500;
    default:
      return TAPPING_TERM;
  }
}*/

// Macros
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case INSR: // Insert row in Sheets
      if (record->event.pressed) { // when keycode is pressed
        SEND_STRING(SS_LCTL(SS_LALT("i") SS_DELAY(250)) "r"); // Ctrl+Alt+i, r
      } else { // when keycode is released
      }
      break;

    case DELR: // Delete row in Sheets
      if (record->event.pressed) { // when keycode is pressed
        SEND_STRING(SS_LCTL(SS_LALT("e") SS_DELAY(250)) "d"); // Ctrl+Alt+e, d
      } else { // when keycode is released
      }
      break;

    case INSC: // Insert column in Sheets
      if (record->event.pressed) { // when keycode is pressed
        SEND_STRING(SS_LCTL(SS_LALT("i") SS_DELAY(250)) "c"); // Ctrl+Alt+i, c
      } else { // when keycode is released
      }
      break;    

    case DELC: // Delete column in Sheets
      if (record->event.pressed) { // when keycode is pressed
        SEND_STRING(SS_LCTL(SS_LALT("e") SS_DELAY(250)) "e"); // Ctrl+Alt+e, e
      } else { // when keycode is released
      }
      break;
  }
  return true;
};

// Tap dance stuff
static xtap make_therick48_state = {
  .is_press_action = true,
  .state = 0
};

static xtap make_nori_state = {
  .is_press_action = true,
  .state = 0
};

static xtap email_state = {
  .is_press_action = true,
  .state = 0
};

static xtap lbkts_state = {
  .is_press_action = true,
  .state = 0
};

static xtap rbkts_state = {
  .is_press_action = true,
  .state = 0
};

//*************** MAKE *******************//
void make_therick48_finished (qk_tap_dance_state_t *state, void *user_data) {
  make_therick48_state.state = cur_dance(state); // Use the dance that favors being held
  switch (make_therick48_state.state) {
    case SINGLE_TAP: SEND_STRING("make therick48:default:dfu"); break; // send therick48 default make code
    case DOUBLE_TAP: SEND_STRING("make therick48:macos:avrdude"); break; // send therick48 macos make code
  }
}

void make_therick48_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (make_therick48_state.state) {
    case SINGLE_TAP: ; break;
    case DOUBLE_TAP: ; break;
  }
  make_therick48_state.state = 0;
}

void make_nori_finished (qk_tap_dance_state_t *state, void *user_data) {
  make_nori_state.state = cur_dance(state); // Use the dance that favors being held
  switch (make_nori_state.state) {
    case SINGLE_TAP: SEND_STRING("make nori:default:dfu"); break; // send nori default make code
    case DOUBLE_TAP: SEND_STRING("make nori:macos:avrdude"); break; // send nori macos make code
  }
}

void make_nori_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (make_nori_state.state) {
    case SINGLE_TAP: ; break;
    case DOUBLE_TAP: ; break;
  }
  make_nori_state.state = 0;
}
//*************** MAKE *******************//

//*************** EMAIL *******************//
void email_finished (qk_tap_dance_state_t *state, void *user_data) {
  email_state.state = cur_dance(state); // Use the dance that favors being held
  switch (email_state.state) {
    case SINGLE_TAP: register_code(KC_LSFT); register_code(KC_2); break; //send @
    case DOUBLE_TAP: SEND_STRING("rick.c.kremer@gmail.com"); break; //send email address
    case TRIPLE_TAP: SEND_STRING("rkremer@bushelpowered.com"); //send work email
  }
}

void email_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (email_state.state) {
    case SINGLE_TAP: unregister_code(KC_LSFT); unregister_code(KC_2); break; //unregister @
    case DOUBLE_TAP: ; break;
    case TRIPLE_TAP: ; break;
  }
  email_state.state = 0;
}
//*************** EMAIL *******************//

//************* BRACKETS ******************//
// Left brackets 
void lbkts_finished (qk_tap_dance_state_t *state, void *user_data) {
  lbkts_state.state = cur_dance(state); // Use the dance that favors being held
  switch (lbkts_state.state) {
    case SINGLE_TAP: register_code(KC_LSFT); register_code(KC_9); break; // send (
    case DOUBLE_TAP: register_code(KC_LBRC); break; // send [
    case TRIPLE_TAP: register_code(KC_LSFT); register_code(KC_LBRC); // send {
  }
}

void lbkts_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (lbkts_state.state) {
    case SINGLE_TAP: unregister_code(KC_LSFT); unregister_code(KC_9); break; // unregister (
    case DOUBLE_TAP: unregister_code(KC_LBRC); break; // unregister [
    case TRIPLE_TAP: unregister_code(KC_LSFT); unregister_code(KC_LBRC); // unregsister {
  }
  lbkts_state.state = 0;
}

// Right brackets
void rbkts_finished (qk_tap_dance_state_t *state, void *user_data) {
  rbkts_state.state = cur_dance(state); // Use the dance that favors being held
  switch (rbkts_state.state) {
    case SINGLE_TAP: register_code(KC_LSFT); register_code(KC_0); break; // send (
    case DOUBLE_TAP: register_code(KC_RBRC); break; // send [
    case TRIPLE_TAP: register_code(KC_LSFT); register_code(KC_RBRC); // send {
  }
}

void rbkts_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (rbkts_state.state) {
    case SINGLE_TAP: unregister_code(KC_LSFT); unregister_code(KC_0); break; // unregister (
    case DOUBLE_TAP: unregister_code(KC_RBRC); break; // unregister [
    case TRIPLE_TAP: unregister_code(KC_LSFT); unregister_code(KC_RBRC); // unregsister {
  }
  rbkts_state.state = 0;
}
//************* BRACKETS ******************//

// Encoder
void encoder_update_user(uint8_t index, bool clockwise) {
  // left encoder
  if (index == 0) {
    switch(biton32(layer_state)){
      case 0: // Base layer
      if (clockwise) { // Volume control
        tap_code(KC_VOLD);
      } else {
        tap_code(KC_VOLU);
      }
      break;
    }
  }
}