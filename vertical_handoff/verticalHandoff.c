/*
 * =====================================================================================
 *
 *       Filename:  verticalHandoff.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Monday 08 July 2013 11:45:21  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Raju (gk), raju2082@gmail.com
 *        Company:  http://www.cdachyd.in/
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>

#include "fgps.c"

#define DEG_TO_RADIANS(degrees) (degrees * M_PI/180)
#define max 100
struct tm *start_time,*end_time;

typedef struct offsets{
	double x,y;		//center of circle region
	double radius;		//radius of circle in meters
}Offset_t;

typedef struct quadrants{
	int region_count;
	Offset_t offset[5];	//Max no. of regions in a quadrant
	double coverage_area; 	//coverage area of circle region in meters
}Quad_t;

typedef struct cords{
	double x,y;
}Coords_t;

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
void latLongToXY(Coords_t anchorpt,Coords_t mobilept_in_latlong,Coords_t *mobilept_in_xy){

        double xx,yy,r,ct,st;
        double angle = DEG_TO_RADIANS(0);

	float Alat,Along,Mlat,Mlong;

	Alat = anchorpt.x;
	Along = anchorpt.y;
	
	Mlat = mobilept_in_latlong.x;
	Mlong = mobilept_in_latlong.y;

        xx = (Mlong - Along) * METERS_DEGLON(Alat);
        yy = (Mlat  - Alat) * METERS_DEGLAT(Alat);
        r  = sqrt(xx*xx + yy*yy);
        if(r){
                ct = xx/r;
                st = yy/r;
                xx = r * ( (ct * cos(angle)) + (st * sin(angle)) );
                yy = r * ( (st * cos(angle)) - (ct * sin(angle)) );
        }
        mobilept_in_xy->x = xx ;
        mobilept_in_xy->y = yy ;
}					/* -----  end of function latLongToXY  ----- */

int quadrantFinder(Coords_t mobilept_in_XY){
	
	if(mobilept_in_XY.x >0 && mobilept_in_XY.y >0)
		return 1;
	else if(mobilept_in_XY.x <0 && mobilept_in_XY.y >0)
		return 2;
	else if(mobilept_in_XY.x <0 && mobilept_in_XY.y <0)
		return 3;
	else 
		return 4;
}

double distance_btwn_two_pts(Offset_t A,Coords_t B){

	double xx,yy,distance;
	
//	printf("c.x = %lf\tc.y=%lf\n",A.x,A.y);
//	printf("m.x = %lf\tm.y=%lf\n",B.x,B.y);
	
	xx = A.x - B.x;
	yy = A.y - B.y;

	distance = sqrt((xx*xx)+(yy*yy));
	printf("distance = %lf\n",distance);
	return distance;
}	

int checkValidRegion(Quad_t quad,Coords_t mobilept_in_XY){

	int i;double dist;
	int flag;
	for(i = 0; i < quad.region_count; i++){
		dist = distance_btwn_two_pts(quad.offset[i],mobilept_in_XY);
		if(dist < quad.offset[i].radius){
			printf("radius = %lf\n",quad.offset[i].radius);
			printf("Inside %d circular region\n",i+1);
			return true;
		}
		else{
			printf("Outside %d Region\n",i+1);
		}	
	}
	return false;
}


