
Key {
	Type "NoModsOnly"
	Scan  01
	Syms  [Escape]
	}
Key {
	Type "NoModsOnly"
	Scan  0E
	Syms  [BackSpace]
	}
Key {
	Type "TwoLevel"
	Scan  0F
	Syms  [Tab] [KP_Tab]
	}
Key {
	Type "NoModsOnly"
	Scan  1C
	Syms  [Return]
	}
Key {
	Type "Unmodified"
	IsMod <LEFT_CTRL>
	Scan  1D
	Syms  [Control_L]
	}
Key {
	Type "Unmodified"
	IsMod <LEFT_SHIFT>
	Scan  2A
	Syms  [Shift_L]
	}
Key {
	Type "Unmodified"
	IsMod <RIGHT_SHIFT>
	Scan  36
	Syms  [Shift_R]
	}
Key {
	Type "Unmodified"
	IsMod <LEFT_ALT>
	Scan  38
	Syms  [Alt_L]
	}
Key {
	Type "Unmodified"
	IsMod <CAPS_LOCK>
	Scan  3A
	Syms  [Caps_Lock]
	}
Key {
	Type "Unmodified"
	Scan  3B
	Syms  [F1]
	}
Key {
	Type "Unmodified"
	Scan  3C
	Syms  [F2]
	}
Key {
	Type "Unmodified"
	Scan  3D
	Syms  [F3]
	}
Key {
	Type "Unmodified"
	Scan  3E
	Syms  [F4]
	}
Key {
	Type "Unmodified"
	Scan  3F
	Syms  [F5]
	}
Key {
	Type "Unmodified"
	Scan  40
	Syms  [F6]
	}
Key {
	Type "Unmodified"
	Scan  41
	Syms  [F7]
	}
Key {
	Type "Unmodified"
	Scan  42
	Syms  [F8]
	}
Key {
	Type "Unmodified"
	Scan  43
	Syms  [F9]
	}
Key {
	Type "Unmodified"
	Scan  44
	Syms  [F10]
	}
Key {
	Type "Unmodified"
	IsMod <NUM_LOCK>
	Scan  45
	Syms  [Num_Lock]
	}
Key {
	Type "Unmodified"
	IsMod <SCROLL_LOCK>
	Scan  46
	Syms  [Scroll_Lock]
	}
Key [KP_7] {
	Type "Keypad"
	Scan  47
	Syms  [Home] '7'
	}
Key [KP_8] {
	Type "Keypad"
	Scan  48
	Syms  [Up] '8'
	}
Key [KP_9] {
	Type "Keypad"
	Scan  49
	Syms  [Pg_Up] '9'
	}
Key [KP_Subtract] {
	Type "NoModsOnly"
	Scan  4A
	Syms  '-'
	}
Key [KP_4] {
	Type "Keypad"
	Scan  4B
	Syms  [Left] '4'
	}
Key {
	Type "Keypad"
	Scan  4C
	Syms  [KP_5] '5'
	}
Key [KP_6] {
	Type "Keypad"
	Scan  4D
	Syms  [Right] '6'
	}
Key [KP_Add] {
	Type "NoModsOnly"
	Scan  4E
	Syms  '+'
	}
Key [KP_1] {
	Type "Keypad"
	Scan  4F
	Syms  [End] '1'
	}
Key [KP_2] {
	Type "Keypad"
	Scan  50
	Syms  [Down] '2'
	}
Key [KP_3] {
	Type "Keypad"
	Scan  51
	Syms  [Pg_Down] '3'
	}
Key [KP_0] {
	Type "Keypad"
	Scan  52
	Syms  [Insert] '0'
	}
Key [KP_Decimal] {
	Type "Keypad"
	Scan  53
	Syms  [Delete] '.'
	}
Key {
	Type "Unmodified"
	Scan  57
	Syms  [F11]
	}
Key {
	Type "Unmodified"
	Scan  58
	Syms  [F12]
	}
Key {
	Type "Unmodified"
	Scan  E0 5B
	Syms  [Hyper_L]
	}
Key {
	Type "Unmodified"
	Scan  E0 5C
	Syms  [Hyper_R]
	}
Key {
	Type "Unmodified"
	Scan  E0 5D
	Syms  [Menu]
	}
Key {
	Type "Unmodified"
	Scan  E0 50
	Syms  [Down]
	}
Key {
	Type "Unmodified"
	IsMod <RIGHT_CTRL>
	Scan  E0 1D
	Syms  [Control_R]
	}
Key {
	Type "Unmodified"
	Scan  E0 49
	Syms  [Pg_Up]
	}
Key {
	Type "Unmodified"
	Scan  E0 48
	Syms  [Up]
	}
Key {
	Type "Unmodified"
	Scan  E0 53
	Syms  [Delete]
	}
Key {
	Type "Unmodified"
	Scan  E0 4F
	Syms  [End]
	}
Key {
	Type "Unmodified"
	Scan  E0 52
	Syms  [Insert]
	}
Key {
	Type "Unmodified"
	Scan  E0 4B
	Syms  [Left]
	}
Key {
	Type "Unmodified"
	Scan  E0 4D
	Syms  [Right]
	}
Key {
	Type "Unmodified"
	Scan  E0 51
	Syms  [Pg_Down]
	}
Key {
	Type "Unmodified"
	Scan  E0 47
	Syms  [Home]
	}
Key {
	Type "Pause"
	Scan  E1 1D 45 E1 9D C5
	Scan  E0 46 E0 C6
	Syms  [Pause] [Break]
	}
Key {
	Type "Print"
	Scan  E0 37
	Syms  [Print] [Help]
	}
Key [KP_Enter] {
	Type "NoModsOnly"
	Scan  E0 1C
	Syms  [Return]
	}
Key [KP_Multiply] {
	Type "NoModsOnly"
	Scan  37
	Syms  '*'
	}
Key [KP_Divide] {
	Type "NoModsOnly"
	Scan  E0 35
	Syms  '/'
	}

DeadScan { E0 2A }
DeadScan { E0 36 }

Compose <Alt> {
	include "compose.inc"
	include "symbols.inc"
	}
