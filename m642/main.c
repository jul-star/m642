#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h> 
#include <fcntl.h> // O_CREAT

int main (int c, char **v)
{

	int fd;
	char *addr;
	char *ptr;

	fd = shm_open("/test.shm", O_CREAT|O_RDWR, 0666);
	if (fd < 0 ) perror("open");

	int size = 1024*1024*2;

	int ftr = ftruncate(fd,size);
	if (ftr<0) 	perror("ftruncate");
	
	addr = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (addr == MAP_FAILED) perror("mmap");

	ptr = addr;
	int i;
	int mb = 1024*1024;
	for (i=0;i<mb;i++)
		*((char*)ptr+i) = 13;

	if(munmap(addr,size)<0) perror("munmap");

	if(close(fd)<0) perror("close");

	return 0;
}
