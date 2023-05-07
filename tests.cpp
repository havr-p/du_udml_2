#include "nowhere_zero_flows.cpp"
#include <vector>
#include <iostream>
#include <chrono>

void test(std::vector<std::vector<int>> graph, std::string name, double expected1,
			double expected2) {
	auto t1 = std::chrono::high_resolution_clock::now();
	double result = rflow(graph);
	auto t2 = std::chrono::high_resolution_clock::now();
	std::cout << name << "\n              rflow: ";
	// malo to nejake problemy so zaokruhlovanim preto == z wishu
	if (result < expected1 + 0.001 && result > expected1 - 0.001) {
		std::cout << "PASSED in " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << "ms" << std::endl;
	}
	else {
		std::cout << "expected " << expected1 << ", got " << result << std::endl;
	}
	if (expected2 != -1) {
		t1 = std::chrono::high_resolution_clock::now();
		result = r2chebyshevflow(graph);
		t2 = std::chrono::high_resolution_clock::now();
		std::cout << "    r2chebyshevflow: ";
		if (result < expected2 + 0.001 && result > expected2 - 0.001) {
			std::cout << "PASSED in " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << "ms" << std::endl;
		}
		else {
			std::cout << "expected " << expected2 << ", got " << result << std::endl;
		}
	}
	std::cout << std::endl;
}

