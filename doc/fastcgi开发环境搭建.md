# fastcgi开发环境搭建

## 1.准备工作
- fcgi.tar.gz（开发库）
- spawn-fcgi-1.6.4.tar.gz（用于启动fastcgi）

将上面两个包解压在同一个目录下，比如/root/tools/nginx/下

## 2.编译fcgi

```
./configure
make
make install
```

> 在make的时候会有编译错误，是因为./include/fcgio.h中缺少头文件<stdio.h>

编译成功后，默认开发库文件会放到/usr/local/lib目录下，有可能会出现fastcgi程序找不到so文件的问题

可以将相关的so文件拷贝到/lib64下即可

```
cp /usr/local/lib/libfcgi* /lib64/
```

## 3.编译spawn-fcgi

```
./configure
make
make install
```

编译后，会在src目录下生成spawn-fcgi程序，为了使用方便，将其拷贝到nginx程序同一目录下

```
cd src
cp ./spawn-fcgi /usr/local/nginx/
```

## 4.启动fcgi

`./spawn-fcgi -p 8000 -f  /usr/local/nginx/fcgi/fcgi`

注意：

> -p 后面的端口号要和nginx启动配置文件中的端口号要一致
>
> -f 后面必须为fastcgi程序的绝对路径，否则启动会报127错误
>
> 还有如果fastcgi找不到依赖的so文件，也会报127错误