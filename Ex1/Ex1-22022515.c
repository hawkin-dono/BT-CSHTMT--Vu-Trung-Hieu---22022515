#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char name[2];
    int a; // arrive
    int d; // dealine
    int C; // compute
} task;

// compare function for task sort
int compare_by_d(const void *a, const void *b) {
    task *task1 = (task *)a;
    task *task2 = (task *)b;
    if (task1->d == task2->d) return task1->C - task2->C;
    return task1->d - task2->d;
}

int compare_char(char s1, char s2) {
    int a = s1 - s2;
    return a;
}

int compare_by_name(const void *a, const void *b) {
    task *task1 = (task *)a;
    task *task2 = (task *)b;
    
    return strcmp(task1->name, task2->name);
}


void plot_table(task tasks[], int n_task) {
    qsort(tasks, n_task, sizeof(task), compare_by_name);
    int end_time = tasks[n_task - 1].d;
    for (int i = 0; i < n_task; i++) {
        printf("%s |", tasks[i].name);
        for(int j = 0; j < tasks[i].a; j++) {
            printf(" ");
        }
        for(int k = 0; k < tasks[i].C; k++) {
            printf("_");
        }
        printf("\n");
    }
    printf("   |");
    for(int i = 0; i < end_time; i++) {
        printf("_");
    }
    printf("\n\n");
}

// Earliest Due Date (EDD) Algorithm
void scheduleByEDD(task tasks[], int n_task) {
    // assume that all tasks arrive at t=0
    int i = 0;
    
    // sort by due date, if due date is equal, sort by computing time
    qsort(tasks, n_task, sizeof(task), compare_by_d);
    
    tasks[0].a = 0;
    for (i = 0; i < n_task - 1; i++) {
        tasks[i + 1].a = tasks[i].a + tasks[i].C;
    }

    for (i = 0; i < n_task; i++) {
        printf("%s     %d    %d   %d\n", tasks[i].name, tasks[i].a, tasks[i].C, tasks[i].d);
    }
    
    printf("\n\n");
    plot_table(tasks, n_task);
}

void get_info(int d[], int s[], int f[], int a[], int C[], int L[], int E[], int n_task) {
    // '''
    // input:
    // d : deadline    int[]
    // s : start time  int[]
    // f : finish time int[]
    // a : arrival time    int * [] emptied
    // c : computing time  int * [] emptied
    // L : lateness    int * []    emptied
    // E : exceeding time  int * [] emptied
    // int n_task  
    // '''
    for (int i = 0; i < n_task; i++) {
        a[i] = s[i];
        C[i] = f[i] - s[i];
        L[i] = f[i] - d[i];
        E[i] = L[i] > 0 ? L[i] : 0;
    }
}

void print_info(int a[], int f[], int C[], int L[], int E[], int n_task) {
    
    // input:
    // a : arrival time 
    // f : finish time
    // c : computing time
    // L : lateness
    // E : exceeding time
    
    printf("\n");
    printf("Arrival time: a\n");
    int i = 0;
    for (i = 0; i < n_task; i++) {
        printf("% 3d  ", a[i]);
    }

    printf("\n\n");
    printf("Finish time: f\n");
    for (i = 0; i < n_task; i++) {
        printf("% 3d  ", f[i]);
    }

    printf("\n\n");
    printf("Computing time: C\n");
    for (i = 0; i < n_task; i++) {
        printf("% 3d  ", C[i]);
    }

    printf("\n\n");
    printf("Lateness: L\n");
    int max_L = L[0];
    for (i = 0; i < n_task; i++) {
        printf("% 3d  ", L[i]);
        if (L[i] > max_L) {
            max_L = L[i];
        }
    }
    printf("\n");
    printf("=> Max lateness: % 3d\n\n", max_L);

    printf("Exceeding time: E\n");
    for (i = 0; i < n_task; i++) {
        printf("% 3d  ", E[i]);
    }
    printf("\n-----------------------------------\n\n");
}

int main() {
    int d[] = {15, 11, 18, 16, 20, 20, 20}; // deadline
    int s[] = {3, 0, 10, 5, 13, 14, 16}; // start time
    int f[] = {5, 3, 13, 10, 14, 16, 20}; // finish time


    int n_task = sizeof(d) / sizeof(d[0]);
    int C[n_task]; // Computing time
    int L[n_task]; // Lateness
    int a[n_task]; // arrival time
    int E[n_task]; // exceeding time

    int i = 0;

    // Bai 1
    get_info(d, s, f, a , C, L, E, n_task);
    print_info(a, f, C, L, E, n_task);


    // Bai 2
    printf("EDD Algorithm:\n");
    printf("task   a    C    d\n");
    task tasks[n_task];
    for (i = 0; i < n_task; i++) {
        snprintf(tasks[i].name, 3, "J%d", i + 1);
        tasks[i].a = a[i];
        tasks[i].d = d[i];
        tasks[i].C = C[i];
    }
    scheduleByEDD(tasks, n_task);
    return 0;
}