#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#define RADIANS         57.2957795 
//#define DEG_TO_RADIANS(degrees) (degrees/RADIANS)
#define DEG_TO_RADIANS(degrees) (degrees * M_PI/180)

double METERS_DEGLAT(double latitude){/*change in one degree latitude*/
        return(111132.09 - (566.05 * cos(2.0*DEG_TO_RADIANS(latitude)))\
                + (1.20 * cos(4.0*DEG_TO_RADIANS(latitude)))\
                - (0.002 * cos(6.0*DEG_TO_RADIANS(latitude))));
}
double METERS_DEGLON(double latitude){/*change in one degree longitude*/
        return((111415.13 * cos(DEG_TO_RADIANS(latitude)))\
                - (94.55 * cos(3.0*DEG_TO_RADIANS(latitude)))\
                + (0.12 * cos(5.0*DEG_TO_RADIANS(latitude))));
}
void latLong_to_XY(double Alat,double Along,double plat,double plong,double *x,double *y){
	double xx,yy,r,ct,st;
	double angle = DEG_TO_RADIANS(0);
	xx = (plong - Along) * METERS_DEGLON(Alat);
        yy = (plat  - Alat) * METERS_DEGLAT(Alat);
        r  = sqrt(xx*xx + yy*yy);
        if(r){
		ct = xx/r;
                st = yy/r;
                xx = r * ( (ct * cos(angle)) + (st * sin(angle)) );
                yy = r * ( (st * cos(angle)) - (ct * sin(angle)) );
	}
        *x = xx ;
        *y = yy ;
	printf("xx = %f\t,y = %f\n",xx,yy);
}
/*
int main(){
	double A1,A2,x1,y1,X,Y;
	printf("enter origin lat long\n");
	scanf("%lf %lf",&A1,&A2);
	printf("enter random lat long\n");
	scanf("%lf %lf",&x1,&y1);
	latLong_to_XY(A1,A2,x1,y1,&X,&Y);
	printf("X = %lf\tY = %lf\n",X,Y);
	return 0;
}*/
