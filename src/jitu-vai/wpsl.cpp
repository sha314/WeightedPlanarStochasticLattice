//
// Created by shahnoor on 11/24/19.
//
/******
 * Originally Written by
 * Zahidul Islam Jitu vai
 */
#include "wpsl.h"
#include "../view.h"


using namespace std;
void remove_neighbor(vector<vector<int> > &neighbor, int i, int j) {
    int index = -1;
    for (int k = 0; k < neighbor[i].size(); k++) {
        if (neighbor[i][k] == j) {
            index = k;
        }
    }
    if (index != -1) {
        neighbor[i].erase(neighbor[i].begin() + index);
        index = -1;
        for (int k = 0; k < neighbor[j].size(); k++) {
            if (neighbor[j][k] == i) {
                index = k;
            }
        }
        if (index != -1) {
            neighbor[j].erase(neighbor[j].begin() + index);
        }

    }
}

void add_neigbor(vector<vector<int> > &neighbor, int i, int j) {
    bool found = false;
    for (int k = 0; k < neighbor[i].size(); k++) {
        if(neighbor[i][k] == j) {
            found = true;
        }
    }
    if (!found && i!=j) {
        neighbor[i].push_back(j);
        neighbor[j].push_back(i);
        //cout << "pushing " << i << " and " << j << endl;
    }
}

//this evaluates whether x<z<y
bool is_it_between(double x, double y, double z) {
    bool result = false;
    if (x < z && z < y) {
        result= true;
    }

    return result;
}

bool is_neighbor(vector<vector<double> > x_lim, vector<vector<double> > y_lim, int site1, int site2) {
    bool result = false;
    bool x_same = false;
    bool y_same = false;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (x_lim[site1][i] == x_lim[site2][j]) {
                x_same = true;
            }
            if (y_lim[site1][i] == y_lim[site2][j]) {
                y_same = true;
            }
        }
    }
    if ((x_lim[site1][0] == 0.0 && x_lim[site2][1] == 1.0) || (x_lim[site1][1] == 1.0 && x_lim[site2][0] == 0.0)) {
        x_same = true;
    }
    if ((y_lim[site1][0] == 0.0 && y_lim[site2][1] == 1.0) || (y_lim[site1][1] == 1.0 && y_lim[site2][0] == 0.0)) {
        y_same = true;
    }
    if (y_same) {
        if (is_it_between(x_lim[site1][0], x_lim[site1][1], x_lim[site2][0]) || is_it_between(x_lim[site1][0], x_lim[site1][1], x_lim[site2][1])) {
            return true;
        }
        if (is_it_between(x_lim[site2][0], x_lim[site2][1], x_lim[site1][0]) || is_it_between(x_lim[site2][0], x_lim[site2][1], x_lim[site1][1])) {
            return true;
        }
        if (x_lim[site1][0] == x_lim[site2][0] && x_lim[site1][1] == x_lim[site2][1] && site1 != site2) {
            return true;
        }
    }
    if (x_same) {
        if (is_it_between(y_lim[site1][0], y_lim[site1][1], y_lim[site2][0]) || is_it_between(y_lim[site1][0], y_lim[site1][1], y_lim[site2][1])) {
            return true;
        }
        if (is_it_between(y_lim[site2][0], y_lim[site2][1], y_lim[site1][0]) || is_it_between(y_lim[site2][0], y_lim[site2][1], y_lim[site1][1])) {
            return true;
        }
        if (y_lim[site1][0] == y_lim[site2][0] && y_lim[site1][1] == y_lim[site2][1] && site1 != site2) {
            return true;
        }
    }
    return result;
}

