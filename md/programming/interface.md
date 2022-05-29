General purpose interfaces have many advantages over special purpose one. They
tend to be simpler, with fewer methods that are deeper, they also provide a
cleaner separation betwwen classes, whereas special-purpose interfaces tend to
leak information between classes. Making your modules somewhat general purpose
is one of the best ways to reduce overall system complexity.

Having methods with same signature is not awalys bad. The important thing is
that each new method should contribute significant functionality. Pass-through
methods are bad because they contribute no new functionality.

A dispatcher is a method that uses its arguments to select one of serval
methods to invoke; Then it passes most or all of its arguments to the chosen
method. The signature of dispatcher often same as the methods it calls.

Interfaces with different implementations also provides useful and distinct
functionality. Such as disk drivers in an operate system, it reduces congnitive
load. Methods like this are usually in the same layer and don't invoke each
other.


