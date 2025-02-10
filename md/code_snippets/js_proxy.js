---
title: "Simple JavaScript Proxy Implementation"
---

if (prev.isProxy) return prev;
return new Proxy(prev, {
    set(target, p, newValue, receiver) {
        if (newValue === undefined) debugger;
        return Reflect.set(target, p, newValue, receiver);
    },
    get(target, p, receiver) {
        if (p === 'isProxy') return true;
        return Reflect.get(target, p, receiver);
    },
});