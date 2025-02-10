---
title: "CPU Instruction Processing Stages"
---

Processing instructions in particular sequence of stages:

- Fetch
Reads the bytes of an instruction from memorym using the program counter as the memory address.

- Decode
Reads up to two operands from the register file, giving values valA and/or valB.

- Execute
The ALU performs the operation specified by the instruction, computes the effective address of a
memory reference, or increments or decrements the stack pointers.

- Memory
May write data to memory, or read data from memory

- Write back
Writes up to  2 results to the register file

- PC update
The PC is set to the address of the next instrction

The processor loops indefinitely, performaning these stages unless any exception occurs, invalid instruction, halt instruction, read or write invalid address.

## hardware stages
![stages](./assets/hardware_stages.png)


## Pipeline

Not all instructions have the same stages in modern processors, for example the add instrction may only need 1 clock
cycle to complete.


> icode and ifun
The icode (instruction code) is the high-order nyble (4 bits) of the instruction byte, and it specifies the operation to be performed12. For example, it could represent operations like add, subtract, and, or, etc34.
The ifun (instruction function) is the low-order nyble of the instruction byte, and it provides additional information needed for some instructions12. For example, in conditional jump instructions, ifun specifies the type of condition to be tested