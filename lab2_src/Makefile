CXX      = g++
CXXFLAGS = -std=c++17 -Wall

TARGETS = ex1 ex2 ex3 ex4 ex5

all: $(TARGETS)

ex1: ex1_vector_addition.cpp utils.h
	$(CXX) $(CXXFLAGS) -o $@ $<

ex2: ex2_matrix_addition.cpp utils.h
	$(CXX) $(CXXFLAGS) -o $@ $<

ex3: ex3_mat_vec_mul.cpp utils.h
	$(CXX) $(CXXFLAGS) -o $@ $<

ex4: ex4_mat_mat_mul.cpp utils.h
	$(CXX) $(CXXFLAGS) -o $@ $<

ex5: ex5_dot_product.cpp utils.h
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(TARGETS)
