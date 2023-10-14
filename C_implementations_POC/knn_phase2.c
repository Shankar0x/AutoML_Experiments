#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define K 3

typedef struct {
    double mean_r;
    double std_r;
    double min_r;
    double max_r;
    double var_r;
    double mean_g;
    double std_g;
    double min_g;
    double max_g;
    double var_g;
    double mean_b;
    double std_b;
    double min_b;
    double max_b;
    double var_b;
    double mean_h;
    double std_h;
    double min_h;
    double max_h;
    double var_h;
    double mean_s;
    double std_s;
    double min_s;
    double max_s;
    double var_s;
    double mean_v;
    double std_v;
    double min_v;
    double max_v;
    double var_v;
    double mean_l;
    double std_l;
    double min_l;
    double max_l;
    double var_l; 
    double mean_a; 
    double std_a; 
    double min_a; 
    double max_a; 
    double var_a; 
    double mean_b1; 
    double std_b1; 
    double min_b1; 
    double max_b1; 
    double var_b1; 
    int Target; // 0, 1, or 2
} Data;

typedef struct {
    int label;
    double distance;
} Neighbor;

Data* read_csv(const char* filename, int* n) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error: could not open file %s\n", filename);
        exit(1);
    }

    char line[1024];
    int i = 0;
    int max_rows = 1000;
    Data* data = (Data*)malloc(sizeof(Data) * max_rows);

    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%d",
               &data[i].mean_r, &data[i].std_r, &data[i].min_r, &data[i].max_r, &data[i].var_r,
               &data[i].mean_g, &data[i].std_g, &data[i].min_g, &data[i].max_g, &data[i].var_g,
               &data[i].mean_b, &data[i].std_b, &data[i].min_b, &data[i].max_b, &data[i].var_b,
               &data[i].mean_h, &data[i].std_h, &data[i].min_h, &data[i].max_h, &data[i].var_h,
               &data[i].mean_s, &data[i].std_s, &data[i].min_s, &data[i].max_s, &data[i].var_s,
               &data[i].mean_v, &data[i].std_v, &data[i].min_v, &data[i].max_v, &data[i].var_v,
               &data[i].mean_l, &data[i].std_l, &data[i].min_l, &data[i].max_l, &data[i].var_l,
               &data[i].mean_a, &data[i].std_a, &data[i].min_a, &data[i].max_a, &data[i].var_a,
               &data[i].mean_b1, &data[i].std_b1, &data[i].min_b1, &data[i].max_b1, &data[i].var_b1,
               &data[i].Target);
        i++;

        if (i == max_rows) {
            max_rows *= 2;
            data = (Data*)realloc(data, sizeof(Data) * max_rows);
        }
    }

    fclose(fp);

    *n = i;

    return data;
}

double euclideanDistance(Data p1, Data p2) {
    double sum = 0.0;

    sum += pow(p1.mean_r - p2.mean_r, 2);
    sum += pow(p1.std_r - p2.std_r, 2);
    sum += pow(p1.min_r - p2.min_r, 2);
    sum += pow(p1.max_r - p2.max_r, 2);
    sum += pow(p1.var_r - p2.var_r, 2);

    sum += pow(p1.mean_g - p2.mean_g, 2);
    sum += pow(p1.std_g - p2.std_g, 2);
    sum += pow(p1.min_g - p2.min_g, 2);
    sum += pow(p1.max_g - p2.max_g, 2);
    sum += pow(p1.var_g - p2.var_g, 2);

    sum += pow(p1.mean_b - p2.mean_b, 2);
    sum += pow(p1.std_b - p2.std_b, 2);
    sum += pow(p1.min_b - p2.min_b, 2);
    sum += pow(p1.max_b - p2.max_b, 2);
    sum += pow(p1.var_b - p2.var_b, 2);

    sum += pow(p1.mean_h - p2.mean_h, 2);
    sum += pow(p1.std_h - p2.std_h, 2);
    sum += pow(p1.min_h - p2.min_h, 2);
    sum += pow(p1.max_h - p2.max_h, 2);
    sum += pow(p1.var_h - p2.var_h, 2);

    sum += pow(p1.mean_s - p2.mean_s, 2);
    sum += pow(p1.std_s - p2.std_s, 2);
    sum += pow(p1.min_s - p2.min_s, 2);
    sum += pow(p1.max_s - p2.max_s, 2);
    sum += pow(p1.var_s - p2.var_s, 2);

    sum += pow(p1.mean_v - p2.mean_v, 2);
    sum += pow(p1.std_v - p2.std_v, 2);
    sum += pow(p1.min_v - p2.min_v, 2);
    sum += pow(p1.max_v - p2.max_v, 2);
    sum += pow(p1.var_v - p2.var_v, 2);

    sum += pow(p1.mean_l - p2.mean_l, 2);
    sum += pow(p1.std_l - p2.std_l, 2);
    sum += pow(p1.min_l - p2.min_l, 2);
    sum += pow(p1.max_l - p2.max_l, 2);
    sum += pow(p1.var_l - p2.var_l, 2);

    sum += pow(p1.mean_a - p2.mean_a, 2);
    sum += pow(p1.std_a - p2.std_a, 2);
    sum += pow(p1.min_a - p2.min_a, 2);
    sum += pow(p1.max_a - p2.max_a, 2);
    sum += pow(p1.var_a - p2.var_a, 2);

    sum += pow(p1.mean_b1 - p2.mean_b1, 2);
    sum += pow(p1.std_b1 - p2.std_b1, 2);
    sum += pow(p1.min_b1 - p2.min_b1, 2);
    sum += pow(p1.max_b1 - p2.max_b1, 2);
    sum += pow(p1.var_b1 - p2.var_b1, 2);

    return sqrt(sum);
}

void knn(Data* training_set, int training_size, Data* test_set, int test_size, int k) {
    for (int i = 0; i < test_size; i++) {
        Neighbor neighbors[k];

        for (int j = 0; j < k; j++) {
            neighbors[j].distance = INFINITY;
        }

        for (int j = 0; j < training_size; j++) {
            double distance = euclideanDistance(test_set[i], training_set[j]);

            int max_index = 0;
            for (int m = 1; m < k; m++) {
                if (neighbors[m].distance > neighbors[max_index].distance) {
                    max_index = m;
                }
            }

            if (distance < neighbors[max_index].distance) {
                neighbors[max_index].distance = distance;
                neighbors[max_index].label = training_set[j].Target;
            }
        }

        int count[K] = {0};
        for (int j = 0; j < k; j++) {
            count[neighbors[j].label]++;
        }

        int max_count = 0;
        int max_label = 0;
        for (int j = 0; j < K; j++) {
            if (count[j] > max_count) {
                max_count = count[j];
                max_label = j;
            }
        }

        printf("Test instance %d: Predicted label = %d\n", i, max_label);
    }
}

int main() {
    int training_size;
    int test_size;

    Data* training_set = read_csv("phase_2_rgbhsvlab_withoutbg.csv", &training_size);
    Data* test_set = read_csv("test_set.csv", &test_size);

    int k = 3; // Set your desired value of k here

    knn(training_set, training_size, test_set, test_size, k);

    free(training_set);
    free(test_set);

    return 0;
}
