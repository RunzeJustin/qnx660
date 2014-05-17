/*
 *  This file defines modifiers, actions, and common key types for
 *  keyboards with the AltGr key.  It treats CAPS_LOCK as a toggleable
 *  CAPS_LOCK key.
 */

Modifiers {
	<LEFT_SHIFT>
	<RIGHT_SHIFT>
	<LEFT_CTRL>
	<RIGHT_CTRL>
	<LEFT_ALT>
	<ALTGR>
	<CAPS_LOCK>
	<SCROLL_LOCK>
	<NUM_LOCK>
	<LOCK_SAVE>
	<ISO_LOCK>
	<CAPS_LED>
	}

Action {
	if   Up      <Num_Lock>
	and  Press   <NUM_LOCK>
	then Press   <Num_Lock>
	}

Action {
	if   Down    <Num_Lock>
	and  Press   <NUM_LOCK>
	then Release <Num_Lock>
	}

Action {
	if   Up      <Scroll_Lock>
	and  Press   <SCROLL_LOCK>
	then Press   <Scroll_Lock>
	}

Action {
	if   Down    <Scroll_Lock>
	and  Press   <SCROLL_LOCK>
	then Release <Scroll_Lock>
	}

Action {
	if   Press   <LEFT_SHIFT>
	or   Press   <RIGHT_SHIFT>
	then Press   <Shift>
	}

Action {
	if   Press   <Shift>
	then Up      <Shift_Lock>
	}

Action {
	if   Press   <LEFT_CTRL>
	or   Press   <RIGHT_CTRL>
	then Press   <Ctrl>
	}

Action {
	if   Press   <Ctrl>
	then Up      <Ctrl_Lock>
	}

Action {
	if   Press   <LEFT_ALT>
	then Press   <Alt>
	}

Action {
	if   Press   <Alt>
	then Up      <Alt_Lock>
	}

Action {
	if   Press   <ALTGR>
	then Press   <AltGr>
	}

Action {
	if   Press   <AltGr>
	then Up      <AltGr_Lock>
	}

Action {
	if   Press   <CAPS_LOCK>
	and  Down    <Caps_Lock>
	then Down    <LOCK_SAVE>
	}

Action {
	if   Press   <CAPS_LOCK>
	and  Up      <Caps_Lock>
	then Up      <LOCK_SAVE>
	}

Action {
	if   Up      <Caps_Lock>
	and  Press   <CAPS_LOCK>
	then Press   <Caps_Lock>
	}

Action {
	if   Down    <Caps_Lock>
	and  Press   <CAPS_LOCK>
	then Release <Caps_Lock>
	}

Action {
	if   Press   <Shift>
	or   Press   <Ctrl>
	or   Press   <Alt>
	or   Press   <AltGr>
	then Down    <ISO_LOCK>
	}

Action {
	if   Up      <CAPS_LOCK>
	then Up      <ISO_LOCK>
	}

Action {
	if   Down    <ISO_LOCK>
	and  Down    <LOCK_SAVE>
	then Down    <Caps_Lock>
	}

Action {
	if   Down    <ISO_LOCK>
	and  Up      <LOCK_SAVE>
	then Up      <Caps_Lock>
	}

Action {
	if   Down    <ISO_LOCK>
	and  Press   <Shift>
	then Press   <Shift_Lock>
	}

Action {
	if   Down    <ISO_LOCK>
	and  Press   <Ctrl>
	then Press   <Ctrl_Lock>
	}

Action {
	if   Down    <ISO_LOCK>
	and  Press   <Alt>
	then Press   <Alt_Lock>
	}

Action {
	if   Down    <ISO_LOCK>
	and  Press   <AltGr>
	then Press   <AltGr_Lock>
	}

Action {
	if   Up      <Shift_Lock>
	and  Up      <LEFT_SHIFT>
	and  Up      <RIGHT_SHIFT>
	then Up      <Shift>
	}

Action {
	if   Up      <Ctrl_Lock>
	and  Up      <LEFT_CTRL>
	and  Up      <RIGHT_CTRL>
	then Up      <Ctrl>
	}

Action {
	if   Up      <Alt_Lock>
	and  Up      <LEFT_ALT>
	then Up      <Alt>
	}

Action {
	if   Up      <AltGr_Lock>
	and  Up      <ALTGR>
	then Up      <AltGr>
	}

Action {
	then Up      <CAPS_LED>
	}

