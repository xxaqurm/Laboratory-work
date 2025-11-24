CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I include

# Цель по умолчанию (компиляция main)
app: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o main

# Цель для тестов
tests: tests/*.cpp
	$(CXX) $(CXXFLAGS) tests/*.cpp -o run_tests

# Очистка
clean:
	rm -f main run_tests
