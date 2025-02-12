---
title: Why use QUIC
---


## why QUIC generally outperforms multiple TCP connections in mobile scenarios.
Connection Migration: QUIC was specifically designed with mobility in mind. When a device changes networks (e.g., from WiFi to cellular or between cell towers), QUIC can maintain the same connection without requiring a new handshake. This works because:

QUIC connections are identified by a Connection ID rather than by the 4-tuple (source IP, source port, destination IP, destination port)
When the IP address changes, the Connection ID remains valid
The connection state is preserved during the transition


**0-RTT Connection Resumption**: If a connection does drop completely, QUIC can often resume with zero round-trips, whereas each TCP connection would need to go through the full handshake process again.
Unified Congestion Control: Multiple TCP connections compete with each other, which can actually worsen performance during network transitions. QUIC uses a single congestion window for all streams.

The multiplication of reliability that you're thinking of with multiple TCP connections doesn't work quite as expected in mobile scenarios because:

**Correlated Failures**: When a mobile device changes networks or experiences a coverage gap, all TCP connections typically fail simultaneously since they're all using the same physical path.
Handshake Overhead: Each TCP connection needs to be re-established separately, multiplying the reconnection delay.
Slow Start After Reconnection: Each TCP connection must go through slow start again after reconnection, whereas QUIC can often maintain its congestion window.

Imagine a mobile user downloading content requiring 6 connections while moving between cell towers:

### Multiple TCP Scenario:

All 6 connections break during the handover
Each connection requires a new 1-RTT or 2-RTT handshake (plus TLS handshake)
Each connection starts with a small congestion window
Total recovery time: ~6-12 RTTs plus connection establishment

### QUIC Scenario:

The QUIC connection identifies the IP change
Connection ID remains valid
No new handshake required
Congestion control state is preserved
Total recovery time: ~0-1 RTTs

There are scenarios where multiple TCP connections might perform better (very stable networks with high bandwidth), but for the specific case of mobile networks with frequent transitions and connection drops, QUIC's design provides significant advantages over multiple parallel TCP connections.

## Server-Side Resource Management
1. Multiple TCP Connections:

Each TCP connection maintains separate state (congestion window, RTT estimation, etc.)
For 1,000 clients with 6 connections each = 6,000 TCP states to track
Memory overhead: ~2-4KB per connection = 12-24MB for connection state alone
Significant CPU overhead from context switching between connections
Kernel-level TCP processing becomes a bottleneck

2. QUIC (One connection per client):

One connection state per client = 1,000 QUIC connection states
Memory overhead: ~5-8KB per connection = 5-8MB total (despite slightly larger per-connection state)
Reduced context switching overhead
More efficient CPU utilization
User-space implementation allows for better scaling on multicore systems

## Network-level Effects
1. Multiple TCP Connections:

Congestion Window Multiplication: Each client gets 6× the bandwidth they would with a single connection
Fairness Issues: Clients with more connections get disproportionate bandwidth
Amplified Network Congestion: During network congestion, thousands of independent TCP connections react individually:

Each connection reduces its window size independently
Results in chaotic "TCP sawtooth" behavior at scale
Can cause network-wide congestion oscillation


SYN Flood Risk: Thousands of new connections in short time periods can overwhelm connection tracking

2. QUIC:

Fair Bandwidth Allocation: Each client gets appropriate share regardless of resource count
Coordinated Congestion Response: All streams within a connection respond cohesively
Reduced Network Load: Fewer handshakes and control packets
Better Congestion Signal Processing: More accurate network modeling with unified measurements
Connection Coalescing: Multiple domain resources can share a single connection if they are the same server


## Where TCP wins?
multiple TCP connections might achieve higher throughput than QUIC because:

Hardware offloading reduces CPU impact of TCP processing
The multiple connections quickly ramp up to fill the available bandwidth
Stable network conditions mean TCP's congestion control rarely backs off
The connections benefit from parallel processing across CPU cores

These advantages typically only manifest in very controlled environments like:

Enterprise data centers with high-quality infrastructure
Research networks with specialized hardware
Dedicated point-to-point links
Environments with extensive TCP optimization
