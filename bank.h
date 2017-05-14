//define msg struct, account struct 
#ifndef BANK_H
#define BANK_H 

extern const int key1;
extern const int key2;

#define M_OPEN 1 //kai hu
#define M_DESTROY  2 // xiao hu
#define M_SAVE 3 //cun qian
#define M_TAKE 4 //qu qian
#define M_QUERY 5 //cha xun
#define M_TRANSF 6 //zhuan zhang 
#define M_SUCCESS 7 //success
#define M_FAILED 8 //failed 

typedef struct Account
{
	int id;
	char username[20];
	char passwd[6];
	double balance;
}Account;

typedef struct Msg
{
	long mtype;
	Account acc;
}Msg;

#endif

