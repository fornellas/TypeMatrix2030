#include <avr/pgmspace.h>

#include "../Keyboard.h"
#include "extraKeys.h"

#include <LUFA/Drivers/USB/USB.h>

const uint16_t PROGMEM us_dvorak[NUM_KEYS]={
  // 0 Q
  HID_KEYBOARD_SC_APOSTROPHE_AND_QUOTE,
  // 1 W
  HID_KEYBOARD_SC_COMMA_AND_LESS_THAN_SIGN,
  // 2 E
  HID_KEYBOARD_SC_DOT_AND_GREATER_THAN_SIGN,
  // 3 R
  HID_KEYBOARD_SC_P,
  // 4 U
  HID_KEYBOARD_SC_G,
  // 5 I
  HID_KEYBOARD_SC_C,
  // 6 O/Tab
  HID_KEYBOARD_SC_R,
  // 7 P/
  HID_KEYBOARD_SC_L,
  // 8 Ply/CX
  KEY_PLAY,
  // 9 Tab
  HID_KEYBOARD_SC_TAB,
  // 10 CapsLock/Clear
  HID_KEYBOARD_SC_CAPS_LOCK,
  // 11 F3
  HID_KEYBOARD_SC_F3,
  // 12 T
  HID_KEYBOARD_SC_Y,
  // 13 Y
  HID_KEYBOARD_SC_F,
  // 14 ]}-
  HID_KEYBOARD_SC_EQUAL_AND_PLUS,
  // 15 F7/Pwr
  HID_KEYBOARD_SC_F7,
  // 16 [{*
  HID_KEYBOARD_SC_SLASH_AND_QUESTION_MARK,
  // 17 Bs/V+
  HID_KEYBOARD_SC_BACKSPACE,
  // 18 Calc
  KEY_CALC,
  // 19 LSft
  HID_KEYBOARD_SC_LEFT_SHIFT,
  // 20 AT/CV
  HID_KEYBOARD_SC_LEFT_ALT,
  // 21 Start
  HID_KEYBOARD_SC_LEFT_GUI,
  // 22 1!
  HID_KEYBOARD_SC_1_AND_EXCLAMATION,
  // 23 2@
  HID_KEYBOARD_SC_2_AND_AT,
  // 24 3#
  HID_KEYBOARD_SC_3_AND_HASHMARK,
  // 25 4$
  HID_KEYBOARD_SC_4_AND_DOLLAR,
  // 26 7&
  HID_KEYBOARD_SC_7_AND_AMPERSAND,
  // 27 8*
  HID_KEYBOARD_SC_8_AND_ASTERISK,
  // 28 9(
  HID_KEYBOARD_SC_9_AND_OPENING_PARENTHESIS,
  // 29 0)
  HID_KEYBOARD_SC_0_AND_CLOSING_PARENTHESIS,
  // 30 F10/PSc
  HID_KEYBOARD_SC_F10,
  // 31 End/3
  HID_KEYBOARD_SC_END,
  // 32 PDwn/Nx
  HID_KEYBOARD_SC_PAGE_DOWN,
  // 33 F5
  HID_KEYBOARD_SC_F5,
  // 34 Fn
  NO_KEY,
  // 35 A
  HID_KEYBOARD_SC_A,
  // 36 `~
  HID_KEYBOARD_SC_GRAVE_ACCENT_AND_TILDE,
  // 37 Esc
  HID_KEYBOARD_SC_ESCAPE,
  // 38 Z
  HID_KEYBOARD_SC_SEMICOLON_AND_COLON,
  // 39 S
  HID_KEYBOARD_SC_O,
  // 40 D
  HID_KEYBOARD_SC_E,
  // 41 F
  HID_KEYBOARD_SC_U,
  // 42 J/Up
  HID_KEYBOARD_SC_H,
  // 43 K/End
  HID_KEYBOARD_SC_T,
  // 44 L/7
  HID_KEYBOARD_SC_N,
  // 45 ;:8
  HID_KEYBOARD_SC_S,
  // 46 \|6
  HID_KEYBOARD_SC_BACKSLASH_AND_PIPE,
  // 47 www/Bs
  NO_KEY, // FIXME
  // 48 RSft/+
  HID_KEYBOARD_SC_RIGHT_SHIFT,
  // 49 Dsk/Pv
  NO_KEY,
  // 50 F1/Dvk
  HID_KEYBOARD_SC_F1,
  // 51 F2
  HID_KEYBOARD_SC_F2,
  // 52 5%
  HID_KEYBOARD_SC_5_AND_PERCENTAGE,
  // 53 6^
  HID_KEYBOARD_SC_6_AND_CARET,
  // 54 =+
  HID_KEYBOARD_SC_CLOSING_BRACKET_AND_CLOSING_BRACE,
  // 55 F8/Slp
  HID_KEYBOARD_SC_F8,
  // 56 -_
  HID_KEYBOARD_SC_OPENING_BRACKET_AND_OPENING_BRACE,
  // 57 F9/Wke
  HID_KEYBOARD_SC_F9,
  // 58 Home/1
  HID_KEYBOARD_SC_HOME,
  // 59 PUp/Bck
  HID_KEYBOARD_SC_PAGE_UP,
  // 60 LCtrl
  HID_KEYBOARD_SC_LEFT_CONTROL,
  // 61 Mail/BackTab
  NO_KEY, // FIXME
  // 62 Del/Ins
  HID_KEYBOARD_SC_DELETE,
  // 63 F4
  HID_KEYBOARD_SC_F4,
  // 64 G
  HID_KEYBOARD_SC_I,
  // 65 H/Home
  HID_KEYBOARD_SC_D,
  // 66 F6/Ejct
  HID_KEYBOARD_SC_F6,
  // 67 '"9
  HID_KEYBOARD_SC_MINUS_AND_UNDERSCORE,
  // 68 F11/SLk
  HID_KEYBOARD_SC_F11,
  // 69 Up/2
  HID_KEYBOARD_SC_UP_ARROW,
  // 70 LAlt
  HID_KEYBOARD_SC_LEFT_ALT,
  // 71 Spc/Mte
  HID_KEYBOARD_SC_SPACE,
  // 72 X
  HID_KEYBOARD_SC_Q,
  // 73 C
  HID_KEYBOARD_SC_J,
  // 74 V
  HID_KEYBOARD_SC_K,
  // 75 M/Dwn
  HID_KEYBOARD_SC_M,
  // 76 ,</Rgt
  HID_KEYBOARD_SC_W,
  // 77 .>4
  HID_KEYBOARD_SC_V,
  // 78 Ret/V-
  HID_KEYBOARD_SC_ENTER,
  // 79 RCtl/Ret
  HID_KEYBOARD_SC_RIGHT_CONTROL,
  // 80 NLock
  HID_KEYBOARD_SC_NUM_LOCK,
  // 81 B
  HID_KEYBOARD_SC_X,
  // 82 N/Left
  HID_KEYBOARD_SC_B,
  // 83 Menu/CC
  HID_KEYBOARD_SC_APPLICATION,
  // 84 /?5
  HID_KEYBOARD_SC_Z,
  // 85 F12/Pse
  HID_KEYBOARD_SC_F12,
  // 86 Left/0
  HID_KEYBOARD_SC_LEFT_ARROW,
  // 87 Rght/.
  HID_KEYBOARD_SC_RIGHT_ARROW,
  // 88 RAlt/Nx
  HID_KEYBOARD_SC_RIGHT_ALT,
  // 89 Dwn/00
  HID_KEYBOARD_SC_DOWN_ARROW, 
  };

