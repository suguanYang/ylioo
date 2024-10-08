```javascript
function acquireLock() {
    // Implementation by a lock file
}

function releaseLock() {
    // Implementation by a lock file
}

function updateCounter(operation) {
    acquireLock();
    if (operation === "increment") {
        COUNTER++;
    } else if (operation === "decrement") {
        COUNTER--;
    }
    releaseLock();
}

function runOne() {
    acquireLock();
    if (COUNTER === 0) {
        // Run 离线包安装
    }
    releaseLock();
}

function runMany() {
    updateCounter("increment");
    
    // Run Processe
    
    updateCounter("decrement");
}
```

