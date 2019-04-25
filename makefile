default:
	gcc matmul_naive.c -o naive
	gcc matmul_opt.c -o opt
	#include the brackets, you can also not do this and just do time ./executable arg1 arg2 arg3
	echo "run these commands and compare the results\n\
	 { time ./naive 1000 1000 400 > command.output 2>&1 ; } 2> naive.txt\n\
	 { time ./opt 1000 1000 400 > command.output 2>&1 ; } 2> opt.txt\n"
clean:
	rm naive opt naive.txt opt.txt
