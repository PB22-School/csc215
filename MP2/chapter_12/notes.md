# Chapter 12

***programs should be broken down into blocks to simply the programming effort.***

The stack allows for a lot of function depths to be easily incorporated into our projects.

CR:				0D 		(character return)
LF:				0A 		(line feed)
CTRLZ: 		0A 		(operator interrupt)
RCONF:		1 			(read con to A)
WCONF:	2 			(write A to con)
RBOOT:		0 			(reboot cpm)
BDOS:		5 			(system call entry)
TPA:			100H	(transient program area)

Semicolons are comments
Programmers aren't humans

ED's line command works with negative numbers, and the Beginning command can also be negative (puts the cursor at the end.)

The 'K' command kills lines.
The 'F' command finds whatever you type:
```
FSTART1cr
```
Use this to find the string you're looking for, reverse back to the beginning of the line, then type it to the screen:
```
FSTART1ctrlz0LT
```
#A:					Append complete file onto editor buffer
I:						Enter insert mode
Ctrl Z:				Exit insert mode
B:					Point to beginning of editor buffer
-B:					Point to end of editor buffer
V:					Turn on automatic line numbering
-V:					Turn off automatic line numbering
E:						Write editor buffer to disk and exit
Q:					Exit ED without writing buffer to disk
$\pm$nL:		Move back or ahead n lines
nT:					Type n lines to console
nK:					Kill n lines on console
Fstring:			Find the first occurence of string
Sold Znew Z:	Substitute new for old
Ctrl I:				Tab forward to next tab stop
Rubout:			Erase and echo last character
