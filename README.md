# Complexity Analyzer

O Complexity Analyzer é um projeto em C++, desenvolvido na disciplina de Estruturas de Dados Básicas II que tem como objetivo analisar empiricamente o tempo de execução de algoritmos para diferentes tamanhos de entrada, ajustando os dados coletados a funções assintóticas conhecidas — como O(n), O(log n) e O(n²) — para determinar a ordem de complexidade que melhor descreve seu comportamento.

---

## Estrutura do Projeto

```
complexity-analyzer/
├── CMakeLists.txt        # Configuração do build com CMake
├── lib/
│   └── gnuplot-iostream.h # Biblioteca auxiliar para gráficos com Gnuplot
├── src/
│   ├── main.cpp           # Ponto de entrada da aplicação
│   ├── algorithms.cpp     # Implementações dos algoritmos analisados
│   ├── data_generator.cpp # Geração de dados de entrada
│   ├── function.cpp       # Representação de funções matemáticas
│   ├── plotter.cpp        # Módulo de plotagem com Gnuplot
│   ├── utils.cpp          # Funções auxiliares
│   └── include/           # Cabeçalhos (.hpp) correspondentes
│       ├── algorithms.hpp
│       ├── data_generator.hpp
│       ├── function.hpp
│       ├── plotter.hpp
│       └── utils.hpp
```

---

## 🛠️ Compilação

Clone o repositório:

```bash
git clone https://github.com/tiago-rodrigues1/complexity-analyzer.git
cd complexity-analyzer
```
Instale as dependecias do gnuplot:
```
sudo apt-get install libboost-all-dev  (biblioteca usada pelo gnuplot)
sudo apt-get install gnuplot (biblioteca do gnuplot)

```
Após a intalação, gere o executável principal dentro da pasta `build/` e
executar programa:
```
cmake -S . -B build;
cmake –build build;
./build/analyzer

```


---

## 🧩 Funcionalidades

* ✅ Implementação de múltiplos algoritmos para estudo
* ✅ Geração automática de dados de entrada
* ✅ Comparação de complexidade empírica
* ✅ Integração com Gnuplot para visualização

---

## Autores

| [![Kézia Ketillen Santos Lima](https://avatars3.githubusercontent.com/u/88369589?s=100&v=4)](https://github.com/Kk3tillen) | [![Tiago Rodrigues dos Santos](https://avatars.githubusercontent.com/u/70401246?s=100&v=4)](https://github.com/tiago-rodrigues1) |
| :---: | :---: |
| **Kézia Ketillen Santos Lima** | **Tiago Rodrigues dos Santos** |



