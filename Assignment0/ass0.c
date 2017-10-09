/**********************************************************************
Filename:			ass0.c
Version: 			2.0
Author:				Justin Bertrand
Student No:  		040 786 592
Course Name/Number:	Numerical Computing CST8233    
Lab Sect: 			301                                                      
Assignment #:		0
Assignment name:	FleaBay
Due Date:			September 23 2015                                           
Submission Date:	
Professor:			Andrew Tyler
Purpose: 			A mock Online Sales Management System (OSMS) which 
					allows for the creation, validation, and printing
					of user accounts.
*********************************************************************/
#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef enum { FALSE = 0, TRUE }BOOL;

typedef struct
{
	char* ID;
	char* PassWord;
}Account, *pAccount, **ppAccount;

typedef struct
{
	unsigned int numAccounts;
	ppAccount accounts;
}FleaBay, *pFleaBay;

void FleaBayInit(pFleaBay);			/* Initialise the FleaBay instance */
int FleaBayLogin(pFleaBay);			/* login to the FleaBay */
int FleaBayReport(pFleaBay);			/* Print all the Accounts */
void FleaBayCleanUp(pFleaBay);			/* Free all dynamically allocated memory */
void AddNewAccount(pFleaBay);			/* Add a new Account to the FleaBay */

/********************************************************************
Function name:	main
Purpose:		main function
				Offers a text-based interface for the manipulation
					of the FleaBay Online Sales Management System
In parameters:	none
Out parameters:	0 for successful execution
Version:		1.0
Author:			Andrew Tyler
**********************************************************************/
int main(void)
{
	BOOL bRunning = TRUE;
	char i_response;
	FleaBay e;

	FleaBayInit(&e);

	while (bRunning)
	{
		printf("\nPlease enter your choice\n");
		printf("1. FleaBay Login\n");
		printf("2. FleaBay Report\n");
		printf("3. Quit\n");
		fflush(stdin);
		scanf("%c", &i_response);
		switch (i_response)
		{
		case '1':
			if (!FleaBayLogin(&e))
				return 1;
			break;
		case '2':
			if (!FleaBayReport(&e))
				return 1;
			break;
		case '3':
			FleaBayCleanUp(&e);
			bRunning = FALSE;
			break;
		}
	}
	return 0;
}

/********************************************************************
Function name:	FleaBayInit
Purpose:		Initialises the FleaBay structure
In parameters:	pointer to a FleaBay structure
Out parameters:	none
Version:		2.0
Author:			Justin Bertrand
**********************************************************************/
void FleaBayInit(pFleaBay FleaBayInstance) 
{	
	FleaBayInstance->numAccounts = 0;
	FleaBayInstance->accounts = 0;
}

/********************************************************************
Function name:	FleaBayLogin
Purpose:		Provides a text-based interface which allows for the 
					creation of accounts, the opening of accounts,
					and the validation of passwords.
In parameters:	pointer to a FleaBay structure
Out parameters:	Returns TRUE for success
				Returns FALSE for an invalid input
Version:		2.0
Author:			Justin Bertrand
**********************************************************************/
int FleaBayLogin(pFleaBay FleaBayInstance)
{
	char input;
	char buffer[256];
	unsigned int index;
	BOOL account_found = FALSE;

	if (FleaBayInstance->numAccounts == 0)
	{
		printf("**NO ACCOUNTS**\n");
	}

	printf("1. Add a new Account\n");
	printf("2. Open an existing Account\n");
	printf("3. Return to Main Menu\n");

	fflush(stdin);
	scanf("%c", &input);
	switch (input)
	{
	case '1':
		AddNewAccount(FleaBayInstance);
		break;
	case '2':
		fflush(stdin);
		printf("please enter your account ID: ");
		gets(buffer);

		for (index = 0; index < FleaBayInstance->numAccounts; ++index) {
			if (strcmp(buffer, FleaBayInstance->accounts[index]->ID) == 0)
			{
				account_found = TRUE;
				break;
			}
		}

		if (account_found)
		{
			printf("please enter your account password: ");
			gets(buffer);
			if (strcmp(buffer, FleaBayInstance->accounts[index]->PassWord) == 0)
			{
				printf("Account is valid.\n");
			}
			else
			{
				printf("\n%s password doesn't match this ID:\n", buffer);
			}
		}
		else
		{
			printf("%s\n is invalid ID\n", buffer);
		}
		break;
	case '3':
		printf("Returning to Main Menu.");
		break;
	}

	return TRUE;
}