void generate_new_site(
        vector<vector<int> > &neighbor,
        vector<vector<double> > &x_lim,
        vector<vector<double> > &y_lim,
        int site, double x_new, double y_new)
{
    vector<int> temp_neighbor_list;
    vector<int> empty;
    vector<double> empty_double;
    temp_neighbor_list.push_back(site);
    int size_neighbor = neighbor.size();
    for (int i = 0; i < 3; i++) {
        neighbor.push_back(empty);
        x_lim.push_back(empty_double);
        y_lim.push_back(empty_double);
        int site_new = size_neighbor + i;
        temp_neighbor_list.push_back(site_new);
    }
    for (int i = 0; i < neighbor[site].size(); i++) {
        temp_neighbor_list.push_back(neighbor[site][i]);
    }

    /*
    for (int i = 0; i < temp_neighbor_list.size(); i++) {
        cout << temp_neighbor_list[i] << endl;
    }
    */

    double x1 = x_lim[site][0];
    double x2 = x_lim[site][1];
    double y1 = y_lim[site][0];
    double y2 = y_lim[site][1];

    int site2 = size_neighbor;
    int site3 = site2 + 2;
    int site4 = site2 + 1;

    x_lim[site][0] = x1;
    x_lim[site2].push_back(x_new);
    x_lim[site3].push_back(x1);
    x_lim[site4].push_back(x_new);

    x_lim[site][1] = x_new;
    x_lim[site2].push_back(x2);
    x_lim[site3].push_back(x_new);
    x_lim[site4].push_back(x2);

    y_lim[site][0] = y1;
    y_lim[site2].push_back(y1);
    y_lim[site3].push_back(y_new);
    y_lim[site4].push_back(y_new);

    y_lim[site][1] = y_new;
    y_lim[site2].push_back(y_new);
    y_lim[site3].push_back(y2);
    y_lim[site4].push_back(y2);



    for (int i = 0; i < temp_neighbor_list.size(); i++) {
        for (int j = i + 1; j < temp_neighbor_list.size(); j++) {
            //cout << "is " << temp_neighbor_list[i] << " and " << temp_neighbor_list[j] << " neighbor??" << endl;
            if (is_neighbor(x_lim, y_lim, temp_neighbor_list[i], temp_neighbor_list[j])) {
                add_neigbor(neighbor, temp_neighbor_list[i], temp_neighbor_list[j]);
                //cout << "yes, adding them!" << endl;
            }
            else {
                remove_neighbor(neighbor, temp_neighbor_list[i], temp_neighbor_list[j]);
                //cout << "no, removing them!" << endl;
            }
        }
    }
}

int find_site(vector<vector<double> > x_lim, vector<vector<double> > y_lim, double x_new, double y_new) {
    int result = -1;
    for (int i = 0; i < x_lim.size(); i++) {
        if (is_it_between(x_lim[i][0], x_lim[i][1], x_new)) {
            if (is_it_between(y_lim[i][0], y_lim[i][1], y_new)) {
                result = i;
            }
        }
    }
    return result;
}

//Another testing function
double my_rand() {
    return (double)rand() / RAND_MAX;
}


void neighbor_init(vector<vector<int> > &neighbor, vector<vector<double> > &x_lim, vector<vector<double> > &y_lim) {
    double x_new, y_new;
    int site;
    for (int t = 0; t < 1000; t++) {
        x_new = my_rand();
        y_new = my_rand();
        site = find_site(x_lim, y_lim, x_new, y_new);
        if (site != -1) {
            generate_new_site(neighbor, x_lim, y_lim, site, x_new, y_new);
        }
        cout << "generated series: " << t << endl;
    }
}

//this is a testing function
void test_neighbor_init(vector<vector<int> > &neighbor) {
    vector<int> empty;

    for (int i = 0; i < 4; i++) {
        neighbor.push_back(empty);
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            add_neigbor(neighbor, i, j);
        }
    }
    remove_neighbor(neighbor, 0, 3);
    remove_neighbor(neighbor, 1, 2);
    remove_neighbor(neighbor, 1, 2);
}

//testing parameter starts here

double x_cube(vector<vector<double> > x_lim) {
    double result = 0.0;
    double length = 0.0;
    for (int i = 0; i < x_lim.size(); i++) {
        length = x_lim[i][1] - x_lim[i][0];
        result += pow(length, 3.0);
    }
    return result;
}

