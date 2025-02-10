---
title: "ACID Properties with Lag-Based Design"
---

If a system do not require real time data, we can make all data operations
append-only, and run a merge background task to aggrate data.
This can avoid concurrency situation, and still keep ACID property