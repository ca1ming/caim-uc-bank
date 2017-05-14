//receive message ,and operation
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
#include "bank.h"
#include "dao.h"

int main(void){
	int msgid1 = msgget(key1,0);
	if(-1==msgid1){
		perror("msgget msg1 error\n"),exit(-1);
	}
	printf("msgget mgs1 success\n");

	int msgid2 = msgget(key2,0);
	if(-1==msgid2){
		perror("msgget msg2 error\n"),exit(-1);
	}
	printf("msgget msg2 success\n");
	while(1)
	{
		Msg msg;
		if(msgrcv(msgid1,&msg,sizeof(msg),0,0)<=0){
			continue;
		}
		if(msg.mtype ==M_OPEN)
		{
			int idTemp = generator_id();
			msg.acc.id = idTemp;

			if(-1==createUser(msg.acc))
			{
				printf("save account failed\n");
				msg.mtype = M_FAILED;
			}
			else
			{
				printf("save account success\n");
				msg.mtype = M_SUCCESS;
			}
			msgsnd(msgid2,&msg,sizeof(msg),0);
		}
		/*
		if(msgrcv(msgid1.&msg,sizeof(msg.acc),M_DESTROY)<=0){
				continue;
		}
		*/
		if(msg.mtype==M_DESTROY){
			int temp=deleteUser(msg.acc);
			if(0==temp)
			{
				printf("delete success,please check get money form bank\n");	
				msg.mtype =M_SUCCESS;
			}
			else
			{
				if(-1==temp)
					printf("passwd or id error,can not delete account\n");	
				if(-2==temp)
					printf("You don't want to delete your account\n");
				msg.mtype = M_FAILED;
			}
			msgsnd(msgid2,&msg,sizeof(msg.),0);
		}
	}	
	return 0;
}

