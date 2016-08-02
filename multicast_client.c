#include "mylib.h"
void main()
{
	struct sockaddr_in addr_me, addr_other;
	struct ip_mreq mreq;
	int sock ,struct_len = sizeof(addr_me);
	char buf[MSGLEN];
	if ((sock = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP)) == -1)
	{
		perror("socket");
	}
	addr_me.sin_family = AF_INET;
	addr_me.sin_port = htons(PORT);
	addr_me.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (struct sockaddr *)&addr_me, sizeof(addr_me)) == -1)
	{
		perror("bind");
	}
	memset(&mreq,0,sizeof(mreq));
	inet_aton(MCASTIP,&mreq.imr_multiaddr);
	mreq.imr_interface.s_addr = htonl(INADDR_ANY);
	setsockopt(sock,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq));
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