#include <iostream>
#include <vector>
#include <cmath>
#include <lp_lib.h>
#include "lphelper.hpp" // Include the LPHelper class
#include <algorithm>
#include <set>
#include <sstream>
#include <string>
// uncomment to disable assert()
#define NDEBUG

#include <cassert>
// This function takes a graph as input and solves a linear programming problem using Google OR Tools.
// More details can be found here: https://developers.google.com/optimization/lp/lp_example#c++
LinearProgrammingExampleRelax(std::vector<std::vector<int>> graph)
{
// Create a solver using the SCIP backend
std::unique_ptr<MPSolver> solver(MPSolver::CreateSolver("SCIP"));

// Check if SCIP solver is available
if (!solver)
{
LOG(WARNING) << "SCIP solver unavailable.";
return;
}

// Define infinity as the solver's infinity constant
const double infinity = solver->infinity();

// Create the variable r with a lower bound of 2 and an upper bound of infinity
MPVariable* const r = solver->MakeNumVar(2.0, infinity, "r");

// Create edge variables for each edge in the graph
MPVariable* edge_var[MAX_VERTEX_COUNT][MAX_VERTEX_COUNT];
for (int i = 0; i < graph.size(); i++)
for (int j = 0; j < graph[i].size(); j++)
{
int v1 = i, v2 = graph[i][j];
if (v1 < v2)
{
std::string str = std::to_string(v1) + "-" + std::to_string(v2);
edge_var[v1][v2] = solver->MakeNumVar(-infinity, infinity, str);
edge_var[v2][v1] = edge_var[v1][v2];
}
}

// Create constraints for each vertex in the graph
for (int i = 0; i < graph.size(); i++)
{
MPConstraint* const c = solver->MakeRowConstraint(0.0, 0.0);
for (int j = 0; j < graph[i].size(); j++)
{
int v1 = i, v2 = graph[i][j];
if (v1 < v2)
c->SetCoefficient(edge_var[v1][v2], 1);
else
c->SetCoefficient(edge_var[v2][v1], -1);

// Create additional constraints for each edge in the graph
if (v1 < v2)
{
std::string str = "b" + std::to_string(v1) + "-" + std::to_string(v2);
MPVariable* b = solver->MakeNumVar(0.0, 1.0, str);

// Create four constraints for each edge in the graph
MPConstraint* const ce1 = solver->MakeRowConstraint(1.0, infinity);
ce1->SetCoefficient(edge_var[v1][v2], 1);
ce1->SetCoefficient(r, 1);

MPConstraint* const ce2 = solver->MakeRowConstraint(-infinity, -1.0);
ce2->SetCoefficient(edge_var[v1][v2], 1);
ce2->SetCoefficient(r, -1);

MPConstraint* const ce3 = solver->MakeRowConstraint(1.0, infinity);
ce3->SetCoefficient(edge_var[v1][v2], 1);
ce3->SetCoefficient(b, AV_CONSTANT);

MPConstraint* const ce4 = solver->MakeRowConstraint(1
0 - AV_CONSTANT, infinity);
ce4->SetCoefficient(edge_var[v1][v2], -1);
ce4->SetCoefficient(b, -AV_CONSTANT);
}
}
}

// Define the objective function
MPObjective* const objective = solver->MutableObjective();
objective->SetCoefficient(r, 1);
objective->SetMinimization();

// Solve the linear programming problem
const MPSolver::ResultStatus result_status = solver->Solve();

// Check that the problem has an optimal solution
if (result_status != MPSolver::OPTIMAL) {
LOG(FATAL) << "The problem does not have an optimal solution!";
}

// Print the solution values for each edge variable
for (int i = 0; i < graph.size(); i++)
for (int j = 0; j < graph[i].size(); j++)
{
int v1 = i, v2 = graph[i][j];
// if (v1 < v2)
//   LOG(INFO) << edge_var[v1][v2]->name() << "=" << edge_var[v1][v2]->solution_value();
}

// Print the objective value and solution
LOG(INFO) << "Solution:";
LOG(INFO) << "Objective value = " << objective->Value();
}