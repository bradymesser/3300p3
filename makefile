default:
	gcc matmul_naive.c -o naive -O0
	gcc matmul_opt.c -o opt -O0
	./naive 1000 1000 400 > naive.txt
	./opt 1000 1000 400 > opt.txt
	diff opt.txt naive.txt
clean:
	rm naive opt naive.txt opt.txt

#echo "run these commands and compare the results\n\
 { time ./naive 1000 1000 400 > command.output 2>&1 ; } 2> naive.txt\n\
 { time ./opt 1000 1000 400 > command.output 2>&1 ; } 2> opt.txt\n"

naive:
	gcc matmul_naive.c -o naive -O0
	./naive 1000 1000 1000
	./naive 2000 2000 2000
	./naive 3000 3000 3000
	./naive 4000 4000 4000
	./naive 5000 5000 5000

opt:
	gcc matmul_opt.c -o opt -O0
	./opt 1000 1000 1000
	./opt 2000 2000 2000
	./opt 3000 3000 3000
	./opt 4000 4000 4000
	./opt 5000 5000 5000

check: 	#un comment the print statements to use this
	gcc matmul_naive.c -o naive -O0
	gcc matmul_opt.c -o opt -O0
	./naive 10 10 10 > naive.txt
	./opt 10 10 10 > opt.txt
	diff naive.txt opt.txt
