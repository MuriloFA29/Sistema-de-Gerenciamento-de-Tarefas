#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "task_manager.h"

Tarefa *tarefas = NULL; // Ponteiro para o array de tarefas
int quantidadeTarefas = 0; // Quantidade de tarefas no array
int capacidadeTarefas = 10; // Capacidade inicial do array
int configuracaoOrdenacao = 1; // 1 = Padrão, 2 = Prioridade, 3 = Data

void adicionarTarefa() {
    system("cls");

    // Verificar Capacidade

    if (quantidadeTarefas == capacidadeTarefas) {
        capacidadeTarefas *= 2;
        Tarefa* novo = realloc(tarefas, capacidadeTarefas * sizeof(Tarefa));
        if (novo == NULL) {
            printf("Erro ao realocar memória.\n");
            exit(1);
        }
        tarefas = novo;
    }

    // Limpar buffer antes de fgets

    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    // Pegar Dados da Tarefa

    printf("\nTítulo: ");
    fgets(tarefas[quantidadeTarefas].titulo, 50, stdin);
    tarefas[quantidadeTarefas].titulo[strcspn(tarefas[quantidadeTarefas].titulo, "\n")] = 0;

    printf("Descrição: ");
    fgets(tarefas[quantidadeTarefas].descricao, 200, stdin);
    tarefas[quantidadeTarefas].descricao[strcspn(tarefas[quantidadeTarefas].descricao, "\n")] = 0;

    do {
        printf("Prioridade (1 = Alta, 2 = Média, 3 = Baixa): ");
        scanf("%d", &tarefas[quantidadeTarefas].prioridade);
    } while (tarefas[quantidadeTarefas].prioridade < 1 || tarefas[quantidadeTarefas].prioridade > 3);

    printf("Data (dd/mm/aaaa): ");
    scanf("%s", tarefas[quantidadeTarefas].data);

    // Atualizar ID e Concluido

    tarefas[quantidadeTarefas].id = quantidadeTarefas + 1;
    tarefas[quantidadeTarefas].concluida = 0;

    // Somar 1 a Quantidade de Tarefas

    quantidadeTarefas++;

    backupTarefas();
}

void listarTarefas() {
    system("cls");

    // Aplicar ordenação conforme a configuração

    if (configuracaoOrdenacao == 2) {
        ordenarPorPrioridade();
    } else if (configuracaoOrdenacao == 3) {
        ordenarPorData();
    }

    // Verificar se Existe Tarefas

    if (quantidadeTarefas == 0) {
        printf("Nenhuma tarefa cadastrada.\n");
        return; // termina a função se não tiver tarefas
    }

    for (int q = 0; q < quantidadeTarefas; q++) {
        char concluida[10];

        if (tarefas[q].concluida == 0) {
            strcpy(concluida, "Pendente");
        } else {
            strcpy(concluida, "Concluída");
        }

        printf("ID: %d\n", tarefas[q].id);
        printf("Título: %s\n", tarefas[q].titulo);
        printf("Prioridade: %d\n", tarefas[q].prioridade);
        printf("Data: %s\n", tarefas[q].data);
        printf("Status: %s\n", concluida);
        printf("-------------------------\n");
    }
}

void mostrarTarefa() {
    int id, opcao, confirm;

    // Verificar se existem tarefas

    if (quantidadeTarefas == 0) {
        printf("Nenhuma tarefa cadastrada.\n");
        return;
    }

    // Mostrar IDs e títulos disponíveis

    printf("Tarefas disponíveis:\n");
    for (int q = 0; q < quantidadeTarefas; q++) {
        printf("ID: %d | Título: %s\n", tarefas[q].id, tarefas[q].titulo);
    }

    // Escolher ID

    printf("Digite o ID da tarefa que deseja ver: ");
    scanf("%d", &id);
    getchar(); // limpar o \n do buffer

    // Procurar o índice correto

    int indice = -1;
    for (int i = 0; i < quantidadeTarefas; i++) {
        if (tarefas[i].id == id) {
            indice = i;
            break;
        }
    }
    if (indice == -1) {
        printf("Tarefa com ID %d não encontrada.\n", id);
        return;
    }

    // Mostrar dados da tarefa

    system("cls");

    printf("\nID da tarefa selecionada: %d\n\n", tarefas[indice].id);
    printf("Título: %s\n", tarefas[indice].titulo);
    printf("Descrição: %s\n\n", tarefas[indice].descricao);
    printf("Prioridade: %d\n", tarefas[indice].prioridade);
    printf("Data: %s\n", tarefas[indice].data);
    printf("Status: %s\n", tarefas[indice].concluida ? "Concluída" : "Pendente");

    printf("\n");
    system("pause");
    system("cls");
}

