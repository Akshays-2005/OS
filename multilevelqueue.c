#include <stdio.h>
#include <stdlib.h>

struct Process {
    int bt, wt, tat;
    char ch;
    int num;
};
typedef struct Process pro;

void main() {
    int n;
    float avgtat = 0.0, avgwt = 0.0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

       pro* p[n];
    for (int i = 0; i < n; i++) {
        p[i] = (pro*) malloc(sizeof(pro));
        printf("Enter the process number :");
        scanf("%d", &p[i]->num);
        printf("Enter the burst time for process %d: ", i + 1);
        scanf("%d", &p[i]->bt);
        printf("Enter whether the process is foreground or background (F for foreground, B for background): ");
        scanf(" %c", &p[i]->ch);
    }


    pro* p1[n];
    pro* p2[n];
    int k1 = 0, k2 = 0;
    for (int i = 0; i < n; i++) {
        if (p[i]->ch == 'F' || p[i]->ch == 'f') {
            p1[k1++] = p[i];
        } else {
            p2[k2++] = p[i];
        }
    }

    pro* p_combined[n];
    for (int i = 0; i < k1; i++) {
        p_combined[i] = p1[i];
    }
    for (int i = 0; i < k2; i++) {
        p_combined[k1 + i] = p2[i];
    }

    p_combined[0]->wt = 0;
    p_combined[0]->tat = p_combined[0]->bt;
    avgtat += p_combined[0]->tat;
    avgwt += p_combined[0]->wt;


    for (int i = 1; i < n; i++) {
        p_combined[i]->wt = p_combined[i - 1]->wt + p_combined[i - 1]->bt;
        p_combined[i]->tat = p_combined[i]->wt + p_combined[i]->bt;
        avgwt += p_combined[i]->wt;
        avgtat += p_combined[i]->tat;
    }


    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p_combined[i]->num > p_combined[j]->num) {
                // Swap entire process structures
                pro* temp = p_combined[i];
                p_combined[i] = p_combined[j];
                p_combined[j] = temp;
            }
        }
    }


    printf("\nThe times after computation are:\n");
    printf("\tPROCESS\tBT\tQueue\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("\tP%d\t%d\t%c\t%d\t%d\n", p_combined[i]->num, p_combined[i]->bt, p_combined[i]->ch, p_combined[i]->tat, p_combined[i]->wt);
    }

    printf("\nAverage wait time = %f", avgwt / n);
    printf("\nAverage turn around time = %f", avgtat / n);

       for (int i = 0; i < n; i++) {
        free(p[i]);
    }
}
