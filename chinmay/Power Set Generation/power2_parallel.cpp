#include <iostream>
#include <vector>
#include <math.h>
#include <sys/time.h>
#include <omp.h>
#define SET_SIZE 20

using namespace std;

void power_set(int s[])
{
  	
	struct timeval tim1, tim2;	
	omp_set_num_threads(8);
	long long int p = pow(2, SET_SIZE);

	gettimeofday(&tim1, NULL);
	
	#pragma omp parallel for
	for(long long int i = 0; i < p; i++)
	{
		vector<int> v;
		int m  = i;
		while(m>1)
		{
			v.push_back(m%2);
			m = m / 2;
		}
		v.push_back(m);
		
		int k = 0;
		for(int k = 0; k < v.size(); ++k)
		{
			// do something
		}
		v.clear();
	}
	gettimeofday(&tim2, NULL);

	double t1 = tim1.tv_sec + (tim1.tv_usec/1000000.0);
	double t2 = tim2.tv_sec + (tim2.tv_usec/1000000.0);

	cout<<t2-t1<<"\n";    
}


int main()
{
	int v[SET_SIZE];
	for(int i=0;i<SET_SIZE;i++)
		cin>>v[i];

	power_set(v);
}