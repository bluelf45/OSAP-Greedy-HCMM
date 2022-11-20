run:
	g++ -o main main.cpp Functions/Functions.h Functions/Functions.cpp Functions/HCMM.h Functions/HCMM.cpp -Wall
	./main
clean:
	rm main