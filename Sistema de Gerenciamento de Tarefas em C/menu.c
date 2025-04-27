#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <unistd.h>
#include "task_manager.h"
#include "file_handler.h"
#include "menu.h"

// Códigos ANSI para cores

#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"

void exibirMenu() {
    int opcao;

    do {
        printf("\n=== Sistema de Gerenciamento de Tarefas ===\n");
        printf("1. Adicionar Tarefa\n");
        printf("2. Mostrar Tarefa Específica\n");
        printf("3. Listar Tarefas\n");
        printf("4. Listar Tarefas por Filtros\n");
        printf("5. Editar Tarefa\n");
        printf("6. Remover Tarefa\n");
        printf("7. Marcar Tarefa como Concluída\n");
        printf("8. Carregar Tarefas do Arquivo\n");
        printf("9. Salvar Tarefas em Arquivo\n");
        printf("10. Configurar Ordenação\n");
        printf("11. Modo Pomodoro\n");
        printf("12. Modo Foco\n");
        printf("13. Limpar Tela\n");
        printf("14. Sair\n\n");
        printf("Escolha uma opção: ");

        // Coleta e valida a entrada do usuário
        if (scanf("%d", &opcao) != 1) {
            // Caso a entrada não seja um número
            while(getchar() != '\n'); // Limpa o buffer
            printf("Opção inválida! Digite um número entre 1 e 14.\n");
            continue;
        }

        switch(opcao) {
            case 1:
                system("cls");
                adicionarTarefa();
                break;
            case 2:
                system("cls");
                mostrarTarefa();
                break;
            case 3:
                system("cls");
                listarTarefas();
                break;
            case 4:
                system("cls");
                exibirMenuFiltros();
                break;
            case 5:
                system("cls");
                editarTarefa();
                break;
            case 6:
                system("cls");
                removerTarefa();
                break;
            case 7:
                system("cls");
                marcarTarefaComoConcluida();
                break;
            case 8:
                system("cls");
                carregarTarefasDoArquivo();
                break;
            case 9:
                system("cls");
                salvarTarefasEmArquivo();
                break;
            case 10:
                system("cls");
                configurarOrdenacao();
                break;
            case 11:
                modoPomodoro();
                break;
            case 12:
                modoPomodoroPersonalizado();
                break;
            case 13:
                system("cls");
                break;
            case 14:
                system("cls");
                printf("Saindo... Até logo!\n");
                break;
            default:
                system("cls");
                printf("Opção inválida! Digite um número entre 1 e 14.\n");
        }

    } while (opcao != 14); // O loop continua até a opção 14 (Sair)
}

