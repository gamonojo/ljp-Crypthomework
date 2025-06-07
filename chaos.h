#ifndef CHAOS_H
#define CHAOS_H

#include <QRandomGenerator>
#include <cmath>
#include <vector>
#define M 2000
#define SEED 2000

struct CycleAnalysisResult
{
    std::vector<int> cycle_counts;
    int order;
};

void create_cycles(int* table2, double tabel1[], double sortedtable[], int N);

CycleAnalysisResult test_cycles(const int* cycletable, int N);

void lojistic(double seed, double* table, int N);

void singer(double seed, double* table, int N);

void cubic(double seed, double* table, int N);

double calculate_average_order(int N  , int value);

#endif // CHAOS_H
