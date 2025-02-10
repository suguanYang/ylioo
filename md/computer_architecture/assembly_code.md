---
title: "x86-64 Assembly Stack Operations"
---

## x86-64 Stack: Push

- pushq Src
    - Fetch operand at Src
    - Decrement %rsp by 8
    - Write operand at address given by %rsp

## x86-64 Stack: Pop

- popq Dest
    - Read value at address given by %rsp
    - Increment %rsp by 8
    - Store value at Dest(must be register)

