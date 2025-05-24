#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <sys/wait.h>
struct message {
    long type;
    char txt[6];
};

void mail(int message_queue);
void otp(int message_queue);
void login(int message_queue);

int main(){
    int q_id;
    int otp_id;
    q_id=msgget(IPC_PRIVATE,0666|IPC_CREAT);
    if (q_id==-1){
    perror("Queue Failed");
    exit(1);
    }
    
    otp_id=fork();
    if(otp_id<0){
    perror("Fork failed for OTP");
    exit(1);
    }
    
    else if (otp_id==0){
    	otp(q_id);
    	exit(0);
    }
    
    else{
    	login(q_id);
    	wait(NULL);
    	msgctl(q_id,IPC_RMID,NULL);
    }
    
    return 0;
 }
 
 void login(int message_queue){
 	struct message msg;
 	char ws[200];
 	printf("Enter workspace name:\n");
 	fgets(ws,sizeof(ws),stdin);
 	strtok(ws,"\n");
 	
 	if (strcmp(ws,"cse321")!=0){
 	   printf("Invalid workspace name\n");
 	   exit(1);
 	}
 	msg.type=2;
 	strcpy(msg.txt,ws);
 	if (msgsnd(message_queue,&msg,sizeof(msg.txt),0)==-1){
 	    perror("Failed to send workspace name");
 	    exit(1);
 	}
 	printf("OTP generator received workspace name from log in: %s\n",msg.txt);
 	
 	if (msgrcv(message_queue,&msg, sizeof(msg.txt),3,0)==-1){
 	   perror("Failed to receive OTP");
 	   exit(1);
 	}
 	printf("OTP sent to log in from mail: %s\n", msg.txt);
 	char otp_from_otp[6];
 	strcpy(otp_from_otp,msg.txt);
 	
 	if (msgrcv(message_queue,&msg, sizeof(msg.txt),5,0)==-1){
 	   perror("Failed to receive OTP from E-mail");
 	   exit(1);
 	} 	
 	
 	printf("Login received OTP from mail: %s\n", msg.txt);
 	
 	if (strcmp(otp_from_otp, msg.txt) == 0) {
        printf("OTP Verified\n");
        } 
        else {
        printf("OTP Incorrect\n");
        }
}
void otp(int message_queue) {
     pid_t mail_id;
     struct message msg;
     if (msgrcv(message_queue, &msg, sizeof(msg.txt), 2, 0) == -1) {
        perror("Failed to receive workspace");
        exit(1);
     }
     printf("OTP received workspace from login: %s\n",msg.txt);
     
     pid_t otp_id;
     otp_id=getpid();
     sprintf(msg.txt, "%d", otp_id);
     msg.type=3;
     if (msgsnd(message_queue, &msg, sizeof(msg.txt), 0) == -1) {
        perror("Failed to send OTP to login");
        exit(1);
    }
    printf("OTP sent to log in from OTP generator: %s\n", msg.txt);
    
    mail_id=fork();
    if (mail_id<0){
       perror("Mail fork failed");
       exit(1);
    }
    
    else if (mail_id==0){
        mail(message_queue);
        exit(0);
    }
    
    else{
        msg.type=4;
        if (msgsnd(message_queue, &msg, sizeof(msg.txt), 0) == -1) {
            perror("Failed to send OTP to mail");
            exit(1);
        }
        printf("OTP sent to mail from OTP generator %s\n",msg.txt);
        
        wait(NULL);
    }
}

void mail(int message_queue){
     struct message msg;
     if (msgrcv(message_queue, &msg, sizeof(msg.txt), 4, 0) == -1) {
        perror("Failed to receive OTP from OTP");
        exit(1);
    }
    printf("Mail received OTP from OTP generator: %s\n", msg.txt);
    msg.type = 5;
    if (msgsnd(message_queue, &msg, sizeof(msg.txt), 0) == -1) {
        perror("Failed to send OTP to login");
        exit(1);
    }
    printf("Log in received OTP from OTP generator: %s\n", msg.txt);
}
