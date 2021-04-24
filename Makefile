a.out:
	g++ -o a.out main.cpp Parser.cpp json.cpp test.cpp -I. -std=c++11
clean:
	rm -rf *.O *.out