const uint16_t PROGMEM us_dvorak_fn[NUM_KEYS]={
  // 0 Q
  HID_KEYBOARD_SC_APOSTROPHE_AND_QUOTE,
  // 1 W
  HID_KEYBOARD_SC_COMMA_AND_LESS_THAN_SIGN,
  // 2 E
  HID_KEYBOARD_SC_DOT_AND_GREATER_THAN_SIGN,
  // 3 R
  HID_KEYBOARD_SC_P,
  // 4 U
  HID_KEYBOARD_SC_G,
  // 5 I
  HID_KEYBOARD_SC_C,
  // 6 O/Tab
  HID_KEYBOARD_SC_TAB,
  // 7 P/
  HID_KEYBOARD_SC_KEYPAD_SLASH,
  // 8 Ply/CX
  NO_KEY,
  // 9 Tab
  HID_KEYBOARD_SC_TAB,
  // 10 CapsLock/Clear
  HID_KEYBOARD_SC_ERROR_ROLLOVER,
  // 11 F3
  HID_KEYBOARD_SC_F3,
  // 12 T
  HID_KEYBOARD_SC_Y,
  // 13 Y
  HID_KEYBOARD_SC_HOME,
  // 14 ]}-
  HID_KEYBOARD_SC_KEYPAD_MINUS,
  // 15 F7/Pwr
  HID_KEYBOARD_SC_POWER,
  // 16 [{*
  HID_KEYBOARD_SC_KEYPAD_ASTERISK,
  // 17 Bs/V+
  HID_KEYBOARD_SC_VOLUME_UP,
  // 18 Calc
  KEY_CALC,
  // 19 LSft
  HID_KEYBOARD_SC_LEFT_SHIFT,
  // 20 AT/CV
  NO_KEY,
  // 21 Start
  HID_KEYBOARD_SC_LEFT_GUI,
  // 22 1!
  HID_KEYBOARD_SC_1_AND_EXCLAMATION,
  // 23 2@
  HID_KEYBOARD_SC_2_AND_AT,
  // 24 3#
  HID_KEYBOARD_SC_3_AND_HASHMARK,
  // 25 4$
  HID_KEYBOARD_SC_4_AND_DOLLAR,
  // 26 7&
  HID_KEYBOARD_SC_7_AND_AMPERSAND,
  // 27 8*
  HID_KEYBOARD_SC_8_AND_ASTERISK,
  // 28 9(
  HID_KEYBOARD_SC_9_AND_OPENING_PARENTHESIS,
  // 29 0)
  HID_KEYBOARD_SC_0_AND_CLOSING_PARENTHESIS,
  // 30 F10/PSc
  HID_KEYBOARD_SC_PRINT_SCREEN,
  // 31 End/3
  HID_KEYBOARD_SC_KEYPAD_3_AND_PAGE_DOWN,
  // 32 PDwn/Nx
  KEY_BROWSER_FORWARD,
  // 33 F5
  HID_KEYBOARD_SC_F5,
  // 34 Fn
  NO_KEY,
  // 35 A
  HID_KEYBOARD_SC_A,
  // 36 `~
  HID_KEYBOARD_SC_GRAVE_ACCENT_AND_TILDE,
  // 37 Esc
  HID_KEYBOARD_SC_ESCAPE,
  // 38 Z
  HID_KEYBOARD_SC_SEMICOLON_AND_COLON,
  // 39 S
  HID_KEYBOARD_SC_O,
  // 40 D
  HID_KEYBOARD_SC_E,
  // 41 F
  HID_KEYBOARD_SC_U,
  // 42 J/Up
  HID_KEYBOARD_SC_UP_ARROW,
  // 43 K/End
  HID_KEYBOARD_SC_END,
  // 44 L/7
  HID_KEYBOARD_SC_KEYPAD_7_AND_HOME,
  // 45 ;:8
  HID_KEYBOARD_SC_KEYPAD_8_AND_UP_ARROW,
  // 46 \|6
  HID_KEYBOARD_SC_KEYPAD_6_AND_RIGHT_ARROW,
  // 47 www/Bs
  HID_KEYBOARD_SC_KEYPAD_BACKSPACE,
  // 48 RSft/+
  HID_KEYBOARD_SC_KEYPAD_PLUS,
  // 49 Dsk/Pv
  KEY_MEDIA_PREVIOUS,
  // 50 F1/Dvk
  NO_KEY,
  // 51 F2
  HID_KEYBOARD_SC_F2,
  // 52 5%
  HID_KEYBOARD_SC_5_AND_PERCENTAGE,
  // 53 6^
  HID_KEYBOARD_SC_6_AND_CARET,
  // 54 =+
  HID_KEYBOARD_SC_EQUAL_AND_PLUS,
  // 55 F8/Slp
  KEY_SLEEP,
  // 56 -_
  HID_KEYBOARD_SC_MINUS_AND_UNDERSCORE,
  // 57 F9/Wke
  NO_KEY,
  // 58 Home/1
  HID_KEYBOARD_SC_KEYPAD_1_AND_END,
  // 59 PUp/Bck
  KEY_BROWSER_BACK,
  // 60 LCtrl
  HID_KEYBOARD_SC_LEFT_CONTROL,
  // 61 Mail/BackTab
  NO_KEY, // FIXME
  // 62 Del/Ins
  HID_KEYBOARD_SC_INSERT,
  // 63 F4
  HID_KEYBOARD_SC_F4,
  // 64 G
  HID_KEYBOARD_SC_I,
  // 65 H/Home
  HID_KEYBOARD_SC_HOME,
  // 66 F6/Ejct
  KEY_EJECT,
  // 67 '"9
  HID_KEYBOARD_SC_KEYPAD_9_AND_PAGE_UP,
  // 68 F11/SLk
  HID_KEYBOARD_SC_SCROLL_LOCK,
  // 69 Up/2
  HID_KEYBOARD_SC_KEYPAD_2_AND_DOWN_ARROW,
  // 70 LAlt
  HID_KEYBOARD_SC_LEFT_ALT,
  // 71 Spc/Mte
  HID_KEYBOARD_SC_MUTE,
  // 72 X
  HID_KEYBOARD_SC_Q,
  // 73 C
  HID_KEYBOARD_SC_J,
  // 74 V
  HID_KEYBOARD_SC_K,
  // 75 M/Dwn
  HID_KEYBOARD_SC_DOWN_ARROW,
  // 76 ,</Rgt
  HID_KEYBOARD_SC_RIGHT_ARROW,
  // 77 .>4
  HID_KEYBOARD_SC_KEYPAD_4_AND_LEFT_ARROW,
  // 78 Ret/V-
  HID_KEYBOARD_SC_VOLUME_DOWN,
  // 79 RCtl/Ret
  HID_KEYBOARD_SC_KEYPAD_ENTER,
  // 80 NLock
  HID_KEYBOARD_SC_NUM_LOCK,
  // 81 B
  HID_KEYBOARD_SC_X,
  // 82 N/Left
  HID_KEYBOARD_SC_LEFT_ARROW,
  // 83 Menu/CC
  NO_KEY,
  // 84 /?5
  HID_KEYBOARD_SC_KEYPAD_5,
  // 85 F12/Pse
  HID_KEYBOARD_SC_PAUSE,
  // 86 Left/0
  HID_KEYBOARD_SC_KEYPAD_0_AND_INSERT,
  // 87 Rght/.
  HID_KEYBOARD_SC_KEYPAD_DOT_AND_DELETE,
  // 88 RAlt/Nx
  KEY_MEDIA_NEXT,
  // 89 Dwn/00
  HID_KEYBOARD_SC_KEYPAD_00,
  };

