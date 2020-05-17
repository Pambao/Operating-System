<h1> OPERATING SYSTEM REVIEW QUESTION </h1>

*The followings are the list of solutions for the final exam review question*

# Chapter 1: Introduction

## Review question 
- 1.2 *Provide at least three resources the operating system allocate*
    - CPU time, memory space, file-storage space, I/O devices
- 1.5 *What is an interrupt?*
    - A signal sent from either hardware or software the stops a CPU from performing its current action and transfers execution to a fixed location (interrupt vector) in order to perform a specific service routine
- 1.17 *What are the two separate modes of operation?*
    - User and kernel
- 1.31 *Provide an example of an open source operating system*
    - Linux
    - BSD Unix
    - Solaris
 ## Exercise
- 1.1 *What are three main purposes of an operating system?*
    - Manage system resources
    - Control execution of application software
    - Make it easier for users to interact with computers
- 1.10 *Give two reasons why caches are useful. What problems do they solve? What problems do they cause? If a cache can be made as large as the device for which it is caching (for instance, a cache as large as a disk), why not make it that large and eliminate the device?*
    - Caches are useful when two or more components need to exchange data, and that components perform transfers at different speeds. Caches solve the problem by providing a buffer of intermediate speed between the components. If fast device find data it need in the cache, it doesn't have to wait for the slow devices.
    - The problem it has is the data in the cache must be consistent with the data in the components. If the data component change the value, that data in cache must be updated as well (Additional level of coherency and consistency assurance). Additionally, we also incur an economic and space (at the computer organization level) penalty when we add a cache. 
    - Making a cache as large as a disk would be ineffective because it would be too costly to setup a equal-size-cache as disk. Moreover, data on disks are required to be persistent while cache is generally a volatile memory.
# Chapter 2: Operating System Structure
## Review Question
- 2.4 *What is a system call?*
    - Is an interface to the services made available by an operating system.
- 2.7 *List at least three of the major categories of system calls.*
    - Process control
    - File manipulation
    - Device manipulation
    - Information maintenance
    - Communication
    - Protection
- 2.14 *List at least three different ways of structuring an operating system.*
    - Monolithic
    - Layered
    - Microkernel
    - Modular
    - Hybrid
- 2.16 *What are the two devices that run the IOS operating system?*
    - Iphone
    - Ipad
## Exercise
- 2.1 *What is the purposes of system call?*
    - System call allow user-level processes to request services of opearing system.
- 2.13 *Describe the three general methods of passing parameters to operating system.*
    - Pass the parameters in registers (this way prove insufficient when there are more parameters than registers).
    - Store the parameter in a block or table in memory and pass the address of block to the register (This approach is used by Linux and Solaris).
    - Push the parameters onto a stack to be popped off by the OS. (This approach does not limit the number of length of parameters passed).
# Chapter 3: Processes
## Review Question
- 3.1 *What are the four components of a process?*
    - Stack
    - Heap
    - Data
    - Text 
- 3.2 *Provide at least three possible states a process maybe in.*
    - New
    - Ready
    - Waiting
    - Running
    - Terminated
- 3.7 *What is the degree of multiprogramming?*
    - The maximum number of process in memory controlled by the long term scheduler.
- 3.15 *What are the two fundamental models of interprocess communication?*
    - Independent
    - Cooperating
  ## Exercise
- 3.1 *Using the program shown in Figure 3.30, explain what the output will be at Line A*
![Figure 3.30](Resource\Figure3_30.JPG)
    - The result is still 5 as the child updates it copied value. When control return to parent, the value is remain at 5.
- 3.2 *Including the initial parent process, how many processes are created by the program shown in Figure 3.31?*
![Figure 3.31](Resource\Figure3_31.JPG)
    - There are 8 processes created.
- 3.5 *When a process creates a new process using fork() operation, which of the following state (stack, heap, shared memory segments) is shared between the parent processes and the child processes ?*
    - Only the shared memory segments are shared between the parent process and newly fork child processes. Copies of the stack and the heap are make for the newly created processes.
- 3.14 *Using the program in Figure 3.34, identify the values of pid at lines A, B, C and D. (Assume that the actual pids of the parent and child are 2600, and 2603 respectively)*
![Figure 3.34](Resource\Figure3_34.JPG)
    - A = 0
    - B = 2603
    - C = 2603
    - D = 2600
    
 # Chapter 4: Threads
 ## Review Question
 - 4.2 *Provide at least three benefits of multithreaded programming*
    - Responsiveness
    - Resource sharing
    - Economy
    - Scalability
- 4.6 *What are the two general types of parallelism?*
    - Data parallelism - focuses on distributing subsets of the same data across multiple computing cores and performing the same operation on each core.
    - Task parallelism - involves distributing tasks across multiple computing cores.
- 4.7 *List three common ways of mapping user thread to kernel thread*
    - Many-to-one
    - One-to-one
    - Many to many
- 4.10 *What are three main thread libraries in use?*
    - POSIX PTHREADS
    - Windows Threads
    - Java
## Exercise
- 4.1 *Provide three programming examples in which multithreading provides better performance than a single-thread solution.*
    - A Web server that services each request in a separate thread.
    - A parallelized application such as a matrix multiplication where different part of the matrix may be work on in paralledl.
    - An interactive GUI program such as a debugger where a thread is used to monitor user input, another thread represents the running application, and the third thread monitors performance. 
- 4.2 *What are two differences between user-level threads and kernel-level threads? Under what circumstances is one type better tha the other?*
    - User
- 4.8
- 4.15
 # Chapter 5:
  ## Review Question
  - 5.2
  - 5.3
  - 5.4
  - 5.25
  ## Exercise
  - 5.3
  - 5.7
  - 5.8
  - 5.10
  - 5.17
 # Chapter 6: 
  ## Review Question
  - 6.1
  - 6.3
  - 6.9
  - 6.15
  ## Exercise
  - 6.2
  - 6.16
  - 6.17
  - 6.19
 # Chapter 7:
  ## Review Question
  - 7.1
  - 7.2
  - 7.14
  - 7.15
  ## Exercise
  - 7.1
  - 7.4
  - 7.11
  - 7.20
 # Chapter 8:
  ## Review Question
  - 8.3
  - 8.7
  - 8.8
  - 8.9
  ## Exercise
  - 8.3
  - 8.8
  - 8.21
 # Chapter 9:
  ## Review Question
  - 9.10
  - 9.11
  ## Exercise
  - 9.3
  - 9.4
  - 9.6
  - 9.6
 # Chapter 10:
  ## Review Question
  - 10.1
  - 10.2
  - 10.3
  - 10.7
  ## Exercise
  - 10.7
  - 10.12
 # Chapter 11:
  ## Review Question
  - 11.3
  - 11.6
  - 11.7
  - 11.9
 
 
 