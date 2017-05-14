#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include "dao.h"

const char* ID_FILE ="id.dat";

int generator_id(void)
{
	int idUser = 100000;
	if(-1==access(ID_FILE,F_OK)){
		int fd = open(ID_FILE,O_CREAT|O_EXCL|O_WRONLY,0666);
		if(-1==fd){
			perror("write file  failed\n");
			exit(-1);
		}
		printf("file  write success\n");
		if(-1==write(fd,&idUser,sizeof(idUser))){
			perror("write file failed\n");
			exit(-1);
		}
		close (fd);
		return idUser;
	}
	int fd = open(ID_FILE,O_RDWR);
	if(-1==fd){
		perror("open file error\n");
		exit(-1);
	}
	printf("open file success\n");

	read(fd,&idUser,sizeof(idUser));
	idUser++;
	lseek(fd,0,SEEK_SET);
	write(fd,&idUser,sizeof(idUser));
	close(fd);
	
	return idUser;
}

int createUser(Account acc)
{
	char filename[20] = {0};
	sprintf(filename,"%d.dat",acc.id);
	int fd= open(filename,O_CREAT|O_EXCL|O_WRONLY,0666);
	if(-1==fd){
		perror("createUser() create file error\n");
		exit(-1);
	}
	printf("create file success\n");
	if(-1==write(fd,&acc,sizeof(acc))){
		printf("write error\n");
		exit(-1);
	}
	close(fd);
	return 0;
}

int deleteUser(Account acc)
{
	char filename[20]={0};
	char a;
	sprintf(filename,"%d.dat",acc.id);
	int fd = open(filename,O_RDONLY);
	if(-1==fd){
		printf("dose not exit the file\n");
		return -1;
	}
	Account acc1={0};
	if(-1==read(fd,&acc1,sizeof(acc1))){
		printf("read file error \n");
		return -1;		
	}
	close(fd);

	if(0==strcmp(acc1.passwd,acc.passwd)){
		printf("welcome to your account\n");
		return 0;
	}
	else{
		printf("sorry  passwd doesn't right!");
		return -1;			
	}
}
