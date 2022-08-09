#include <iostream>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

using namespace boost::interprocess;
using namespace boost::detail;

shared_memory_object shm1;
mapped_region region1;

//variables for peterson's solution
shared_memory_object shm2, shm3, shm4;
mapped_region region2, region3, region4;

int* get_shared_variable_bank_balance();

int* get_shared_variable_turn();
int* get_shared_variable_flag0();
int* get_shared_variable_flag1();

int main()
{
	printf("program started to withdraw money from account\n\n");

	int* bank_balance = get_shared_variable_bank_balance();

	int* turn = get_shared_variable_turn();
	int* flag0 = get_shared_variable_flag0();
	int* flag1 = get_shared_variable_flag1();

	//lets withdraw 500 from this account
	for (int i = 0; i < 500; i++)
	{
		//entry section of Peterson's solution
		*flag1 = 1;
		*turn = 1;
		while (*flag0 == 1 && *turn == 1);

		//critical section

		//withdraw one by one
		int current_balance = *bank_balance;
		current_balance = current_balance - 1;
		*bank_balance = current_balance;
		printf(".");
		Sleep(1);

		//exit section of Peterson's solution
		*flag1 = 0;
	}

	printf("\n\nMoney withdraw has been completed. Final Bank balance is: %d\n\n", *bank_balance);
	getchar();
}


int* get_shared_variable_bank_balance()
{
	shm1 = shared_memory_object(open_only, "bank_balance", read_write);

	//map the address of variable
	region1 = mapped_region(shm1, read_write);

	int* p = (int*)region1.get_address();

	return p;
}


int* get_shared_variable_turn()
{
	shm2 = shared_memory_object(open_only, "turn", read_write);

	//map the addres of variable
	region2 = mapped_region(shm2, read_write);

	int* p = (int*)region2.get_address(); //read existing value

	return p;
}


int* get_shared_variable_flag0()
{
	shm3 = shared_memory_object(open_only, "flag0", read_write);

	//map the addres of variable
	region3 = mapped_region(shm3, read_write);

	int* p = (int*)region3.get_address(); //read existing value

	return p;
}


int* get_shared_variable_flag1()
{
	shm4 = shared_memory_object(open_only, "flag1", read_write);

	//map the addres of variable
	region4 = mapped_region(shm4, read_write);

	int* p = (int*)region4.get_address(); //read existing value

	return p;
}


