# Complexity Analyzer

Um projeto em **C++** para **análise de complexidade de algoritmos**, incluindo geração de dados, execução de testes e visualização gráfica com **Gnuplot**.
O objetivo é facilitar o estudo e a comparação entre diferentes algoritmos por meio de simulações práticas e gráficos intuitivos.

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
git clone [https://github.com/seu-usuario/complexity-analyzer.git](https://github.com/tiago-rodrigues1/complexity-analyzer.git)
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
