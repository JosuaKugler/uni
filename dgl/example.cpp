#include <iostream>
#include <vector>

double beispielmethode(std::vector<double> eingabe) {
    for (int i = 0; i < eingabe.size(); ++i) {
        std::cout << eingabe[i] << std::endl;
    }
    return eingabe[0];
}

int main() {
    std::vector<double> beispielvektor {1.5,5,12,13,14};
    double ausgabe = beispielmethode(beispielvektor);
    return 0;
}