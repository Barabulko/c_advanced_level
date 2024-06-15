#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

void printFirstAndLastWord(char* str) {
    int len = strlen(str);
    int start = 0;
    int end = len - 1;

    // Пропускаем начальные пробелы
    while (start < len && str[start] == ' ') {
        start++;
    }

    // Пропускаем конечные пробелы
    while (end >= 0 && str[end] == ' ') {
        end--;
    }

    // Находим позиции начала и конца первого слова
    int firstWordStart = start;
    while (start <= end && str[start] != ' ') {
        start++;
    }
    int firstWordEnd = start - 1;

    // Находим позиции начала и конца последнего слова
    int lastWordEnd = end;
    while (end >= start && str[end] != ' ') {
        end--;
    }
    int lastWordStart = end + 1;

    // Печатаем первое и последнее слово
    printf("Первое слово: ");
    for (int i = firstWordStart; i <= firstWordEnd; i++) {
        printf("%c", str[i]);
    }
    printf("\n");

    printf("Последнее слово: ");
    for (int i = lastWordStart; i <= lastWordEnd; i++) {
        printf("%c", str[i]);
    }
    printf("\n");
}

int main() {
    char input[MAX_LEN];
    printf("Введите строку: ");
    fgets(input, MAX_LEN, stdin);
    input[strcspn(input, "\n")] = 0; // удаляем символ новой строки (\n), если есть
    printFirstAndLastWord(input);

    return 0;
}