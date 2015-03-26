#include <iostream>
#include <vector>
#include <math.h>
#include <sys/time.h>
#define SET_SIZE 30
#define THRESHOLD 1000

using namespace std;

int v[SET_SIZE], w[SET_SIZE];

void power_set(int v[], int w[])
{
  	vector<int> p;
  	long long int max=-1;
	struct timeval tim1, tim2;
	unsigned long long int po = pow(2, SET_SIZE);

	gettimeofday(&tim1, NULL);

	for(unsigned long long int i = 0; i < po; i++)
	{
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