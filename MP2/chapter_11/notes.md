# Chapter 11: Learning By Doing

## ED

Ed is a stand-alone program which lets us edit files. Commands are case insensitive. Assembly files should be typed in upper case only.

```
ED TEST.ASMcr
```
the ```cr``` key designates a new line (the user pressed enter.)

The "-V" command turns off ED's automatic line numbering.

Use command "I" and enter to begin insert mode.
CTRL+I is the same as pressing the TAB key.

CTRL+Z exits the input mode and returns to the editor command mode.

This is a sample command sequence:
```
B8Tcr
```
The pointer goes to the **B**eginning of the text buffer, and **T**ypes eight lines of the program. (writes the program you entered in insert mode)

If you make a mistake, you might want to do:
```
3LT
```

which moves ED down 3 **L**ines and **T**ypes one line.

it's a good practice to type the line you're trying to change before changing it.
