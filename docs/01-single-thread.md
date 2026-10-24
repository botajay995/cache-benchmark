
#stage 1:Single-threaded row vs column traversal

##machine specs
-CPU i7-10750H, 6 cores/ 12 threads
-L1d 32 Kib/core, L2 256 Kib/core, L3 12 Mib shared
-OS: Ubuntu on WSL2, gcc 15.2.0

##Hypothesis Row major traversal will be faster than column major due to the way cache works and it it stores it in the memory and in column major the problem is that the cpu cannot predict where the next element will be
##so it wastes a lot of traversals to the main memory and it does not find it locally in the cache memory

##predixtion is that for n=16 the row column will be much faster due to the reason that 15/16 memory location will be accesed from the cache itself
##but for the column around 1/16 will be accessed from the cache rather than the memory so it must be much much slower

##result the graph show very accurately depicts how the numerator (column time increases much more with respect to the row major time)

##analysis: the row major  fetches 16 16 integers at a single time out of which only a single one time is from main memory 
##and the remaining cache are cache hits and not cache misses

