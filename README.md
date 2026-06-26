# 📜 JavaScript Program Interpreter

<p align="center">

![C](https://img.shields.io/badge/C-Language-blue.svg)
![Status](https://img.shields.io/badge/Status-Completed-success)
![License](https://img.shields.io/badge/License-MIT-green)

Projeto desenvolvido para a disciplina de **Estruturas de Dados II**, implementando um **interpretador simplificado da linguagem JavaScript**, utilizando estruturas de dados desenvolvidas manualmente em linguagem C.

</p>

---

# 📖 Sobre o Projeto

Este projeto implementa um **interpretador para uma versão simplificada da linguagem JavaScript**, permitindo a leitura, análise e execução de scripts contendo variáveis, expressões e estruturas de controle.

Todo o processamento foi desenvolvido em **linguagem C**, utilizando estruturas de dados próprias, sem o uso de bibliotecas específicas para interpretação de linguagens.

O objetivo principal foi aplicar conceitos de estruturas de dados, manipulação de memória e interpretação de código-fonte.

---

# 🚀 Funcionalidades

✅ Leitura de arquivos `.js`

✅ Análise léxica dos comandos

✅ Interpretação de expressões matemáticas

✅ Gerenciamento de variáveis em memória

✅ Execução de comandos da linguagem

✅ Suporte a estruturas de decisão

✅ Avaliação de expressões utilizando pilhas

✅ Interface em modo texto

---

# 🛠️ Tecnologias Utilizadas

* 💻 Linguagem C
* 📚 Estruturas de Dados
* 🔗 Listas Encadeadas
* 📦 Pilhas
* 🧠 Lista Genérica
* 📂 Manipulação de Arquivos
* ⚙️ Algoritmos de Parsing

---

# 📁 Estrutura do Projeto

```text
js-program-interpreter/
│
├── src/
│   ├── Interpretador.c
│   ├── meuconio.h
│   ├── tadEstruturas.h
│   ├── tadListaGen_Pilha.h
│   ├── tadPilhaExpressoesChar.h
│   ├── tadPilhaExpressoesFloat.h
│   ├── tadPilhaVariaveis.h
│   └── TesteTadEstruturas.c
│
├── examples/
│   ├── exemplo1.js
│   ├── exemplo2.js
│   ├── ...
│   ├── exemplo9.js
│   └── teste.js
│
├── docs/
│   └── Estruturas Usadas.docx
│
├── README.md
├── .gitignore
└── LICENSE
```

---

# ⚙️ Como Funciona

O interpretador executa as seguintes etapas:

1. 📄 Lê o arquivo JavaScript.
2. 🔍 Analisa os comandos encontrados.
3. 🧠 Armazena variáveis em memória.
4. 📦 Utiliza pilhas para avaliar expressões.
5. ⚙️ Executa os comandos seguindo a lógica do programa.
6. 🖥️ Exibe o resultado da execução.

---

# 🧠 Conceitos Aplicados

Durante o desenvolvimento foram utilizados conceitos importantes da Ciência da Computação:

* Estruturas de Dados
* Pilhas
* Listas Encadeadas
* Lista Genérica
* Manipulação Dinâmica de Memória
* Parsing
* Interpretação de Linguagens
* Manipulação de Arquivos
* Expressões Matemáticas
* Organização Modular em C

---

# 📈 Complexidade

O projeto envolve diversos algoritmos fundamentais utilizados em interpretadores, incluindo:

| Operação                | Complexidade |
| ----------------------- | ------------ |
| Leitura do código       | O(n)         |
| Análise dos tokens      | O(n)         |
| Avaliação de expressões | O(n)         |
| Busca de variáveis      | O(n)         |

> *A complexidade pode variar conforme a quantidade de variáveis e comandos presentes no script.*

---

# 🎯 Objetivos de Aprendizado

Este projeto teve como objetivo desenvolver conhecimentos em:

* Implementação de interpretadores
* Estruturas de Dados
* Manipulação de memória
* Organização modular em C
* Processamento de arquivos
* Resolução de problemas utilizando algoritmos

---

# 👨‍💻 Autor

Desenvolvido por **Gustavo Imada**.

Caso tenha sugestões ou queira conversar sobre o projeto, fique à vontade para abrir uma Issue ou entrar em contato.

---

⭐ Se este projeto foi útil ou interessante, considere deixar uma estrela no repositório!
