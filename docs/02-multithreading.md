now we will try to introduce thread to acheive higher performance
we will first try to split the work among the thread as equal as possible
we will introduce padding if its required

2)we will give each one of the threads its own local sum variable and add all the local sums in the end
 rather than using a shared total variable as it can lead to the problem of data race where multiple threads
 reach the same variable and writing takes place

1)how much growth should i expect as the number of cores and threads increase (CPU has 6 cores 2 threads per core)
-As the number of cores increase i would expect linear growth according to that and as mroe and more hyper threads 
are introduced there should be no linear increase rather a very very small incremental increase close to 10-15%


FORMULA:The formula used to evenly split the work among the different threads will be:
start=t*base+min(t,extra)

where:t=number of threads
base:total number of rows/number of threads

RESULTS:We expected a near linear speedup for the row major traversal but according to the results what we notice is that at a lower N we are bounded by the
time it takes to distribute the work and synchronization
but for the larger N it is bounded by the memory bandwidth of the ram(the weight the bus can carry basically)

