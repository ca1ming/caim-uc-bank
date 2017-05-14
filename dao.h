//file operation function declaration
#ifndef DAO_H
#define DAO_H
#include "bank.h"


int generator_id(void);

int createUser(struct Account acc);
int deleteUser(struct Account acc);
#endif
