#include <stdio.h>

int main() {
    int N, num, unique = 0;

    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &num);
        unique ^= num;
    }

    printf("%d\n", unique);

    return 0;
}