all: clean compile run

compile: main.cpp Directory.cpp SoftLink.cpp shell.cpp RegularFile.cpp
	@echo "-------------------------------------------"
	@echo "Compiling..."
	@g++ -o test main.cpp Directory.cpp SoftLink.cpp shell.cpp RegularFile.cpp -lm

run:
	@echo "-------------------------------------------"
	@echo "Running the tests...."
	@echo "================================================================================="
	./test
	@echo "================================================================================="
	@echo "Completed tests...."

clean:
	@echo "-------------------------------------------"
	@echo "Removing compiled files..."
	@rm -f *.o
	@rm -f test