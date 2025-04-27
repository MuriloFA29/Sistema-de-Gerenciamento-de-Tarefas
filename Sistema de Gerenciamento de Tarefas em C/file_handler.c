#include "task_manager.h"
#include <stdio.h>

void salvarTarefasEmArquivo() {
    FILE *file;
    char *filename = "tarefas.txt";

    // Abre o arquivo em modo de escrita
    file = fopen(filename, "w");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Verificar se existe tarefas

    if (quantidadeTarefas == 0) {
        printf("Erro ao fazer a escrita, nenhuma tarefa cadastrada.\n");

        // Fecha o arquivo
        fclose(file);

        return; // termina a função se não tiver tarefas
    }

    // Escrever tarefas no arquivo

    for (int q = 0; q < quantidadeTarefas; q++) {
        fprintf(file, "%d|%s|%s|%d|%s|%d\n",
            tarefas[q].id,
            tarefas[q].titulo,
            tarefas[q].descricao,
            tarefas[q].prioridade,
            tarefas[q].data,
            tarefas[q].concluida
        );
    }

    printf("Arquivo escrito com sucesso!\n");

    // Fecha o arquivo
    fclose(file);

    return;
}

void carregarTarefasDoArquivo() {
    FILE *file;
    char *filename = "tarefas.txt";

    // Abre o arquivo em modo de leitura
    file = fopen(filename, "r");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Lê o arquivo linha por linha
    while (fscanf(file, "%d|%49[^|]|%199[^|]|%d|%10[^|]|%d\n",
            &tarefas[quantidadeTarefas].id,
            tarefas[quantidadeTarefas].titulo,
            tarefas[quantidadeTarefas].descricao,
            &tarefas[quantidadeTarefas].prioridade,
            tarefas[quantidadeTarefas].data,
            &tarefas[quantidadeTarefas].concluida) != EOF) {

        quantidadeTarefas++;  // Incrementa a quantidade de tarefas

        // Verifica se é necessário expandir o array de tarefas
        if (quantidadeTarefas >= capacidadeTarefas) {
            capacidadeTarefas *= 2;
            tarefas = realloc(tarefas, capacidadeTarefas * sizeof(Tarefa));

            // Verifica se o realloc falhou
            if (tarefas == NULL) {
                printf("Erro ao realocar memória.\n");
                fclose(file);
                return;
            }
        }
    }

    printf("Arquivo lido com sucesso!\n");

    // Fecha o arquivo
    fclose(file);

    return;
}

void exportarRelatorioConcluidas() {
    FILE *file;
    char *filename = "relatorio_concluidas.txt";
    int tarefasExportadas = 0;

    // Abre o arquivo em modo de escrita
    file = fopen(filename, "w");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Verificar se existe tarefas

    if (quantidadeTarefas == 0) {
        printf("Erro ao fazer a escrita, nenhuma tarefa cadastrada.\n");

        // Fecha o arquivo
        fclose(file);

        return; // termina a função se não tiver tarefas
    }

    // Escrever tarefas concluidas no arquivo

    for (int i = 0; i < quantidadeTarefas; i++) {
        if (tarefas[i].concluida == 1) {
            fprintf(file, "%d|%s|%s|%d|%s|%d\n",
            tarefas[i].id,
            tarefas[i].titulo,
            tarefas[i].descricao,
            tarefas[i].prioridade,
            tarefas[i].data,
            tarefas[i].concluida
            );
            tarefasExportadas++;
        }
    }

    printf("Arquivo escrito com sucesso!\n");

    // Fecha o arquivo
    fclose(file);

    if (tarefasExportadas == 0) {
        printf("Nenhuma tarefa concluída para exportar.\n");
        remove(filename); // Deleta o arquivo quando vazio
    } else {
        printf("Relatório exportado com sucesso (%d tarefas concluídas).\n", tarefasExportadas);
    }

    return;
}

void backupTarefas() {
    FILE *backupFile;
    char *backupFilename = "tarefas_backup.txt";

    // Abrir arquivo de backup
    backupFile = fopen(backupFilename, "w");

    if (backupFile == NULL) {
        printf("Erro ao abrir arquivo de backup.\n");
        return;
    }

    // Escrever todas as tarefas no arquivo de backup
    for (int i = 0; i < quantidadeTarefas; i++) {
        fprintf(backupFile, "%d|%s|%s|%d|%s|%d\n",
            tarefas[i].id,
            tarefas[i].titulo,
            tarefas[i].descricao,
            tarefas[i].prioridade,
            tarefas[i].data,
            tarefas[i].concluida);
    }

    printf("Backup realizado com sucesso!\n");
    fclose(backupFile);
}



