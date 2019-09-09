# nginx下fastcgi开发之hello world

## 1.准备工作

### 1.1 [nginx源码编译](./doc/nginx源码编译.md)

### 1.2 [fastcgi开发环境搭建](./doc/fastcgi开发环境搭建.md)

## 2.编写配置文件

```
cd /usr/local/nginx/conf
vim fcgi.conf
```

fcgi.conf文件：

```
worker_processes  1;

#pid        logs/nginx.pid;

events {
    worker_connections  1024;
}

http {
    server {
        listen       80;
        server_name  localhost;

        location / {
            root   html;
            index  index.html index.htm;
        }

		location /fcgi {
			fastcgi_pass 127.0.0.1:8000; 
			fastcgi_index index.cgi;
			include fastcgi.conf;
		}
    }
}
```

## 3. 源代码

```
cd /usr/local/nginx
mkdir fcgi
cd fcgi
vim /fcgi.c
```

fcgi.c文件：

```
#include <fcgi_stdio.h>
#include <stdlib.h>
#include<stdio.h>

int getUserList() {
	FILE *fp = NULL;
	char data[200] = {'0'};
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
```

## 4.编译

```
gcc -o fcgi fcgi.c -lfcgi
```

## 5.启动fcgi

```
cd /usr/local/nginx/sbin
./spawn-fcgi -p 8000 -f /usr/local/nginx/fcgi/fcgi
```

启动成功提示：

`spawn-fcgi: child spawned successfully: PID: 24367`

## 6.启动nginx

cd /usr/local/nginx/sbin
./nginx -c ../conf/fcgi.conf

## 7.浏览器测试

地址栏输入：192.168.31.235/fcgi，回车

**Hello World!**

**request times: 1**

QUERY_STRING: 

REMOTE_ADDR: 192.168.31.228

mysql zm

验证结果：

```
ls /home
mysql  zm
```

