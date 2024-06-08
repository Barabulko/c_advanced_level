#include <stdio.h>
#include <string.h>

int findMaxLength(char* s1, char* s2) {
    int max = 0, current = 0;

    for (int i = 0; i < strlen(s1); i++) {
        current = 0;
        for (int j = 0; j < strlen(s2); j++) {
            if (s1[i] == s2[j]) {
                current++;
                if (current > max) {
                    max = current;
                }
                i++;
            } else {
                current = 0;
            }
        }
    }

    return max;
}

int main() {
    char str1[100], str2[100];

    // Ввод данных
    printf("Введите две символьные строки, разделенные символом перевода строки: ");
    scanf("%s\n%s", str1, str2);

    // Вычисление длины максимального фрагмента
    int maxLength = findMaxLength(str1, str2);

    // Вывод результата
    printf("Длина максимального фрагмента: %d\n", maxLength);

    return 0;
}