#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    FILE *p = fopen("time.dat", "w");
    if (p == NULL)
    {
        printf("Error opening the file\n");
        return 1;
    }

    srand(time(0));

    for (int u = 500; u <= 20000; u += 3000)
    {
        int *arr = (int *)malloc(u * sizeof(int));
        if (arr == NULL)
        {
            printf("Memory allocation failed\n");
            fclose(p);
            return 1;
        }

        // Fill array with random numbers
        for (int i = 0; i < u; i++)
        {
            arr[i] = rand() % 50;
        }

        clock_t start = clock();

        int isUnique = 1;

        // O(n^2) duplicate check
        for (int i = 0; i < u - 1 && isUnique; i++)
        {
            for (int j = i + 1; j < u; j++)
            {
                if (arr[i] == arr[j])
                {
                    isUnique = 0;
                    break;
                }
            }
        }

        clock_t end = clock();

        double time_taken = (double)(end - start) / CLOCKS_PER_SEC;

        if (isUnique)
            printf("Unique for n = %d\n", u);
        else
            printf("Not Unique for n = %d\n", u);

        fprintf(p, "%d %lf\n", u, time_taken);

        free(arr);
    }

    fclose(p);

    // Plot using gnuplot
    FILE *gnuplot = popen("gnuplot -persistent", "w");
    if (gnuplot == NULL)
    {
        printf("Error opening gnuplot\n");
        return 1;
    }

    fprintf(gnuplot, "set terminal png size 800,600\n");
    fprintf(gnuplot, "set output 'graph.png'\n");
    fprintf(gnuplot, "set title 'Time vs n (O(n^2) Duplicate Check)'\n");
    fprintf(gnuplot, "set xlabel 'n'\n");
    fprintf(gnuplot, "set ylabel 'Time (seconds)'\n");
    fprintf(gnuplot, "set grid\n");
    fprintf(gnuplot, "plot 'time.dat' with linespoints lw 2 title 'Time'\n");

    pclose(gnuplot);

    printf("Graph saved as graph.png\n");

    return 0;
}
