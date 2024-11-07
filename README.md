keyMouse
========
**keyMouse** is a small utility to control the mouse using the keyboard. It is a
rewrite of the included python script (which the linter tells me is awful) that
I wrote years ago after getting fed up with the existence of the mouse
(I rewrote it for the same reason).

Usage
-----
`$ keyMouse`

Info
----
**keyMouse** grabs the keyboard and moves/clicks the cursor according to the keybindings
specified (`hjkl` and `asd` for mouse l/m/r by default; `qwex` control scrolling).

It waits `STARTUPTIME` before grabbing the keyboard.

The cursor moves `MOVEMENT` (default 5) pixels per keypress. This is multiplied
by `MULTIPLIER` (default 5) for each modifier key pressed down. The modifier
keys are also passed through and otherwise act normally.

Pressing any unbound key, ungrabs the keyboard and exits.

Exit Status
-----------
**keyMouse** exits 1 on error and prints the error to stderr.

Customization
-------------
**keyMouse** can be customized by editing the variables and defines under
`/* config */`.

Dependencies
------------
- X11 development headers
