// don't forget to use compilation key for Linux: -lm
/**************************************************************************
* N.Kozak // Lviv'2020 // ACM // Compute result and search result example *
*    file: acmhw5.cpp                                                     *
***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include <time.h>

#define NANOSECONDS_PER_SECOND_NUMBER 1000000000

#define DATA_TYPE_ float
#define DATA_TYPE  volatile DATA_TYPE_

#define A  0.33333333
#define B  0.
#define C -3.

#define REPEAT_COUNT 1000000
#define REPEATOR(count, code) \
for (unsigned int indexIteration = (count); indexIteration--;){ code; }

float getCurrentTime(){
	clock_t time = clock();
	if (time != (clock_t)-1) {
		return ((float)time / (float)CLOCKS_PER_SEC);
	}
	return 0.; // else
}

void run_native(DATA_TYPE * const dArr){
	DATA_TYPE * const dAC = dArr;
	DATA_TYPE * const dA = &dAC[0];
	DATA_TYPE * const dC = &dAC[1];
	DATA_TYPE * const dB = &dArr[2];
	DATA_TYPE * const dResult = &dArr[4];
	DATA_TYPE * const dX1 = &dResult[1];
	DATA_TYPE * const dX2 = &dResult[0];

	DATA_TYPE vD = (DATA_TYPE_)sqrt((double)*dB* *dB - 4.* *dA * *dC);
	*dX1 = (-*dB + vD) / ((DATA_TYPE_)2.* *dA);
	*dX2 = (-*dB - vD) / ((DATA_TYPE_)2.* *dA);
}

void run_search(DATA_TYPE * const dArr){
	DATA_TYPE * const dAC = dArr;
	DATA_TYPE * const dA = &dAC[0];
	DATA_TYPE * const dC = &dAC[1];
	DATA_TYPE * const dB = &dArr[2];
	DATA_TYPE * const dResult = &dArr[4];
	DATA_TYPE * const dX1 = &dResult[1];
	DATA_TYPE * const dX2 = &dResult[0];

	*dX1 = 0.; // reset the result
	*dX2 = 0.; // reset the result
	//printf("x1 = %5.2f; x2 = %5.2f;\r\n", *dX1, *dX2);
	
	unsigned int * const uX1 = (unsigned int * const)dX1;
	for (*uX1 = 0; *uX1 < ~0; ++*uX1){
		if (*dA * *dX1 * *dX1 + *dB * *dX1 + *dC == 0){
			break;
		}
	}

	unsigned int * const uX2 = (unsigned int * const)dX2;
	for (*uX2 = *uX1 + 1; *uX2 < ~0; ++*uX2){
		if (*dA * *dX2 * *dX2 + *dB * *dX2 + *dC == 0){
			break;
		}
	}
}


void printResult(char * const title, DATA_TYPE * const dArr, unsigned int runTime, unsigned int runTimeBySeconds){
	DATA_TYPE * const dAC = dArr;
	DATA_TYPE * const dA = &dAC[0];
	DATA_TYPE * const dC = &dAC[1];
	DATA_TYPE * const dB = &dArr[2];
	DATA_TYPE * const dResult = &dArr[4];
	DATA_TYPE * const dX1 = &dResult[1];
	DATA_TYPE * const dX2 = &dResult[0];

	printf("%s:\r\n", title);
	printf("%fx^2 + %fx + %f = 0;\r\n", *dA, *dB, *dC);
	printf("x1 = %5.2f; x2 = %5.2f;\r\n", *dX1, *dX2);
	if (runTime){
		printf("run time: %dns\r\n\r\n", runTime);
	}
	else if (runTimeBySeconds){
		printf("run time: %ds (~%d.000.000.000ns)\r\n\r\n", runTimeBySeconds, runTimeBySeconds);
	}
}

int main() {
	DATA_TYPE * const dArr = (DATA_TYPE_ *)malloc(6 * sizeof(DATA_TYPE_));
	
	if(!dArr){
		return 0;
	}

	DATA_TYPE * const dAC = dArr;
	DATA_TYPE * const dA = &dAC[0];
	DATA_TYPE * const dC = &dAC[1];
	DATA_TYPE * const dB = &dArr[2];
	DATA_TYPE * const dResult = &dArr[4];
	DATA_TYPE * const dX1 = &dResult[1];
	DATA_TYPE * const dX2 = &dResult[0];
	
	*dA = (DATA_TYPE_)A;
	*dB = (DATA_TYPE_)B;
	*dC = (DATA_TYPE_)C;	

	float startTime, endTime;

	// compute by the formula with compiler optimization
	startTime = getCurrentTime();
	REPEATOR(REPEAT_COUNT, run_native(dArr););
	endTime = getCurrentTime();
	printResult((char*)"compute by the formula with compiler optimization",
		dArr,
		(unsigned int)((endTime - startTime) * (NANOSECONDS_PER_SECOND_NUMBER / REPEAT_COUNT)), 0);

	printf("please wait, the full search takes a few tens of seconds...");
	startTime = getCurrentTime();
	run_search(dArr);
	endTime = getCurrentTime();
	printf("\r                                                           \r");
	printResult((char*)"search",
		dArr,
		0, (unsigned int)(endTime - startTime));

	printf("Press any key to continue . . .");
	(void)getchar();
	return 0;
}
