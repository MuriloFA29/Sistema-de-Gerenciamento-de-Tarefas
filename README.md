# 📋 Sistema de Gerenciamento de Tarefas (CLI)

> Um gerenciador de tarefas completo em C executado no terminal, com persistência de dados, modo Pomodoro integrado e geração de relatórios.

---

## 🛠️ Tech Stack & Conceitos Aplicados

* **Linguagem:** C
* **Manipulação de Arquivos:** Persistência de dados em arquivos `.txt` (`fopen`, `fwrite`, `fread`).
* **Estrutura de Dados:** Uso de structs (`struct Tarefa`) e ponteiros para arrays dinâmicos.
* **Gerenciamento de Memória:** Alocação dinâmica com `malloc` e `free`.
* **Algoritmos:** Ordenação de tarefas por data ou prioridade utilizando Bubble Sort.
* **Arquitetura:** Modularização de código através de arquivos `.c` e `.h`.

---

## ✨ Funcionalidades

- [x] **Gestão de Tarefas:** Adicionar (título, descrição, prioridade e data), editar, listar e remover.
- [x] **Filtros e Status:** Listagem filtrada por status ou prioridade e marcação de conclusão.
- [x] **Persistência de Dados:** Salva e carrega automaticamente as tarefas em arquivo local.
- [x] **Modo Pomodoro:** Timer integrado no terminal para auxiliar na produtividade.
- [x] **Exportação de Relatórios:** Geração de relatórios de tarefas concluídas em `.txt`.

---

## 📁 Estrutura do Projeto

* `main.c` — Ponto de entrada do programa.
* `task_manager.c / .h` — Lógica principal de gerenciamento das tarefas.
* `file_handler.c / .h` — Leitura, escrita e persistência em arquivos.
* `menu.c / .h` — Interface do usuário no terminal.

---

## 🚀 Como Rodar o Projeto

### Pré-requisitos
* Um compilador C instalado (ex: `gcc`).
* Terminal (Windows, Linux ou macOS).

### Passo a Passo

1. **Clone o repositório:**
   ```bash
   git clone https://github.com/MuriloFA29/Sistema-de-Gerenciamento-de-Tarefas.git

2. **Acesse a pasta do projeto:**
   ```bash
   cd Sistema-de-Gerenciamento-de-Tarefas

3. **Compile o projeto com o GCC:**
   ```bash
   gcc main.c task_manager.c file_handler.c menu.c -o sistema_tarefas

4. **Execute o programa:**
   ```bash
   sistema_tarefas.exe

---

## 📄 Licença

Este projeto está sob a licença MIT. Veja o arquivo LICENSE para mais detalhes.
