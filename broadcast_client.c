#include "mylib.h"
void main()
{
	struct sockaddr_in addr_me,addr_other;
	int sock ,struct_len = sizeof(addr_me);
	char buf[MSGLEN];
	if ((sock = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP)) == -1)
	{
		perror("socket");
	}
	addr_me.sin_family = AF_INET;
	addr_me.sin_port = htons(PORT);
	inet_aton(BCASTIP,&addr_me.sin_addr);
	if (bind(sock, (struct sockaddr *)&addr_me, sizeof(addr_me)) == -1)
	{
		perror("bind");
	}
	while(1)
	{
		if (recvfrom(sock,buf,MSGLEN,0,(struct sockaddr *)&addr_other,&struct_len) == -1)
		{
			perror("recvfrom");
		}
		printf("%s\n",buf);
	}
	close(sock);
}