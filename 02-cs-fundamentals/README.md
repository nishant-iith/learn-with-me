# Computer Science Fundamentals

Core computer science concepts and theory.

## Contents
- [Operating Systems](./operating-systems/)
- [Database Systems](./database-systems/)
- [Computer Networks](./computer-networks/)

---

## The CS Fundamentals Master Stack

### 1. Operating Systems (The Foundation)
**The Bible (Book):** [OSTEP (Operating Systems: Three Easy Pieces)](https://pages.cs.wisc.edu/~remzi/OSTEP/)

**Why:** It is free, industry-standard, and reads like a story, not a manual.

**Focus Chapters:** Virtualization (CPU/Memory) and Concurrency

**The Visualization (Video):** [Gate Smashers OS Playlist](https://www.youtube.com/@GateSmashers)

**Usage:** Watch only if you get stuck on a concept in the book. It's excellent for visualizing algorithms (like Round Robin or Paging).

### 2. DBMS (The Data Engine)
**The Internals (Video):** [CMU 15-445: Intro to Database Systems](https://15445.courses.cs.cmu.edu/) (Andy Pavlo)

**Warning:** This is hard. It teaches you how to build a database, not just use one.

**Focus:** Lectures 01-06 (Architecture, Storage, Buffer Pools) and 16-18 (Concurrency Control)

**The Basics (SQL & Normalization):** [Gate Smashers DBMS Playlist](https://www.youtube.com/@GateSmashers)

**Usage:** Use this for 2NF/3NF/BCNF and basic SQL queries.

### 3. Computer Networks (The Glue)
**The Modern Bible (Book):** [High Performance Browser Networking (HPBN)](https://hpbn.co/)

**Why:** Most colleges teach the "OSI Model" from the 90s. This book teaches TCP/UDP/TLS/HTTP in the context of modern Web Apps (crucial for your Node.js goals).

**The Basics (Video):** [Neso Academy - Computer Networks](https://www.youtube.com/@nesoacademy)

**Usage:** Watch the first 10-15 videos to understand OSI Model, IP Addressing, and Subnetting.

---

## Execution Order (Sequential)

**We will not do all three simultaneously.** We rotate them based on your C++ progress.

### Month 1 (With C++ Memory): Operating Systems
**Reason:** Learning Pointers in C++ helps you understand "Virtual Memory" in OS. They are the same concept.

**Topic:** Virtualization (Processes, Threads, Context Switching)

### Month 2 (With C++ OOPS): DBMS
**Reason:** Understanding "Classes" helps you understand "Tables" and "Schema Design".

**Topic:** Normalization, Indexing (B-Trees), SQL

### Month 3 (With Node.js): Computer Networks
**Reason:** You cannot understand Backend (Node.js) without understanding HTTP/TCP.

**Topic:** TCP/IP, UDP, HTTP/1.1 vs HTTP/2

---

## Study Strategy

1. **Parallel with C++:** CS Fundamentals should be studied alongside C++ programming
2. **Sequential Topics:** Focus on one CS fundamental at a time
3. **Conceptual Synergy:** Leverage knowledge from one domain to understand another
4. **Practical Application:** Connect theoretical concepts with real-world implementations
