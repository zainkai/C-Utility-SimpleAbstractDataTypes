#include <stdio.h>
#include <string.h>

#include "../minunit.h"
#include "../../src/ADTArray.c"

#define ARRSIZE 10
adtarr* IntSuite;

void setup_int_Test(){
	int i,temp;

	//assuming assume works out of the box.
	IntSuite = adtarr_create(10);

	for(i = 0;i < ARRSIZE;i++){
		adtarr_set(IntSuite,-1,&i);
	}
}

void teardown_int_Test(){
	adtarr_free(IntSuite);
}

MU_TEST(size_TESTS){
	int i;

	mu_check(EXIT_FAILURE == adtarr_size(NULL));

	mu_check(10 == adtarr_size(IntSuite));

	adtarr_remove(IntSuite,9);
	mu_check(9 == adtarr_size(IntSuite));

	for(i = 0;i< ARRSIZE;i++){
		adtarr_remove(IntSuite,-1);
	}

	mu_check(0 == adtarr_size(IntSuite));
}

MU_TEST(insert_TESTS){
	//mu_check(adtarr_insert(IntSuite));
}

MU_TEST(resize_TESTS){
	mu_assert(EXIT_FAILURE == adtarr_resize(NULL,11),"1) adtarr_resize returns -1 or EXIT_FAILURE");

	mu_assert(EXIT_FAILURE == adtarr_resize(IntSuite,0),"2) adtarr_resize returns -1 or EXIT_FAILURE");

	mu_assert(EXIT_SUCCESS == adtarr_resize(IntSuite,20),"3) adtarr_resize returns 0 or EXIT_SUCCESS");

	mu_check(20 == adtarr_capacity(IntSuite));

	mu_check(EXIT_SUCCESS == adtarr_resize(IntSuite,5));
	mu_check(4 == *(int*)adtarr_get(IntSuite,-1));
}

MU_TEST_SUITE(test_suite) {
	MU_SUITE_CONFIGURE(&setup_int_Test, &teardown_int_Test);

	//adtarr_size
	MU_RUN_TEST(size_TESTS);


	//adtarr_resize
	MU_RUN_TEST(resize_TESTS);
}

int main(int argc, char *argv[]) {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return 0;
}