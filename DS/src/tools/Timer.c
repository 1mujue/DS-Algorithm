#include "tools/Timer.h"
#include <time.h>

double MeasureTime(TestFunction function, int argc, char* argv[]){
    clock_t beginTime, endTime;
    beginTime = clock(); 
    function(argc, argv);
    endTime = clock();
    return ((double)(endTime - beginTime)) / CLOCKS_PER_SEC;
}