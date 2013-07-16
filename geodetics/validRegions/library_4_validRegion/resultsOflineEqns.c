#include <stdio.h>
#include <stdlib.h>

#include "declarations.h"

float lineEqn_btwn_twoPts(float xx1,float yy1,float x2,float y2,float x,float y,Region *reg1){ /*finding the Eqn of each line of a polygon*/
        float R;
	float m[4],c[4],NaN = -0;
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
		reg1->eachLine_res[i] = R;
		reg1->m[i] = m[i];
		reg1->c[i] = c[i];
		printf("reg1->eachLine_res[%d]=%lf\treg1->m[%d]=%lf\treg1->c[%d]=%lf\n",i,reg1->eachLine_res[i],i,reg1->m[i],i,reg1->c[i]);
                printf("R = %f\n",R);
                i = i+1; 
                if(i == 4) 
                        i=0; 
                return R;
        }
} 