void exibirMenuFiltros() {
    int opcaoFiltro;

    system("cls");

    printf("Escolha o filtro desejado:\n");
    printf("1. Apenas tarefas pendentes\n");
    printf("2. Apenas tarefas concluídas\n");
    printf("3. Filtrar por prioridade\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcaoFiltro);

    switch (opcaoFiltro) {
        case 1:
            filtrarPorStatus(0);  // Filtro para tarefas PENDENTES
            break;
        case 2:
            filtrarPorStatus(1);  // Filtro para tarefas CONCLUÍDAS
            break;
        case 3: {
            int prioridade;

            // Verificação para ver se o usúario vai escrever um numero correspondente
            do {
                printf("\n\nEscolha a prioridade (1 = Alta, 2 = Média, 3 = Baixa): ");
                scanf("%d", &prioridade);
            } while (prioridade < 1 || prioridade > 3); // Se estiver errado, pergunta de novo a escolha
            filtrarPorPrioridade(prioridade);  // Filtro para tarefas PRIORIDADE
            break;
        }
        default:
            printf("Opção inválida.\n");
            break;
    }
}

void configurarOrdenacao() {
    printf("Escolha o critério de ordenação das tarefas:\n");
    printf("1. Ordenar por ID\n");
    printf("2. Ordenar por Prioridade\n");
    printf("3. Ordenar por Data\n");
    printf("Escolha uma opção: ");

    int escolha;
    scanf("%d", &escolha);

    switch(escolha) {
            case 1:
                ordenarPorID();
                configuracaoOrdenacao = 1;  // Ordenação por Prioridade
                printf("Ordenação por ID selecionada.\n");
                break;
            case 2:
                configuracaoOrdenacao = 2;  // Ordenação por Prioridade
                printf("Ordenação por Prioridade selecionada.\n");
                break;
            case 3:
                system("cls");
                configuracaoOrdenacao = 3;  // Ordenação por Data
                printf("Ordenação por Data selecionada.\n");
                break;
            default:
                system("cls");
                printf("Opção inválida. Voltando ao menu principal.\n");
                break;
    }
}

void modoPomodoro() {
    int minutos = 25;
    int minutosPausa = 5;
    int segundos = 0;

    system("cls");
    printf(GREEN "Comece o foco! 25 minutos iniciando agora...\n\n" RESET);

    sleep(2);

    // ===== Foco =====

    while (minutos > 0 || segundos > 0) {
        system("cls");

        printf(GREEN "Tempo restante de foco: %02d:%02d\n" RESET, minutos, segundos);

        sleep(1);

        if (segundos == 0) {
            if (minutos > 0) {
                minutos--;
                segundos = 59;
            }
        } else {
            segundos--;
        }
    }

    // Aviso de término do foco

    system("cls");
    printf(RED "\nTempo de foco esgotado! Hora da pausa!\n\n" RESET);

    // Toque um beep 5 vezes

    for (int i = 0; i < 5; i++) {
        Beep(1000, 500);
        sleep(2);
    }

    // ===== Pausa =====

    segundos = 0;
    while (minutosPausa > 0 || segundos > 0) {
        system("cls");
        printf(RED "Pausa - Tempo restante: %02d:%02d\n" RESET, minutosPausa, segundos);
        sleep(1);

        if (segundos == 0) {
            if (minutosPausa > 0) {
                minutosPausa--;
                segundos = 59;
            }
        } else {
            segundos--;
        }
    }

    // Aviso de término da pausa

    system("cls");
    printf(GREEN "\nPausa encerrada! Pronto para mais um ciclo!\n\n" RESET);
    for (int i = 0; i < 2; i++) {
        Beep(1500, 400);
        sleep(1);
    }

    system("cls");
}

void modoPomodoroPersonalizado() {
    int minutosFoco, minutosPausa, segundos = 0;

    // Pega os valores

    printf(GREEN "Digite o tempo de foco (em minutos): " RESET);
    scanf("%d", &minutosFoco);
    getchar();

    printf(GREEN "Digite o tempo de pausa (em minutos): " RESET);
    scanf("%d", &minutosPausa);
    getchar();

    sleep(1);

    // ===== Foco =====

    printf(GREEN "\nComece o foco! %d minutos iniciando agora...\n\n" RESET, minutosFoco);
    sleep(2);

    while (minutosFoco > 0 || segundos > 0) {
        system("cls");
        printf(GREEN "Foco - Tempo restante: %02d:%02d\n" RESET, minutosFoco, segundos);
        sleep(1);

        if (segundos == 0) {
            if (minutosFoco > 0) {
                minutosFoco--;
                segundos = 59;
            }
        } else {
            segundos--;
        }
    }

    // Aviso de término do foco

    system("cls");
    printf(RED "\nTempo de foco esgotado! Hora da pausa!\n\n" RESET);
    for (int i = 0; i < 3; i++) {
        Beep(1000, 500);
        sleep(1);
    }
    sleep(2);

    // ===== Pausa =====

    segundos = 0;
    while (minutosPausa > 0 || segundos > 0) {
        system("cls");
        printf(RED "Pausa - Tempo restante: %02d:%02d\n" RESET, minutosPausa, segundos);
        sleep(1);

        if (segundos == 0) {
            if (minutosPausa > 0) {
                minutosPausa--;
                segundos = 59;
            }
        } else {
            segundos--;
        }
    }

    // Aviso de término da pausa

    system("cls");
    printf(GREEN "\nPausa encerrada! Pronto para mais um ciclo!\n\n" RESET);
    for (int i = 0; i < 2; i++) {
        Beep(1500, 400);
        sleep(1);
    }
}

