# How To Use The Altair Clone
## Loading Minicom
you can start Minicom by running:
```
minicom altair
```
in the terminal.
## Booting Programs
You boot CP/M by examining address 0xff00.
You can boot the Turn Key Monitor at address 0xfd00.

## Turn Key Monitor

From Turn Key Monitor, you can boot CPM by running this command:
```
.J177400
```

This jumps to memory address 177400 in Octal (where CP/M is).

You can also 'examine' memory on the Altair by using:

```
.M{address_octal}
```

## Interacting With Files
There's two ways to put files on the Altair.
The first is using the Altair Clone's built in debug menu.

You can reach the debug menu by pressing stop + aux.

```
=== Configuration Monitor 1.94 ===

1) Floppies
2) PROMs
3) Serial Ports
4) Load .BIN
5) Load .HEX
6) Admin
7) Exit to Altair

Choice: 4

Load address in hex: 0h

Send .bin file now...
```

Now we can use Ctrl+A S, then select ascii to get to a menu which lets us upload files.

The uploaded file will be put into Altair memory.

The second way is to use the PCPUT and PCGET files with CP/M.
```
PCPUT {filename}
```
This command puts {filename} on the computer we're using to run Minicom.
```
PCGET {filename}
```
This command lets us upload a file and saves it to {filename}.

Both of these commands use the XMODEM protocol.

## Saving Drives

booting up the debug menu we see this:
```
=== Configuration Monitor 1.94 ===

1) Floppies
2) PROMs
3) Serial Ports
4) Load .BIN
5) Load .HEX
6) Admin
7) Exit to Altair

Choice: 1
```
from here we can go to the "Floppies" menu
```
=== 8 Inch Floppy Drive Content ===

Drive 0: CP/M 2.2
Drive 1: C
Drive 2: Other

Drive to Update (x to exit):
```
Then we input the index of the drive we want to load, download
```
=== Floppy Drive Menu ===

1) Change Drive Number
2) Load Floppy from PC
3) Save Floppy to PC
4) Change Description
x) Exit Menu
```
This menu lets us load and save disk images to / from our computer.
