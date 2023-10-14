#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define K 3

typedef struct {
    double sepal_length;
    double sepal_width;
    double petal_length;
    double petal_width;
    int species; // 0: setosa, 1: versicolor
} Iris;

Iris *read_csv(const char *filename, int *n) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error: could not open file %s\n", filename);
        exit(1);
    }

    char line[1024];
    int i = 0;
    Iris *data = (Iris *)malloc(sizeof(Iris) * 150);

    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%lf,%lf,%lf,%lf,%d", &data[i].sepal_length, &data[i].sepal_width,
               &data[i].petal_length, &data[i].petal_width, &data[i].species);

        printf("%lf,%lf,%lf,%lf,%d\n", data[i].sepal_length, data[i].sepal_width, data[i].petal_length, data[i].petal_width, data[i].species);
        i++;
    }

    *n = i;
    fclose(fp);
    return data;
}

double euclidean_distance(Iris a, Iris b) {
    double d1 = a.sepal_length - b.sepal_length;
    double d2 = a.sepal_width - b.sepal_width;
    double d3 = a.petal_length - b.petal_length;
    double d4 = a.petal_width - b.petal_width;
    return sqrt(d1 * d1 + d2 * d2 + d3 * d3 + d4 * d4);
}

int compare(const void *a, const void *b) {
    double d1 = ((Iris *)a)->sepal_length;
    double d2 = ((Iris *)b)->sepal_length;
    if (d1 < d2) return -1;
    if (d1 > d2) return 1;
    return 0;
}

int predict(Iris data[], int n, Iris x) {
    for (int i = 0; i < n; i++) {
        data[i].sepal_length = euclidean_distance(data[i], x);
    }

    qsort(data, n, sizeof(Iris), compare);

    int counts[2] = {0};
    for (int i = 0; i < K; i++) {
        counts[data[i].species]++;
    }

    return counts[0] > counts[1] ? 0 : 1;
}

double accuracy(Iris data[], int n) {
    int correct = 0;

    for (int i = 0; i < n; i++) {
        Iris x = data[i];
        int pred = predict(data, n, x);
        if (pred == x.species) {
            correct++;
        }
    }

    return (double)correct / n;
}

int main() {
    int n;
    Iris *data = read_csv("Iris.csv", &n);

    printf("Accuracy: %.2f\n", accuracy(data, n));

    free(data);
}
