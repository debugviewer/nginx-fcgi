# nginx源码编译

## 1.准备工作
- nginx-1.13.7.tar.gz
- pcre-8.41.tar.gz
- openssl-1.1.0g.tar.gz
- zlib-1.2.11.tar.gz

将上面四个包解压在同一个目录下，比如/root/tools/nginx/下

进入nginx-1.13.7目录下依次执行

## 2.编译

```
./configure --prefix=/usr/local/nginx --with-http_realip_module --with-http_addition_module --with-http_gzip_static_module --with-http_secure_link_module --with-http_stub_status_module --with-stream --with-pcre=/root/tools/nginx/pcre-8.41 --with-zlib=/root/tools/nginx/zlib-1.2.11 --with-openssl=/root/tools/nginx/openssl-1.1.0g

make

make install
```

编译成功后，会在/usr/local/nginx下生成几个目录

- conf  配置文件
- html  静态网页
- sbin  主程序
- logs  日志

查看nginx版本信息：

```
cd ./sbin
./nginx -v
nginx version: nginx/1.13.7
```

## 3.运行nginx

```
cd ./sbin
./nginx -c ../conf/nginx.conf
```

查看nginx是否启动成功，可以用以下命令:

`ps -aux | grep nginx`

如果知道nginx启动的端口号，比如8080端口：

`netstat -anop | grep 8080`