const uint16_t PROGMEM us_dvorak_keypad[NUM_KEYS]={
  // 0 Q
  HID_KEYBOARD_SC_APOSTROPHE_AND_QUOTE,
  // 1 W
  HID_KEYBOARD_SC_COMMA_AND_LESS_THAN_SIGN,
  // 2 E
  HID_KEYBOARD_SC_DOT_AND_GREATER_THAN_SIGN,
  // 3 R
  HID_KEYBOARD_SC_P,
  // 4 U
  HID_KEYBOARD_SC_G,
  // 5 I
  HID_KEYBOARD_SC_C,
  // 6 O/Tab
  HID_KEYBOARD_SC_TAB,
  // 7 P/
  HID_KEYBOARD_SC_KEYPAD_SLASH,
  // 8 Ply/CX
  KEY_PLAY,
  // 9 Tab
  HID_KEYBOARD_SC_TAB,
  // 10 CapsLock/Clear
  HID_KEYBOARD_SC_ERROR_ROLLOVER,
  // 11 F3
  HID_KEYBOARD_SC_F3,
  // 12 T
  HID_KEYBOARD_SC_Y,
  // 13 Y
  HID_KEYBOARD_SC_HOME,
  // 14 ]}-
  HID_KEYBOARD_SC_KEYPAD_MINUS,
  // 15 F7/Pwr
  HID_KEYBOARD_SC_F7,
  // 16 [{*
  HID_KEYBOARD_SC_KEYPAD_ASTERISK,
  // 17 Bs/V+
  HID_KEYBOARD_SC_BACKSPACE,
  // 18 Calc
  KEY_CALC,
  // 19 LSft
  HID_KEYBOARD_SC_LEFT_SHIFT,
  // 20 AT/CV
  HID_KEYBOARD_SC_LEFT_ALT,
  // 21 Start
  HID_KEYBOARD_SC_LEFT_GUI,
  // 22 1!
  HID_KEYBOARD_SC_1_AND_EXCLAMATION,
  // 23 2@
  HID_KEYBOARD_SC_2_AND_AT,
  // 24 3#
  HID_KEYBOARD_SC_3_AND_HASHMARK,
  // 25 4$
  HID_KEYBOARD_SC_4_AND_DOLLAR,
  // 26 7&
  HID_KEYBOARD_SC_7_AND_AMPERSAND,
  // 27 8*
  HID_KEYBOARD_SC_8_AND_ASTERISK,
  // 28 9(
  HID_KEYBOARD_SC_9_AND_OPENING_PARENTHESIS,
  // 29 0)
  HID_KEYBOARD_SC_0_AND_CLOSING_PARENTHESIS,
  // 30 F10/PSc
  HID_KEYBOARD_SC_F10,
  // 31 End/3
  HID_KEYBOARD_SC_KEYPAD_3_AND_PAGE_DOWN,
  // 32 PDwn/Nx
  HID_KEYBOARD_SC_PAGE_DOWN,
  // 33 F5
  HID_KEYBOARD_SC_F5,
  // 34 Fn
  NO_KEY,
  // 35 A
  HID_KEYBOARD_SC_A,
  // 36 `~
  HID_KEYBOARD_SC_GRAVE_ACCENT_AND_TILDE,
  // 37 Esc
  HID_KEYBOARD_SC_ESCAPE,
  // 38 Z
  HID_KEYBOARD_SC_SEMICOLON_AND_COLON,
  // 39 S
  HID_KEYBOARD_SC_O,
  // 40 D
  HID_KEYBOARD_SC_E,
  // 41 F
  HID_KEYBOARD_SC_U,
  // 42 J/Up
  HID_KEYBOARD_SC_UP_ARROW,
  // 43 K/End
  HID_KEYBOARD_SC_END,
  // 44 L/7
  HID_KEYBOARD_SC_KEYPAD_7_AND_HOME,
  // 45 ;:8
  HID_KEYBOARD_SC_KEYPAD_8_AND_UP_ARROW,
  // 46 \|6
  HID_KEYBOARD_SC_KEYPAD_6_AND_RIGHT_ARROW,
  // 47 www/Bs
  HID_KEYBOARD_SC_KEYPAD_BACKSPACE,
  // 48 RSft/+
  HID_KEYBOARD_SC_KEYPAD_PLUS,
  // 49 Dsk/Pv
  NO_KEY,
  // 50 F1/Dvk
  HID_KEYBOARD_SC_F1,
  // 51 F2
  HID_KEYBOARD_SC_F2,
  // 52 5%
  HID_KEYBOARD_SC_5_AND_PERCENTAGE,
  // 53 6^
  HID_KEYBOARD_SC_6_AND_CARET,
  // 54 =+
  HID_KEYBOARD_SC_CLOSING_BRACKET_AND_CLOSING_BRACE,
  // 55 F8/Slp
  HID_KEYBOARD_SC_F8,
  // 56 -_
  HID_KEYBOARD_SC_OPENING_BRACKET_AND_OPENING_BRACE,
  // 57 F9/Wke
  HID_KEYBOARD_SC_F9,
  // 58 Home/1
  HID_KEYBOARD_SC_KEYPAD_1_AND_END,
  // 59 PUp/Bck
  HID_KEYBOARD_SC_PAGE_UP,
  // 60 LCtrl
  HID_KEYBOARD_SC_LEFT_CONTROL,
  // 61 Mail/BackTab
  NO_KEY, // FIXME
  // 62 Del/Ins
  HID_KEYBOARD_SC_DELETE,
  // 63 F4
  HID_KEYBOARD_SC_F4,
  // 64 G
  HID_KEYBOARD_SC_I,
  // 65 H/Home
  HID_KEYBOARD_SC_HOME,
  // 66 F6/Ejct
  HID_KEYBOARD_SC_F6,
  // 67 '"9
  HID_KEYBOARD_SC_KEYPAD_9_AND_PAGE_UP,
  // 68 F11/SLk
  HID_KEYBOARD_SC_F11,
  // 69 Up/2
  HID_KEYBOARD_SC_KEYPAD_2_AND_DOWN_ARROW,
  // 70 LAlt
  HID_KEYBOARD_SC_LEFT_ALT,
  // 71 Spc/Mte
  HID_KEYBOARD_SC_SPACE,
  // 72 X
  HID_KEYBOARD_SC_Q,
  // 73 C
  HID_KEYBOARD_SC_J,
  // 74 V
  HID_KEYBOARD_SC_K,
  // 75 M/Dwn
  HID_KEYBOARD_SC_DOWN_ARROW,
  // 76 ,</Rgt
  HID_KEYBOARD_SC_RIGHT_ARROW,
  // 77 .>4
  HID_KEYBOARD_SC_KEYPAD_4_AND_LEFT_ARROW,
  // 78 Ret/V-
  HID_KEYBOARD_SC_ENTER,
  // 79 RCtl/Ret
  HID_KEYBOARD_SC_KEYPAD_ENTER,
  // 80 NLock
  HID_KEYBOARD_SC_NUM_LOCK,
  // 81 B
  HID_KEYBOARD_SC_X,
  // 82 N/Left
  HID_KEYBOARD_SC_LEFT_ARROW,
  // 83 Menu/CC
  HID_KEYBOARD_SC_APPLICATION,
  // 84 /?5
  HID_KEYBOARD_SC_KEYPAD_5,
  // 85 F12/Pse
  HID_KEYBOARD_SC_F12,
  // 86 Left/0
  HID_KEYBOARD_SC_KEYPAD_0_AND_INSERT,
  // 87 Rght/.
  HID_KEYBOARD_SC_RIGHT_ARROW,
  // 88 RAlt/Nx
  HID_KEYBOARD_SC_RIGHT_ALT,
  // 89 Dwn/00
  HID_KEYBOARD_SC_KEYPAD_00,
  };
