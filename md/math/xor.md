---
title: "Understanding XOR Operation Properties"
---

Think of the XOR operator as a 'conditional flip' operator, that is think of a⊕b
as saying if a is 1, take flipped b as the output, while if a
is 0, take b as the output. Because of the commutative property, a⊕b
is completely equivalent to b⊕a
which says that b conditionally flips a.

Now consider a⊕(b⊕c). This is saying that b conditionally flips c, the result of which is itself conditionally flipped by a. Because of the nature of the flipping operation, ultimately c
is conditionally flipped by both b and a, and it doesn't matter in which order these two flip
operations are performed. Because of this, it is seen that a⊕(b⊕c) is equivalent to b⊕(a⊕c).

Finally, by using commutativity, one can write a⊕(b⊕c)=(b⊕c)⊕a, which was just showed to be
equivalent to b⊕(a⊕c), itself equivalent to b⊕(c⊕a) by commutativity.

Therefore, (b⊕c)⊕a=b⊕(c⊕a) which proves associativity.
