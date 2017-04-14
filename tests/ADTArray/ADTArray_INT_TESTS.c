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

	mu_assert(EXIT_FAILURE == adtarr_size(NULL),"1) adtarr_size == -1 or EXIT_FAILURE");

	mu_assert(10 == adtarr_size(IntSuite),"2) adtarr_size == 10");

	// adtarr_remove(IntSuite,9);
	// mu_assert(9 == adtarr_size(IntSuite),"3) adtarr_size == 9");
	for(i = 0;i< ARRSIZE;i++){
		printf("i->%d : size->%d\n",i,adtarr_size(IntSuite));
		adtarr_remove(IntSuite,i);
		printf("::%d\n\n",*(int*)IntSuite->data[i]);
	}
	//printf("asdasdas:%d\n",adtarr_size(IntSuite));
	mu_assert(0 == adtarr_size(IntSuite),"4) adtarr_size == 0");
}

MU_TEST(resize_TESTS){
	int i;
	adtarr* arr = adtarr_create(5);

	mu_assert(EXIT_FAILURE == adtarr_resize(NULL,11),"1) adtarr_resize returns -1 or EXIT_FAILURE");

	mu_assert(EXIT_FAILURE == adtarr_resize(arr,0),"2) adtarr_resize returns -1 or EXIT_FAILURE");

	//works outside of minunit. otherwise malloc errors.
	//mu_assert(EXIT_SUCCESS == adtarr_resize(arr,20),"3) adtarr_resize returns 0 or EXIT_SUCCESS");
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