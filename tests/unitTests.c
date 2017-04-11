#include <stdio.h>
#include <string.h>

#include "minunit.h"


//https://github.com/siu/minunit

int main(int argc, char *argv[]) {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return 0;
}