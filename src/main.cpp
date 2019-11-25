#include <iostream>
#include "jitu-vai/wpsl.h"
#include <random>

using namespace std;

class Index{
    double x_{}, y_{};
public:
    Index(double x, double y):x_{x}, y_{y}{}
    friend std::ostream& operator<<(ostream& os, const Index& index){
        return os << "(" << index.x_ << "," << index.y_ << ")";
    }
    double getX() const {return x_;}
    double getY() const {return y_;}
};

class WPSL{
    std::vector<Index> index_lower_left;
    std::vector<Index> index_upper_right;
    std::vector<unsigned> _node_label;
    std::vector<double > _area;
//    const string symbol = " _< ^> ";
    const string symbol = " to ";

    std::mt19937 random_engine; // Mersenne Twister 19937 generator (class )
//    std::mt19937_64 random_engine_64; // Mersene Twister 19937 generator (64 bit) (class )
    size_t random_state{};
private:
    double getArea(size_t label);
    Index randomIndex(const Index &ll, const Index &ur);

    size_t chooseIndexRandomly();

    void add_point_v1();
    void add_point_v2();
public:
    WPSL();

    virtual ~WPSL() = default;

    virtual void reset(){
        index_lower_left.clear();
        index_upper_right.clear();
        _node_label.clear();
        _area.clear();
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
    void totalArea();

    size_t chooseIndexPreferentially(); // to be declared private
    void addNeighbor(const Index &ll, const Index &ur);
};

/**
 * Construct a network while constructing WPSL
 */
class WPSL_Network : public WPSL{
    vector<int> networkMapA;
    vector<int> networkMapB;

public:
    ~WPSL_Network() override = default;
    WPSL_Network();
    void reset() override;

