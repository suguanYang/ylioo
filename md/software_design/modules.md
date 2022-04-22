## Modularity
A well-defined segmentation of the project effort ensures
system modularity. Each task forms a separate, distinct program
module. At implementation time each module and its inputs and
outputs are well-defined, there is no confusion in the intended
interface with other system modules. At checkout time the integrity
of the module is tested independently; there are few scheduling
problems in synchronizing the completion of several tasks
before checkout can begin. Finally, the system is maintained in
modular fashion; system errors and deficiencies can be traced to
specific system modules, thus limiting the scope of detailed error
searching.

The benefits expected of modular programming are:
(1) managerial--development time should be shortened
because separate groups would work on each module
with little need for communication:
(2) product flexibility-it should be possible to make drastic changes to
one module without a need to change others;
(3) comprehensibility-it should be possible to study the
system one module at a time. The whole system can
therefore be better designed because it is better understood. 

In some context "module" is considered to be a responsibility assignment
rather than a subprogram. The modularizations include the design decisions
which must be made before the work on independent modules can begin. Quite
different decisions are included for each alternative, but in all cases the
intention is to describe all "system level" decisions (i.e. decisions which
affect more than one module)

## Information hiding
The purpose of information hiding is to obtain a modularization of the code of
a system that isolates changes into single modules.

## References
On the Criteria To Be Used in Decomposing Systems into Modules [D.L. Parnas]