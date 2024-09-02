# OPERATION OF THE ALTAIR 8800

## Front Panel Switches:

- **On-Off Switch**
	- Turns the machine on or off
- **Stop-Run Switch**
	- Stop or Start program execution
- **Single Step Switch**
	- Processes a single instruction
- **Examine-Examine Next Switch**
	- displays the contents of any specified memory address previously loaded into the Data-Address switches. Examine Next shows the sequential memory address.
- **Deposit-Deposit Next**
	- Loads the data from the 8 switches to the previously designated memory address. Deposit Next puts data in the next sequential memory address.
- **Reset-Clear Switch**
	- Reset sets program counter to 0. Clear clears external input/output.
- **Protect-Unprotect Switch**
	- Protect prevents memory from being changed, Unprotect permits the changing of memory.
- **Aux Switches**
	- Used for peripheral devices
- **Data-Address Switches**
	- Data has 8 switches, Address has 16. Up = 1, Down = 0.

## Indicator LEDs
- **ADDRESS**
	- LEDs designated A15-A0. Denotes memory address.
- **DATA**
	-  D7-D0. Denotes the specified memory address's data.
- **INTE**
	- Shows if an interrupt has been enabled.
- **PROT**
	- Shows if the memory is protected
- **WAIT**
	- Shows if the CPU is in a wait state.
- **HLDA**
	- Shows if a Hold has been acknowledged.

## Status LEDs
- **MEMR**
	- The memory bus will be reading data
- **INP**
	- The address is an input.
- **M1**
	- The CPU is processing the first machine cycle of an instruction
- **OUT**
	- The address is an output.
- **HLTA**
	- A Halt instruction has been executed and acknowledged.
- **STACK**
	- The address holds the Stack Pointer's push-down stack address.
- **WO**
	- If the light is on, it's in Write / Output mode, otherwise it's in Read / Input mode. 
- **INT**
	- An Interrupt has been acknowledged.

## Sample Program

***the program adds two numbers:***

1. **LDA $0x8000$**
	- Loads accumulator with contents of memory address 128.
2. **MOV $(A\to B)$**
	- Moves the contents of the Accumulator to Register B.
3. **LDA $0x8100$**
	- Loads accumulator with contents of memory address 129.
4. **ADD $(B+A)$**
	- Adds Register B to the Accumulator.
5. **STA $0x8200$**
	- Stores the Accumulator's contents at memory address 130.
6. **JMP $0x0000$**
	- Jump to memory location 0.

## Memory Addressing

**Direct Addressing** is where you give two bytes to an instruction to tell it what address to use.

**Register Pair Addressing** uses the contents of a register pair, such as **B** and **C**, or **D** and **E**.

**Stack Pointer Addressing** uses the stack operations **PUSH** and **POP** to fetch memory.