double moments(vector<vector<double> > x_lim, vector<vector<double> > y_lim, double n) {
    double result = 0.0;
    double length = 0.0;
    double width = 0.0;
    double width_power = 0.0;
    for (int i = 0; i < x_lim.size(); i++) {
        length = x_lim[i][1] - x_lim[i][0];
        width = y_lim[i][1] - y_lim[i][0];
        width_power = (4.0 / n) - 1.0;
        result += pow(length, n-1)*pow(width,width_power);
    }
    return result;
}

//this function is for testing purpose
//delete it if you plan to use it as module
int main_jitu() {
    srand(time(NULL));

    string filename1 = "res/x_cube-vs-t.data";
    ofstream write1(filename1.c_str());

    string filename2 = "res/moments_n_3-vs-t.data";
    ofstream write2(filename2.c_str());

    string filename3 = "res/moments_n_4-vs-t.data";
    ofstream write3(filename3.c_str());

    string filename4 = "res/moments_n_5-vs-t.data";
    ofstream write4(filename4.c_str());

    vector<vector<int> > neighbor;
    vector<vector<double> > x_lim;
    vector<vector<double> > y_lim;
    //test_neighbor_init(neighbor);
    vector<int> empty;
    vector<double> empty_double;

    neighbor.push_back(empty);
    neighbor[0].push_back(0);

    x_lim.push_back(empty_double);
    x_lim[0].push_back(0.0);
    x_lim[0].push_back(1.0);

    y_lim.push_back(empty_double);
    y_lim[0].push_back(0.0);
    y_lim[0].push_back(1.0);
    /*
    double x_new = 0.6;
    double y_new = 0.45;


    generate_new_site(neighbor, x_lim, y_lim, 0, x_new, y_new);
    cout << "******new*******" << endl;
    cout << "(0.3,0.37) is in the site: " << find_site(x_lim, y_lim, 0.3, 0.37) << endl;
    generate_new_site(neighbor, x_lim, y_lim, 0, 0.3, 0.37);
    cout << "******new*******" << endl;
    cout << "(0.8,0.1) is in the site: " << find_site(x_lim, y_lim, 0.8, 0.1) << endl;
    generate_new_site(neighbor, x_lim, y_lim, 1, 0.8, 0.1);

    cout << "(0.8,0.1) is in the site: " << find_site(x_lim, y_lim, 0.8, 0.1) << endl;

    */

    double x_new, y_new;
    int site;
    double length_cube = 0.0;
    double moment_3 = 0.0;
    double moment_4 = 0.0;
    double moment_5 = 0.0;
    int no_site = 0;
    for (int t = 1; t < 100000; t++) {
        x_new = my_rand();
        y_new = my_rand();
        site = find_site(x_lim, y_lim, x_new, y_new);
        if (site != -1) {
            generate_new_site(neighbor, x_lim, y_lim, site, x_new, y_new);
            if (t % 50 == 0 && t>1000) {
                no_site = 3 * t + 1;
                length_cube = x_cube(x_lim);
                moment_3 = moments(x_lim, y_lim, 3.0);
                moment_4 = moments(x_lim, y_lim, 4.0);
                moment_5 = moments(x_lim, y_lim, 5.0);

                // writing at each iteration makes program run very slower // by shahnoor
                write1 << no_site << "  " << length_cube << endl;
                write2 << no_site << "  " << moment_3 << endl;
                write3 << no_site << "  " << moment_4 << endl;
                write4 << no_site << "  " << moment_5 << endl;
            }
        }
        cout << "generated series: " << t << endl;
    }

    /*
    for (int i = 0; i < neighbor.size(); i++) {
        cout << "neighbor of " << i << " is: ";
        for (int j = 0; j < neighbor[i].size(); j++) {
            cout << neighbor[i][j] << "   ";
        }
        cout << endl;
    }
    */
    return 0;
}


