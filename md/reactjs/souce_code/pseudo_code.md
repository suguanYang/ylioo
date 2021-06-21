```javascript
// react-reconciler
class FiberRootNode {
  constructor(container) {
    // this.tag = tag;
    // this.containerInfo = containerInfo;
    // this.pendingChildren = null;
    // this.current = null;
    // this.pingCache = null;
    // this.finishedWork = null;
    // this.timeoutHandle = noTimeout;
    // this.context = null;
    // this.pendingContext = null;
    // this.hydrate = hydrate;
    // this.callbackNode = null;
    // this.callbackPriority = NoLane;
    // this.eventTimes = createLaneMap(NoLanes);
    // this.expirationTimes = createLaneMap(NoTimestamp);

    // this.pendingLanes = NoLanes;
    // this.suspendedLanes = NoLanes;
    // this.pingedLanes = NoLanes;
    // this.expiredLanes = NoLanes;
    // this.mutableReadLanes = NoLanes;
    // this.finishedLanes = NoLanes;

    // this.entangledLanes = NoLanes;
    // this.entanglements = createLaneMap(NoLanes);
  }
}

class FiberNode {
  constructor(HostRoot) {
    this.balabala = balabala;
  }
}

function initializeUpdateQueue(fiber) {
  fiber.updateQueue = {
    baseState: fiber.memoizedState,
    firstBaseUpdate: null,
    lastBaseUpdate: null,
    shared: {
      pending: null,
      interleaved: null,
      lanes: NoLanes
    },
    effects: null
  };
}

function createFiber(HostRoot) {
  return new FiberNode(HostRoot)
}

function createHostRootFiber() {
  return createFiber(HostRoot);
}

function createFiberRoot(container) {
  const root = new FiberRootNode(container);
  const uninitializedFiber = createHostRootFiber();
  return root;
}

// react-dom.js
class ReactDomRoot {
  constructor(container) {
    // this._internalRoot = createFiberRoot(container);

    const uninitializedFiber = new FiberNode(HostRoot);
    this._internalRoot = new FiberRootNode(container);
    this._internalRoot.current = uninitializedFiber;
    uninitializedFiber.stateNode = root;
    uninitializedFiber.updateQueue = {
      // states
    };
  }
}

const container = document.querySelector('div)';
const uninitializedFiber = new FiberNode(HostRoot);
uninitializedFiber.stateNode = root;
uninitializedFiber.updateQueue = {
  // states
  // baseState: fiber.memoizedState,
  // firstBaseUpdate: null,
  // lastBaseUpdate: null,
  // shared: {
  //   pending: null,
  //   interleaved: null,
  //   lanes: NoLanes
  // },
  // effects: null
};
const root = new FiberRootNode(container);
root.current = uninitializedFiber;

container.__reactContainer$q23123 = root.current;
// delegate some events
listenToNativeEvent(container);

// render

container.context = {}; // first render
container.pendingContext = {}; // none first render
// createUpdate
const update = {
  // states
  // baseState: fiber.memoizedState,
  // firstBaseUpdate: null,
  // lastBaseUpdate: null,
  // shared: {
  //   pending: null,
  //   interleaved: null,
  //   lanes: NoLanes
  // },
  // effects: null
  payload: element
};
// enqueueUpdate
if (isInterleavedUpdate) {

} else {
  if (root.current.updateQueue.pending === null) {
    // this is the first update
    update.next = update;
  } else {
    update.next = pending.next;
    pending.next = update;
  }
  sharedQueue.pending = update;
}

```