#include <stdio.h>
#include <math.h>
#include <iostream>
#include <sys/time.h>
#define SET_SIZE 20

using namespace std;

void printPowerSet(int *set)
{
    unsigned long int pow_set_size = pow(2, SET_SIZE);
    int counter, j;
    int flag;

    for(counter = 0; counter < pow_set_size; counter++)
    {
      for(j = 0; j < SET_SIZE; j++)
       {
          if(counter & (1<<j))
            flag=1;
       }
    }
}

int main()
{
    int set[SET_SIZE];

    for(int i=0;i<SET_SIZE;i++)
      cin>>set[i];

    struct timeval tim1, tim2;

    gettimeofday(&tim1, NULL);
    printPowerSet(set);
    gettimeofday(&tim2, NULL);

    double t1, t2;
    t1 = tim1.tv_sec + (tim1.tv_usec/1000000.0);
    t2 = tim2.tv_sec + (tim2.tv_usec/1000000.0);

    cout<<t2-t1<<"\n";

    getchar();
    return 0;
}