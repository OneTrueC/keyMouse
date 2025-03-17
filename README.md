# NAME

**keymouse** - small program to control the mouse using the keyboard.

# SYNOPSIS

**keymouse** \[*-v*\]

# DESCRIPTION

**keymouse** is a small utility to control the mouse using the keyboard.

It grabs the keyboard and moves/clicks the cursor according to the
keybindings specified (hjkl and asd for mouse l/m/r by default; qwex
control scrolling).

**keymouse** waits *STARTUPTIME* before grabbing the keyboard.

The cursor moves *MOVEMENT* (default 5) pixels per keypress. This is
multiplied by *MULTIPLIER* (default 5) for each modifier key pressed
down. The modifier keys are also passed through and otherwise act
normally.

Pressing any unbound key ungrabs the keyboard and exits.

# EXIT STATUS

| Return Code |              Meaning |
| :---------- |--------------------: |
| 1           |  display open failed |
| 2           | keyboard grab failed |
| 3           | getting event failed |

# CUSTOMIZATION

**keymouse** can be customized be editing the variables under
*/\* config \*/* near the top of the source, and recompiling.
