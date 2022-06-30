make: 
	gcc sudoku.c -Wall -o sudoku

run: make

	for number in 1 2 3 4 5 6 7 8 9 ; do \
		./sudoku ./checker/input/task1/board0$$number.json 123 ; \
	done

	for num in 1 2; do \
		for number in 0 1 2 3 4 5 6 7 8 9 ; do \
			./sudoku ./checker/input/task1/board$$num$$number.json 123 ; \
		done ; \
	done

	for number in 0 1 2 3 4 5; do \
		./sudoku ./checker/input/task1/board3$$number.json 123 ; \
	done 

	for number in 1 2 3 4 5 6 7 8 9 ; do \
		./sudoku ./checker/input/task4/board0$$number.bmp 4 ; \
	done

	for number in 0 1 2 3 4 5 ; do \
		./sudoku ./checker/input/task4/board1$$number.bmp 4 ; \
	done
clean:
	rm sudoku
	rm output_task*