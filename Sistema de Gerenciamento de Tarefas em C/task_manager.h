#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

typedef struct {
    int id;
    char titulo[50];
    char descricao[200];
    int prioridade; // 1 = alta, 2 = média, 3 = baixa
    char data[11]; // formato: dd/mm/aaaa
    int concluida; // 0 = não, 1 = sim
} Tarefa;

// Variáveis globais
extern Tarefa* tarefas;
extern int quantidadeTarefas;
extern int capacidadeTarefas;
extern int configuracaoOrdenacao;

#endif
