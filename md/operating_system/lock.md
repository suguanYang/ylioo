---
title: "Software and Hardware Locking Mechanisms"
---

## Software-based solutions

### Out-of-Order Execution
Modern processors may execute instructions out of the original program order to improve performance.

This can cause operations within a lock to execute in an unexpected sequence, potentially violating the lock's correctness.

### Memory Barriers/Fences
Processors and compilers may reorder memory operations for efficiency.

Without proper memory barriers, changes made by one thread to shared variables may not be visible to another in the correct order, leading to race conditions.

### Atomicity Issues

Certain operations that are intended to be atomic (indivisible) may not be atomic on all architectures.

If the underlying architecture does not support atomic operations for the instructions used in the lock, it can result in partial updates and inconsistencies.

### Cache Coherence

Multi-core systems maintain caches that must stay coherent.

If lock variables are cached inconsistently across cores, one core might not see updates made by another, causing incorrect behavior.

### Speculative Execution

Processors may speculatively execute instructions based on predictions.

If a lock's condition is speculated incorrectly, it might allow unintended access to protected resources.

### Interrupts and Preemption

A thread may be interrupted while acquiring a lock, leaving the system in an inconsistent state.

Proper handling of interruptions is crucial to maintain lock correctness.

### Architecture-Specific Behavior

Different processor architectures (e.g., x86, ARM, MIPS) have varying memory models and instruction behaviors.

A software lock that works on one architecture may fail on another due to these differences.

### Compiler Optimizations

Compilers might reorder instructions or optimize variable accesses in ways that break the intended lock behavior.

The compiler must be instructed properly (e.g., using volatile keywords or compiler barriers) to prevent such issues.

Example for software lock:
   leave noteA;
    while noteB // busy waiting! waste CPU time
        ;
    // critical section
    dosomething;
    // critical section end
    remove noteA;
and Thread 2 performs
    leave noteB;
    if no noteA
        // critical section
        dosomething;
        // critical section end
    remove noteB;

## Hardware Support

### Memory Barriers
a memory model falls into one of two categories:
1. *Strongly ordered*, where a memory modification on one processor is immediately visible to all other processors.
2. *Weakly ordered*, where modifications to memory on one processor may not be immediately visible to others.
```
When a memory barrier instruction is performed, the system ensures that all loads and stores are completed before any subse-
quent load or store operations are performed. 

As an example, consider the following data that are shared between two
threads:
    boolean flag = false;
    int x = 0;
where Thread 1 performs the statements
    while (!flag) // Busy waiting!
    ;
    print x;
and Thread 2 performs
    x = 100;
    flag = true;
The expected behavior is, of course, that Thread 1 outputs the value 100 for variable x. However, as there are no data dependencies between the variables flag and x, it is possible that a processor may reorder the instructions for Thread 2 so that flag is assigned true before assignment of x = 100. In this situation, it is possible that Thread 1 would output 0 for variable x.

If we add a memory barrier operation to Thread 1
    while (!flag)
    memory barrier();
    print x;
we guarantee that the value of flag is loaded before the value of x.
Similarly, if we place a memory barrier between the assignments per-
formed by Thread 2
    x = 100;
    memory barrier();
    flag = true;
```

### Hardware instructions
The important thing about these instructions is that they are atomic., if 2 threads try to execute it at the same time, it will be executed in sequentially in some arbitrary order.
1. *Test and set*
```
boolean test and set(boolean *target) {
    boolean rv = *target;
    *target = true;
    return rv;
}
<!-- Mutual-exclusion implementation -->
do {
    while (test and set(&lock))
        ; /* do nothing if lock is already set */

    /* critical section */
    lock = false;
    /* remainder section */
} while (true);
```
2. *Compare and swap*
```
int compare and swap(int *value, int expected, int new value) {
    int temp = *value;
    if (*value == expected)
        *value = new value;
    return temp;
}

<!-- Mutual exclusion -->
while (true) {
    while (compare and swap(&lock, 0, 1) != 0)
        ; /* do nothing if lock is already set to 1 */
    /* critical section */
    lock = 0;
    /* remainder section */
}

<!== Muttual exclusion by test and set ==>
while (true) {
    while (test and set(&lock))
        ; /* do nothing if lock is already set */
    /* critical section */
    lock = false;
    /* remainder section */
}
```
because the original value of lock was equal to the expected value of 0. Subse-
quent calls to compare and swap() will not succeed, because lock now is not
equal to the expected value of 0. When a process exits its critical section, it sets
lock back to 0, which allows another process to enter its critical section.

### Atomic Variables
provides atomic operations on basic data types such as integers and booleans
```
void increment(atomic int *v)
{
int temp;
    do {
        temp = *v;
    }
    while (temp != compare and swap(v, temp, temp+1)); // this ensures that v is incremented by 1, since we know that temp is the original value of v(not modified by other threads)
}
```

### Mutex Locks
use the mutex lock to protect critical sections and thus prevent race conditions. That
is, a process must acquire the lock before entering a critical section; it releases
the lock when it exits the critical section.

```
acquire() {
    while (!available)
        ; /* busy wait */
    available = false;
}

release() {
    available = true;
}

while (true) {
    acquire lock
        // critical section
    release lock
        // remainder section
}
```
Calls to either acquire() or release() must be performed atomically. Thus, mutex locks can be implemented using the CAS operation

All the lock described above are *spinlocks*, which means that the thread will keep spinning in the loop until the lock is available. It is suitable for Short Duration Locks.
> Duration Locks: Given that waiting on a lock requires
two context switches a context switch to move the thread to the waiting
state and a second context switch to restore the waiting thread once the lock
becomes available the general rule is to use a spinlock if the lock will be
held for a duration of less than two context switches.

### Semaphores


The value of a binary semaphore can range only between 0 and 1. Thus, binary semaphores behave similarly to mutex locks.
Counting semaphores can be used to control access to a given resource consisting of a finite number of instances.

Implementation
```
typedef struct {
    int value;
    struct process *list;
} semaphore;

wait(semaphore *S) {
    S->value--;
    if (S->value < 0) { // if there are no resources left
        add this process to S->list;
        sleep();
    }
}

signal(semaphore *S) {
    S->value++;
    if (S->value <= 0) { // if there are waiting processes
        remove a process P from S->list;
        wakeup(P);
    }
}
```

No busy waiting?
we have limited busy waiting to the critical sections of the wait() and signal() operations(Hardware instructions), and these sections are short