int main ( int argc, char *argv[] )
{
	int quad_res,flag,quadrant,switch_bit=false;
	Quad_t quadI,quadII,quadIII,quadIV;
	Coords_t anchorpt,mobilept_in_latlong,mobilept_in_XY;
	fakedata fake_gps;
	double Tcoverage,estimated_spent_time,Tswitch_time=20;
	int fd,r,w;
	time_t ltime;
	int switched=0;
//	ltime = time(NULL);
	char buff[max],ch[max];
	int t=0;
			
	anchorpt.x            = 17.494412;	anchorpt.y            = 78.391897;	
//	mobilept_in_latlong.x = 17.494995; 	mobilept_in_latlong.y = 78.391661;

	quadI.region_count = 1;
	quadI.offset[0].x = 94.1;		quadI.offset[0].y = 87.2;	//JNTU block circle region center in cartesian co-ordinates
	quadI.offset[0].radius = 50;						//JNTU block circle region radius
	quadI.coverage_area = 2*quadI.offset[0].radius;	

	quadII.region_count =3;
	quadII.offset[0].x = -89.4;	quadII.offset[0].y = 4.5;       //Mech block circle region center in cartesian co-ordinates	
	quadII.offset[0].radius = 50;			  	        //Mech block circle region radius
	quadII.offset[1].x = -25.1;	quadII.offset[1].y = 64.5;   //RoadPt1 circle region center in cartesian co-ordinates
	quadII.offset[1].radius = 50; 			  		//RoadPt1 circle region radius
	quadII.offset[2].x = 37.1;	quadII.offset[2].y = 121.2;     //RoadPt2 circle region center in cartesian co-ordinates
	quadII.offset[2].radius = 50;			    	        //RoadPt2 circle region radius
	quadII.coverage_area = 2*(quadII.offset[0].radius + quadII.offset[1].radius + quadII.offset[2].radius);

	quadIII.region_count = 1;
	quadIII.offset[0].x = -37.0;	quadIII.offset[0].y = -160.2;	//CDAC block circle region center in cartesian co-ordinates
	quadIII.offset[0].radius = 50;
	quadIII.coverage_area = 2*quadIII.offset[0].radius;

	quadIV.region_count = 2;
	quadIV.offset[0].x = 33.7;	quadIV.offset[0].y = -131.9;	//CSE block
	quadIV.offset[0].radius = 50;
	quadIV.offset[1].x = 65.5;	quadIV.offset[1].y = -74.8;	//ECE block
	quadIV.offset[1].radius = 50;
	quadIV.coverage_area = 2*(quadIV.offset[0].radius + quadIV.offset[1].radius);

	fd = open("with_estimated_time.csv",O_CREAT|O_RDWR,0666);
	printf("fd = %d\n",fd);
	strcpy(buff,"Y,X\n");
	write(fd,buff,strlen(buff));
	while(1)
	{
		fake(&fake_gps);
		mobilept_in_latlong.x = fake_gps.latitude;
		mobilept_in_latlong.y = fake_gps.longitude;

		latLongToXY(anchorpt,mobilept_in_latlong,&mobilept_in_XY);
		printf("mobile.X=%lf\tmobile.Y=%lf\n",mobilept_in_XY.x,mobilept_in_XY.y);
		quad_res = quadrantFinder(mobilept_in_XY);

		switch(quad_res){
		
			case 1: printf("In Quadrant I\n");
				flag = checkValidRegion(quadI,mobilept_in_XY);
				quadrant = 1;
				break;
			case 2: printf("In Quadrant II\n");
				flag = checkValidRegion(quadII,mobilept_in_XY);
				quadrant = 2;
				break;
			case 3: printf("In Quadrant III\n");
				flag = checkValidRegion(quadIII,mobilept_in_XY);	
				quadrant = 3;
				break;
			case 4: printf("In Quadrant IV\n");
				flag = checkValidRegion(quadIV,mobilept_in_XY);
				quadrant = 4;
				break; 
		}
		
		printf("fake_gps.speed=%lf\n",fake_gps.speed);

		if(flag == true){
			if(switch_bit == false)
			{
/*				switch_bit = true;
 				switched = 1;
				printf("switch_bit =%d\n",switch_bit);
				ltime = time(&ltime);
			//	sprintf(start_time,"switchON_start_time = %s",asctime(localtime(&ltime)));
				start_time = gmtime(&ltime);
				
				printf("start_sec = %d\n",start_time->tm_sec);
				sleep(5);
				t = t+5;
				ltime = time(&ltime);
			//	sprintf(end_time,"switchON_end_time = %s",asctime(localtime(&ltime)));
				end_time = gmtime(&ltime);
				printf("end_sec = %d\n",end_time->tm_sec);
				sprintf(buff,"%d,%d\n",switched,t);	
				sprintf(ch,"%d,%d\n",switched,end_time->tm_sec);
				w =write(fd,buff,strlen(buff));
			//	w =write(fd,ch,strlen(ch));
				printf("written = %d\n",w);
*/				if( ((quadrant == 3) ||(quadrant == 4)) && (0< fake_gps.course < 90) ){
					Tcoverage = quadIII.coverage_area + quadIV.coverage_area;
					estimated_spent_time = ((Tcoverage *18) /(5* fake_gps.speed));
					
					if(estimated_spent_time > Tswitch_time){
						switch_bit = true;
						switched = 1;
						//switch from 3G to WLAN	
			printf("estimated_spent_time = %lf\tTcoverage=%lf\tfake_gps.speed=%lf\n",estimated_spent_time,Tcoverage,fake_gps.speed);
						printf("switch_bit = %d\n",switch_bit);
						ltime = time(&ltime);
					//	sprintf(start_time,"switchON_start_time = %s",asctime(localtime(&ltime)));
						start_time = gmtime(&ltime);
						printf("start_sec = %d\n",start_time->tm_sec);
						sleep(5);
						t = t+5;
						ltime = time(&ltime);
					//	sprintf(end_time,"switchON_end_time = %s",asctime(localtime(&ltime)));
						end_time = gmtime(&ltime);
						printf("end_sec = %d\n",end_time->tm_sec);
//			sprintf(buff,"estimated_spent_time = %lf Tcoverage=%lf fake_gps.speed=%lf switch_bit=%d %d %d\n",estimated_spent_time,Tcoverage,fake_gps.speed,switch_bit,start_time,end_time);
	
						sprintf(buff,"%d,%d\n",switched,t);
						sprintf(ch,"%d,%d\n",switched,end_time->tm_sec);
						w = write(fd,buff,strlen(buff));
				//		w = write(fd,ch,strlen(ch));
						printf("written = %d\n",w);	
					}
				}
				if( (quadrant == 1) && ( (0< fake_gps.course < 30) || (270< fake_gps.course < 360) )){
					Tcoverage = quadI.coverage_area;
					estimated_spent_time = ((Tcoverage *18) /(5* fake_gps.speed));
				
					if(estimated_spent_time > Tswitch_time)
					{
						switch_bit = true;
						//switch from 3G to WLAN	
			printf("estimated_spent_time = %lf\tTcoverage=%lf\tfake_gps.speed=%lf\n",estimated_spent_time,Tcoverage,fake_gps.speed);
						printf("switch_bit = %d\n",switch_bit);
						ltime = time(&ltime);
				//		sprintf(start_time,"switchON_start_time = %s",asctime(localtime(&ltime)));
						start_time = gmtime(&ltime);
						printf("start_sec = %d\n",start_time->tm_sec);
						sleep(5);
						t = t+5;
						ltime = time(&ltime);
				//		sprintf(end_time,"switchON_end_time = %s",asctime(localtime(&ltime)));
						end_time = gmtime(&ltime);
						printf("end_sec = %d\n",end_time->tm_sec);

//			sprintf(buff,"estimated_spent_time=%lf Tcoverage=%lf fake_gps.speed=%lf switch_bit=%d %d %d\n",estimated_spent_time,Tcoverage,fake_gps.speed,switch_bit,start_time,end_time);
		
						sprintf(buff,"%d,%d\n",switched,t);
						sprintf(ch,"%d,%d\n",switched,end_time->tm_sec);
						w = write(fd,buff,strlen(buff));
				//		w = write(fd,ch,strlen(ch));
							
						printf("written = %d\n",w);
					}
				}
			}
		}
		else{
			if(switch_bit == true ){
				switch_bit = false;
				switched = 1;
				//switch back to 3G from WLAN
				printf("switch_bit = %d\n",switch_bit);
				ltime = time(&ltime);
		//		sprintf(start_time,"switchOFF_start_time = %s",asctime(localtime(&ltime)));
				start_time = gmtime(&ltime);
				printf("start_sec = %d\n",start_time->tm_sec);
				sleep(5);
				t = t+5;
				ltime = time(&ltime);
				end_time = gmtime(&ltime);
		//		sprintf(end_time,"switchOFF_end_time = %s",asctime(localtime(&ltime)));
				printf("end_sec = %d\n",end_time->tm_sec);
				//sprintf(buff,"switch_bit = %d %s %s\n",switch_bit,start_time,end_time);
			
				sprintf(buff,"%d,%d\n",switched,t);	
				sprintf(ch,"%d,%d\n",switched,end_time->tm_sec);
				w = write(fd,buff,strlen(buff));
//				w = write(fd,ch,strlen(ch));
				printf("written = %d\n",w);
			}
		}	
		switched = 0;
		ltime = time(&ltime);
		start_time = gmtime(&ltime);
//		sprintf(start_time,"time1 = %s",asctime(localtime(&ltime)));
		sleep(2);	
		t = t+2;
		ltime = time(&ltime);
		end_time = gmtime(&ltime);
//		sprintf(end_time,"time2 = %s",asctime(localtime(&ltime)));
		sprintf(buff,"%d,%d\n",switched,t);
		sprintf(ch,"%d,%d\n",switched,end_time->tm_sec);
		w = write(fd, buff, strlen(buff));
//		w = write(fd, ch, strlen(ch));
	}
	return EXIT_SUCCESS;
}					/* ----------  end of function main  ---------- */
