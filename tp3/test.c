#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_STATES 1000000
#define MAX_PATH_LEN 1000

typedef struct {
    int* numbers; // array current numbers - 8 bytes
    int size; // size array - 4 bytes
    char path[MAX_PATH_LEN]; // string store sequence operations - 1000 bytes
} State;

typedef struct HashNode {
    int* key; // array represent state
    int size; // size array
    struct HashNode* next; // pointer to next node
} HashNode;

HashNode* hashTable[MAX_STATES] = {NULL};

State queue[MAX_STATES];
int front = 0, rear = 0;

// fonction creer une copie d'un array
int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}
int* sorted_copy(int* arr, int size) {
    int* sorted = malloc(size * sizeof(int));
    memcpy(sorted, arr, size * sizeof(int));
    qsort(sorted, size, sizeof(int), compare);
    return sorted;
}

// fonction de hachage
// check si un etat existe dans la table de hachage
// si non, ajouter l'etat dans la table de hachage
unsigned int hash(int* arr, int size) {
    unsigned int value = 0;
    for (int i = 0; i < size; i++){
        value = (value * 31) ^ arr[i]; // Dùng XOR để phân phối đều hơn
    }
    return value % MAX_STATES;
}

int exists(int* arr, int size) {
    int* sorted = sorted_copy(arr, size); // create a sorted copy of arr
    unsigned int h = hash(sorted, size); // get hash value
    HashNode* node = hashTable[h]; // get node from hashTable
    // si l'etat existe, libérer la mémoire => retourner 1
    while (node) {
        if (node->size == size && memcmp(node->key, sorted, size * sizeof(int)) == 0) {
            free(sorted);
            return 1;
        }
        node = node->next;
    }
    // sinon, ajouter l'etat dans la table de hachage
    HashNode* newNode = malloc(sizeof(HashNode));
    newNode->key = sorted;
    newNode->size = size;
    newNode->next = hashTable[h]; // assigner next node = null
    hashTable[h] = newNode; // assigner le nouveau noeud à la table
    return 0;
}

// au lieu de stocker les valeurs des éléments de l'array, 
// on stocke des paires d'index de ces éléments
void generate_pairs(int size, int* pairs) {
    int idx = 0;
    for (int i = 0; i < size-1; i++){
        for (int j = i+1; j < size; j++){
            if (i != j) pairs[idx++] = i * 100 + j;
        }
    }
}

void apply_operations(State* current, State* new_states, int* count) {
    int size = current->size;
    int pair_count = size * (size - 1)/2;
    int* pairs = malloc(pair_count * sizeof(int));
    generate_pairs(size, pairs);

    for (int p = 0; p < pair_count; p++) {
        int i = pairs[p] / 100; // extract i, j index
        int j = pairs[p] % 100;
        if (i >= size || j >= size) continue; // si i, j >= size, passer à la prochaine paire

        int a = current->numbers[i]; // get value of i, j in current
        int b = current->numbers[j];
        int new_size = size - 1;

        // Tạo bản sao base numbers
        int* base_nums = malloc((size - 2) * sizeof(int));
        int base_idx = 0;
        for (int k = 0; k < size; k++) {
            if (k != i && k != j) {
                base_nums[base_idx++] = current->numbers[k];
            }
        }

        // Xử lý từng phép toán
        // Phép cộng
        int* new_nums = malloc(new_size * sizeof(int));
        memcpy(new_nums, base_nums, (size-2)*sizeof(int));
        new_nums[new_size-1] = a + b;
        if (!exists(new_nums, new_size)) {
            strcpy(new_states[*count].path, current->path);
            sprintf(new_states[*count].path + strlen(new_states[*count].path), "%d+%d=%d; ", a, b, a+b);
            new_states[*count].numbers = new_nums;
            new_states[*count].size = new_size;
            (*count)++;
        } else {
            free(new_nums);
        }

        // Phép nhân
        new_nums = malloc(new_size * sizeof(int));
        memcpy(new_nums, base_nums, (size-2)*sizeof(int));
        new_nums[new_size-1] = a * b;
        if (!exists(new_nums, new_size)) {
            strcpy(new_states[*count].path, current->path);
            sprintf(new_states[*count].path + strlen(new_states[*count].path), "%d*%d=%d; ", a, b, a*b);
            new_states[*count].numbers = new_nums;
            new_states[*count].size = new_size;
            (*count)++;
        } else {
            free(new_nums);
        }

        // Phép trừ
        if (a > b) {
            new_nums = malloc(new_size * sizeof(int));
            memcpy(new_nums, base_nums, (size-2)*sizeof(int));
            new_nums[new_size-1] = a - b;
            if (!exists(new_nums, new_size)) {
                strcpy(new_states[*count].path, current->path);
                sprintf(new_states[*count].path + strlen(new_states[*count].path), "%d-%d=%d; ", a, b, a-b);
                new_states[*count].numbers = new_nums;
                new_states[*count].size = new_size;
                (*count)++;
            } else {
                free(new_nums);
            }
        } else if (b > a) {
            new_nums = malloc(new_size * sizeof(int));
            memcpy(new_nums, base_nums, (size-2)*sizeof(int));
            new_nums[new_size-1] = b - a;
            if (!exists(new_nums, new_size)) {
                strcpy(new_states[*count].path, current->path);
                sprintf(new_states[*count].path + strlen(new_states[*count].path), "%d-%d=%d; ", b, a, b-a);
                new_states[*count].numbers = new_nums;
                new_states[*count].size = new_size;
                (*count)++;
            } else {
                free(new_nums);
            }
        }

        // Phép chia
        if (b != 0 && a % b == 0) {
            new_nums = malloc(new_size * sizeof(int));
            memcpy(new_nums, base_nums, (size-2)*sizeof(int));
            new_nums[new_size-1] = a / b;
            if (!exists(new_nums, new_size)) {
                strcpy(new_states[*count].path, current->path);
                sprintf(new_states[*count].path + strlen(new_states[*count].path), "%d/%d=%d; ", a, b, a/b);
                new_states[*count].numbers = new_nums;
                new_states[*count].size = new_size;
                (*count)++;
            } else {
                free(new_nums);
            }
        } else if (a != 0 && b % a == 0) {
            new_nums = malloc(new_size * sizeof(int));
            memcpy(new_nums, base_nums, (size-2)*sizeof(int));
            new_nums[new_size-1] = b / a;
            if (!exists(new_nums, new_size)) {
                strcpy(new_states[*count].path, current->path);
                sprintf(new_states[*count].path + strlen(new_states[*count].path), "%d/%d=%d; ", b, a, b/a);
                new_states[*count].numbers = new_nums;
                new_states[*count].size = new_size;
                (*count)++;
            } else {
                free(new_nums);
            }
        }

        free(base_nums);
    }
    free(pairs);
}

