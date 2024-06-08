#include <stdio.h>

int binomialCoefficient(int n, int k) {
    if (k == 0 || k == n) {
        return 1;
    } else {
        return binomialCoefficient(n-1, k-1) + binomialCoefficient(n-1, k);
    }
}

int main() {
    int N, M;
    
    // Ввод данных
    printf("Введите количество номеров N и количество выпавших номеров M через пробел: ");
    scanf("%d %d", &N, &M);
    
    // Вычисление количества вариантов
    int result = binomialCoefficient(N, M);
    
    // Вывод результата
    printf("Количество вариантов наборов номеров: %d\n", result);
    
    return 0;
}