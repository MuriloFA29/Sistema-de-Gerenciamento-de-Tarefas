#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "task_manager.h"
#include "menu.h"

int main() {
    // Comando para não bugar caracteres especiais
    setlocale(LC_ALL, "");

    // Aloca memória para o array de tarefas
    capacidadeTarefas = 10;
    tarefas = malloc(capacidadeTarefas * sizeof(Tarefa));

    if (tarefas == NULL) {
        printf("Erro ao alocar memória para as tarefas.\n");
        return 1;  // Termina o programa se a alocação falhar
    }

    // Chama a função de exibição do menu
    exibirMenu();

    // Libera a memória alocada antes de terminar o programa
    free(tarefas);

    // Backup das tarefas antes de terminar o programa
    backupTarefas();

    return 0;
}
