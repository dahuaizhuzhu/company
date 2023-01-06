#include "SinCosTable.h"


const float SinCosTable[91] = {
0.000000,
0.017452,
0.034899,
0.052336,
0.069756,
0.087156,
0.104528,
0.121869,
0.139173,
0.156434,
0.173648,
0.190809,
0.207912,
0.224951,
0.241922,
0.258819,
0.275637,
0.292372,
0.309017,
0.325568,
0.342020,
0.358368,
0.374607,
0.390731,
0.406737,
0.422618,
0.438371,
0.453990,
0.469472,
0.484810,
0.500000,
0.515038,
0.529919,
0.544639,
0.559193,
0.573576,
0.587785,
0.601815,
0.615661,
0.629320,
0.642788,
0.656059,
0.669131,
0.681998,
0.694658,
0.707107,
0.719340,
0.731354,
0.743145,
0.754710,
0.766044,
0.777146,
0.788011,
0.798636,
0.809017,
0.819152,
0.829038,
0.838671,
0.848048,
0.857167,
0.866025,
0.874620,
0.882948,
0.891007,
0.898794,
0.906308,
0.913545,
0.920505,
0.927184,
0.933580,
0.939693,
0.945519,
0.951057,
0.956305,
0.961262,
0.965926,
0.970296,
0.974370,
0.978148,
0.981627,
0.984808,
0.987688,
0.990268,
0.992546,
0.994522,
0.996195,
0.997564,
0.998630,
0.999391,
0.999848,
1.000000,
};

int rangeAngle(int angle,int min,int max)
{
	while(angle < min)angle+=(max-min);
	while(angle > max)angle-=(max-min);
	return angle;
}

float fast_sin(int angle)
{
	angle=rangeAngle(angle,0,360);

	if(angle>=0 && angle<=90)return SinCosTable[angle];
	else if(angle>=90 && angle<=180)return SinCosTable[180-angle];
	else if(angle>=180 && angle<=270)return -SinCosTable[angle-180];
	else return -SinCosTable[360-angle];
}

float fast_cos(int angle)
{
	angle=rangeAngle(angle,0,360);

	if(angle>=0 && angle<=90)return SinCosTable[90-angle];
	else if(angle>=90 && angle<=180)return -SinCosTable[90-(180-angle)];
	else if(angle>=180 && angle<=270)return -SinCosTable[90-(angle-180)];
	else return SinCosTable[90-(360-angle)];
}
