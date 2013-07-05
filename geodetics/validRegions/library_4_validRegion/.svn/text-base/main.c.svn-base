#include <stdio.h>
#include <stdlib.h>

#include "arithmetic_reckoning.h"
#define COUNT 8

int main(){
	Offset_t offset[3],origin,anchorpt,vehiclept_in_xy,vehiclept_in_latlong;
	int flag;
	Region_t reg[COUNT];

	origin.x = 0;   	offset[0].x = 32.5;
	origin.y = 0;		offset[0].y = -56.0;

	offset[1].x = 22.5;	offset[2].x = -10.3;
	offset[1].y = -58.3;	offset[2].y = -3.1;

	anchorpt.x = 17.426270;
	anchorpt.y = 78.452819;
	vehiclept_in_latlong.x = 17.426091;//17.42648;//17.426091;//	vehiclept_in_xy.x = 5.1;
	vehiclept_in_latlong.y = 78.452867;//78.45262;//78.452867;//	vehiclept_in_xy.y = -19.8;
	
	initRegion(&reg[0],&origin,&offset[0],&offset[1],&offset[2]);

	printf("reg1->eachLine_res[]=%lf\treg1->m[]=%lf\treg1->c[]=%lf\n",reg[0].eachLine_res[0],reg[0].m[0],reg[0].c[0]);
		
	latLongToXY(anchorpt,vehiclept_in_latlong,&vehiclept_in_xy);
	printf("vehiclept x = %f\t,y = %f\n", vehiclept_in_xy.x,vehiclept_in_xy.y);
	flag = checkValidRegion(&reg[0],&vehiclept_in_xy);

	if(flag == true)
		printf("Vehicle lies inside the region\n");
	else
		printf("Outside the region\n");
	return 0;
}
