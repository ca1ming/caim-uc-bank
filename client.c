#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdlib.h>
#include "bank.h"

static int msgid1;
static int msgid2;

void getId(void)
{
	msgid1 = msgget(key1,0);
	if(-1==msgid1){
		printf("get msg1 failed \n");
		exit(-1);
	}
	printf("success get msg1 \n");

	msgid2 = msgget(key2,0);
	if(-1==msgid2){
		printf("get msg2 failed \n");
		exit(-1);
	}
	printf("success get msg2\n");
}

void createUser(void)
{
	Account acc;
	printf("name:\n");
	scanf("%s",acc.username);
	printf("password:\n");
	scanf("%s",acc.passwd);
	printf("balance:\n");
	scanf("%lf",&acc.balance);
	Msg msg = {M_OPEN,acc};
	getId();
	if(-1==msgsnd(msgid1,&msg,sizeof(msg),0))
	{
		printf("send first msg error\n");
		break;
	}
	printf("send first msg success\n");

	msgrcv(msgid2,&msg,sizeof(msg),0,0);
	if(msg.mtype==M_SUCCESS){
		printf("NOTICE:count:%d\nname:%s\npassword:%s\nbalance:%lf\n",msg.acc.id,msg.acc.username,msg.acc.passwd,msg.acc.balance);
	}
	else{
		printf("open error\n");
	}
}
Account login_acc(Account *acc){
	printf("printf input id:(1*****)\n");
	scanf("%d",acc->id);
	printf("printf input password\n");
	scanf("%s",acc->passwd);	
	return acc;	
}
void deleteUser(void){
	
	Account acc;
	/*
	printf("printf input id:(1*****)\n");
	scanf("%d",&acc.id);
	printf("printf input password\n");
	scanf("%s",acc.passwd);
	*/
	login_acc(acc);
	Msg msg = {M_DESTROY,acc};
	getId();
	if(-1==msgsnd(msgid1,&msg,sizeof(msg),0))
	{
		printf("send first msg error\n");
		break;
	}
	printf("send first msg success\n");
	
	msgrcv(msgid2,&msg,sizeof(msg),0,0);
	if(msg.mtype == M_SUCCESS){
		printf("congrulations ,delete  success\n");
	}
	else{
		printf("delete error\n");
	}

}
void mainPage(void)
{
	while(1)
	{
		printf("********ATM********\n");
		printf("[1]open  [2]xiaohu [3]cunqian\n");
		printf("[4]quqian [5]chaxun [6]zhuanzhang\n");
		printf("[0]tuichu \n choose:\n");
		int choose = 0;
		scanf("%d",&choose);
		switch(choose)
		{
			case 1:createUser();break;
			case 2:deleteUser();break;
			case 3:
			case 4:
			case 5:
			case 6:printf("buinding please hoding");break;
			case 0:printf("thanks use byebye\n");break;
		default: printf("input error\n");continue;
		}
		printf("\n\n");
	}
}

int main(){
	mainPage();
	return 0;
}
