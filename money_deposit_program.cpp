#include <iostream>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

#define INITIAL_BANK_BALANCE 1000

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
	printf("program started to deposit money to account\n\n");

	int* bank_balance = get_shared_variable_bank_balance();

	//variables for peterson's solution
	int* turn = get_shared_variable_turn();
	int* flag0 = get_shared_variable_flag0();
	int* flag1 = get_shared_variable_flag1();

	printf("Initial Bank Balance is: %d\n\n", *bank_balance);

	//lets deposit 500 to this account
	for (int i = 0; i < 500; i++)
	{
		//entry section of Peterson's solution
		*flag0 = 1;
		*turn = 0;
		while (*flag1 == 1 && *turn == 0);

		//critical section
		
		//adding one by one
		int current_balance = *bank_balance;
		current_balance = current_balance + 1;
		*bank_balance = current_balance;
		printf(".");
		Sleep(1);

		//exit section of Peterson's solution
		*flag0 = 0;

	}

	printf("\n\nMoney depositing has been completed. Bank balance is: %d\n\n", *bank_balance);
	getchar();
}


int* get_shared_variable_bank_balance()
{
	//remove the variable bank_balance if it already exists
	shared_memory_object::remove("bank_balance");

	shm1 = shared_memory_object(create_only, "bank_balance", read_write);

	//set the size
	shm1.truncate(sizeof(int));
	
	//map the address of variable and then set its final value
	region1 = mapped_region(shm1, read_write);

	int *p = (int *) region1.get_address();
	*p = INITIAL_BANK_BALANCE;

	return p;
}


int* get_shared_variable_turn()
{
	//remove the variable
	shared_memory_object::remove("turn");

	shm2 = shared_memory_object(create_only, "turn", read_write);

	//set the size
	shm2.truncate(sizeof(int));

	//map the addres of variable and then set its final value
	region2 = mapped_region(shm2, read_write);

	int* p = (int*)region2.get_address();
	*p = 0;

	return p;
}


int* get_shared_variable_flag0()
{
	//remove the variable
	shared_memory_object::remove("flag0");

	shm3 = shared_memory_object(create_only, "flag0", read_write);

	//set the size
	shm3.truncate(sizeof(int));

	//map the addres of variable and then set its final value
	region3 = mapped_region(shm3, read_write);

	int* p = (int*)region3.get_address();
	*p = 0; //initial value of flag0 is 0

	return p;
}


int* get_shared_variable_flag1()
{
	//remove the variable
	shared_memory_object::remove("flag1");

	shm4 = shared_memory_object(create_only, "flag1", read_write);

	//set the size
	shm4.truncate(sizeof(int));

	//map the addres of variable and then set its final value
	region4 = mapped_region(shm4, read_write);

	int* p = (int*)region4.get_address();
	*p = 0; //initial value of flag1 is 0

	return p;
}