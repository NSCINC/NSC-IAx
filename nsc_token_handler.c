#include <stdio.h>
#include <string.h>

// Função para criar e validar tokens NSC
int validate_nsc_token(const char *token) {
    // Lógica para validar o token NSC
    if (strcmp(token, "VALID_TOKEN") == 0) {
        return 1;  // Token válido
    }
    return 0;  // Token inválido
}
