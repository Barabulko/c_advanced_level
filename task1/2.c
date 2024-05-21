#include <stdio.h>

int main() {
    unsigned int N;

    scanf("%u", &N);

    // Получаем старший байт и инвертируем его биты
    unsigned int mask = 0xFF000000;
    unsigned int high_byte = (N & mask) >> 24;
    unsigned int inverted_high_byte = ~high_byte & 0xFF;
    
    // Обновляем старший байт и выводим результат
    unsigned int result = (N & (~mask)) | (inverted_high_byte << 24);
    printf("%u\n", result);

    return 0;
}