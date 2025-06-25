# 🧠 Jogo de Perguntas e Respostas sobre Algoritmos

Este é um jogo em linguagem C baseado em perguntas de múltipla escolha sobre programação e algoritmos. O jogo é dividido em 5 níveis, com perguntas armazenadas em arquivos `.txt`, lidas dinamicamente durante a execução.

---

## 🎯 Objetivo

Responda corretamente às perguntas de cada nível. A cada acerto, você avança para o próximo. Você tem **3 vidas** — errou, perde uma. Vença ao chegar ao nível 5 e acertar a última pergunta!

---

## 📁 Estrutura do Projeto

📂 projeto-jogo/
├── jogo.c
├── nivel1.txt
├── nivel2.txt
├── nivel3.txt
├── nivel4.txt
├── nivel5.txt
└── README.md


---

## 🛠️ Funcionalidades

- ✅ Leitura de perguntas e alternativas diretamente de arquivos `.txt`
- ✅ Perguntas de múltipla escolha com alternativas variáveis
- ✅ Avanço de nível automático
- ✅ Controle de pontuação e vidas
- ✅ Uso de `struct`, `enum` e alocação dinâmica (`malloc`/`free`)

---

## 📦 Requisitos

- Compilador C (GCC recomendado)
- Terminal (Linux, macOS ou Windows com WSL/CMD/PowerShell)

---

📄 Formato dos Arquivos de Perguntas (nivel1.txt, nivel2.txt, ...)

PERGUNTA: O que é um algoritmo? 
ALTERNATIVA: Um tipo de dado \n
ALTERNATIVA: Um software
ALTERNATIVA: Um conjunto de passos para resolver um problema
ALTERNATIVA: Um compilador
CORRETA: 2

CORRETA: deve indicar o índice (começando em 0) da resposta correta.
Separe perguntas com uma linha em branco.
## 🚀 Como Compilar e Executar

No terminal, execute:

```bash
gcc jogo.c -o jogo
./jogo 