    void addNode();

};

WPSL_Network::WPSL_Network():WPSL() {

}

void WPSL_Network::reset() {
    WPSL::reset();
    networkMapA.clear();
    networkMapB.clear();
}

void WPSL_Network::addNode() {

}

WPSL::WPSL() {
    index_lower_left.emplace_back(Index(0, 0));
    index_upper_right.emplace_back(Index(1, 1));
    _node_label.emplace_back(0);
    _area.emplace_back(getArea(0));
}

void WPSL::viewIndex() {
    cout << _node_label.size() << " elements" << endl;
    cout << "[label] => {(lower left)" << symbol << "(upper right)}, A=$Area" << endl;
    for(size_t i{}; i < _node_label.size(); ++i){
        cout << "[" << _node_label[i] << "] => " << "{"
             << index_lower_left[i] << symbol
             << index_upper_right[i] << "}  A="
             << _area[i]
             << endl;
    }
}

/**
 * Add new point to the lattice
 */
void WPSL::addPoint() {
//    add_point_v1();
    add_point_v2();

}

/**
 * Lower Left and Upper Right index is provided
 * @param ll
 * @param ur
 */
void WPSL::addNeighbor(const Index &ll, const Index &ur) {
    index_lower_left.emplace_back(ll);
    index_upper_right.emplace_back(ur);
    _area.emplace_back(getArea(_node_label.size()));
    _node_label.emplace_back(_node_label.size());
}

double WPSL::getArea(size_t label) {
    Index ll = index_lower_left[label];
    Index ur = index_upper_right[label];
    double a = ll.getX() - ur.getX();
    double b = ll.getY() - ur.getY();
    return abs(a*b);
}

// give
/**
 * give a random Index inside a rectangle bounded by `ll` and `ur`
 * @param ll  : lower left index
 * @param ur  : upper right index
 * @return    : random Index inside a rectangle bounded by `ll` and `ur`
 */
Index WPSL::randomIndex(const Index &ll, const Index &ur) {
    uniform_real_distribution<double> dist1(ll.getX(), ur.getX());
    uniform_real_distribution<double> dist2(ll.getY(), ur.getY());
    double new_x = dist1(random_engine);
    double new_y = dist2(random_engine);
    return {new_x, new_y};
}

/**
 * preferentially select a box according to their area to divide it into four parts
 * @return
 */
size_t WPSL::chooseIndexPreferentially() {
    std::discrete_distribution<size_t> dist(_area.begin(), _area.end());

//    cout << "{";
//    for(auto a: dist.probabilities()){
//        cout << a << ", ";
//    }
//    cout << "}" << endl << "{";
//    vector<size_t> frequency(_area.size());
//    size_t limit  = 10000;
//    for(size_t i{}; i < limit; ++i) {
//        auto r = dist(random_engine);
//        cout << r << ",";
//        ++frequency[r];
//    }
//    cout << "}" << endl << "frequency {" << endl;
//    for(size_t i{}; i < frequency.size(); ++i) {
//        cout << frequency[i] << ",";
//        cout << frequency[i] / double(limit) << endl;
//    }
//    cout << "}" << endl;

    return dist(random_engine);
}

void WPSL::totalArea() {
    double total{};
    for(auto a: _area){
        total += a;
    }
    cout << "total area A= " << total << endl;
}

size_t WPSL::chooseIndexRandomly() {
    return random_engine() % _node_label.size();
}

void WPSL::add_point_v1() {
// randomly select a box and divide it into four parts
    size_t r = chooseIndexRandomly();
//    size_t r = chooseIndexPreferentially();

    size_t i = _node_label[r];
    Index ll = index_lower_left[i];
    Index ur = index_upper_right[i];

    auto n = randomIndex(ll, ur); // randomly selected new index in the box bounded by ll and ur

    // index is reused for new lower left box
    index_lower_left[i] = ll; // reuse space
    index_upper_right[i] = n; // reuse space
    _area[i] = getArea(i);

    // lower right
    index_lower_left.emplace_back(Index(n.getX(), ll.getY()));
    index_upper_right.emplace_back(Index(ur.getX(), n.getY()));
    _area.emplace_back(getArea(_node_label.size()));
    _node_label.emplace_back(_node_label.size());

    // upper right
    index_lower_left.emplace_back(n);
    index_upper_right.emplace_back(ur);
    _area.emplace_back(getArea(_node_label.size()));
    _node_label.emplace_back(_node_label.size());

    // upper left
    index_lower_left.emplace_back(Index(ll.getX(), n.getY()));
    index_upper_right.emplace_back(Index(n.getX(), ur.getY()));
    _area.emplace_back(getArea(_node_label.size()));
    _node_label.emplace_back(_node_label.size());
}

void WPSL::add_point_v2() {
// randomly select a box and divide it into four parts
    size_t r = chooseIndexRandomly();
//    size_t r = chooseIndexPreferentially();

    size_t i = _node_label[r];
    Index ll = index_lower_left[i];
    Index ur = index_upper_right[i];

    auto n = randomIndex(ll, ur); // randomly selected new index in the box bounded by ll and ur

    // index is reused for new lower left box
    index_lower_left[i] = ll; // reuse space
    index_upper_right[i] = n; // reuse space
    _area[i] = getArea(i);

    // lower right
    addNeighbor(Index(n.getX(), ll.getY()), Index(ur.getX(), n.getY()));
    // upper right
    addNeighbor(n, ur);
    // upper left
    addNeighbor(Index(ll.getX(), n.getY()), Index(n.getX(), ur.getY()));
}

void test_class(){
    WPSL wpsl;
    wpsl.viewIndex();

    wpsl.addPoint();
    wpsl.viewIndex();
    wpsl.totalArea();

    wpsl.addPoint();
    wpsl.viewIndex();
    wpsl.totalArea();

    wpsl.chooseIndexPreferentially();
}

int main(int argc, char* argv[]) {
    std::cout << "Hello, World!" << std::endl;
//    srand(time(NULL));

//    main_jitu();

//    main_jitu_test();

    test_class();


    return 0;
}