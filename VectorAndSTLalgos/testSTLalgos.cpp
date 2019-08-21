#include <algorithm>
#include <vector>
#include <iterator>
#include <iostream>
#include <numeric>

void printVector(const std::vector<int>& vec) {
    std::for_each(vec.begin(), vec.end(),
     [](int const& v){ std::cout << v << " " << std::endl;});
}


int main() {
    std::vector<int> prviVektor;

    std::generate_n(std::back_inserter(prviVektor), 20, [n = 0] () mutable { n = n+5; return n; });
    printVector(prviVektor);
    std::cout<<std::endl<<std::endl;

    std::transform(prviVektor.begin(), prviVektor.end(), prviVektor.begin(),  [](auto c) { return c*c; });

    std::vector<int> drugiVektor;

    std::copy_if(prviVektor.begin(), prviVektor.end(), std::back_inserter(drugiVektor),
    [] (const int& v) { return v % 7 ? v : 0;});
    printVector(drugiVektor);
    std::cout<<std::endl<<std::endl;


    double reciprocnaSuma = std::accumulate(drugiVektor.begin(), drugiVektor.end(), 0.0,
     [](auto x, auto v){ return x + 1.0/v;});
    std::cout << "Suma reciprocnih vrednosti drugog vektora je " << reciprocnaSuma << std::endl;

    drugiVektor.erase(std::remove_if(drugiVektor.begin(), drugiVektor.end(),
    [] (const int& v) { return v % 9 ? 0 : v;}), drugiVektor.end());
    printVector(drugiVektor);
    std::cout<<std::endl<<std::endl;

    auto cc = std::find_if(drugiVektor.begin(), drugiVektor.end(), [] (auto v) { return v % 13 == 0;});
    std::cout << (cc == drugiVektor.end() ? -1 : cc - drugiVektor.begin()) << std::endl;

}
