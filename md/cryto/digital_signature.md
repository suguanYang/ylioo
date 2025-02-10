---
title: "Digital Signature API and Requirements"
---

## API for digital signat

```
(sk, pk) := generateKeys(keySize)
sig := sign(sk, message)
isValid := verify(pk, message, sig)
```

## Requrements for signatures
### valid signatures verify
`verify(pk, message, sign(sk, message))`
### can't forge signatures
