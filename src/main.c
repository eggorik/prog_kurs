#include <reader.h>
#include <writer.h>

#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
    if (argc != 5) {
        printf("Неправильное количество аргументов\n");
        return -1;
    }
    if (strcmp(argv[2], "-o") != 0) {
        printf("Ожидался аргумент -o для указания имени выходного файла\n");
        return -1;
    }
    if ((strcmp(argv[1], "-c") != 0) && (strcmp(argv[1], "-d") != 0)) {
        printf("Ожидался аргумент -с для сжатия или -d для распаковки\n");
        return -1;
    }
    if (strcmp(argv[1], "-c") == 0) {
        compress(argv[4], argv[3]);
    }
    if (strcmp(argv[1], "-d") == 0) {
        decompress(argv[4], argv[3]);
    }
    printf("Успех!\n");
    return 0;
}
