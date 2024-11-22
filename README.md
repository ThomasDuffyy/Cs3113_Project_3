# Cs3113_Project_3
A shared Protected Circular Queue and Communication between threads

Producer-Consumer Problem with Semaphores

Overview

This project demonstrates the implementation of the classic Producer-Consumer Problem using C programming and semaphores. The program showcases how to synchronize two threads (producer and consumer) accessing a shared circular buffer with a fixed size of 15. It focuses on managing resource sharing, avoiding race conditions, and ensuring proper inter-thread communication.

Features
	Implements a circular buffer with 15 slots for inter-thread communication.
	Uses POSIX semaphores for synchronization:
	empty: Tracks empty slots in the buffer.
	full: Tracks filled slots in the buffer.
	mutex: Ensures mutual exclusion when accessing the buffer.
	Includes a producer thread:
	Reads characters from a file (mytest.dat).
	Writes characters into the circular buffer.
	Signals completion by inserting a special marker (*).
	Includes a consumer thread:
	Reads characters from the circular buffer.
	Prints characters to the screen with a 1-second delay between reads.
	Stops when the special marker (*) is read.
	Handles up to 150 characters from the input file.
	Ensures proper cleanup of semaphores and resources after execution.

 How it Works
 	Producer:
	•Reads characters from a file (mytest.dat) one by one.
	•Writes each character into the buffer, waiting if the buffer is full.
	•Inserts a special marker (*) to signal the end of input.
	Consumer:
	•Reads characters from the buffer, waiting if the buffer is empty.
	•Prints each character to the screen.
	•Sleeps for 1 second after printing each character to simulate a slower consumer.
	Synchronization:
	•Semaphores ensure:
	•The producer and consumer do not access the buffer simultaneously.
	•The producer does not overwrite unread data, and the consumer does not read unproduced data.

 Set up and compilation instructions

  In my directory called Project, I have two files, Project_3.c and mytest.dat 
  
  Compile the program using GCC:
    gcc -pthread -o Project_3 Project_3.c
    
  Execute the program 
    ./Project_3
    
  The program will read the file mytest.dat and display its contents character by character, with a 1-second delay between each character.
  
<img width="703" alt="Screenshot 2024-11-22 at 5 24 34 PM" src="https://github.com/user-attachments/assets/5b59f10c-49eb-454e-a35a-eb5883f698ca">

Code Structure
	Header Files:
	  •<pthread.h>: For multithreading.
	  •<semaphore.h>: For semaphores.
	  •<stdio.h> and <stdlib.h>: For file I/O and standard functions.
	  •<unistd.h>: For sleep function.
  Main Components:
	  •producer(): The producer thread function.
	  •consumer(): The consumer thread function.
	  •main(): Initializes semaphores, creates threads, and handles cleanup.

  Key Concepts
  	  Circular Buffer: A fixed-size data structure where the producer writes data, and the consumer reads it in a circular manner.
	  	Semaphores:
	  •Prevent simultaneous access to shared resources.
	  •Synchronize producer and consumer operations.
	   Multithreading: Allows concurrent execution of producer and consumer threads.
	
