compile:
	g++ sniffer.cpp end.cpp worker.cpp -o sniffer

run:
	./sniffer -p ./