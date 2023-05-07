//
// Created by havr on 21.4.2023.
//

#ifndef DU_UDML_2_LPHELPER_H
#define DU_UDML_2_LPHELPER_H

#endif //DU_UDML_2_LPHELPER_H
#ifndef LPHELPER_HPP
#define LPHELPER_HPP

//To make this compile you need to add the path to this file into include paths
//For me its -I /usr/include/lpsolve/
//To link you must add the path to lpsolve library + the library itself, for me it is
//-L /usr/lib/lp_solve -Wl,-rpath,/usr/lib/lp_solve -llpsolve55
#include <lp_lib.h>

#include <vector>
#include <string>
#include <exception>

class LPHelper {
    std::vector<std::string> vns;
    lprec *lp;
public:
    //LPHelper class performs the checks and throws this exception when something is wrong.
    class LPHelperException : public std::exception {
        std::string i;
    public:
        LPHelperException(std::string info): i(info) {}
        const char * what() const noexcept {return i.c_str();}
    };

    //I write this so you do not need to manage memory && make life simpler in general.
    //The variables are assigned a number according to thir orded in the vector
    //!!!Variables are indexed starting from one, so variable_names[0] is the name of variable 1.
    //See http://lpsolve.sourceforge.net/5.5/formulate.htm#C/C++ for example
    LPHelper(std::vector<std::string> variable_names): vns(variable_names) {
        lp = make_lp(0, vns.size());
        if (lp == NULL) throw LPHelperException("make_lp failed.");
        for(int i=0; i<vns.size(); i++)
            if (set_col_name(lp, i+1, const_cast<char*>(vns[i].c_str())) == FALSE)
                throw LPHelperException("set_col_name failed.");
    }
    ~LPHelper() {delete_lp(lp);}

    //no copying
    LPHelper(const LPHelper &) = delete;
    LPHelper& operator=(const LPHelper &) = delete;


    //Sets that the variable is binary, value is TRUE or FALSE
    //remember, indexed from 1
    void set_binary(int variable_no, unsigned char value) {
        if (::set_binary(lp, variable_no, value) == FALSE)
            throw LPHelperException("set_binary failed.");
    }

    //Sets that the variable is integral, value is TRUE or FALSE
    //remember, indexed from 1
    void set_int(int variable_no, unsigned char value) {
        if (::set_int(lp, variable_no, value) == FALSE)
            throw LPHelperException("set_int failed.");
    }


    //should be set to true while adding constraints, false otherwise
    void set_add_rowmode(unsigned char mode) {
        if (::set_add_rowmode(lp, mode) == FALSE)
            throw LPHelperException("set_add_rowmode failed.");
    }

    //Adds a constraint; row_variables and row_coeficients have to have the same length
    void add_constraint(std::vector<REAL> row_coeficients, std::vector<int> row_variables, int OP, REAL other_side) {
        if (add_constraintex(lp, row_coeficients.size(), row_coeficients.data(),
                             row_variables.data(), OP, other_side) == FALSE)
            throw LPHelperException("add_constraintex failed.");
    }

    //Adds the objecitve function; row_variables and row_coeficients have to have the same length
    void set_obj_fn(std::vector<REAL> row_coeficients, std::vector<int> row_variables) {
        if (set_obj_fnex(lp, row_coeficients.size(), row_coeficients.data(),
                         row_variables.data()) == FALSE)
            throw LPHelperException("set_obj_fn failed.");
    }

    //Maximize
    void set_maxim() {
        ::set_maxim(lp);
    }

    //Minimize
    void set_minim() {
        ::set_minim(lp);
    }

    //always writes to stdout
    void write() {
        if (write_LP(lp, stdout) == FALSE)
            throw LPHelperException("write_LP failed.");
    }

    //see http://lpsolve.sourceforge.net/5.5/set_verbose.htm
    void set_verbose(int verbose) {
        ::set_verbose(lp, verbose);
    }

    //see http://lpsolve.sourceforge.net/5.5/solve.htm
    int solve() {
        return ::solve(lp);
    }

    REAL get_objective() {
        return ::get_objective(lp);
    }


    std::vector<REAL> get_solution() {
        std::vector<REAL> res(vns.size());
        if (get_variables(lp, res.data()) == FALSE)
            throw LPHelperException("get_variables failed.");
        return res;
    }

    std::vector<std::string> get_variable_names() {
        std::vector<std::string> res(vns.size());
        for(int i=0; i<vns.size(); i++)
            res[i] = get_col_name(lp, i+1);
        return res;
    }


    //You can do much more, see. I expose the pointer so you can do whatever you want
    //http://lpsolve.sourceforge.net/5.5/lp_solveAPIreference.htm
    lprec *get() {return lp;}
};

#endif
