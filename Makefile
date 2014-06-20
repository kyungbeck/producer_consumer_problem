all:
	gcc -g -o producer_consumer_problem producer_consumer_problem.c sbuf.c csapp.c -pthread
run:
	./producer_consumer_problem
run_goodcnt:
	./goodcnt 10000000
run_sbufcnt:
	./sbufcnt 10000000
clean:
	rm -rf producer_consumer_problem
