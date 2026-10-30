#include <thread>
#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>

std::vector<double> median(std::vector<double> nums){
	std::sort(nums.begin(),nums.end());
	double res=nums[nums.size()/2];
	
	return {nums[0],res,nums[nums.size()-1]};
}
void worker(const std::vector<int>& a,size_t n,size_t start,size_t end,long long& out){
        long long sum=0;
        for(size_t i=start;i<end;i++){
                for(size_t j=0;j<n;j++){
                        sum+=a[i*n+j];
                }
        }

        out=sum;
}
long long row_rows(const std::vector<int>& a,size_t n,size_t T){
	std::vector<long long> partial(T,0);
        std::vector<std::thread> threads;
        for(size_t t=0;t<T;t++){
                size_t base=n/T;
                size_t extra=n%T;
                size_t start=t*base+std::min(t,extra);
                size_t end=start+base+(t < extra ? 1 :0);
                threads.emplace_back(worker, std::ref(a), n, start, end, std::ref(partial[t]));

        }
        for(auto& th:threads){
                th.join();
        }
        long long total=0;
        for(auto parsum:partial){
                total+=parsum;
        }
        
	return total;
}

int main(int argc, char* argv[]){
	if(argc < 3) {
		std::cerr << "Usage: ./traversal <N><T>\n";
		return 1;
	}
	size_t n = std::strtoul(argv[1], nullptr, 10);		
	size_t T = std::strtoul(argv[2], nullptr, 10);
	std::vector<int> a(n*n);
	for(size_t i=0;i<n*n;i++){
		a[i]=i%100;
	}
	long long warm_sum=0;
	for(size_t i=0;i<n;i++){
		for(size_t j=0;j<n;j++){
			warm_sum+=a[i*n+j];
		}
	}
	int reps=7;
	
	long long total=run_rows(a,n,T);
	long long sink=0;
	sink+=total;
	std::vector<double> ttime(reps);
	for(int i=0;i<reps;i++){
		auto t3=std::chrono::high_resolution_clock::now();
		long long rowtime=run_rows(a,n,T);
		auto t4=std::chrono::high_resolution_clock::now();
		double col_ms = std::chrono::duration<double, std::milli>(t4-t3).count();
		ttime[i]=col_ms;
		sink+=total;
	}
	std::vector<double> medtime=median(ttime);
	std::cerr<<sink<<"\n";
	std::cout<<n<<","<<T<<","<<medtime[1]<<"\n";
	
	return 0;
}
