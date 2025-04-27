#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "task_manager.h"
#include "menu.h"

int main() {
    // Comando para n�o bugar caracteres especiais
    setlocale(LC_ALL, "");

    // Aloca mem�ria para o array de tarefas
    capacidadeTarefas = 10;
    tarefas = malloc(capacidadeTarefas * sizeof(Tarefa));

    if (tarefas == NULL) {
        printf("Erro ao alocar mem�ria para as tarefas.\n");
        return 1;  // Termina o programa se a aloca��o falhar
    }

    // Chama a fun��o de exibi��o do menu
    exibirMenu();

    // Libera a mem�ria alocada antes de terminar o programa
    free(tarefas);

    // Backup das tarefas antes de terminar o programa
    backupTarefas();

    return 0;
}
