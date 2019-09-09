//gcc -o fcgi fcgi.c -lfcgi
#include <fcgi_stdio.h>
#include <stdlib.h>
#include<stdio.h>

int getUserList() {
	FILE *fp = NULL;
	char data[100] = {'0'};
	fp = popen("ls /home", "r");
	if (fp == NULL)
	{
		FCGI_printf("popen error!\n");
		return 1;
	}
	while (fgets(data, sizeof(data), fp) != NULL)
	{
		FCGI_printf("%s", data);
	}
	pclose(fp);
	return 0;
}

int main() {
    unsigned int req_count = 0;

    while(FCGI_Accept() >= 0) {
        FCGI_printf("Content-type: text/html\r\n\r\n");
        FCGI_printf("<title>Hello World!</title>"
            "<h1>Hello World!</h1>");
        FCGI_printf("<h2>request times: %u</h2>", ++req_count);
        FCGI_printf("QUERY_STRING: %s</br>", getenv("QUERY_STRING"));
        FCGI_printf("REMOTE_ADDR: %s</br>", getenv("REMOTE_ADDR"));
		getUserList();
    }   

    return 0;
}