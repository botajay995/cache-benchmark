#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>

std::vector<int> median(vector<int> nums){
	sort(nums.begin(),nums.end());
	int res=nums[nums.size()/2];
	
	return {nums[0],res,nums[nums.size()-1]};
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
	long long sink=0;
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
		sink+=row_sum;
		double row_ms = std::chrono::duration<double, std::milli>(t2-t1).count();
		row.push_back(row_ms);

	}
	std::cout<<"The total sum through the repetitions is: "<<sink<<"\n";
	int tempc=reps;
	sink=0;
	while(tempc--){
		auto t3=std::chrono::high_resolution_clock::now();
		long long col_sum=0;
		for(size_t i=0;i<n;i++){
			for(size_t j=0;j<n;j++){
				col_sum+=a[j*n+i];
			}
		}
		auto t4=std::chrono::high_resolution_clock::now();
		sink+=col_sum;
		double col_ms = std::chrono::duration<double, std::milli>(t4-t3).count();
		col.push_back(col_ms);
	}
	std::vector<int> row_val=median(row);
	std::vector<int> col_val=median(col);
	
	std::cout<<"The total sum through the repetitions is: "<<sink<<"\n";
	std::cout<<"The minimum time, median time,maximum time taken for row major is: "<<"\n";
	for(int i=0;i<3;i++){
		std::cout<<row_val[i]<<" ";
	}
	std::cout<<"\n";
	std::cout<<"The time taken for column major is: "<<"\n";	
	for(int i=0;i<3;i++){
		std::cout<<col_val[i]<<" ";
	}
	std::cout<<"\n";

	return 0;
}
