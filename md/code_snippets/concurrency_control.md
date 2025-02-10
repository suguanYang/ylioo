---
title: "Concurrency Control Implementation with Queue"
---
```javascript
const PENDING_CREATE_QUEUE = [];
const MAX_CONCURRENCY_REQUEST = 20;

let pendingSize = 0;

const runNext = () => {
    if (pendingSize < MAX_CONCURRENCY_REQUEST && PENDING_CREATE_QUEUE.length > 0) {
        PENDING_CREATE_QUEUE.shift()!();
    }
};

const run = async (task) => {
    let onResolve;
    const pendingSignal = new Promise((res) => (onResolve = res));
    let ret = null;
    let error = null;

    PENDING_CREATE_QUEUE.push(() => {
        pendingSize++;
        task()
            .then(
                (res) => (ret = res),
                (err) => (error = err),
            )
            .catch((err) => (error = err))
            .finally(() => {
                pendingSize--;
                onResolve(null);
                runNext();
            });
    });

    runNext();

    await pendingSignal;

    if (error) {
        return Promise.reject(error);
    }

    return ret;
};

export default run;

// can not runing with nested run(() => run(() => task()))
// the first run is to run the nested run, but the
// nested run can only run if its not blocked by the
// concurrency control, thus if the MAX_CONCURRENCY_REQUEST
// is 1, this run will be blocked forever
```
