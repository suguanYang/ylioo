---
title: "Error Handling Strategies"
---

The exceptions thrown by a class are part of its interface; classes with lots of exceptions have complex interfaces, and they are shallower than classes with fewer exceptions.

Reducing the number of exception handlers.

## Define errors out of existence

## Mask exception
eg, TCP package loss

## Exception aggregation 
eg, rails application level catch

## Crash
eg, out of memory

## Design special cases out of existence
special cases can result in code that is riddled with if statements.
By designing the normal case in a way that automatically handles the special cases without any extra code.
eg, text edtor, var no_selection = false; vs selections = '';

## Conclusion
With exceptions, as with many other areas in software design, you must determine what is
important and what is not important. Things that are not important should be hidden, and the
more of them the better. But when something is important, it must be exposed. 
