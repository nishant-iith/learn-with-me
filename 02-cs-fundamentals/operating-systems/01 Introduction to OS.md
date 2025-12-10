## \#️⃣ Operating System and its Functions

### 💻 OS Definition

An Operating System (OS) is a software that manages the hardware and software resources of a computer. It is the **interface** between the user and the computer.

Primary Goals:

1.  **Convenience** $\rightarrow$ To make the computer easy to use and efficient.
2.  **Throughput** $\rightarrow$ To make the computer perform well. (Throughput = Number of tasks completed per unit time)

Functions of OS:

1.  **Resource Management** $\rightarrow$ To manage the primary (memory) and secondary (disk) resources of the computer.
2.  **Process Management** $\rightarrow$ To manage the processes of the computer.
3.  **File Management** $\rightarrow$ To manage the files of the computer.
4.  **Device Management** $\rightarrow$ To manage the I/O devices of the computer.
5.  **Security Management** $\rightarrow$ To manage the security of the computer.
6.  **Storage Management** $\rightarrow$ To manage the storage of the computer (primarily through the file system).
7.  **Network Management** $\rightarrow$ To manage the network of the computer.
8.  **Memory Management** $\rightarrow$ To manage the **RAM** (Primary Memory) of the computer.
9.  **Input/Output Management** $\rightarrow$ To manage the input/output operations of the computer.
10. **Process Scheduling** $\rightarrow$ To schedule which processes get access to the CPU.

-----

## ⚙️ Types of OS

1.  **Batch OS**

      * **Definition:** Batch OS is a type of OS that processes a set of similar tasks (a batch) one after the other.
      * **How it works:** The user submits tasks, the OS gathers them into a batch, and the tasks are processed sequentially without user interaction.
      * **Problems:** Long wait time, inefficient use of resources (CPU idle time), limited interactivity.
      * **Punch Cards:** Used to input data/instructions into the computer. Each card had holes representing the data.
      * **Example:** Fortran, IBSYS.

2.  **Multiprogramming OS**

      * **Characteristic:** **Non-Preemptive** (usually).
      * **Mechanism:** Multiple programs reside in memory (RAM) simultaneously. When one program waits for I/O, the OS switches to another program to utilize the CPU, increasing efficiency.

3.  **Multitasking OS (Time-Sharing OS)**

      * **Characteristic:** **Preemptive** (essential).
      * **Mechanism:** Multiple programs run on a single processor, each getting a small **Time Quantum** to run before being forced to switch (context switching). This gives the illusion of simultaneous execution and allows high interactivity.

4.  **Multiprocessing OS**

      * **Mechanism:** Utilizes **multiple CPUs/processors** within a single computer system to execute processes simultaneously (true parallel execution).

-----

## 🔑 Key Terms

  * **Preemptive**: The OS can **force** a process to stop (preempt) its execution, typically due to its time quantum expiring or a higher-priority process arriving. A process may be completed in multiple runs.
  * **Non-Preemptive**: The OS **cannot** force a process to stop. A process runs until it voluntarily yields the CPU (e.g., completes or waits for I/O). The process is completed in a single run.
  * **Long Term Scheduler (LTS)**: **Selects processes from secondary memory** (New state) and loads them into RAM (Ready Queue). It controls the **degree of multiprogramming**.
  * **Short Term Scheduler (STS) / CPU Scheduler**: **Selects a process from the Ready Queue** and assigns it to the CPU (moves it to the Running state). This is the **most frequent** scheduler.
  * **Medium Term Scheduler (MTS)**: Responsible for **swapping** (moving) processes *out* of RAM (to the **Suspended** state in secondary memory) and later *back in* to reduce the degree of multiprogramming and free up memory.
  * **Context Switching**: The process of **saving the state (Context)** of the currently Running process and **restoring the state** of the next process to be run. This is a pure overhead cost.
  * **Time Quantum**: A small, fixed unit of CPU time assigned to each process in a round-robin scheduling algorithm (used in Multitasking OS).

-----

## 🚦 Process States in OS:

1.  **New**: Process is created but has not yet been loaded into RAM (In secondary memory).
2.  **Ready Queue**: Process is in RAM and is waiting for the CPU (Ready to run).
3.  **Running**: Process is currently executing instructions in the CPU (still in RAM).
4.  **Wait/Block**: Process is waiting for some event to occur (e.g., I/O completion, resource availability). Just another queue in RAM.
5.  **Terminated**: Process is finished. Deallocation of all resources occurs.
6.  **Suspended**: Process is temporarily moved out of RAM to secondary memory (handled by the Medium Term Scheduler).

<!-- end list -->

```mermaid
flowchart TD
    New --["Long Term Scheduler (LTS)"]--> Ready_Queue
    Ready_Queue --["Short Term Scheduler (STS)"]--> Running
    Running --["I/O Request / Hardware Event"]--> Wait_Block
    Running --["Time Quantum Expires / Higher Priority"]--> Ready_Queue
    Wait_Block --["I/O Complete / Event Occurred"]--> Ready_Queue
    Running --> Terminated
    Wait_Block --["Medium Term Scheduler (Swapping Out)"]--> Suspended
    Suspended --["Medium Term Scheduler (Swapping In)"]--> Ready_Queue
```