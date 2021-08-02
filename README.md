# philosophers
Along with the processes, another important part of the optimization of a program resides in the use of threads. With this project, we are going to learn what a thread is, how to use threads to
that our program can run faster and how to lock shared resources with a mutex. With this project, the C branch of 42 will be seen and completed.

### Concurrent programming
Concurrent programming is a form of programming where executions are performed at overlapping runtimes rather than sequentially. A concurrent system is characterized
by being able to execute processes that do not have to wait for other previous executions to finish. It is also characterized by being able to run multiple executions
at the same time.<br>
The main advantages of concurrent programming are:

- Improvements in the efficiency of the applications.
- Improvements in the response times of input/output operations.
- The time that the CPU is not used can be used by another process

One of the most important libraries for working with threading and concurrent programming is pthread. This library will allow you to:

- <b>Manage threads:</b> create, join and manage the lifespan of a thread.
- <b>Mutex:</b> synchronizes access to shared data between threads.

### What is a thread?

