#include "chaos.h"

void create_cycles(int* table2, double tabel1[], double sortedtable[], int N)
{
    int i = 0, j = 0, k = 1, m = 1;
    for(i = 0; i < N; i++)
        table2[i] = 0;
    for(i = 0; i < N; )
    {
        if(table2[i])
        {
            i++;
            k++;
            continue;
        }
        if(k != m)
        {
            m++;
            k = m;
        }
        for(j = 0; j < N; j++)
        {
            if(tabel1[i] == sortedtable[j])
            {
                table2[i] = m;
                i = j;
                break;
            }
        }
    }
}

CycleAnalysisResult test_cycles(const int* cycletable, int N)
{
    CycleAnalysisResult result;
    result.cycle_counts.resize(N + 1, 0);
    std::vector<bool> visited(N, false);
    result.order = 1;
    for(int i = 0; i < N; i++) {
        if(!visited[i]) {
            int current = i;
            int cycle_length = 0;
            do {
                visited[current] = true;
                cycle_length++;
                for(int j = 0; j < N; j++) {
                    if(cycletable[j] == cycletable[current] && !visited[j]) {
                        current = j;
                        break;
                    }
                }
            } while(current != i && !visited[current]);
            if(cycle_length > 0) {
                result.cycle_counts[cycle_length]++;
                result.order = std::lcm(result.order, cycle_length);
            }
        }
    }
    return result;
}

void analyse_cycles(int table[])
{

}

void lojistic(double seed, double* table, int N)
{
    double x = seed;
    int y = 4;

    for(int i = 0; i < M; i++)
        x = y * x * (1 - x);

    for(int i = 0; i < N; i++)
    {
        x = y * x * (1 - x);
        table[i] = x;
    }
}

void singer(double seed, double* table, int N)
{
    double x = seed;
    double y = 1.04;

    for(int i = 0; i < M; i++)
        x = y * (7.86 * x - 23.31 * std::pow(x, 2) + 28.75 * std::pow(x, 3) - 13.302875 * std::pow(x, 4));

    for(int i = 0; i < N; i++)
    {
        x = y * (7.86 * x - 23.31 * std::pow(x, 2) + 28.75 * std::pow(x, 3) - 13.302875 * std::pow(x, 4));
        table[i] = x;
    }

}

void cubic(double seed, double* table, int N)
{
    double x = seed;
    double y = 2.595;

    for(int i = 0; i < M; i++)
        x = y * x * (1 - pow(x, 2));

    for(int i = 0; i < N; i++)
    {
        x = y * x * (1 - pow(x, 2));
        table[i] = x;
    }
}

double calculate_average_order(int N, int value)
{
    double average = 0.0;
    std::vector<double> table(N);
    std::vector<double> sortedtable(N);
    std::vector<int> cycletable(N);

    for(int j = 0; j < SEED; j++)
    {
        double seed = QRandomGenerator::global()->generateDouble();
        if(value == 1)
            lojistic(seed, table.data(), N);
        else if(value == 2)
            singer(seed, table.data(), N);
        else
            cubic(seed, table.data(), N);

        std::copy(table.begin(), table.end(), sortedtable.begin());
        std::sort(sortedtable.begin(), sortedtable.end());

        create_cycles(cycletable.data(), table.data(), sortedtable.data(), N);
        auto result = test_cycles(cycletable.data(), N);
        average += result.order;
    }

    return average / SEED;
}
