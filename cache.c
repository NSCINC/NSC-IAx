#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

// Definição da estrutura do Cache
typedef struct {
    char **keys;         // Array de chaves
    char **values;       // Array de valores
    int max_size;        // Tamanho máximo do cache
    int current_size;    // Tamanho atual do cache
    pthread_mutex_t lock; // Mutex para controle de concorrência
} Cache;

// Função para inicializar o Cache
Cache* create_cache(int max_size) {
    Cache *cache = (Cache *)malloc(sizeof(Cache));
    cache->keys = (char **)malloc(max_size * sizeof(char *));
    cache->values = (char **)malloc(max_size * sizeof(char *));
    cache->max_size = max_size;
    cache->current_size = 0;
    pthread_mutex_init(&cache->lock, NULL); // Inicializa o mutex
    return cache;
}

// Função para adicionar dados ao cache (Thread-safe)
void add_to_cache(Cache *cache, const char *key, const char *value) {
    pthread_mutex_lock(&cache->lock); // Trava o mutex

    // Verifica se o cache está cheio e remove o item mais antigo (LRU)
    if (cache->current_size >= cache->max_size) {
        printf("Removido do cache (LRU): %s\n", cache->keys[0]);
        free(cache->keys[0]);
        free(cache->values[0]);
        // Desloca os itens para remover o mais antigo
        for (int i = 1; i < cache->current_size; i++) {
            cache->keys[i - 1] = cache->keys[i];
            cache->values[i - 1] = cache->values[i];
        }
        cache->current_size--;
    }

    // Adiciona a nova chave e valor
    cache->keys[cache->current_size] = strdup(key);
    cache->values[cache->current_size] = strdup(value);
    cache->current_size++;
    printf("Novo item adicionado ao cache: %s\n", key);

    pthread_mutex_unlock(&cache->lock); // Libera o mutex
}

// Função para buscar um item no cache (Thread-safe)
const char* get_from_cache(Cache *cache, const char *key) {
    pthread_mutex_lock(&cache->lock); // Trava o mutex

    // Busca pela chave no cache
    for (int i = 0; i < cache->current_size; i++) {
        if (strcmp(cache->keys[i], key) == 0) {
            pthread_mutex_unlock(&cache->lock); // Libera o mutex
            printf("Item encontrado no cache: %s\n", key);
            return cache->values[i];
        }
    }

    pthread_mutex_unlock(&cache->lock); // Libera o mutex
    printf("Item não encontrado no cache: %s\n", key);
    return NULL;
}

// Função para remover um item do cache (Thread-safe)
void remove_from_cache(Cache *cache, const char *key) {
    pthread_mutex_lock(&cache->lock); // Trava o mutex

    for (int i = 0; i < cache->current_size; i++) {
        if (strcmp(cache->keys[i], key) == 0) {
            printf("Item removido do cache: %s\n", key);
            free(cache->keys[i]);
            free(cache->values[i]);
            // Desloca os itens
            for (int j = i + 1; j < cache->current_size; j++) {
                cache->keys[j - 1] = cache->keys[j];
                cache->values[j - 1] = cache->values[j];
            }
            cache->current_size--;
            break;
        }
    }

    pthread_mutex_unlock(&cache->lock); // Libera o mutex
}

// Função para listar todos os itens do cache (Thread-safe)
void list_cache(Cache *cache) {
    pthread_mutex_lock(&cache->lock); // Trava o mutex
    printf("Listando todos os itens no cache:\n");
    for (int i = 0; i < cache->current_size; i++) {
        printf("%s: %s\n", cache->keys[i], cache->values[i]);
    }
    pthread_mutex_unlock(&cache->lock); // Libera o mutex
}

// Função de processamento paralelo para simular adição e busca no cache
void* cache_operations(void *arg) {
    Cache *cache = (Cache *)arg;
    add_to_cache(cache, "Chave1", "Valor1");
    add_to_cache(cache, "Chave2", "Valor2");
    const char *value = get_from_cache(cache, "Chave1");
    if (value) {
        printf("Valor encontrado: %s\n", value);
    }
    remove_from_cache(cache, "Chave1");
    return NULL;
}

int main() {
    // Cria o cache com tamanho máximo de 3
    Cache *myCache = create_cache(3);

    // Cria duas threads para processar operações no cache simultaneamente
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, cache_operations, myCache);
    pthread_create(&thread2, NULL, cache_operations, myCache);

    // Aguarda a finalização das threads
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Lista os itens restantes no cache
    list_cache(myCache);

    // Libera memória e destrói o cache
    for (int i = 0; i < myCache->current_size; i++) {
        free(myCache->keys[i]);
        free(myCache->values[i]);
    }
    free(myCache->keys);
    free(myCache->values);
    free(myCache);
    pthread_mutex_destroy(&myCache->lock);

    return 0;
}
