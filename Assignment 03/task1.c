#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/wait.h> 
struct shared{
  char sel[100];
  int b;
};
int main(){
    int fd[2];
    int pipe_1=pipe(fd);
    char buff[200];
    if (pipe_1==-1){
    	perror("pipe_1");
    	exit(1);
    }
    int sm_id,sm_id1;
    struct shared *s_m_ptr;
    sm_id=shmget((key_t)101,sizeof(s_m_ptr),0666|IPC_CREAT);
    s_m_ptr=(struct shared *)shmat(sm_id,NULL,0);
    if (s_m_ptr==(void *)-1){
    	perror("shmat");
    	exit(1);
    }
    s_m_ptr->b=1000;
    printf("Provide Your Input From Given Options:\n");
    printf("1. Type a to Add Money\n");
    printf("2. Type w to Withdraw Money\n");
    printf("3. Type c to Check Balance\n");
    char ip[100];
    scanf("%s",ip);
    printf("Your selection: %s\n",ip);
    strcpy(s_m_ptr->sel,ip);
    
    pid_t p1;
    p1=fork();
    if(p1<0){
    	perror("FORK");
    }
    
    else if (p1==0){
    	close(fd[0]);
    	struct shared *s_m_ptr1;
    	sm_id1=shmget((key_t)101,sizeof(s_m_ptr1),0666|IPC_CREAT);
    	s_m_ptr1=(struct shared *)shmat(sm_id1,NULL,0);
    	char store[100];
    	int mny;
    	mny=s_m_ptr1->b;
    	strcpy(store,s_m_ptr1->sel);
    	int i;
    	if (strcmp(store,"a")==0){
    		printf("Enter amount to be added:\n");
		scanf("%d", &i);
		if (i>0){
		mny+=i;
		s_m_ptr1->b=mny;
		printf("Balance added successfully\n");
		printf("Updated balance after addition:\n");
		printf("%d\n", s_m_ptr1->b);
		}
		else{
		  printf("Adding failed, Invalid ammount\n");
		  }
         }
         
         else if (strcmp(store,"w")==0){
         	printf("Enter ammount to be withdrawn:\n");
         	scanf("%d",&i);
         	if (i<=0 || i>mny){
         	  printf("Withdrawal failed, Invalid ammount\n");
		}
		
		else{
		mny-=i;
		s_m_ptr1->b=mny;
		printf("Withdrawal successful\n");
		printf("Updated balance after withdrawal:\n");
		printf("%d\n", s_m_ptr1->b);
		}
	}
	else if (strcmp(store,"c")==0){
		printf("Your current balance is:\n");
		printf("%d\n", s_m_ptr1->b);
		}
	
	else{
	    printf("Invalid selection\n");
	    }
	    
	strcpy(buff,"Thank you for using");
	write(fd[1],buff,sizeof(buff));
	close(fd[1]);
}

     else{
	int sts;
	wait(&sts);
	close(fd[1]);
	read(fd[0],buff,sizeof(buff));
	printf("%s\n",buff);
	close(fd[0]);
     }

return 0;
}
