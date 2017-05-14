#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include "bank.h"

//define msg ID
static int msgid1;
static int msgid2;

void init(void)
{
	printf("server initing ,please wait.......\n\n");
	sleep(2);
	msgid1=msgget(key1,IPC_CREAT|IPC_EXCL|0666);
	if(-1==msgid1){
		perror("create msgid1 failed\n");
		exit(-1);
	}
	printf("create msgid1 success\n\n");
	msgid2 = msgget(key2,IPC_CREAT|IPC_EXCL|0666);
	if(-1==msgid2){
		perror("create msgid2 failed");
		exit(-1);
	}
	printf("create msgid2 success\n");
	printf("******server init success*******\n");
}

void destory(void){
	printf("*****closeing server ,please wait....\n");
	sleep(2);
	if(-1==msgctl(msgid1,IPC_RMID,0))
	{
		perror("delete msgid1 failed\n");
		exit(-1);
	}
	printf("destory msg1 success\n");

	if(-1==msgctl(msgid2,IPC_RMID,0))
	{
		perror("delete msgid2 failed \n");
		exit(-1);
	}
	printf("destroy msg2 success\n");
	printf("*****close server success*****\n");
}

void start(void)
{
	pid_t pid_open=vfork();
	if(-1==pid_open){
		perror("create son process failed\n");
		exit(-1);
	}
	if(0==pid_open){
		execl("./open","open",NULL);
	}
	waitpid(pid_open,NULL,0);
}

void sig_exit(int signo)
{
	exit(0);
}

int main()
{
	atexit(destory);
	printf("close  server please tipe CTRL+C \n");
	signal(SIGINT,sig_exit);
	init();
	start();
	return 0;
}
