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
		TYPE temp_item = malloc(sizeof(TYPE));
		memcpy(temp_item,&i,sizeof(TYPE));
		IntSuite->size++;
		IntSuite->data[i] = temp_item;
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
	int num = 1111;

	mu_check(EXIT_FAILURE == adtarr_insert(IntSuite,-1,&num));
	mu_check(EXIT_FAILURE == adtarr_insert(NULL,-1,&num));
	mu_check(EXIT_FAILURE == adtarr_insert(NULL,-2,&num));

	num = 1212;
	adtarr_remove(IntSuite,-1);
	mu_check(EXIT_SUCCESS == adtarr_insert(IntSuite,2,&num));
	mu_check(1212 == *(int*)adtarr_get(IntSuite,2));

	num = 2222;
	adtarr_remove(IntSuite,2);
	mu_check(EXIT_SUCCESS == adtarr_insert(IntSuite,-1,&num));
	mu_check(2222 == *(int*)adtarr_get(IntSuite,-1));

	num = 3333;
	adtarr_remove(IntSuite,0);
	mu_check(EXIT_SUCCESS == adtarr_insert(IntSuite,0,&num));
	mu_check(3333 == *(int*)adtarr_get(IntSuite,0));
}

MU_TEST(resize_TESTS){
	mu_check(EXIT_FAILURE == adtarr_resize(NULL,11));

	mu_check(EXIT_FAILURE == adtarr_resize(IntSuite,0));

	mu_check(EXIT_SUCCESS == adtarr_resize(IntSuite,20));

	mu_check(20 == adtarr_capacity(IntSuite));

	mu_check(EXIT_SUCCESS == adtarr_resize(IntSuite,5));
	mu_check(4 == *(int*)adtarr_get(IntSuite,-1));
}

MU_TEST(remove_TESTS){
	mu_check(EXIT_FAILURE == adtarr_remove(NULL,11));

	mu_check(EXIT_FAILURE == adtarr_remove(IntSuite, 11));

	mu_check(EXIT_SUCCESS == adtarr_remove(IntSuite,-1));
	mu_check(8 == *(int*)adtarr_get(IntSuite,-1));

	mu_check(EXIT_SUCCESS == adtarr_remove(IntSuite,3));
	mu_check(4 == *(int*)adtarr_get(IntSuite,3));

	mu_check(EXIT_SUCCESS == adtarr_remove(IntSuite,0));
	mu_check(1 == *(int*)adtarr_get(IntSuite,0));

	mu_check(EXIT_SUCCESS == adtarr_remove(IntSuite,7));
	mu_check(7 == *(int*)adtarr_get(IntSuite,-1));
}

MU_TEST(set_TESTS){
	int i;
	int num = 1111;

	mu_check(NULL == adtarr_set(IntSuite,-1,NULL));
	mu_check(NULL == adtarr_set(NULL,-1,&num));
	mu_check(NULL == adtarr_set(NULL,-2,&num));

	num = 9000;
	mu_check(9000 == *(int*)adtarr_set(IntSuite,0,&num));
	mu_check(9000 == *(int*)adtarr_get(IntSuite,0));


	num = 3434;
	mu_check(3434 == *(int*)adtarr_set(IntSuite,-1,&num));
	mu_check(3434 == *(int*)adtarr_get(IntSuite,-1));

	num = 2222;
	adtarr_remove(IntSuite,2);
	mu_check(2222 == *(int*)adtarr_set(IntSuite,2,&num));
	mu_check(2222 == *(int*)adtarr_get(IntSuite,2));

	for(i =0;i<ARRSIZE;i++){
		adtarr_remove(IntSuite,-1);
	}

	num = 231231;
	mu_check(NULL == adtarr_set(IntSuite,2,&num));
	mu_check(231231 == *(int*)adtarr_set(IntSuite,-1,&num));
	mu_check(231231 == *(int*)adtarr_get(IntSuite,0));

	num = 44444;
	mu_check(NULL == adtarr_set(IntSuite,2,&num));
	mu_check(NULL == adtarr_set(IntSuite,2,&num));
	mu_check(NULL == adtarr_get(IntSuite,1));
}

MU_TEST_SUITE(test_suite) {
	MU_SUITE_CONFIGURE(&setup_int_Test, &teardown_int_Test);

	// //adtarr_size
	MU_RUN_TEST(size_TESTS);

	//adtarr_resize
	MU_RUN_TEST(resize_TESTS);

	//adtarr_insert
	MU_RUN_TEST(insert_TESTS);

	//adtarr_remove
	MU_RUN_TEST(remove_TESTS);

	//adtarr_set
	MU_RUN_TEST(set_TESTS);

	//
}

int main(int argc, char *argv[]) {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return 0;
}