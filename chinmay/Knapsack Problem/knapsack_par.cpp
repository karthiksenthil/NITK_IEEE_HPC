#include <iostream>
#include <vector>
#include <math.h>
#include <sys/time.h>
#include <omp.h>
#define SET_SIZE 30
#define THRESHOLD 1000

using namespace std;

int v[SET_SIZE], w[SET_SIZE];

void power_set(int v[], int w[])
{
  	// vector<int> p;
  	cout<<"inside";
  	long long int max=-1;
	struct timeval tim1, tim2;
	int po = SET_SIZE;
	unsigned long long int two_n = pow(2, po);	
	
	omp_set_num_threads(16);


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
	cout<<max<<"\n";   
}


int main()
{
	for(int i=0;i<SET_SIZE;i++)
		cin>>v[i];

	for(int i=0;i<SET_SIZE;i++)
		cin>>w[i];

	power_set(v, w);
}