Action {
	if   Down    <Caps_Lock>
	or   Down    <Shift_Lock>
	or   Down    <Ctrl_Lock>
	or   Down    <Alt_Lock>
	or   Down    <AltGr_Lock>
	or   Press   <Caps_Lock>
	or   Press   <Shift_Lock>
	or   Press   <Ctrl_Lock>
	or   Press   <Alt_Lock>
	or   Press   <AltGr_Lock>
	then Down    <CAPS_LED>
	}

Indicators {
	<Scroll_Lock>
	<Num_Lock>
	<CAPS_LED>
	}

KeyType "Unmodified" {
	NoSym <AltGr>
	Unmodified Sym #1
	}

KeyType "TwoLevel" {
	NoSym <AltGr>
	NoSym <Ctrl>
	NoSym <Alt>
	Unmodified Sym #1
	<Shift> Sym #2
	}

KeyType "TwoLevelLetter" {
	NoSym <AltGr>
	NoSym <Ctrl>
	NoSym <Alt>
	Unmodified Sym #1
	<Caps_Lock> Sym #2
	<Shift> Sym #2
	<Shift> + <Caps_Lock> Sym #1
	}

KeyType "ThreeLevel" {
	NoSym <Ctrl>
	NoSym <Alt>
	Unmodified Sym #1
	<Shift> Sym #2
	<AltGr> Sym #3
	<AltGr> + <Shift> Sym #3
	}

KeyType "ThreeLevelLetter" {
	NoSym <Ctrl>
	NoSym <Alt>
	Unmodified Sym #1
	<Caps_Lock> Sym #2
	<Shift> Sym #2
	<Shift> + <Caps_Lock> Sym #1
	<AltGr> Sym #3
	<AltGr> + <Caps_Lock> Sym #3
	<AltGr> + <Shift> Sym #3
	<AltGr> + <Shift> + <Caps_Lock> Sym #3
	}

KeyType "Keypad" {
	NoSym <AltGr>
	Unmodified Sym #1
	<Alt> Sym #1
	<Ctrl> Sym #1
	<Ctrl> + <Alt> Sym #1
	<Shift> Sym #2
	<Shift> + <Alt> Sym #2
	<Shift> + <Ctrl> Sym #2
	<Shift> + <Ctrl> + <Alt> Sym #2
	<Num_Lock> Sym #2
	<Num_Lock> + <Alt> NoSym
	<Num_Lock> + <Ctrl> NoSym
	<Num_Lock> + <Ctrl> + <Alt> NoSym
	<Num_Lock> + <Shift> Sym #1
	<Num_Lock> + <Shift> + <Alt> NoSym
	<Num_Lock> + <Shift> + <Ctrl> NoSym
	<Num_Lock> + <Shift> + <Ctrl> + <Alt> NoSym
	}

KeyType "Pause" {
	NoSym <AltGr>
	NoSym <Shift>
	NoSym <Alt>
	Unmodified Sym #1
	<Ctrl> Sym #2
	}

KeyType "Print" {
	NoSym <AltGr>
	NoSym <Shift>
	NoSym <Ctrl>
	Unmodified Sym #1
	<Alt> Sym #2
	}

KeyType "DoubleDead" {
	NoSym <AltGr>
	Unmodified Deadkey #1
	<Shift> Deadkey #2
	}

KeyType "NoModsOnly" {
	NoSym <AltGr>
	NoSym <Ctrl>
	NoSym <Alt>
	Unmodified Sym #1
	}

KeyType "TwoDeadAndOneAlive" {
	NoSym <Ctrl>
	NoSym <Alt>
	Unmodified Deadkey #1
	<Shift> Deadkey #2
	<AltGr> Sym #3
	<AltGr> + <Shift> Sym #3
	}

KeyType "TripleDead" {
	NoSym <Ctrl>
	NoSym <Alt>
	Unmodified Deadkey #1
	<Shift> Deadkey #2
	<AltGr> Deadkey #3
	<AltGr> + <Shift> Deadkey #3
	}

KeyType "TwoAliveAndOneDead" {
	NoSym <Ctrl>
	NoSym <Alt>
	Unmodified Sym #1
	<Shift> Sym #2
	<AltGr> Deadkey #3
	<AltGr> + <Shift> Deadkey #3
	}

KeyType "AliveOrDead" {
	NoSym <AltGr>
	Unmodified Sym #1
	<Shift> Deadkey #2
	}

Key {
	Type "Unmodified"
	IsMod <ALTGR>
	Scan  E0 38
	Syms  [Alt_R]
	}

