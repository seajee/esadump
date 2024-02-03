#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "ERROR: No input file provided\n");
        fprintf(stderr, "%s <file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char* file_path = argv[1];

    FILE *file = fopen(file_path, "rb");
    if (file == NULL) {
        fprintf(stderr, "ERROR: Could not read file: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    char *data = (char*)malloc(size);
    if (data == NULL) {
        fprintf(stderr, "ERROR: Could not allocate memory");
        fclose(file);
        return EXIT_FAILURE;
    }

    fread(data, size, 1, file);

    fclose(file);

    for (long i = 0; i < size; i += 16) {
        printf("%08lx  ", i);

        for (long j = i; j < i+16; ++j) {
            if (j < size) {
                printf("%02x ", (unsigned char)data[j]);
            } else {
                printf("   ");
            }

            if (j == i+7) {
                printf(" ");
            }
        }

        printf(" |");

        for (int j = i; j < i+16 && j < size; ++j) {
            char it = data[j];
            if (it < ' ' || it > '~') {
                it = '.';
            }
            printf("%c", it);
        }
        printf("|\n");
    }

    printf("%08lx\n", size);

    free(data);

    return EXIT_SUCCESS;
}
