#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_rwlock_t lock = PTHREAD_RWLOCK_INITIALIZER;

//if server_client.c is included in other files then it can use all the functions and variables from that file 

void *downtime(){
	sleep(1);
	pthread_rwlock_wrlock(&lock);
	Node * newroot;
	newroot = balanceTree(root);
	root = freeSubtree(root);
	root = newroot;
	pthread_rwlock_unlock(&lock);
	//TODO: 1st downtime: Do balanceTree here



	sleep(1);
	//TODO: 2nd downtime: Do balanceTree here
	pthread_rwlock_wrlock(&lock);
	newroot = balanceTree(root);
	root = freeSubtree(root);
	root = newroot;
	pthread_rwlock_unlock(&lock);
	sleep(1);


	//TODO: 3rd downtime: Do balanceTree here
	pthread_rwlock_wrlock(&lock);
	newroot = balanceTree(root);
	root = freeSubtree(root);
	root = newroot;
	pthread_rwlock_unlock(&lock);
	return NULL;
}


void* ServeClient(char *client){
	//printSubtree(root);

	FILE * fp ;
	char command [256];
	int data;

	
	fp = fopen(client,"r");
	
	
	//reading the file
	while (fscanf(fp, "%s %d",command, &data)!= EOF){
		if (strcmp(command,"insertNode")==0){
			
			pthread_rwlock_wrlock(&lock);
			root = insertNode(root, data);
			
			
			
	
			printf("[%s]insertNode %d\n", client, data);
			pthread_rwlock_unlock(&lock);
		}
		else if (strcmp(command,"deleteNode") ==0){
			//pthread_rwlock_wrlock(&lock);
			
			pthread_rwlock_wrlock(&lock);
			root = deleteNode(root,data);
			
			
			printf("[%s]deleteNode %d\n", client, data);
			pthread_rwlock_unlock(&lock);
			//pthread_rwlock_unlock(&lock);
		}
		else if (strcmp(command, "sumSubtree")==0){
			int c ;
			pthread_rwlock_rdlock(&lock);
			c =sumSubtree(root);
			
			printf("[%s]sumSubtree = %d\n", client, c);
			pthread_rwlock_unlock(&lock);
		}
		else if (strcmp(command, "countNodes")==0){
			int w;
			pthread_rwlock_rdlock(&lock);
			w =countNodes(root);
			
			printf("[%s]countNodes = %d\n", client, w);
			pthread_rwlock_unlock(&lock);
			
		}
		
		//printSubtree(root);
	}


	fclose(fp);
	

	return NULL;
}
