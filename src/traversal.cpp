#include <iostream>
#include <vector>
#include <chrono>

int main(){
	size_t n;
	std::cout<<"Enter size: ";
	std::cin>>n;
	std::vector<int> a(n*n);
	for(size_t i=0;i<n*n;i++){
		a[i]=i%100;
	}
	//for row major we will first time it
	auto t1=std::chrono::high_resolution_clock::now();
	long long row_sum=0;
	for(size_t i=0;i<n;i++){
		for(size_t j=0;j<n;j++){
			row_sum+=a[i*n+j];
		}
	}
	auto t2=std::chrono::high_resolution_clock::now();
	double row_ms = std::chrono::duration<double, std::milli>(t2-t1).count();
	std::cout<<"Time taken for row major is: "<<row_ms<<"\n"<<"The sum for row major is: "<<row_sum<<"\n";
	auto t3=std::chrono::high_resolution_clock::now();
	long long col_sum=0;
	for(size_t i=0;i<n;i++){
		for(size_t j=0;j<n;j++){
			col_sum+=a[j*n+i];
		}
	}
	auto t4=std::chrono::high_resolution_clock::now();
	double col_ms = std::chrono::duration<double, std::milli>(t4-t3).count();
	std::cout<<"Time taken for column major: "<<col_ms<<"\n"<<"The sum for column major is: "<<col_sum<<"\n";
	

	return 0;
}
