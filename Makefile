CXXOPTS += -std=c++11 -W -Wall

template-indenter: template-indenter.cpp
	$(CXX) $(CXXOPTS) $< -o $@

test: template-indenter
	./"$<" < example.txt

clean:
	rm -f template-indenter

.PHONY: test clean
