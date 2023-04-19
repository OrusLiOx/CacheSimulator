# Cache Simulator
Given a file of addresses, the program will identify cache hits and misses. Misses will be classified as compulsory, capacity, or conflict misses. The program will either run as a multi level cache or single level cache depending on the number of arguements as shown in step 3 of "How to build and run".

The input file should contain a list of positive integers separated by spaces. This repository contains a file called "input". This file can be modified or a new file can be made in the same directory as the executable to test a different input. The index in the cache is specified by low order bits of the address and the tag is the high order bits.
## How to build and run
1. Clone this repository

       git clone https://github.com/OrusLiOx/CacheSimulator.git
3. Build the code

       g++ -o cache_sim Main.cpp
3. Run the executable

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Single Level Cache:

    ./cache_sim num_entries associativity memory_reference_file
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Multi Level Cache:

    ./cache L1_num_entries L1_associativity L2_num_entries L2_associativity filename
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;num_entries and associativity are positive integers
   
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;memory_reference_file is the name of the input file
   
4. Results of the program are placed in cache_sim_output
    
## Known bugs / limitations
- This program has only been tested on a university provided Linux server using g++ version 4.8.5. Performance on other systems is unknown.
- I'm not confident that conflict and capacity misses are identified correctly.
