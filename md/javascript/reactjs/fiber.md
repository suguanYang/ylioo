## How Dependencies Breaks the Closure
React manages this by:
Storing the previous dependencies array
Comparing with new dependencies on each render
Cleaning up the old effect and running a new one with new closure static context when dependencies change
