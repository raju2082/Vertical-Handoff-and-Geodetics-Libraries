#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0
#define NaN -99999999
static float OA1,OA2;
static float m[4],c[4];
//static float Xmin,Xmax,Ymin,Ymax;

float lineEqn_btwn_twoPts(float xx1,float yy1,float x2,float y2,float x,float y){ /*finding the Eqn of each line of a polygon*/
	float R;
	static int i=0;
	if(xx1==x2&&yy1==y2) { 
		printf("they are same points, infinite number of lines are possible\n");
		exit(1); 
	} 
	else if(xx1==x2||yy1==y2) { 
		if(xx1==x2){ 
			printf("the equation of line is x= %f\n",xx1); 
			m[i] = NaN;	
			c[i] = NaN;
			R = x-xx1;
			printf("R = %f\n",R);
			i = i+1;
			if(i == 4)	
				i=0;
			return R;
		}
		else {
			printf("the equation of line is y= %f\n",yy1); 
			m[i] = 0;
			c[i] = y2-(m[i]*x2);
			R = y-yy1;
			printf("R = %f\n",R);
			i = i+1;
			if(i == 4)	
				i=0;
			return R;
		}
	} 
	else { 
		m[i] = (y2-yy1)/(x2-xx1); 
		c[i] = y2-(m[i]*x2); 
		printf("the equation of line is y=%fx+%f \n",m[i],c[i]); 
		R = (m[i]*x) - y + c[i];
		printf("R = %f\n",R);
		i = i+1;
		if(i == 4)	
			i=0;
		return R;
	} 
	
}

void setAnchorPtasOrigin(){ /*taking the Anchor point as Origin to calculate the offsets*/
	OA1 = 0;
	OA2 = 0;
}

int conditionCheck(float p,float x,float y,int j){ /*valid region check*/
	float V;
	V = (m[j]*x) -y + c[j];
	printf("m[%d] = %f c[%d]= %f V = %f",j,m[j],j,c[j],V);

/*	if((t == 0 ) || (t == NaN) ){
       		if((Xmin<x<Xmax)&&(Ymin<y<Ymax)){
                        printf("Point lies inside\n");
                        return true;
                }
                else{
                        printf("Point doesn't lie inside\n");
                        return false;
                }
        }	
*/	if(p >= 0){
		if(V >= 0){
			printf("%d line eqn satisfied\n",j+1);
			return true;
		}
		else{
			printf("%d line eqn not satisfied\n",j+1);
			return false;
		}
	}
	else if(p <= 0){
		if(V <= 0){
			printf("%d line eqn satisfied\n",j+1);
			return true;
		}
		else{
			printf("%d line eqn not satisfied\n",j+1);
			return false;
		}
	}
	
}

//void maxCoordinates(float x2,float y2,float x3,float y3,float x4,float y4){ /*setting the MAX and MIN values of x ,y from the co-ordinates*/
//	Xmin = OA1;
//	Ymin = OA2;
//	Xmax = ((x2>=x3)&&(x2>=x4))?x2:((x3>=x2)&&(x3>=x4))?x3:x4;
//	Ymax = ((y2>=y3)&&(y3>=y4))?y2:((y3>=y2)&&(y3>=y4))?y3:y4;
//	printf("Xmax = %f Ymax = %f\n",Xmax,Ymax);
//}