int main() {
	std::vector<std::vector<int>> simple_multigraph = {
		{1,1}, {0, 0}
	};
	std::vector<std::vector<int>> simple_multigraph2 = {
		{1, 1, 1}, {0, 0, 0}
	};
	std::vector<std::vector<int>> simple_graph = {
		{1, 2}, {0, 2}, {0, 1}
	};
	std::vector<std::vector<int>> simple_graph2 = {
		{1, 3, 4}, {0, 2, 4}, {1, 3, 5}, {0, 2, 5}, {0, 1, 5}, {2, 3, 4}
	};
	std::vector<std::vector<int>> k23 = {
		{1,1,1}, {0,0,0}
	};
	std::vector<std::vector<int>> k33 = {
		{3, 4, 5}, {3, 4, 5}, {3, 4, 5}, {0, 1, 2}, {0, 1, 2}, {0, 1, 2}
	};
	std::vector<std::vector<int>> prism_graph = {
		{1, 2, 3}, {0, 2, 4}, {0, 1, 5}, {0, 4, 5}, {1, 3, 5}, {2, 3, 4}
	};
	std::vector<std::vector<int>> petersen_graph = {
		{1, 4, 5}, {0, 2, 6}, {1, 3, 7}, {2, 4, 8}, {0, 3, 9},
		{0, 7, 8}, {1, 8, 9}, {2, 5, 9}, {3, 5, 6}, {4, 6, 7}
	};
	std::vector<std::vector<int>> flower_snark2 = {
		{2,1,1}, {0,3,0}, {0,4,6}, {1,5,7}, {2,7,7},
		{6,6,3}, {2,5,5}, {4,3,4}
	};
	std::vector<std::vector<int>> flower_snark3 = {
		{1, 2, 10}, {0, 3, 11}, {0, 4, 6}, {1, 5, 7}, {2, 5, 11},
		{3, 4, 10}, {2, 7, 8}, {3, 6, 8}, {6, 7, 9}, {8, 10, 11},
		{0, 5, 9}, {1, 4, 9}
	};
	std::vector<std::vector<int>> flower_snark4 = {
		{4,1,3}, {0,5,2}, {1,6,3}, {2, 7, 0}, {0,8,12},
		{1,9,13}, {2,10,14}, {3,11,15}, {4,13,15}, {12,5,14},
		{13, 6, 15}, {14,7,12}, {4,9,11}, {8,5,10}, {9,6,11},
		{10,7,8}
	};
	std::vector<std::vector<int>> flower_snark5 = {
		{2, 3, 6}, {2, 5, 8}, {0, 1, 15}, {0, 4, 10}, {3, 5, 16},
		{1, 4, 11}, {0, 7, 14}, {6, 8, 19}, {1, 7, 13}, {10, 11, 17},
		{3, 9, 13}, {5, 9, 14}, {13, 14, 18}, {8, 10, 12}, {6, 11, 12},
		{2, 16, 19}, {4, 15, 17}, {9, 16, 18}, {12, 17, 19}, {7, 15, 18}
	};
	std::vector<std::vector<int>> flower_snark7 = {
		{1, 6, 7}, {0, 2, 10}, {1, 3, 13}, {2, 4, 16}, {3, 5, 19},
		{4, 6, 22}, {0, 5, 25}, {0, 8, 9}, {7, 12, 26}, {7, 11, 27},
		{1, 11, 12}, {9, 10, 14}, {8, 10, 15}, {2, 14, 15}, {11, 13, 17},
		{12, 13, 18}, {3, 17, 18}, {14, 16, 20}, {15, 16, 21}, {4, 20, 21},
		{17, 19, 23}, {18, 19, 24}, {5, 23, 24}, {20, 22, 26}, {21, 22, 27},
		{6, 26, 27}, {8, 23, 25}, {9, 24, 25}
	};
	std::vector<std::vector<int>> flower_snark11 = {
		{11,1,10}, {0,12,2}, {1,13,3}, {2,14,4}, {3,15,5},
		{4,16,6}, {5,17,7}, {6,18,8}, {7,19,9}, {8, 20, 10},
		{9,21,0}, {0,22,33}, {1,23,34}, {2,24,35}, {3, 25, 36},
		{4,26,37}, {5,27,38}, {6,28,39}, {7,29,40}, {8,30,41},
		{9,31,42}, {10,32,43}, {11,34,43}, {33,12,35}, {34,13,36},
		{35,14,37}, {36,15,38}, {37,16,39}, {38,17,40}, {39,18,41},
		{40,19,42}, {41,20,43}, {42,21,33}, {11,23,32}, {22,12,24},
		{23,13,25}, {24,14,26}, {25,15,27}, {26,16,28}, {27,17,29},
		{28,18,30}, {29,19,31}, {30,20,32}, {31,21,22}
	};
	std::vector<std::vector<int>> flower_snark15 = {
		{15,1,14}, {0,16,2}, {1,17,3}, {2,18,4}, {3,19,5},
		{4,20,6}, {5,21,7}, {6,22,8}, {7,23,9}, {8,24,10},
		{9,25,11}, {10,26,12}, {11,27,13}, {12,28,14}, {13,29,0},
		{0,30,45}, {1,31,46}, {2,32,47}, {3,33,48}, {4,34,49},
		{5,35,50}, {6,36,51}, {7,37,52}, {8,38,53}, {9,39,54},
		{10,40,55}, {11,41,56}, {12,42,57}, {13,43,58}, {14,44,59},
		{15,46,59}, {45,16,47}, {46,17,48}, {47,18,49}, {48,19,50},
		{49,20,51}, {50,21,52}, {51,22,53}, {52,23,54}, {53,24,55},
		{54,25,56}, {55,26,57}, {56,27,58}, {57,28,59}, {58,29,45},
		{15,31,44}, {30,16,32}, {31,17,33}, {32,18,34}, {33,19,35},
		{34,20,36}, {35,21,37}, {36,22,38}, {37,23,39}, {38,24,40},
		{39,25,41}, {40,26,42}, {41,27,43}, {42,28,44}, {43,29,30}
	};
	test(simple_multigraph, "simple multigraph", 2, 2);
	test(simple_multigraph2, "simple multigraph 2", 3, 2);
test(simple_graph, "simple graph", 2, 2);
	test(simple_graph2, "simple graph 2", 4, 2); //tu dvojku povedala moja funkcia ale nemam to overene
	test(k23, "cubic bipartite graph K23", 3, 2);
	test(k33, "cubic bipartite graph K33", 3, 2);
	test(prism_graph, "prism graph", 4, 2);
	test(petersen_graph, "petersen graph", 5, 2.5);
	test(flower_snark2, "flower snark I2", 3, 2);
	test(flower_snark3, "flower snark I3", 5, 2.5);
	test(flower_snark4, "flower snark I4", 3, 2);
	test(flower_snark5, "flower snark I5", 4.5, 2 + (double)1 / 3);
	test(flower_snark7, "flower snark I7", 4 + (double)1 / 3, -1);
	test(flower_snark11, "flower snark I11", 4 + (double)1 / 5, -1);
	test(flower_snark15, "flower snark I15", 4 + (double)1 / 5, -1);
	return 0;
}