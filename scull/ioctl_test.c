#include <sys/ioctl.h>	/* ioctl */
#include <fcntl.h>	/* open */	
#include <unistd.h>	/* exit */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define SCULL_IOC_MAGIC 'k'
#define SCULL_IOCTQUANTUM _IO(SCULL_IOC_MAGIC, 3)
#define SCULL_IOCSQUANTUM _IOW(SCULL_IOC_MAGIC, 1, int)
#define SCULL_IOCQQUANTUM _IO(SCULL_IOC_MAGIC, 7)
#define SCULL_IOCGQUANTUM _IOR(SCULL_IOC_MAGIC, 5, int)

#define SCULL_SET_QUANTUM 3000
#define SCULL_TELL_QUANTUM 4000

extern int errno;

int main()
{
	int fp = open("/dev/scull0", O_RDWR);
	if (fp < 0)
	{
		printf("Opening device file failed with error: %s\n", strerror(errno));
	/*	return fp;*/
	}
	int tell_quantum = SCULL_TELL_QUANTUM, set_quantum = SCULL_SET_QUANTUM, get_quantum, query_quantum;
	int res_t_quantum = ioctl(fp, SCULL_IOCTQUANTUM, tell_quantum); 	/* Just set scull_quantum variable in kernel module for scull to quantum value. */
	if (res_t_quantum < 0)	 printf("Error in telling scull for quantum with %s\n", strerror(errno));
	int res_s_quantum = ioctl(fp, SCULL_IOCSQUANTUM, &set_quantum);	/* Just set scull_quantum variable in kernel module for scull to value pointed by quantum_pr */
	if (res_s_quantum < 0)	 printf("Error in setting scull for quantum with %s\n", strerror(errno));
	int res_q_quantum = query_quantum = ioctl(fp, SCULL_IOCQQUANTUM);		/* Just get scull_quantum */ 
	if (res_q_quantum < 0)	 printf("Error in quering scull for quantum with %s\n", strerror(errno));
	else	printf("Response from query: %i\n", query_quantum );
	int res_g_quantum = ioctl(fp, SCULL_IOCGQUANTUM, &get_quantum);
	if (res_g_quantum < 0) 	printf("Error in getting scull for quantum with %s\n", strerror(errno));
	else 	printf("Response from get: %i\n", get_quantum);
	exit(0);
}
