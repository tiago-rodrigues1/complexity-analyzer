#include "data_generator.hpp"
#include <algorithm> // para std::sort

int main() {
    data_generator dg(20000);

    dg.run_data_generator([](std::vector<int>& v) {
        std::sort(v.begin(), v.end());
    });

    dg.export_to_csv("resultados.csv");
    return 0;
}