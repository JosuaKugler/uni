#include <ctime>
// Setzt Marke und gibt Zeitdifferenz zur letzten Marke zurueck
clock_t last_time;
double time_stamp () {
    clock_t current_time = clock();
    double duration =
        ((double)(current_time-last_time)) / CLOCKS_PER_SEC;
    last_time = current_time;
    return duration;
}
