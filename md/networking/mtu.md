---
title: "Why my network hang"
---

I recently went down a debugging what seemed like a simple connection failure, and the journey revealed some fundamental truths about how the internet works.

The Setup and The Symptom
It all started with a simple setup:

A curl command to a secure website (https://google.com).

Running inside WSL2 (Windows Subsystem for Linux).

All traffic routed over a Tailscale VPN tunnel.

The command would just hang, eventually timing out. My first instinct was to open Wireshark to see what was happening on the network. The capture showed the TCP three-way handshake (SYN, SYN-ACK, ACK) completing successfully, but then the connection would stall right after my client sent its Client Hello message to start the TLS encryption. After a long pause, the connection would end with a [RST] reset packet.

![](../assets/debugging.png)

The key symptom was clear: the connection was established, but it died waiting for the server's response (the Server Hello), which seemed to vanish into thin air.

The Plot Twist: Isolating the Problem
After checking for firewall rules and application bugs, the most critical clue emerged: the connection worked perfectly when run from PowerShell on the Windows host. It only failed from within WSL2.

This was the key. The problem wasn't with Google's server or my internet connection in general. The issue was specific to the interaction between WSL2's virtual network and the Tailscale VPN.

Unmasking the Culprit: MTU
The culprit was a classic, often-overlooked network setting: the Maximum Transmission Unit (MTU).

Think of MTU as the largest "package size" allowed on a network path. The standard for the internet is 1500 bytes. However, a VPN like Tailscale adds its own encryption headers to every packet, effectively creating a "narrower tunnel" that requires smaller packages to get through.

![](../assets/mtu_debugging.png)


WSL2 wasn't aware of this narrower tunnel. It was creating standard-sized 1500-byte packets, but when these oversized packets hit the VPN, a router somewhere down the line saw they were too big and, following the rules, simply dropped them. The Server Hello from Google, often a large packet due to security certificates, was the first victim.

The 'Why': How a Client Setting Affects the Server
You might be wondering, "How does changing a setting on my client fix a problem with a packet sent from the server?"

The answer lies in the initial TCP handshake. When your client sends its first [SYN] packet, it includes a value called the Maximum Segment Size (MSS), which is calculated from its MTU. The MSS is your client telling the server, "When you send data back to me, please don't create any data chunks larger than this size."

By lowering the MTU on my WSL2 instance, I forced it to advertise a smaller MSS to Google's server. The server then politely complied, packaging its Server Hello into a smaller packet that was able to successfully navigate the narrow VPN tunnel.

This is a core design principle of TCP/IP: the endpoints cooperate to ensure reliability, rather than relying on the unpredictable network in the middle.