int explore_solution(int R, int* initial, int size) {
    front = rear = 0;
    int* sorted_init = sorted_copy(initial, size);
    State init_state = {sorted_init, size, ""};
    queue[rear++] = init_state;

    while (front < rear) {
        State current = queue[front++];
        
        // Check immediately when state is created
        for (int i = 0; i < current.size; i++) {
            if (current.numbers[i] == R) {
                printf("Solution: %s\n", current.path);
                return 1;
            }
        }

        if (current.size == 1) continue;

        int max_new_states = 4 * current.size * (current.size - 1)/2;
        State* new_states = malloc(max_new_states * sizeof(State));
        int count = 0;
        apply_operations(&current, new_states, &count);
        
        for (int i = 0; i < count; i++) {
            // Kiểm tra nếu trạng thái mới có chứa số R
            for (int j = 0; j < new_states[i].size; j++) {
                if (new_states[i].numbers[j] == R) {
                    printf("Solution: %s\n", new_states[i].path);
                    free(new_states);
                    return 1;  // Kết thúc ngay khi tìm thấy kết quả
                }
            }

            // Nếu chưa đạt kết quả, đưa vào queue như bình thường
            if (rear >= MAX_STATES) {
                printf("Queue overflow!\n");
                free(new_states);
                return 0;
            }
            queue[rear++] = new_states[i];
        }
        free(new_states);
    }
    return 0;
}

void draw_tiles(int* output) {
    // creer un ensemble de 28 plaques
    int tiles[28];
    int index = 0;
    
    // Ajouter 20 plaques numérotées de 1 à 10 (2 par nombre)
    for (int num = 1; num <= 10; num++) {
        tiles[index++] = num;
        tiles[index++] = num;
    }
    
    // Ajouter 2 plaques de (25, 50, 75, 100)
    int specials[] = {25, 50, 75, 100};
    for (int i = 0; i < 4; i++) {
        tiles[index++] = specials[i];
        tiles[index++] = specials[i];
    }
    
    // shuffle les 28 plaques
    for (int i = 27; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = tiles[i];
        tiles[i] = tiles[j];
        tiles[j] = temp;
    }
    
    // Prendre les 6 premières plaques
    for (int i = 0; i < 6; i++) {
        output[i] = tiles[i];
    }
}

// random target
int generate_target() {
    return (rand() % 900) + 100; // 100-999
}

void reset_hash_table() {
    for (int i = 0; i < MAX_STATES; i++) {
        HashNode* node = hashTable[i];
        while (node) {
            HashNode* temp = node;
            node = node->next;
            free(temp->key);
            free(temp);
        }
        hashTable[i] = NULL;
    }
}

int main() {
    int selected[6];
    int target;
    int found_count = 0;
    double total_time = 0.0;

    for (int run = 0; run < 50; run++) {
        reset_hash_table();
        srand(time(NULL) + run);
        draw_tiles(selected);
        target = generate_target();
        
        // print selected numbers and target
        // printf("Run %d\n", run + 1);
        // printf("Selected numbers: ");
        // for (int i = 0; i < 6; i++) {
        //     printf("%d ", selected[i]);
        // }
        // printf("\nTarget: %d\n", target);

        clock_t start_time = clock();
        if (explore_solution(target, selected, 6)) {
            //printf("Found!\n");
            found_count++;
        } else {
            //printf("Not found!\n");
        }
        clock_t end_time = clock();
        double run_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        total_time += run_time;
        printf("Run time: %f seconds\n", run_time);
    }

    double average_time = total_time / 50;
    printf("Average run time: %f seconds\n", average_time);
    printf("Found count: %d out of 50\n", found_count);

    return 0;
}
