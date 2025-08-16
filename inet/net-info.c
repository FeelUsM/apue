//#include "apue.h"
#include "../apue-err.h"
#include <stdio.h>

#if defined(SOLARIS)
#include <netinet/in.h>
#endif
#include <netdb.h>
#include <arpa/inet.h>
#if defined(BSD)
#include <sys/socket.h>
#include <netinet/in.h>
#endif

void print_family(int ai_family) {
	printf(" семейство ");
	switch (ai_family) {
	case AF_INET:
		printf("inet");
	break;
	case AF_INET6:
		printf("inet6");
	break;
	case AF_UNIX:
		printf("unix");
	break;
	case AF_UNSPEC:
		printf("не определено");
	break;
	default:
		printf("неизвестно (%d)",ai_family);
	}
}
void print_type(int ai_socktype) {
	printf(" тип ");
	switch (ai_socktype) {
	case SOCK_STREAM:
		printf("stream (%d)",ai_socktype);
	break;
	case SOCK_DGRAM:
		printf("datagram (%d)",ai_socktype);
	break;
	case SOCK_SEQPACKET:
		printf("seqpacket (%d)",ai_socktype);
	break;
	case SOCK_RAW:
		printf("raw (%d)",ai_socktype);
	break;
	default:
		printf("неизвестный (%d)", ai_socktype);
	}
}
void print_protocol(int ai_protocol) {
	printf(" протокол ");
	switch (ai_protocol) {
	case 0:
		printf("по умолчанию");
	break;
	case IPPROTO_TCP:
		printf("TCP");
	break;
	case IPPROTO_UDP:
		printf("UDP");
	break;
	case IPPROTO_RAW:
		printf("raw");
	break;
	default:
		printf("неизвестный (%d)", ai_protocol);
	}
}
void print_flags(int ai_flags) {
	printf("флаги");
	if (ai_flags == 0) {
		printf(" 0");
	} else {
		if (ai_flags & AI_PASSIVE)
			printf(" passive");
		if (ai_flags & AI_CANONNAME)
			printf(" canon");
		if (ai_flags & AI_NUMERICHOST)
			printf(" numhost");
		if (ai_flags & AI_NUMERICSERV)
			printf(" numserv");
		if (ai_flags & AI_V4MAPPED)
			printf(" v4mapped");
		if (ai_flags & AI_ALL)
			printf(" all");
	}
}

void list_hosts(){
	sethostent(1);
	struct hostent * ent;
	printf("=== hosts ===\n");
	while((ent=gethostent())!=NULL){
		printf("%s [",ent->h_name); print_type(ent->h_addrtype); printf("] %d\n",ent->h_length);
		for(char ** ps = ent->h_aliases; *ps; ps++)
			printf(" '%s'",*ps);
		printf("\n");
		for(char ** ps = ent->h_addr_list; *ps; ps++)
			printf(" '%s'",*ps);
		printf("\n");
	}
	endhostent();
}
void list_nets(){
	setnetent(1);
	struct netent * ent;
	printf("=== nets ===\n");
	while((ent=getnetent())!=NULL){
		printf("%s [",ent->n_name); print_type(ent->n_addrtype); printf("] %d\n",ent->n_net);
		for(char ** ps = ent->n_aliases; *ps; ps++)
			printf(" '%s'",*ps);
		printf("\n");
	}
	endnetent();
}
void list_protocols(){
	setprotoent(1);
	struct protoent * ent;
	printf("=== protocols ===\n");
	while((ent=getprotoent())!=NULL){
		printf("%s [",ent->p_name); print_protocol(ent->p_proto); printf("] ");
		for(char ** ps = ent->p_aliases; *ps; ps++)
			printf(" '%s'",*ps);
		printf("\n");
	}
	endprotoent();
}
int addrinfo(const char * host, const char * service) {
	struct addrinfo *ailist, *aip;
	struct addrinfo hint;
	struct sockaddr_in *sinp;
	const char *addr;
	int err;
	char abuf[INET_ADDRSTRLEN];
	hint.ai_flags = AI_CANONNAME;
	hint.ai_family = 0;
	hint.ai_socktype = 0;
	hint.ai_protocol = 0;
	hint.ai_addrlen = 0;
	hint.ai_canonname = NULL;
	hint.ai_addr = NULL;
	hint.ai_next = NULL;
	if ((err = getaddrinfo(host, service, &hint, &ailist)) != 0) {
		err_msg("ошибка вызова функции getaddrinfo: %s\n", gai_strerror(err));
		return 1;
	}
	for (aip = ailist; aip != NULL; aip = aip->ai_next) {
		print_flags(aip->ai_flags);
		print_family(aip->ai_family);
		print_type(aip->ai_socktype);
		print_protocol(aip->ai_protocol);
		printf("\tхост %s", aip->ai_canonname?aip->ai_canonname:"-");
		if (aip->ai_family == AF_INET) {
			sinp = (struct sockaddr_in *)aip->ai_addr;
			addr = inet_ntop(AF_INET, &sinp->sin_addr, abuf,
			INET_ADDRSTRLEN);
			printf(" адрес %s", addr?addr:"не известен");
			printf(" порт %d", ntohs(sinp->sin_port));
		}
		printf("\n");
	}
	return 0;
}

void list_services(){
	setservent(1);
	struct servent * ent;
	printf("=== services ===\n");
	while((ent=getservent())!=NULL){
		printf("%s [%s",ent->s_name,ent->s_proto); printf(" %d] ",ent->s_port);
		for(char ** ps = ent->s_aliases; *ps; ps++)
			printf(" '%s'",*ps);
		printf("\t");
		addrinfo("localhost",ent->s_name);
	}
	endservent();
	printf("\n");
}
int main(int argc, char *argv[]) {
	if(argc==1){
		list_hosts();
		list_nets();
		list_protocols();
		list_services();
		exit(0);
	}
	if (argc != 3)
		err_quit("Использование: %s имя_узла служба", argv[0]);
	exit(addrinfo(argv[1], argv[2]));
}