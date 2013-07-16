#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include "geodetic_routines.h"
struct timeval  tv1, tv2;

	double time_spent;

int i;

clock_t begin,end;

int main(int argc, char **argv)
{
	int i;	
	double distance,dist,ans;

	if(argc < 2 ){
		printf("Program for calculating distance between two lat long coordinates\n");
		printf("usage : abc.elf lat1 long1  lat2 long2\n");
		exit(0);
	}
	gettimeofday(&tv1, NULL);
//	begin = time(0);
		distance = haversine(argc, argv);
	printf("\ndistance_haversine = %lf\n",distance);
//	end = time(0);
	gettimeofday(&tv2, NULL);
	printf ("Total time = %f seconds\n\n", (double) (tv2.tv_usec - tv1.tv_usec)/1000000 + (double) (tv2.tv_sec - tv1.tv_sec));
//	time_spent = (double)(end -begin)/ CLOCKS_PER_SEC;
//	printf("time_spent1 = %lf beg = %d end = %d\n",time_spent,begin,end);
//	long distance = EARTH_RADIUS * c;
//   printf("%ld\n", distance);
	
//	printf("distance in meters = %g\n",6378140 * c);
//	begin = time(0);
	gettimeofday(&tv1, NULL);
		dist = arada_distCal(argc, argv);
	printf("distance_arada = %lf\n",dist);
	gettimeofday(&tv2, NULL);
	printf ("Total time = %f seconds\n\n", (double) (tv2.tv_usec - tv1.tv_usec)/1000000 + (double) (tv2.tv_sec - tv1.tv_sec));

	gettimeofday(&tv1, NULL);
		ans = sloc(argc, argv);
	printf("distance_sloc=%lf\n",(double)ans);	
	gettimeofday(&tv2, NULL);
	printf("Total time = %f seconds\n\n",(double) (tv2.tv_usec - tv1.tv_usec)/1000000 + (double) (tv2.tv_sec - tv1.tv_sec));


//	end = time(0);
//	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
//	printf("time_spent2 = %lf\n",time_spent);
}
