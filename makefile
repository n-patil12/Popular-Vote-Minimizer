build:
	rm -f app.exe
	gcc app.c MinPopVote.c -o app.exe

run:
	./app.exe

run_quiet:
	./app.exe -q

run_fast:
	./app.exe -f

run_combo:
	./app.exe -q -f

run_year:
	./app.exe -y 2000 -f -q

valgrind:
	valgrind -s --tool=memcheck --leak-check=yes --track-origins=yes ./app.exe

built_test:
	rm -f test.exe
	gcc test.c MinPopVote.c -o test.exe

run_test:
	./test.exe

valgrind_test:
	valgrind -s --tool=memcheck --leak-check=yes --track-origins=yes ./test.exe



