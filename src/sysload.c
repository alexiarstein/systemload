// x
// SIMPLE SYSTEM LOAD FOR HUMANS
// AUTHOR: Alexia Michelle <alexiarstein@aol.com>
// LICENSE: GNU GPL 3.0
// Repository https://github.com/alexiarstein/systemload

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CPUS 128
#define BAR_WIDTH 33

// Códigos de color ANSI
#define COLOR_RESET "\033[0m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_RED "\033[31m"
#define COLOR_BOLD "\033[1m"
#define COLOR_CYAN "\033[36m"

void print_colored_bar(double percentage) {
    int filled_width = (int)(percentage / 100.0 * BAR_WIDTH);
    int empty_width = BAR_WIDTH - filled_width;
    
    const char *color;
    if (percentage <= 35) {
        color = COLOR_GREEN;
    } else if (percentage <= 70) {
        color = COLOR_YELLOW;
    } else {
        color = COLOR_RED;
    }
    
    printf("     %s", color);
    for (int i = 0; i < filled_width; i++) {
        printf("█");
    }
    for (int i = 0; i < empty_width; i++) {
        printf("▒");
    }
    printf(COLOR_RESET " %.2f%%\n", percentage);
}

const char* get_load_color(double load, int cores) {
    double percentage = (load / cores) * 100;
    if (percentage <= 35) return COLOR_GREEN;
    if (percentage <= 70) return COLOR_YELLOW;
    return COLOR_RED;
}

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

    double current_usage = (loadavg[0] / num_cpus) * 100;
    printf("\n");
    printf(COLOR_BOLD COLOR_CYAN "     ╔══════════════════════════════════════╗\n");
    printf("     ║              SYSTEM LOAD             ║\n");
    printf("     ╚══════════════════════════════════════╝\n" COLOR_RESET);


    print_colored_bar(current_usage);

    
    printf("\n" COLOR_BOLD "Load Averages:\n" COLOR_RESET);
    printf("          Actual: %s%.2f%s\n", get_load_color(loadavg[0], num_cpus), loadavg[0], COLOR_RESET);
    printf("   5 Minutes Ago: %s%.2f%s\n", get_load_color(loadavg[1], num_cpus), loadavg[1], COLOR_RESET);
    printf("  15 Minutes Ago: %s%.2f%s\n", get_load_color(loadavg[2], num_cpus), loadavg[2], COLOR_RESET);
    
    printf("\n" COLOR_BOLD "System Info:\n" COLOR_RESET);
    printf("  Available Cores: %d\n", num_cpus);
    
    printf("\n" COLOR_BOLD "Current Usage:\n" COLOR_RESET);
    printf("  Using %.2f%% of the %d available cores\n\n", current_usage, num_cpus);
    
    
//    printf("\n" COLOR_BOLD "Load Scale:\n" COLOR_RESET);
//    printf("  %s0-35%%: Light Load%s\n", COLOR_GREEN, COLOR_RESET);
 //   printf("  %s36-70%%: Medium Load%s\n", COLOR_YELLOW, COLOR_RESET);
  //  printf("  %s71-100%%: Heavy Load%s\n", COLOR_RED, COLOR_RESET);

    return 0;
}
