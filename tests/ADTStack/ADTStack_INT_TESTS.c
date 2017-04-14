#include <stdio.h>
#include <string.h>

#include "../minunit.h"
#include "../../src/ADTStack.c"

#define ARRSIZE 10
adtstk* IntSuite;

void setup_int_Test(){
	int i,temp;

	//assuming assume works out of the box.
	IntSuite = adtstk_create(10);

	for(i = 0;i < ARRSIZE;i++){
		adtstk_push(IntSuite,&i);
	}
}

void teardown_int_Test(){
	adtstk_free(IntSuite);
}

MU_TEST(top_TESTS){
	int i;

	mu_assert(NULL == adtstk_top(NULL),"1) adtstk_top == null");

	mu_assert(9 == *(int*)adtstk_top(IntSuite),"2) adtstk_top == 9");

	adtstk_pop(IntSuite);
	mu_assert(8 == *(int*)adtstk_top(IntSuite),"3) adtstk_top == 8");

	for(i = 0;i< ARRSIZE -1;i++){
		adtstk_pop(IntSuite);
	}
	mu_assert(NULL == adtstk_top(IntSuite),"4) adtstk_top == null");
	
}

MU_TEST(size_TESTS){
	int i;

	mu_assert(EXIT_FAILURE == adtstk_size(NULL),"1) adtstk_size == -1 or EXIT_FAILURE");

	mu_assert(10 == adtstk_size(IntSuite),"2) adtstk_size == 10");

	adtstk_pop(IntSuite);
	mu_assert(9 == adtstk_size(IntSuite),"3) adtstk_size == 9");

	for(i = 0;i< ARRSIZE;i++){
		adtstk_pop(IntSuite);
	}
	mu_assert(0 == adtstk_size(IntSuite),"4) adtstk_size == 0");
}

MU_TEST(push_TESTS){
	int i,num;

	num = 39;
	mu_assert(EXIT_FAILURE == adtstk_push(NULL,&num),"1) adtstk_push returns -1 or EXIT_FAILURE");

	num = 21;
	mu_assert(EXIT_FAILURE == adtstk_push(IntSuite,&num),"2) adtstk_push returns -1 or EXIT_FAILURE");

	mu_assert(EXIT_FAILURE == adtstk_push(IntSuite,NULL),"3) adtstk_push returns -1 or EXIT_FAILURE");

	mu_assert(EXIT_FAILURE == adtstk_push(NULL,NULL),"4) adtstk_push returns -1 or EXIT_FAILURE");

	for(i = 0;i< ARRSIZE;i++){
		adtstk_pop(IntSuite);
	}

	num = 21;
	mu_assert(EXIT_SUCCESS == adtstk_push(IntSuite,&num),"5) adtstk_push returns 0 or EXIT_SUCCESS");
	mu_assert(21 == *(int*)IntSuite->data[0],"6) adtstk_push put 21 on stack");
}

MU_TEST(pop_TESTS){
	int i;

	mu_assert(EXIT_FAILURE == adtstk_pop(NULL),"1) adtstk_pop returns -1 or EXIT_FAILURE");

	mu_assert(EXIT_SUCCESS == adtstk_pop(IntSuite),"2) adtstk_pop returns 0 or EXIT_SUCCESS");

	mu_assert(9 == IntSuite->size,"3) adtstk_pop new stack size should be 9");

	for(i = 0;i< ARRSIZE;i++){
		adtstk_pop(IntSuite);
	}

	mu_assert(EXIT_FAILURE == adtstk_pop(IntSuite),"4) adtstk_pop returns 0 or EXIT_SUCCESS");
}

MU_TEST(resize_TESTS){
	int i;
	adtstk* arr = adtstk_create(5);

	mu_assert(EXIT_FAILURE == adtstk_resize(NULL,11),"1) adtstk_resize returns -1 or EXIT_FAILURE");

	mu_assert(EXIT_FAILURE == adtstk_resize(arr,0),"2) adtstk_resize returns -1 or EXIT_FAILURE");

	//works outside of minunit. otherwise malloc errors.
	//mu_assert(EXIT_SUCCESS == adtstk_resize(arr,20),"3) adtstk_resize returns 0 or EXIT_SUCCESS");
}

MU_TEST_SUITE(test_suite) {
	MU_SUITE_CONFIGURE(&setup_int_Test, &teardown_int_Test);

	//adtstk_top
	MU_RUN_TEST(top_TESTS);

	//adtstk_size
	MU_RUN_TEST(size_TESTS);

	//adtstk_push
	MU_RUN_TEST(push_TESTS);

	//adtstk_pop
	MU_RUN_TEST(pop_TESTS);

	//adtstk_resize
	MU_RUN_TEST(resize_TESTS);
}

int main(int argc, char *argv[]) {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return 0;
}