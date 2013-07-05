#include<stdio.h>
#include <stdlib.h> 
#include "validRegion_routines.h"

#define true 1
#define false 0

static float R1,R2,R3,R4;
static float xx1,x2,yy1,y2,x3,y3,x4,y4;
static float P[4];

int main(){
	int flag[4],j;	
	float x[4],y[4],O1,O2;
	double A1=17.42627,A2=78.452819,X,Y,k,l; /*A1,A2 form Anchor point.X,Y is a random point in lat long and 
								k,l form the co-ordinates of random point in cartesian*/
	x2 = 32.5; y2 = -56.0;
	x3 = 22.5; y3 = -58.3;
	x4 = -10.3;y4 = -3.1;
/*	printf("Enter the anchor point lat long\n");
	scanf("%lf %lf",&A1,&A2);
	printf("enter the value of x1 and y1 \n"); 
	scanf("%f %f",&x2,&y2); 
	printf("enter the value of x2 and y2 \n"); 
	scanf("%f %f",&x3,&y3); 
	printf("enter the value of x3 and y3 \n"); 
	scanf("%f %f",&x4,&y4); 
	
	x[0] = A1; y[0] = A2;
	x[1] = x2; y[1] = y2;
	x[2] = x3; y[2] = y3;
	x[4] = x4; y[4] = y4;
*/	
//	setAnchorPtasOrigin(); 
//	maxCoordinates(x2,y2,x3,y3,x4,y4);
	O1= 0; O2 =0;
	R1 = lineEqn_btwn_twoPts(O1,O2,x2,y2,x3,y3); 
	R2 = lineEqn_btwn_twoPts(x2,y2,x3,y3,x4,y4); 
	R3 = lineEqn_btwn_twoPts(x3,y3,x4,y4,O1,O2); 
	R4 = lineEqn_btwn_twoPts(x4,y4,O1,O2,x2,y2); 
	
	P[0] = R1; P[1] = R2;
	P[2] = R3; P[3] = R4;

	printf("enter a random point lat long\n");
	scanf("%lf %lf",&X,&Y);

	latLong_to_XY(A1,A2,X,Y,&k,&l); 	/*calculating the (x,y) i.e., offset from Anchor/origin point*/
	
	printf("k=%f l=%f\n",k,l);

	for(j =0; j< 4; j++){
		flag[j] = conditionCheck(P[j],k,l,j); 
	}	

	if(flag[0]&&flag[1]&&flag[2]&&flag[3] == true)
		printf("The point lies inside the Polygon\n");
	else
		printf("The point does not lie inside the Polygon\n");
		
	return 0;
}
