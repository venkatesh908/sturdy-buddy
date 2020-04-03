#include<pthread.h>
#include<stdio.h>
int res_available=100;
pthread_mutex_t l;
void* increment_resources(int count){
	pthread_mutex_lock(&l);
	int x;
	x=res_available;
	x=x+count;
	sleep(1);
	res_available=x;
	printf("Resources released :) \n\n");
	pthread_mutex_unlock(&l);
}
void* decrement_resources(int count){
	if(res_available<count) printf("No resources available :( \n\n");
	else{
		pthread_mutex_lock(&l);
		int x;
		x=res_available;
		x=x-count;
		sleep(1);
		res_available=x;
		printf("Resources allocated :) \n\n");
		pthread_mutex_unlock(&l);
	}
}
int main(){
	pthread_mutex_init(&l, NULL);
    pthread_t inc_thread,dec_thread;
    while(1){
    	 int inc_res,dec_res;
         printf("Enter inc resources and decrement resources\n");
         scanf("%d %d",&inc_res,&dec_res);
	     pthread_create(&inc_thread,NULL,increment_resources,inc_res);
         pthread_create(&dec_thread,NULL,decrement_resources,dec_res);
	     pthread_join(inc_thread, NULL);
         pthread_join(dec_thread,NULL);
	     printf("Resources Available -> %d \n\n",res_available);
	}
}
