#include <stdio.h>

typedef struct {
    int weight;
    int value;
    double ratio;
} Item;

void calculateRatio(Item items[], int n) {
    for (int i = 0; i < n; i++) {
        items[i].ratio = (double) items[i].value / items[i].weight;
    }
}

double knapsackGreedy(Item items[], int n, int capacity) {

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (items[i].ratio < items[j].ratio) {
                Item temp = items[i];
                items[i] = items[j];
                items[j] = temp;
            }
        }
    }

    double totalValue = 0.0;  
    int remainingCapacity = capacity;

    for (int i = 0; i < n; i++) {
        if (remainingCapacity == 0) break;

        if (items[i].weight <= remainingCapacity) {
            remainingCapacity -= items[i].weight;
            totalValue += items[i].value;
        } else {
            totalValue += items[i].ratio * (double) remainingCapacity;
            remainingCapacity = 0;
        }
    }

    return totalValue;
}

int main() {
    int n = 4;  
    int capacity = 50;  

    Item items[] = {
        {10, 60},
        {20, 100},
        {30, 120},
        {40, 240}
    };

    calculateRatio(items, n);

    double maxValue = knapsackGreedy(items, n, capacity);

    printf("Maximum value in Knapsack = %.2f\n", maxValue);

    return 0;
}
