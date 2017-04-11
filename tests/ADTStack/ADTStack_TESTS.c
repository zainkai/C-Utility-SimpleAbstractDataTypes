#include <stdio.h>
#include <string.h>
#include "../minunit.h"
#include "ADTStack.h"

static ADTStack* IntSuite;

void setup_int_Test(){
	int i,temp;

	IntSuite = ADTStackCreate(10);

	for(i = 0;i < 10;i++){
		ADTStackPush(IntSuite,&i);
	}
}

void teardown_int_Test(){
	ADTStackFree(IntSuite);
}

MU_TEST(test_TopStack){
	int TopOfStack = *(int*)ADTStackTop(IntSuite);
	mu_check(TopOfStack == 9);
}

MU_TEST_SUITE(test_suite) {
	MU_SUITE_CONFIGURE(&setup_int_Test, &teardown_int_Test);

	//TopStack
	MU_RUN_TEST(test_TopStack);
}

int main(int argc, char *argv[]) {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return 0;
}