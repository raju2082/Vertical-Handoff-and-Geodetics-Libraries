/*
 * =====================================================================================
 *
 *       Filename:  arithmetic_reckoning.c
 *
 *    Description:  library for checking whether a point lies 
 *    			inside/outside the region
 *
 *        Version:  1.0
 *        Created:  Saturday 22 June 2013 03:18:17  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Raju (gk), raju2082@gmail.com
 *        Company:  http://www.cdachyd.in/
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "arithmetic_reckoning.h"
//#define RADIANS         57.2957795 
//#define DEG_TO_RADIANS(degrees) (degrees/RADIANS)
#define DEG_TO_RADIANS(degrees) (degrees * M_PI/180)


double METERS_DEGLAT(double latitude){/*change in per degree latitude*/
        return(111132.09 - (566.05 * cos(2.0*DEG_TO_RADIANS(latitude)))\
                + (1.20 * cos(4.0*DEG_TO_RADIANS(latitude)))\
                - (0.002 * cos(6.0*DEG_TO_RADIANS(latitude))));
}
double METERS_DEGLON(double latitude){/*change in per degree longitude*/
        return((111415.13 * cos(DEG_TO_RADIANS(latitude)))\
                - (94.55 * cos(3.0*DEG_TO_RADIANS(latitude)))\
                + (0.12 * cos(5.0*DEG_TO_RADIANS(latitude))));
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  latLongToXY
 *  Description:  convert's lat long co-ordinates to XY 
 * =====================================================================================
 */
void latLongToXY(Offset_t anchorpt,Offset_t vehiclept_in_latlong,Offset_t *vehiclept_in_xy){

        double xx,yy,r,ct,st;
        double angle = DEG_TO_RADIANS(0);

	float Alat,Along,Vlat,Vlong;

	Alat = anchorpt.x;
	Along = anchorpt.y;
	
	Vlat = vehiclept_in_latlong.x;
	Vlong = vehiclept_in_latlong.y;

        xx = (Vlong - Along) * METERS_DEGLON(Alat);
        yy = (Vlat  - Alat) * METERS_DEGLAT(Alat);
        r  = sqrt(xx*xx + yy*yy);
        if(r){
                ct = xx/r;
                st = yy/r;
                xx = r * ( (ct * cos(angle)) + (st * sin(angle)) );
                yy = r * ( (st * cos(angle)) - (ct * sin(angle)) );
        }
        vehiclept_in_xy->x = xx ;
        vehiclept_in_xy->y = yy ;
}/* -----  end of function latLongToXY  ----- */
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  lineEqn_btwn_twoPts
 *  Description:  find's the Eqn of each line of a polygon and stores the result 
 * =====================================================================================
 */
float lineEqn_btwn_twoPts(Region_t *reg,float xx1,float yy1,float x2,float y2,float x,float y){ 
	float R,m,c;
	static int i=0;
	if(xx1==x2&&yy1==y2) { 
		printf("they are same points, infinite number of lines are possible\n");
		exit(1); 
	} 
	else { 
		m = (y2-yy1)/(x2-xx1); 
		c = y2-(m*x2); 
		printf("the equation of line is y=%fx+%f \n",m,c); 
		R = (m*x) - y + c;
		printf("R = %f\n",R);
		reg->m[i] = m;
		reg->c[i] = c;
		reg->eachLine_res[i] = R;
		printf("reg->eachLine_res[%d]=%f\t,reg->m[%d]=%f\t,reg->c[%d]=%f\n",i,reg->eachLine_res[i],i,reg->m[i],i,reg->c[i]);
		i = i+1;
		if(i == 4)	
			i=0;
		return R;
	} 
	
}/* -----  end of function lineEqn_btwn_twoPts  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  initRegion
 *  Description:  Initializes the four point polygon region.
 * 
 * =====================================================================================
 */
void initRegion(Region_t *reg,Offset_t *origin,Offset_t *A, Offset_t *B, Offset_t *C){
	float O1,O2,x2,y2,x3,y3,x4,y4;

	O1 = origin->x;
	O2 = origin->y;
	
	x2 = A->x;
	y2 = A->y;

	x3 = B->x;
	y3 = B->y;
	
	x4 = C->x;
	y4 = C->y;

	lineEqn_btwn_twoPts(reg,O1,O2,x2,y2,x3,y3);
        lineEqn_btwn_twoPts(reg,x2,y2,x3,y3,x4,y4); 
        lineEqn_btwn_twoPts(reg,x3,y3,x4,y4,O1,O2);
        lineEqn_btwn_twoPts(reg,x4,y4,O1,O2,x2,y2);
	
	return ;
}/* -----  end of function initRegion  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  checkValidRegion
 *  Description:  Validates whether a random point lies inside/outside the region
 * =====================================================================================
 */

int checkValidRegion(Region_t *reg,Offset_t *Vpt_in_xy){ 
	float res_of_vehiclept_in_lineqn,Xv,Yv;
	int flag,j;

	Xv = Vpt_in_xy->x;
	Yv = Vpt_in_xy->y;
	
	for(j = 0; j < 4; j++){
		res_of_vehiclept_in_lineqn = (reg->m[j] * Xv) -Yv + reg->c[j];
		if(reg->eachLine_res[j] >= 0){
			if(res_of_vehiclept_in_lineqn >= 0){
				printf("%d line eqn satisfied\n",j+1);
				flag = true;
			}
			else{
				printf("%d line eqn not satisfied\n",j+1);
				flag = false;
				break;
			}
		}
		else if(reg->eachLine_res[j] <= 0){
			if(res_of_vehiclept_in_lineqn <= 0){
				printf("%d line eqn satisfied\n",j+1);
				flag = true;
			}
			else{
				printf("%d line eqn not satisfied\n",j+1);
				flag = false;
				break;
			}
		}
	}
	return flag;
}/* -----  end of function checkValidRegion  ----- */
