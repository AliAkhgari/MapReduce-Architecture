# MapReduce-Architecture

In this project, we aim to build a word counter utilizing the MapReduce architecture, providing an opportunity to learn about managing processes and their inter-communication pathways.

## System Architecture
The system architecture comprises three types of processes: Main process, Map process, and Reduce process:

1. **Main Process:** The central or parent process in this system is the Main process. Its responsibility involves initiating the Reduce and Map processes. It creates a Map child process for each CSV file in the test cases directory and assigns their filenames. An unnamed pipe is used for transferring the filename to the Map process. Additionally, a Reduce process is initiated within the Main process, which transfers the final results back to the Main process. At this point, the Main process records these results in the output.csv file.

2. **Map Process:** Each Map process receives a specific filename on which it is to operate. Each process calculates the frequency of word occurrences within the assigned file at this stage. The output consists of multiple keys (words) and their corresponding values (the count of word repetitions). Each Map process transmits its output to the Reduce process using a named pipe.

3. **Reduce Process:** This process, initiated by the Main process, stays in wait mode until it receives the output from all Map processes. At this point, the received outputs are consolidated and the frequency of each word across all files is calculated. Ultimately, the output is returned to the Main process using an unnamed pipe.

The Main process creates these processes using the fork and exec system calls for their creation and execution.