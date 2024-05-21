#include <stdio.h>

int main() {
    int N, num, max = -1, count = 0;

    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &num);
        if (num > max) {
            max = num;
            count = 1;
        } else if (num == max) {
            count++;
        }
    }

    printf("%d\n", count);

    return 0;
}