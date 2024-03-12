main:
	g++ -g -Wall lab2.cpp -o lab

test:
	./lab input/sample_input.txt
	./lab input/hidden_input.txt

clean:
	rm lab