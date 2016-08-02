#include "mylib.h"
void main()
{
	char buf[MSGLEN];
	struct sockaddr_in  addr_other;
	int sock, struct_len = sizeof(addr_other),fl=1;
	if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	{
		perror("socket");
	}
	addr_other.sin_family = AF_INET;
	addr_other.sin_port = htons(PORT);
	inet_aton(BCASTIP,&addr_other.sin_addr);
	setsockopt(sock,SOL_SOCKET,SO_BROADCAST,&fl,sizeof(int));
	while(1)
	{
		printf("ENTER MESAGE: ");
		scanf("%s",buf);
		if (sendto(sock,buf,MSGLEN,0,(struct sockaddr *)&addr_other,struct_len) == -1)
		{
			perror("sendto");
		}
	}
	close(sock);
}