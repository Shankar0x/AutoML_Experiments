#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_ITER 1000
#define LEARNING_RATE 0.1
#define THRESHOLD 0.5

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
        i++;
    }

    *n = i;
    fclose(fp);
    return data;
}

double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

double predict(Iris iris, double weights[5]) {
    double z = weights[0] + weights[1] * iris.sepal_length + weights[2] * iris.sepal_width +
               weights[3] * iris.petal_length + weights[4] * iris.petal_width;
    return sigmoid(z);
}

void train(Iris data[], int n, double weights[5]) {
    for (int iter = 0; iter < MAX_ITER; iter++) {
        for (int i = 0; i < n; i++) {
            double pred = predict(data[i], weights);
            double error = data[i].species - pred;

            weights[0] += LEARNING_RATE * error;
            weights[1] += LEARNING_RATE * error * data[i].sepal_length;
            weights[2] += LEARNING_RATE * error * data[i].sepal_width;
            weights[3] += LEARNING_RATE * error * data[i].petal_length;
            weights[4] += LEARNING_RATE * error * data[i].petal_width;
        }
    }
}

double accuracy(Iris data[], int n, double weights[5]) {
    int correct = 0;

    for (int i = 0; i < n; i++) {
        double pred = predict(data[i], weights);
        if ((pred >= THRESHOLD && data[i].species == 1) ||
            (pred < THRESHOLD && data[i].species == 0)) {
            correct++;
        }
    }

    return (double)correct / n;
}

int main() {
    int n;
    Iris *data = read_csv("Iris.csv", &n);

    double weights[5] = {0};
    train(data, n, weights);

    printf("Accuracy: %.2f\n", accuracy(data, n, weights));

    free(data);
}
