#stage 1:Single-threaded row vs column traversal

##machine specs
-CPU i7-10750H, 6 cores/ 12 threads
-L1d 32 Kib/core, L2 256 Kib/core, L3 12 Mib shared
-OS: Ubuntu on WSL2, gcc 15.2.0

##Hypothesis Row major traversal will be faster than column major due to the way cache works and it it stores it in the memory and in column major the problem is that the cpu cannot predict where the next element will be
##so it wastes a lot of traversals to the main memory and it does not find it locally in the cache memory
