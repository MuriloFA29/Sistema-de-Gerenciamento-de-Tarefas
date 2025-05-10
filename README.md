# Sistema de Gerenciamento de Tarefas

Este é um gerenciador de tarefas desenvolvido em C, permitindo criar, editar, visualizar e excluir tarefas. Inclui funcionalidades extras como o modo Pomodoro e a exportação de relatórios de tarefas concluídas. A aplicação é executada no terminal e oferece uma interface simples via menu.

## Como Rodar

### Requisitos

- Um compilador C (como `gcc`).
- Sistema operacional que suporte a execução de C no terminal (Windows, Linux, MacOS).

### Passos

1. **Clone o repositório:**
   Se ainda não tiver o projeto, clone-o para sua máquina local com o comando:
   ```bash
   git clone https://github.com/MuriloFA29/Sistema-de-Gerenciamento-de-Tarefas.git

## Projeto: Sistema de Gerenciamento de Tarefas (To-Do CLI App)

Este projeto é um sistema de gerenciamento de tarefas desenvolvido em C, com uma interface de linha de comando (CLI). Ele permite que o usuário adicione, edite, visualize, e remova tarefas, além de funcionalidades extras, como um modo Pomodoro e a exportação de relatórios de tarefas concluídas.

### Funcionalidades:
- Adicionar tarefas com título, descrição, prioridade e data.
- Listar tarefas, com a opção de filtrar por status ou prioridade.
- Marcar tarefas como concluídas.
- Remover ou editar tarefas.
- Persistência de dados: salvar tudo em arquivos `.txt`.
- Organizar as tarefas por data ou prioridade, utilizando algoritmos de ordenação.

### Estrutura do Projeto:
- **main.c** — Entrada do programa.
- **task_manager.c/h** — Lógica de gerenciamento de tarefas.
- **file_handler.c/h** — Leitura e escrita de arquivos.
- **menu.c/h** — Interface do terminal.

### Conceitos Aplicados:
- Manipulação de arquivos (`fopen`, `fwrite`, `fread`).
- Uso de ponteiros e structs (ex.: `struct Tarefa`, ponteiro para arrays dinâmicos).
- Modularização de código (arquivos `.c` e `.h`).
- Algoritmos de ordenação (Bubble Sort).
- Alocação dinâmica com `malloc`/`free`.
- Validação de entradas e controle de fluxo no terminal.

### Funcionalidades Extras:
- Exportação de relatórios de tarefas concluídas em formato `.txt`.
- Modo Pomodoro para aumentar a produtividade.
- Interface em terminal bem estruturada e fácil de usar.