/********************************************************************
Function name:	FleaBayReport
Purpose:		Prints out all accounts in the FleaBay system
In parameters:	pointer to a FleaBay structure
Out parameters:	Returns TRUE when complete.
Version:		2.0
Author:			Justin Bertrand
**********************************************************************/
int FleaBayReport(pFleaBay FleaBayInstance)
{
	unsigned int index;

	if (FleaBayInstance->numAccounts != 0)
	{
		for (index = 0; index < FleaBayInstance->numAccounts; ++index)
		{
			printf("Account name: %s\n\n", FleaBayInstance->accounts[index]->ID);
		}
	}
	else
	{
		printf("**NO ACCOUNTS TO DISPLAY**\n");
	}
	
	return TRUE;
}

/********************************************************************
Function name:	FleaBayCleanUp
Purpose:		Releases all allocated memory upon program exit.
In parameters:	pointer to a FleaBay structure
Out parameters:	none
Version:		2.0
Author:			Justin Bertrand
**********************************************************************/
void FleaBayCleanUp(pFleaBay FleaBayInstance)
{
	unsigned int index;

	/* If no accounts exist, prevent the releasing of memory */
	if (FleaBayInstance->numAccounts != 0)
	{
		for (index = 0; index < FleaBayInstance->numAccounts; ++index)
		{
			free(FleaBayInstance->accounts[index]->ID);
			free(FleaBayInstance->accounts[index]->PassWord);
			free(FleaBayInstance->accounts[index]);
		}
	}

	free(FleaBayInstance->accounts);
}

/********************************************************************
Function name:	AddNewAccount
Purpose:		Allows for the addition of a new account if the ID
					is unique.
In parameters:	pointer to a FleaBay structure
Out parameters:	none
Version:		2.0
Author:			Justin Bertrand
**********************************************************************/
void AddNewAccount(pFleaBay FleaBayInstance)
{
	ppAccount temp;
	pAccount pnewAccount;
	char buffer[256] = { 0 };
	BOOL account_name_unique = TRUE;
	unsigned int index = 0;

	fflush(stdin);
	printf("please enter your account ID: ");
	gets(buffer);

	for (index = 0; index < FleaBayInstance->numAccounts; ++index) {
		if (strcmp(buffer, FleaBayInstance->accounts[index]->ID) == 0) 
		{
			account_name_unique = FALSE;
			break;
		}
	}

	if (account_name_unique)
	{
		temp = malloc(sizeof(pAccount) + sizeof(FleaBayInstance->accounts)*FleaBayInstance->numAccounts);

		/* If there are previous accounts,
		the previous block of memory must be copied
		to the new block, then freed */
		if (FleaBayInstance->numAccounts != 0)
		{
			memcpy(temp, FleaBayInstance->accounts, sizeof(FleaBayInstance->accounts)*FleaBayInstance->numAccounts);
			free(FleaBayInstance->accounts);
		}
		FleaBayInstance->accounts = temp;

		pnewAccount = (pAccount)malloc(sizeof(Account));

		pnewAccount->ID = (char*)malloc(strlen(buffer) + 1);
		strcpy(pnewAccount->ID, buffer);

		printf("please enter your account password: ");
		gets(buffer);
		pnewAccount->PassWord = (char*)malloc(strlen(buffer) + 1);
		strcpy(pnewAccount->PassWord, buffer);

		FleaBayInstance->accounts[FleaBayInstance->numAccounts] = pnewAccount;
		++FleaBayInstance->numAccounts;
	}
	else
	{
		printf("**ACCOUNT NAME NOT UNIQUE**\n");
	}
}
