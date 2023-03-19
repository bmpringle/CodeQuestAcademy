default:
	clang++ -std=c++17 ${FOLDER}/main.cpp -o ${FOLDER}/a.out
run_tests:
	echo RUNNING TESTS
	${FOLDER}/a.out < ${FOLDER}/${FOLDER}-samples/1.in > ${FOLDER}/test.out
	diff ${FOLDER}/test.out ${FOLDER}/${FOLDER}-samples/1.out