//this function is for testing purpose
//delete it if you plan to use it as module
void main_jitu_test() {


    string filename1 = "res/x_cube-vs-t.data";
    ofstream write1(filename1.c_str());

    string filename2 = "res/moments_n_3-vs-t.data";
    ofstream write2(filename2.c_str());

    string filename3 = "res/moments_n_4-vs-t.data";
    ofstream write3(filename3.c_str());

    string filename4 = "res/moments_n_5-vs-t.data";
    ofstream write4(filename4.c_str());

    vector<vector<int> > neighbor;
    vector<vector<double>> x_lim;
    vector<vector<double>> y_lim;
    //test_neighbor_init(neighbor);
    vector<int> empty;
    vector<double> empty_double;

    neighbor.push_back(empty);
    neighbor[0].push_back(0);

    x_lim.push_back(empty_double);
    x_lim[0].push_back(0.0);
    x_lim[0].push_back(1.0);

    y_lim.push_back(empty_double);
    y_lim[0].push_back(0.0);
    y_lim[0].push_back(1.0);

    cout << "neighbor" << endl;
    print(neighbor);
    cout << "x_lim" << endl;
    print(x_lim);
    cout << "y_lim" << endl;
    print(y_lim);
    print_coordinate(x_lim, y_lim);

    /*
    double x_new = 0.6;
    double y_new = 0.45;


    generate_new_site(neighbor, x_lim, y_lim, 0, x_new, y_new);
    cout << "******new*******" << endl;
    cout << "(0.3,0.37) is in the site: " << find_site(x_lim, y_lim, 0.3, 0.37) << endl;
    generate_new_site(neighbor, x_lim, y_lim, 0, 0.3, 0.37);
    cout << "******new*******" << endl;
    cout << "(0.8,0.1) is in the site: " << find_site(x_lim, y_lim, 0.8, 0.1) << endl;
    generate_new_site(neighbor, x_lim, y_lim, 1, 0.8, 0.1);

    cout << "(0.8,0.1) is in the site: " << find_site(x_lim, y_lim, 0.8, 0.1) << endl;

    */

    double x_new, y_new;
    int site;
    double length_cube = 0.0;
    double moment_3 = 0.0;
    double moment_4 = 0.0;
    double moment_5 = 0.0;
    int no_site = 0;
    int limit = 10;
    for (int t = 1; t < limit; t++) {
        cout << "**********  t = " << t << endl;
        x_new = my_rand();
        y_new = my_rand();
        site = find_site(x_lim, y_lim, x_new, y_new);
        if (site != -1) {
            generate_new_site(neighbor, x_lim, y_lim, site, x_new, y_new);
            cout << "neighbor" << endl;
            print(neighbor);
            cout << "x_lim" << endl;
            print(x_lim);
            cout << "y_lim" << endl;
            print(y_lim);
            print_coordinate(x_lim, y_lim);

//            if (t % 50 == 0 && t>1000) {
//                no_site = 3 * t + 1;
//                length_cube = x_cube(x_lim);
//                moment_3 = moments(x_lim, y_lim, 3.0);
//                moment_4 = moments(x_lim, y_lim, 4.0);
//                moment_5 = moments(x_lim, y_lim, 5.0);
//
//                // writing at each iteration makes program run very slower // by shahnoor
//                cout << no_site << "  " << length_cube << endl;
//                cout << no_site << "  " << moment_3 << endl;
//                cout << no_site << "  " << moment_4 << endl;
//                cout << no_site << "  " << moment_5 << endl;
//            }
        }
        cout << "generated series: " << t << endl;
    }

    /*
    for (int i = 0; i < neighbor.size(); i++) {
        cout << "neighbor of " << i << " is: ";
        for (int j = 0; j < neighbor[i].size(); j++) {
            cout << neighbor[i][j] << "   ";
        }
        cout << endl;
    }
    */

}
