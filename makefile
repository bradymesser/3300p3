default:
	gcc matmul_naive.c -o naive -O0
	gcc matmul_opt.c -o opt -O0
	./naive 1000 1000 400
	./opt 1000 1000 400
clean:
	rm naive opt naive.txt opt.txt

#echo "run these commands and compare the results\n\
 { time ./naive 1000 1000 400 > command.output 2>&1 ; } 2> naive.txt\n\
 { time ./opt 1000 1000 400 > command.output 2>&1 ; } 2> opt.txt\n"
