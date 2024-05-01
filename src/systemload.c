// SIMPLE SYSTEM LOAD FOR HUMANS
// AUTHOR: Alexia Michelle <alexiarstein@aol.com>
// LICENSE: GNU GPL 3.0
// Repository https://github.com/alexiarstein/systemload

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CPUS 128

int main() {
    FILE *file;
    double loadavg[3];
    int num_cpus;
    char line[MAX_CPUS];
// primero tomamos los promedios de loadavg
    file = fopen("/proc/loadavg", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    fscanf(file, "%lf %lf %lf", &loadavg[0], &loadavg[1], &loadavg[2]);
    fclose(file);
// y la cantidad de cores de cpuinfo.
// ..y luego hacemos mucha matematica :V

    file = fopen("/proc/cpuinfo", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    num_cpus = 0;
    while (fgets(line, MAX_CPUS, file) != NULL) {
        if (strstr(line, "processor") != NULL) {
            num_cpus++;
        }
    }
    fclose(file);

    printf("System Load\n");
    printf("Actual: %.2f\n", loadavg[0]);
    printf("5 Minutes Ago: %.2f\n", loadavg[1]);
    printf("15 Minutes Ago: %.2f\n", loadavg[2]);
    printf("Using %.2f%% of the %d available cores\n", (loadavg[0] / num_cpus) * 100, num_cpus);

    return 0;
}
