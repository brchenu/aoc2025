.PHONY: d1 d2 d3 d4 d5

d1:
	clang++ day1.cpp && ./a.out
	python3 day1.py

d2:
	clang++ day2.cpp && ./a.out
	python3 day2.py

d3:
	clang++ day3.cpp && ./a.out

d4: 
	clang++ -std=c++20 day4.cpp && ./a.out

d5:
	clang++ day5.cpp && ./a.out