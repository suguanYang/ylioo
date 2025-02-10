---
title: "One-to-Many Locking Mechanism"
---

```javascript
function acquireLock() {
    // Implementation by a lock file
}

function releaseLock() {
    // Implementation by a lock file
}

function updateCounter(operation) {
    acquireReadLock();
    if (operation === "increment") {
        COUNTER++;
    } else if (operation === "decrement") {
        COUNTER--;
    }
    releaseReadLock();
}

function runWrite() {
    if (COUNTER === 0) {
        acquireWriteLock();
        // Write
        releaseWriteLock();
    }
}

function runRead() {
    if (COUNTER === 0) acquireWriteLock();
    updateCounter("increment");
    
    // Read
    
    updateCounter("decrement");
    if (COUNTER === 0) releaseWriteLock();
}
```

