The CPU hardware has a wire called the interrupt-request line that the CPU senses after executing every
instruction, After executing each instruction, the CPU checks (or "polls") the state of the interrupt-request line. This polling happens as part of the CPU's instruction cycle.
The device controller raises an interrupt by asserting a signal on the interrupt request line, the CPU catches the interrupt and transfers control to the interrupt handler, and the controller
clears the interrupt request signal.

implementation of system calls. Usually, a
program uses library calls to issue system calls. The library routines check the
arguments given by the application, build a data structure to convey the argu-
ments to the kernel, and then execute a special instruction called a software
interrupt, or trap. This instruction has an operand that identifies the desired
kernel service. When a process executes the trap instruction, the interrupt hard-
ware saves the state of the user code to the stack on the kernel space, switches to kernel mode, and dispatches
to the kernel routine or thread that implements the requested service. The trap
is given a relatively low interrupt priority compared with those assigned to
device interrupts—executing a system call on behalf of an application is less
urgent than servicing a device controller before its FIFO queue overflows and
loses data.


+---------------------------+
|        User Space         |
|  +--------+   +--------+  |
|  | User   |   | User   |  |
|  |Process1|   |Process2|  |
|  +--------+   +--------+  |
|         |         |       |
|         v         v       |
+---------------------------+
          |         |        
          | System  |        
          | Calls   |        
          v         v        
+---------------------------+
|       Kernel Space        |
| +----------------------+  |
| |   System Call        |  |
| |    Interface         |  |
| +----------------------+  |
|           |              |
|           v              |
| +----------------------+ |
| |     Kernel Core      | |
| +----------------------+ |
|     |             |      |
|     v             v      |
| +----------+ +----------+|
| | Device   | | Device   ||
| | Driver 1 | | Driver 2 ||
| +----------+ +----------+|
|     |             |      |
|     v             v      |
+---------------------------+
          |         |        
          v         v        
+---------------------------+
|        Hardware           |
|  +--------+   +--------+  |
|  | Device |   | Device |  |
|  |   1    |   |   2    |  |
|  +--------+   +--------+  |
+---------------------------+