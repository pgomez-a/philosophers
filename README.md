# philosophers

**If you want to learn more about IT topics, visit my website:** [**IA Notes**](https://ia-notes.com/)

Along with the processes, another important part of the optimization of a program resides in the **use of threads**. With this project, we are going to learn what a thread is, how to use threads to that our program can run faster and how to lock shared resources with a mutex. With this project, the C branch of 42 will be seen and completed.

### Concurrent programming
**Concurrent programming** is a form of programming where executions are performed at overlapping runtimes rather than sequentially. A concurrent system is characterized by being able to execute processes that do not have to wait for other previous executions to finish. It is also characterized by being able to run multiple executions at the same time.<br>
The main advantages of concurrent programming are:
- **Improvements in the efficiency** of the applications.
- **Improvements in the response times** of input/output operations.
- The time that the CPU is not used can be used by another process

One of the most important libraries for working with threading and concurrent programming is **pthread**. This library will allow you to:
- <b>Manage threads:</b> create, join and manage the lifespan of a thread.
- <b>Mutex:</b> synchronizes access to shared data between threads.

### What is a thread?
**A thread** is a programming concept that will allow us to **separate a process into multiple separate tasks**, so that the same program can **execute different operations at the same time**. This gives the processor greater flexibility in optimizing and managing the tasks it has to perform. Threads are the smallest units of processing instructions that the operating system sends to the processor. Using multiple threads to run a single program is more efficient as multiple tasks can be performed simultaneously.<br><br>
The processes are divided into threads. Each process always starts with a single main thread. However, programmers can create more threads. For this reason, a program can be made up of one or more processes that, at the same time, can be divided into one or more threads. The threads of a process **share the code segment and the data segment** to be able to use the same resources at the same time. By doing this, tasks will be completed faster. However, **each thread has its own stack**, so local variables will not be shared between threads in a process.

### What is a core?
**A processor** is responsible for executing the instructions of the programs stored in the RAM of our computer. In the physical aspect, a processor in an integrated circuit made up of millions of transitors that establish logic gates to let or not let bits of data pass in the form of energy.<br><br>
Inside this little chip there are different modules that we can call cores. A few years ago, processors had a single core and could only execute one [**instruction per cycle**](https://github.com/pgomez-a/libasm). These cycles are measured in HZ, so **the more HZ, the more instructions can be executed per second**. Processors today are made up of multiple cores. These special cores are called sub-processors, so if we have a 4-core sub-processor, we will be able to run 4 tasks at the same time. The important aspect of cores is that they exist physically. In contrast, threads are not part of the hardware but are a software concept.

### Threads vs Cores
Threads cannot be confused with the cores of a processor. Threads and multi-cores help programs execute instructions faster, but they are different things. The main difference between them is that we find cores at the hardware level, while threads can only be seen at the software level. **This means that threads do not really exist, while cores are physical processors installed on a single chip**. In order for them to work, threads must share some system resources within the same core, so the data shared between threads will always be stored in the core where the threads are created.

```
There is a downside to using threads and that is that they can interfere with each other, especially when they have to access shared resources.
Imagine that the same data is modified by several threads at the same time. This is a very bad situation that can happen if we don't know how to avoid it.
To solve this, we will learn how to use mutex.
```

### Mutex
Once we know what a thread is and how threads can help us perform different tasks at the same time, we have to realize that conflicts can sometimes arise when accessing shared data. Here, we have some of the downsides to using threads:
- To return the result of a thread's execution, the thread must be stopped.
- There is no way to share data so that the reading or writing of it is done safely.

To solve this problem **we are going to use mutex**, which allow us to:
- **Lock a mutex** with an atomic operation to ensure that only one variable accesses a value that has been shared. In this way, only this variable could access this value until the mutex is unlocked.
- **Unlock a mutex** to allow other processes to access the same memory address.

So **what is a mutex?** Mutex comes from the term **"mutual exclusion"**. They are used in concurrent programming to avoid the access of more than one thread to a critical area simultaneously. The critical area is the code segment where I can modify a share. Most of these resources are signals, counters, queues, and data. Therefore, **a mutex allows you to synchronize the use of a shared resource between threads**.


