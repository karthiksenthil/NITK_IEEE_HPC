#include <iostream>
#include <vector>
#include <math.h>
#include <sys/time.h>
#include <omp.h>
#include <cstdlib>
#define THRESHOLD 1000

using namespace std;

int set_size, num_thr;

void power_set(int v[], int w[])
{

  	long long int max=-1;
	struct timeval tim1, tim2;
	int po = set_size;
	unsigned long long int two_n = pow(2, po);	

	gettimeofday(&tim1, NULL);
	#pragma omp parallel for shared(max)
	for(unsigned long long int i = 0; i < two_n ; i++)
	{
		vector<int> p;
		int m  = i;
		while(m>1)
		{
			p.push_back(m%2);
			m = m / 2;
		}

		int combo_weight=0;
		int combo_value=0;

		p.push_back(m);
		int k = 0;
		for(int k = 0; k < p.size() ; ++k)
		{
			if(p[k])
			{
				combo_weight = combo_weight + w[k];
				combo_value = combo_value + v[k];
			}
		}
		if(combo_weight<THRESHOLD && combo_value>max)
			max=combo_value;
		p.clear();	
	}

	gettimeofday(&tim2, NULL);

	double t1 = tim1.tv_sec + (tim1.tv_usec/1000000.0);
	double t2 = tim2.tv_sec + (tim2.tv_usec/1000000.0);

	cout<<t2-t1<<"\n"; 
	// cout<<max<<"\n";   
}


int main(int argc, char* argv[])
{
	set_size = atoi(argv[1]);

	num_thr = atoi(argv[2]);

	omp_set_num_threads(num_thr);

	int v[set_size], w[set_size];
	
	for(int i=0;i<set_size;i++)
		cin>>v[i];

	for(int i=0;i<set_size;i++)
		cin>>w[i];

	power_set(v, w);
}