#include "mylib.h"
void client_process(int sock_clt)
{
	char buf[MSGLEN];
	while(1)
	{
		printf("Waiting data\n");
		if (recv(sock_clt,buf,MSGLEN,0) == -1)
		{
			perror("recv");
		}
		puts(buf);
		if (send(sock_clt,buf,MSGLEN,0) == -1)
		{
			perror("send");
		}
	}
	close(sock_clt);
}
void main()
{
	pid_t pid;
	struct sockaddr_in addr_me ,addr_other;
	int sock,struct_len = sizeof(addr_other), sock_clt;
	char buf[MSGLEN];
	if ((sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP)) == -1)
	{
		perror("Socket");
	}
	addr_me.sin_family = AF_INET;
	addr_me.sin_port = htons(PORT);
	inet_aton(IPADDR,&addr_me.sin_addr);
	if ((bind(sock,(struct sockaddr*)&addr_me,struct_len)) == -1)
	{
		perror("bind");
	}
	listen(sock,CLIENT);
	while(1)
	{
		if ((sock_clt = accept(sock,(struct sockaddr*)&addr_other,&struct_len)) == -1)
		{
			perror("accept");
		}
		pid = fork();
		if (pid == 0)
		{
			client_process(sock_clt);
		}
	}
	close(sock);
}