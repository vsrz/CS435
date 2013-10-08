#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define SEMKEY ("test")


/* Function prototypes */
 
static void sig_handler( int );


int semid;

int main(int argc ,char *argv[])
{

	struct sembuf  sops;


	int	i, j;

	signal(SIGUSR1, sig_handler);

	if ((semid = semget(ftok(SEMKEY, 1), 1, 0664 | IPC_CREAT)) == -1) {
		printf("Error:: semget errno #%d (%s) \n", errno,
			strerror(errno));
		exit(-1);
	}

	sops.sem_num = 0;
        sops.sem_op = -1;
        sops.sem_flg = SEM_UNDO;


	while (semop(semid, &sops, 1) != 0 && errno == EINTR);

	printf("Semaphore 0x%x available \n", semid); 

	if (semctl(semid, 0, IPC_RMID) == -1)  {
		printf("Error:: semctl() -- errno #%d (%s) \n",
			errno, strerror(errno));
		exit(-1);
	}


	exit(0);
}

static void sig_handler(int signo)
{

	struct sembuf  sops;

	sops.sem_num = 0;
        sops.sem_op = 1;
        sops.sem_flg = SEM_UNDO;

	printf("received signal #%d \n", signo);
	if (semop(semid, &sops, 1) == -1) {
		printf("Error:: semop() -- errno #%d (%s) \n",
			errno, strerror(errno));
		exit(-1);
	}
}

