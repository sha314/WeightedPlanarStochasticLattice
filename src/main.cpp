#include <iostream>
#include "wpsl.h"
#include <random>

using namespace std;

class Index{
    double x_{}, y_{};
public:
    Index(double x, double y):x_{x}, y_{y}{}
    friend std::ostream& operator<<(ostream& os, const Index& index){
        return os << "(" << index.x_ << "," << index.y_ << ")";
    }
};

class WPSL{
    std::vector<Index> index_lower_left;
    std::vector<Index> index_upper_right;
    std::vector<unsigned> _label;
//    const string symbol = " _< ^> ";
    const string symbol = " to ";

    std::mt19937 random_engine; // Mersenne Twister 19937 generator (class )
//    std::mt19937_64 random_engine_64; // Mersene Twister 19937 generator (64 bit) (class )
    size_t random_state{};
public:
    WPSL();
    ~WPSL() = default;

    void reset(){
        index_lower_left.clear();
        index_upper_right.clear();
        _label.clear();
    }

    void setRandomState(size_t rs, bool a){
        random_state = rs;
        if(a) {
            std::random_device r;
            random_state = r();
        }
        random_engine.seed(random_state);
    }
    void viewIndex();
    void addPoint();
};


WPSL::WPSL() {
    index_lower_left.emplace_back(Index(0, 0));
    index_upper_right.emplace_back(Index(1, 1));
    _label.emplace_back(0);
}

void WPSL::viewIndex() {
    cout << _label.size() << " elements" << endl;
    cout << "[label] => {(lower left)" << symbol << "(upper right)}" << endl;
    for(size_t i{}; i < _label.size(); ++i){
        cout << "[" << _label[i] << "] => " << "{"
             << index_lower_left[i] << symbol
             << index_upper_right[i] << "}" << endl;
    }
}

/**
 * Add new point to the lattice
 */
void WPSL::addPoint() {
    // randomly select a box and divide it into four parts
    size_t r = random_engine() % _label.size();
    size_t i = _label[i];


    // todo preferentially select a box and divide it into four parts
}

void test_class(){
    WPSL wpsl;
    wpsl.viewIndex();
}

int main(int argc, char* argv[]) {
    std::cout << "Hello, World!" << std::endl;
//    srand(time(NULL));

//    main_jitu();

//    main_jitu_test();

    test_class();


    return 0;
}