---
title: "JavaScript Event Loop and Task Scheduling"
---

```
eventLoop = {
    taskQueues: {
        // High priority tasks
        input: [], // User input events (touches, clicks, etc.)
        
        // Normal priority tasks
        networking: [], // XHR, fetch, WebSockets
        domEvents: [], // Most DOM events (except input)
        mediaEvents: [], // Media events (video, audio)
        
        // Low priority tasks
        timers: [], // setTimeout, setInterval
        parsing: [], // HTML parser
        callbacks: [], // requestIdleCallback, etc.
    },
    
    microtaskQueue: [],
    
    nextTask: function() {
        // Chrome prioritizes task sources dynamically
        // First check high priority queues
        if (this.taskQueues.input.length > 0)
            return this.taskQueues.input.shift();
            
        // Then check normal priority queues
        for (let q of [this.taskQueues.networking, this.taskQueues.domEvents, this.taskQueues.mediaEvents])
            if (q.length > 0)
                return q.shift();
                
        // Finally check low priority queues
        for (let q of [this.taskQueues.timers, this.taskQueues.parsing, this.taskQueues.callbacks])
            if (q.length > 0)
                return q.shift();
                
        return null;
    },
    
    executeMicrotasks: function() {
        // Process microtasks until queue is empty (including new ones)
        while (this.microtaskQueue.length > 0) {
            let task = this.microtaskQueue.shift();
            task.execute();
        }
    },
    
    needsRendering: function() {
        return (
            this.isVSyncTime() && 
            (this.hasPendingVisualChanges() || this.hasHighPriorityInputEvents())
        );
    },
    
    render: function() {
        // Input events are handled with highest priority
        this.dispatchPendingInputEvents();
        
        // Update layout tree if needed
        if (this.hasPendingStyleOrLayoutChanges()) {
            this.recalculateStyles(); 
            this.updateLayout(); // Reflow
        }
        
        // Run pre-paint steps
        this.runAnimationFrameCallbacks();
        this.updateMediaQueries();
        this.runCSSAnimations();
        this.runCSSTransitions();
        
        // Observer callbacks
        this.runResizeObservers();
        this.runIntersectionObservers();
        
        // Compositing and rendering
        this.updateLayerTree(); // Layerize
        this.paint();
        this.composite();
    },
    
    runIdleCallbacks: function(deadline) {
        while (this.hasIdleCallbacks() && deadline.timeRemaining() > 0) {
            this.executeNextIdleCallback(deadline);
        }
    }
};

while (true) {
    task = eventLoop.nextTask();
    if (task) {
        task.execute();
        eventLoop.executeMicrotasks();
    }
    
    if (eventLoop.needsRendering()) {
        eventLoop.render();
    }
    
    // If there's idle time, run idle callbacks
    if (!task && !eventLoop.needsRendering()) {
        let deadline = eventLoop.createIdleDeadline();
        eventLoop.runIdleCallbacks(deadline);
    }
}
```

normally the task was ordered by FIFO

### example 1
the first setTimeout task was poped out first, beacuse it pushed to task-queue first
```javascript
setTimeout(function () {console.log(1)}, 6);
let i = 0;
while(i < 1000000000) {
 i++;
}
setTimeout(function () {console.log(2)}, 4);
// print
// 1
// 2
```

 
## Nodejs Event Loop

Nodejs event loop is similar to browser's, but it has some differences

```javascript
eventLoop = {
    // Phase queues
    timers: [], // setTimeout, setInterval callbacks
    pendingCallbacks: [], // I/O callbacks deferred to the next iteration
    idleHandlers: [], // setImmediate callbacks
    poll: {
        events: [], // I/O events ready to be processed
        timeout: null // For blocking in poll phase
    },
    check: [], // setImmediate callbacks (alias for idleHandlers)
    close: [], // close event callbacks
    
    // Microtasks are handled differently in Node.js
    nextTickQueue: [], // process.nextTick callbacks
    promiseQueue: [], // Promise resolution callbacks
    
    processMicrotasks: function() {
        // First, process all nextTick callbacks
        while (this.nextTickQueue.length > 0) {
            let callback = this.nextTickQueue.shift();
            callback();
        }
        
        // Then, process all promise callbacks
        while (this.promiseQueue.length > 0) {
            let callback = this.promiseQueue.shift();
            callback();
        }
    },
    
    runPhase: function(phase) {
        let queue = this[phase];
        if (Array.isArray(queue)) {
            // Handle regular array queues
            while (queue.length > 0) {
                let callback = queue.shift();
                callback();
                
                // Process microtasks after each callback
                this.processMicrotasks();
            }
        } else if (phase === 'poll') {
            // Special handling for poll phase
            this.processPollPhase();
        }
    },
    
    processPollPhase: function() {
        // Process any pending I/O events
        while (this.poll.events.length > 0) {
            let event = this.poll.events.shift();
            event.callback();
            
            // Process microtasks after each callback
            this.processMicrotasks();
        }
        
        // If there are setImmediate callbacks or the poll queue is not empty
        // after processing events, don't block
        if (this.check.length > 0 || this.poll.events.length > 0) {
            return;
        }
        
        // If there are timers scheduled, block until the next timer expires
        if (this.timers.length > 0) {
            this.poll.timeout = this.getNextTimerExpiry();
        } else {
            // Otherwise, potentially block indefinitely (or until I/O event)
            this.poll.timeout = Infinity;
        }
        
        // (In reality, this is where libuv would block waiting for I/O events)
    },
    
    getNextTimerExpiry: function() {
        // This would calculate when the next timer is due to expire
        // Simplified for this example
        return Date.now() + 1000; 
    }
};

// Main event loop
function startEventLoop() {
    while (true) {
        // Phase 1: Timers
        eventLoop.runPhase('timers');
        
        // Phase 2: Pending callbacks
        eventLoop.runPhase('pendingCallbacks');
        
        // Phase 3: Idle, prepare (internal only - not represented here)
        
        // Phase 4: Poll
        eventLoop.runPhase('poll');

        // Phase 5: Check
        eventLoop.runPhase('check');

        // Phase 6: Close callbacks
        eventLoop.runPhase('close');
        
        // Check if we need to exit the event loop
        if (this.shouldExit()) {
            break;
        }
    }
}

function shouldExit() {
    // In Node.js, the event loop exits when there are no more:
    // - Active handles (timers, I/O, etc.)
    // - Active requests (ongoing operations)
    // - Pending callbacks in any queue
    
    return (
        eventLoop.timers.length === 0 &&
        eventLoop.pendingCallbacks.length === 0 &&
        eventLoop.idleHandlers.length === 0 &&
        eventLoop.poll.events.length === 0 &&
        eventLoop.check.length === 0 &&
        eventLoop.close.length === 0 &&
        eventLoop.nextTickQueue.length === 0 &&
        eventLoop.promiseQueue.length === 0
    );
}

startEventLoop();
```

### example 2
```javascript
import { Duplex } from 'node:stream';
const stream = new Duplex();
stream._read = () => {}

async function main() {
    const promise = new Promise((resolve, reject) => {
        stream.on("data", (chunk) => console.log('data'));
        stream.on("error", (err) => reject(err));
        stream.on("end", () => resolve("done"));
    });

    console.log("Waiting...");
    await promise;
    console.log("Done");
}

main()
```

The output is:
```
Waiting...
```
There is not active handles, so the event loop will not block, and the event loop will exit.