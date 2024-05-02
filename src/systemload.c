// SIMPLE SYSTEM LOAD FOR HUMANS
// AUTHOR: Alexia Michelle <alexiarstein@aol.com>
// LICENSE: GNU GPL 3.0
// Repository https://github.com/alexiarstein/systemload

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CPUS 128

int main() {
    FILE *loadavg_file, *cpuinfo_file;
    double loadavg[3];
    int num_cpus = 0;
    char cpuinfo_line[128], output[256];

// primero tomamos los promedios de loadavg
    loadavg_file = fopen("/proc/loadavg", "r");
    cpuinfo_file = fopen("/proc/cpuinfo", "r");

    if (loadavg_file == NULL || cpuinfo_file == NULL) {
        perror("Error opening file");
        return 1;
    }
    fscanf(loadavg_file, "%lf %lf %lf", &loadavg[0], &loadavg[1], &loadavg[2]);

// y la cantidad de cores de cpuinfo.
// ... y luego hacemos mucha matematica :V
    while (fgets(cpuinfo_line, sizeof(cpuinfo_line), cpuinfo_file) != NULL) {
        if (strncmp(cpuinfo_line, "processor", 9) == 0) {
            num_cpus++;
        }
    };

    sprintf(output, "System Load\nActual: %.2f\n5 Minutes Ago: %.2f\n15 Minutes Ago: %.2f\nUsing %.2f%% of the %d available cores\n",
            loadavg[0], loadavg[1], loadavg[2], (loadavg[0] / num_cpus) * 100, num_cpus);
    printf("%s", output);

    return 0;
}
