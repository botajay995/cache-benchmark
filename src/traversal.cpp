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
	std::cout<<"N= "<<n<<" first element ="<<a[0]<<"\n";

	return 0;
}
