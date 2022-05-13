compile:
	g++ sniffer.cpp end.cpp worker.cpp -o sniffer

run:
	rm -f ../*.out 
	./sniffer -p ./

clean:
	rm -f ../*.out 
	rm sniffer