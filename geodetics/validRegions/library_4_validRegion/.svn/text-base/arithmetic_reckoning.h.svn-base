
#define true 1
#define false 0
typedef struct validRegion{
	double eachLine_res[4],m[4],c[4];
}Region_t;

typedef struct offsets{
	double x,y;
}Offset_t;

float lineEqnbtwnTwoPts(Region_t *,float ,float ,float ,float ,float ,float ); /*finding the Eqn of each line of a polygon*/
void initRegion(Region_t *, Offset_t *, Offset_t *,Offset_t *,Offset_t *);
int checkValidRegion(Region_t *,Offset_t *);
void latLongToXY(Offset_t ,Offset_t , Offset_t *);
