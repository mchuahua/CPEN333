#include "..\..\rt.h"
#include "..\BankAccount.h"

int main()
{
	BankAccount	b1("Fred") ;

	cout << "Child Process withdrawing $32000 one $ at a time\n";

	for(int i = 0; i < 32000; i ++)
		b1.WithdrawFunds(1.0) ;

	return 0 ;
}