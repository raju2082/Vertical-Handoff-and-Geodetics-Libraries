#include<math.h>
#include <stdlib.h>
#include <stdio.h>

//#define EARTH_RADIUS       (6371.0072 * 0.6214)
#define R (6371.0072)
#define EARTH_RADIUS       (6371.0072 )
#define TORADS(degrees)    (degrees * (M_PI / 180))

static double pidiv180 = 0.017453293;
static double R2divR1 = 0.99330562;
static double R1 = 40680631590769.0; //square of constant 6378137
static double R2 = 40408299984087.05552164; //square of constant 6356752.3142
static double pi = 3.14159265358979323846;


double arada_distCal(int argc, char **argv){ /*Calculating distance b/w two points using Arada's(Vincenty's) formula*/
	double lat1, lon1,  lat2,  lon2, elev=0;
	double ang1,ang2,radpnt1,radpnt2,ethlat1,ethlon1,ethlat2,ethlon2,x,y,dist;
	int i ;
	lat1 = strtod(argv[1],NULL);
	lon1 = strtod(argv[2],NULL);
        lat2 = strtod(argv[3],NULL);
        lon2 = strtod(argv[4],NULL);
	for(i = 0; i< 0xFFFFFFF; i++);
//	lat1 =17.439545,lat2 = 17.4396351, lon1 = 78.448513 ,lon2 = 78.4485840;
        ang1=(atan(R2divR1*tan(lat1*pidiv180)));
	ang2=(atan(R2divR1*tan(lat2*pidiv180)));
	radpnt1=(sqrt(1/(((cos(ang1))*(cos(ang1)))/R1+(((sin(ang1))*(sin(ang1)))/R2))))+elev;	
	radpnt2=(sqrt(1/(((cos(ang2))*(cos(ang2)))/R1+(((sin(ang2))*(sin(ang2)))/R2))))+elev;	
	ethlat1=radpnt1*cos(ang1);
	ethlat2=radpnt2*cos(ang2);
	ethlon1=radpnt1*sin(ang1);
	ethlon2=radpnt2*sin(ang2);
	x=sqrt((ethlat1-ethlat2)*(ethlat1-ethlat2)+(ethlon1-ethlon2)*(ethlon1-ethlon2));
	y=2*pi*((((ethlat1+ethlat2)/2))/360)*(lon1-lon2);
	dist=sqrt(x*x+y*y);
	return dist;
}

double haversine(int argc, char **argv){ /*Calculating distance b/w two points using Haversine formula*/
   double lat1, long1, lat2, long2,dLat, dLong, a, c, d,dist;
   int i ; 
   lat1  = TORADS(strtod(argv[1],NULL));
   long1 = TORADS(strtod(argv[2],NULL));
   lat2  = TORADS(strtod(argv[3],NULL));
   long2 = TORADS(strtod(argv[4],NULL));
	for(i = 0 ; i< 0xFFFFFFF; i++);
   dLat  = lat2 - lat1;
   dLong = long2 - long1;
   a = sin(dLat/2) * sin(dLat/2) +
       cos(lat1) * cos(lat2) * sin(dLong/2) * sin(dLong/2);
   c = 2 * atan2(sqrt(a), sqrt(1-a));
	dist = EARTH_RADIUS * c;
	dist = dist * 1000;
	return dist;

}

double sloc(int argc, char **argv){/*Calculating distance b/w two points using Spherical Law of Cosines*/

	double d,lat1,lat2,long1,long2,dLong;
	int i ;

        lat1  = TORADS(strtod(argv[1],NULL));
        long1 = TORADS(strtod(argv[2],NULL));
        lat2  = TORADS(strtod(argv[3],NULL));
        long2 = TORADS(strtod(argv[4],NULL));
	for(i = 0; i< 0xFFFFFFF; i++);
        dLong = long2 - long1;
        d = acos( sin(lat1) * sin(lat2) + cos(lat1) * cos(lat2) * cos(dLong)) * R;
	return (double)d;
}

