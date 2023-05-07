#include <iostream>
#include <vector>
#include "lphelper.hpp"

int main() {
    constexpr int variables = 2;

    //create lp instance
    LPHelper lp{{"x", "y"}};

    //add rows
    lp.set_add_rowmode(TRUE);
    lp.add_constraint({120, 210}, {1, 2}, LE, 15000);
    lp.add_constraint({110, 30}, {1, 2}, LE, 4000);
    lp.add_constraint({1, 1}, {1, 2}, LE, 75);
    lp.set_add_rowmode(FALSE);

    //We set x is integer
    lp.set_int(1, TRUE);

    //define objective
    lp.set_obj_fn({143, 60}, {1, 2});
    lp.set_maxim();

    //you may use this for debugging
    lp.write();

    //shows important messages while solving
    lp.set_verbose(IMPORTANT);

     //time to solve
     int res = lp.solve();
     if (res != OPTIMAL) {std::cerr<<"No optimal solution found.\n";}


    //print results
    std::cout << "Objective value: " << lp.get_objective() << "\n";
    auto vals = lp.get_solution();
    auto vars = lp.get_variable_names();
    for(int i=0; i<vals.size(); i++) {
        std::cout<<vars[i]<<" : "<<vals[i]<<"\n";
    }


    return 0;
}
