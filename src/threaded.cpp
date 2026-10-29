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
int main(int argc, char* argv[]){
	if(argc < 2) {
		std::cerr << "Usage: ./traversal <N>\n";
		return 1;
	}
	size_t n = std::strtoul(argv[1], nullptr, 10);		
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
	std::vector<double> row;
	std::vector<double> col;
	long long row_sink=0;
	//for row major we will first time it rep times
	int tempr=reps;
	while(tempr--){
		auto t1=std::chrono::high_resolution_clock::now();
		long long row_sum=0;
		for(size_t i=0;i<n;i++){
			for(size_t j=0;j<n;j++){
				row_sum+=a[i*n+j];
			}
		}
		auto t2=std::chrono::high_resolution_clock::now();
		row_sink+=row_sum;
		double row_ms = std::chrono::duration<double, std::milli>(t2-t1).count();
		row.push_back(row_ms);

	}
	int tempc=reps;
	long long col_sink=0;
	while(tempc--){
		auto t3=std::chrono::high_resolution_clock::now();
		long long col_sum=0;
		for(size_t i=0;i<n;i++){
			for(size_t j=0;j<n;j++){
				col_sum+=a[j*n+i];
			}
		}
		auto t4=std::chrono::high_resolution_clock::now();
		col_sink+=col_sum;
		double col_ms = std::chrono::duration<double, std::milli>(t4-t3).count();
		col.push_back(col_ms);
	}
	std::vector<double> row_val=median(row);
	std::vector<double> col_val=median(col);
	
	std::cerr<<row_sink<<" "<<col_sink<<"\n";
	std::cout<<n<<","<<"row,"<<row_val[1]<<"\n";
	std::cout<<n<<","<<"col,"<<col_val[1]<<"\n";

	size_t T=10;
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
	std::cout<<"total= "<<total<<"\n";
	return 0;
}