void editarTarefa() {
    system("cls");

    int id, opcao, confirm;
    char newTitulo[50] = "", newDescricao[200] = "", newData[11] = "";
    int newPrioridade = 0, newStatus = 3;

    // Verificar se existem tarefas

    if (quantidadeTarefas == 0) {
        printf("Nenhuma tarefa cadastrada.\n");
        return;
    }

    // Mostrar IDs e títulos disponíveis

    printf("Tarefas disponíveis:\n");
    for (int q = 0; q < quantidadeTarefas; q++) {
        printf("ID: %d | Título: %s\n", tarefas[q].id, tarefas[q].titulo);
    }

    // Escolher ID

    printf("Digite o ID da tarefa que deseja ver: ");
    scanf("%d", &id);
    getchar(); // limpar o \n do buffer

    // Procurar o índice correto

    int indice = -1;
    for (int i = 0; i < quantidadeTarefas; i++) {
        if (tarefas[i].id == id) {
            indice = i;
            break;
        }
    }
    if (indice == -1) {
        printf("Tarefa com ID %d não encontrada.\n", id);
        return;
    }

    // Mostrar dados atuais

    printf("\nTarefa selecionada:\n");
    printf("Título: %s\n", tarefas[indice].titulo);
    printf("Descrição: %s\n", tarefas[indice].descricao);
    printf("Prioridade: %d\n", tarefas[indice].prioridade);
    printf("Data: %s\n", tarefas[indice].data);
    printf("Status: %s\n", tarefas[indice].concluida ? "Concluída" : "Pendente");

    // Menu de edição

    do {
        printf("\nO que deseja editar?\n");
        printf("1. Título\n");
        printf("2. Descrição\n");
        printf("3. Prioridade\n");
        printf("4. Data\n");
        printf("5. Status de conclusão\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // limpar \n

        switch (opcao) {
            case 1:
                printf("Novo título: ");
                fgets(newTitulo, sizeof(newTitulo), stdin);
                newTitulo[strcspn(newTitulo, "\n")] = '\0'; // remove o \n
                break;

            case 2:
                printf("Nova descrição: ");
                fgets(newDescricao, sizeof(newDescricao), stdin);
                newDescricao[strcspn(newDescricao, "\n")] = '\0';
                break;

            case 3:
                do {
                    printf("Nova prioridade (1 = Alta, 2 = Média, 3 = Baixa): ");
                    scanf("%d", &newPrioridade);
                } while (newPrioridade < 1 || newPrioridade > 3);
                break;

            case 4:
                printf("Nova data (dd/mm/aaaa): ");
                scanf("%10s", newData);
                break;

            case 5:
                printf("Novo status (0 = Pendente, 1 = Concluída): ");
                scanf("%d", &newStatus);
                while (newStatus != 0 && newStatus != 1) {
                    printf("Digite 0 (Pendente) ou 1 (Concluída): ");
                    scanf("%d", &newStatus);
                }
                break;

            case 6:
                printf("Saindo da edição...\n");
                break;

            default:
                printf("Opção inválida!\n");
                break;
        }
    } while (opcao != 6);

    // Confirmar alterações

    printf("\nDeseja confirmar as alterações? (1 = Sim / 2 = Não): ");
    scanf("%d", &confirm);

    if (confirm == 1) {
        if (newTitulo[0] != '\0') {
            strcpy(tarefas[indice].titulo, newTitulo);
        }
        if (newDescricao[0] != '\0') {
            strcpy(tarefas[indice].descricao, newDescricao);
        }
        if (newPrioridade != 0) {
            tarefas[indice].prioridade = newPrioridade;
        }
        if (newData[0] != '\0') {
            strcpy(tarefas[indice].data, newData);
        }
        if (newStatus != 3) { // lembre que 3 é o valor padrão
            tarefas[indice].concluida = newStatus;
        }
        printf("Alterações salvas com sucesso!\n");
    } else {
        printf("Alterações canceladas.\n");
    }

    backupTarefas();
}

void removerTarefa () {
    system("cls");

    int id, confirm, indiceRemover;

    // Verificar se existem tarefas

    if (quantidadeTarefas == 0) {
        printf("Nenhuma tarefa cadastrada.\n");
        return;
    }

    // Mostrar tarefas disponíveis

    printf("Tarefas disponíveis:\n");
    for (int q = 0; q < quantidadeTarefas; q++) {
        printf("ID: %d | Título: %s\n", tarefas[q].id, tarefas[q].titulo);
    }

    // Receber o ID a ser removido

    printf("Digite o ID da tarefa que deseja remover: ");
    scanf("%d", &id);

    // Procurar o índice correto

    int indice = -1; // Inicializar o índice como inválido
    for (int i = 0; i < quantidadeTarefas; i++) {
        if (tarefas[i].id == id) {
            indice = i;
            break;
        }
    }
    if (indice == -1) {
        printf("Tarefa com ID %d não encontrada.\n", id);
        return;
    }

    // Confirmar exclusão

    do {
        printf("\nTem certeza que quer excluir? (1 = Sim / 2 = Não): ");
        scanf("%d", &confirm);
    } while (confirm < 1 || confirm > 2);

    if (confirm == 2) {
        system("cls");
        return 0;
    }

    // Mostrar tarefa a ser removida
    printf("ID: %d\nTítulo: %s\nPrioridade: %d\nData: %s\nStatus: %s\n",
    tarefas[indice].id, tarefas[indice].titulo, tarefas[indice].prioridade,
    tarefas[indice].data, tarefas[indice].concluida == 0 ? "Pendente" : "Concluída");

    // Remover a tarefa: deslocar as tarefas após o índice para a esquerda
    for (int i = indice; i < quantidadeTarefas - 1; i++) {
            tarefas[i] = tarefas[i + 1];
    }

    // Atualizar a quantidade de tarefas
    quantidadeTarefas--;

    // Reordena os IDs das tarefas
    reordenarID();

    backupTarefas();
}

void reordenarID() {
    // Reordenar os IDs das tarefas para garantir sequência contínua
    for (int i = 0; i < quantidadeTarefas; i++) {
        tarefas[i].id = i + 1;  // Define o ID baseado no índice + 1
    }
}

void marcarTarefaComoConcluida() {
    system("cls");

    int id, confirm;

    // Verificar se existem tarefas

    if (quantidadeTarefas == 0) {
        printf("Nenhuma tarefa cadastrada.\n");
        return;
    }

    do {
        // Mostrar IDs, títulos, prioridades e datas para Tarefas Pendentes

        printf("Tarefas pendentes:\n");
        for (int q = 0; q < quantidadeTarefas; q++) {
            if (tarefas[q].concluida == 0) {
                printf("ID: %d", tarefas[q].id);
                printf("\nTítulo: %s", tarefas[q].titulo);
                printf("\nPrioridade: %d", tarefas[q].prioridade);
                printf("\nData: %s", tarefas[q].data);
            }
        }

        // Escolher ID

        printf("Digite o ID da tarefa que deseja marcar como concluída: ");
        scanf("%d", &id);
        getchar(); // limpar o \n do buffer

        // Procurar o índice correto

        int indice = -1;
        for (int i = 0; i < quantidadeTarefas; i++) {
            if (tarefas[i].id == id) {
                indice = i;
                break;
            }
        }

        if (indice == -1) {
            printf("Tarefa com ID %d não encontrada.\n", id);
           return;
        }

        // Marcar como concluído

        tarefas[indice].concluida = 1;
        printf("Tarefa marcada como concluída!\n");

        // Perguntar se quer marcar outra como concluida

        printf("Deseja marcar outra tarefa como concluída? (1 = Sim / 2 = Não): ");
        scanf("%d", &confirm);

    } while (confirm == 1);
}

void ordenarPorID() {
    int i, j;
    Tarefa temp;

    // Ordenação Bubble Sort

    for (i = 0; i < quantidadeTarefas - 1; i++) {
        for (j = 0; j < quantidadeTarefas - i - 1; j++) {
            if (tarefas[j].id > tarefas[j + 1].id) {
                // Troca as tarefas
                temp = tarefas[j];
                tarefas[j] = tarefas[j + 1];
                tarefas[j + 1] = temp;
            }
        }
    }
}

void ordenarPorPrioridade() {
    int i, j;
    Tarefa temp;

    // Bubble Sort para ordenar as tarefas com base na prioridade

    for (i = 0; i < quantidadeTarefas - 1; i++) {
        for (j = 0; j < quantidadeTarefas - i - 1; j++) {
            // Se a prioridade da tarefa j for maior que a de j+1, trocamos
            if (tarefas[j].prioridade > tarefas[j + 1].prioridade) {
                temp = tarefas[j];
                tarefas[j] = tarefas[j + 1];
                tarefas[j + 1] = temp;
            }
        }
    }
}

void ordenarPorData() {
    for (int i = 0; i < quantidadeTarefas - 1; i++) {
        for (int j = 0; j < quantidadeTarefas - i - 1; j++) {
            if (compararDatas(tarefas[j].data, tarefas[j + 1].data) > 0) {
                // Troca as tarefas
                Tarefa temp = tarefas[j];
                tarefas[j] = tarefas[j + 1];
                tarefas[j + 1] = temp;
            }
        }
    }
}

int compararDatas(char *data1, char *data2) {
    int dia1, mes1, ano1;
    int dia2, mes2, ano2;

    // Extrair dia, mês, e ano de data1
    sscanf(data1, "%d/%d/%d", &dia1, &mes1, &ano1);

    // Extrair dia, mês, e ano de data2
    sscanf(data2, "%d/%d/%d", &dia2, &mes2, &ano2);

    // Comparar primeiro ano, depois mês, depois dia
    if (ano1 != ano2) return ano1 - ano2;
    if (mes1 != mes2) return mes1 - mes2;
    return dia1 - dia2;
}

void filtrarPorStatus(int statusFiltro) {
    for (int i = 0; i < quantidadeTarefas; i++) {
        if (tarefas[i].concluida == statusFiltro) {
            // Exibe a tarefa, se o status corresponder ao filtro
            printf("ID: %d\n", tarefas[i].id);
            printf("Título: %s\n", tarefas[i].titulo);
            printf("Prioridade: %d\n", tarefas[i].prioridade);
            printf("Data: %s\n", tarefas[i].data);
            printf("Status: %s\n", tarefas[i].concluida == 0 ? "Pendente" : "Concluída");
            printf("-------------------------\n");
        }
    }
}

void filtrarPorPrioridade(int prioridadeFiltro) {
    for (int i = 0; i < quantidadeTarefas; i++) {
        if (tarefas[i].prioridade == prioridadeFiltro) {
            // Exibe a tarefa, se a prioridade corresponder ao filtro
            printf("ID: %d\n", tarefas[i].id);
            printf("Título: %s\n", tarefas[i].titulo);
            printf("Prioridade: %d\n", tarefas[i].prioridade);
            printf("Data: %s\n", tarefas[i].data);
            printf("Status: %s\n", tarefas[i].concluida == 0 ? "Pendente" : "Concluída");
            printf("-------------------------\n");
        }
    }
}





