#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE (1024 * 1024)  // 1 MB

int main() {
    size_t count = 0;
    void **blocks = NULL;

    while (1) {
        void *block = malloc(BLOCK_SIZE);
        if (block == NULL) {
            printf("malloc() failed after allocating %zu MB\n", count);
            break;
        }

        // Зберігаємо вказівники для подальшого звільнення
        void **temp = realloc(blocks, (count + 1) * sizeof(void *));
        if (temp == NULL) {
            printf("realloc() failed at %zu MB\n", count);
            free(block);
            break;
        }

        blocks = temp;
        blocks[count] = block;
        count++;
    }

    printf("✅ malloc() успішно виділив приблизно %zu MB пам’яті\n", count);

    // Звільнення всієї виділеної пам’яті
    for (size_t i = 0; i < count; ++i) {
        free(blocks[i]);
    }
    free(blocks);

    return 0;
}
