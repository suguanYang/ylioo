---
title: "Code Organization Principles"
---

## Bring together if Related: 
- They share information; for example, both pieces of code might depend on the syntax of a particular type of document. 
- They are used together: anyone using one of the pieces of code is likely to use the other as well. This form of relationship is only compelling if it is bidirectional. As a counter-example, a disk block cache will almost always involve a hash table, but hash tables can be used in many situations that don't involve block caches; thus,these modules should be separate. 
- They overlap conceptually, in that there is a simple higher-level category that includes both of the pieces of code. For example, searching for a substring and case conversion both fall under the category of string manipulation; flow control and reliable delivery both fall under the category of network communication. 
- It is hard to understand one of the pieces of code without looking at the other. 

## Bring together if it will simplify the interface

## Bring together to eliminate duplication

## Separate general-purpose and special-purpose code
In general, the lower layers of a system tend to be more general-purpose and the upper layers more special-purpose. For example, the topmost layer of an application consists of features totally specific to that application. The way to separate special-purpose code from general-purpose code is to pull the special-purpose code upwards, into the higher layers, leaving the lower layers general-purpose.