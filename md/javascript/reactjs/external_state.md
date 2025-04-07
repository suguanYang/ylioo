---
title: React state
---

## External State

useSyncExternalStore may break the pending updates like useTransition, https://react.dev/reference/react/useSyncExternalStore#caveats
But if you subscribe an external store in useEffect will cause tearing, useEffect is async, means it can be defered(especiallyh in concurrent mode, it can cancel and pending the effects) for a long time between it gets the snapshot and the subscription, which will lost updates between this period;
Jotai choose an eventually consistency approch, re-render(useReducer, a no-op dispatch will bailout) the current component to ensure it subscripts to latest updates.

## How Dependencies Breaks the Closure
React manages this by:
Storing the previous dependencies array
Comparing with new dependencies on each render
Cleaning up the old effect and running a new one with new closure static context when dependencies change
