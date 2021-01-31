# touch的作用

linux当中的文件有许多时间参数，其中最主要是三个时间参数

- **modification time (mtime)**：
  当该文件的『内容数据』变更时，就会升级这个时间！内容数据指的是文件的内容，而不是文件的属性或权限喔！
- **status time (ctime)**：
  当该文件的『状态 (status)』改变时，就会升级这个时间，举例来说，像是权限与属性被更改了，都会升级这个时间啊。
- **access time (atime)**：
  当『该文件的内容被取用』时，就会升级这个读取时间 (access)。举例来说，我们使用 cat 去读取 /etc/man.config ， 就会升级该文件的 atime 了。

当我们使用ls时，展示出的是mtime（现在是1月30号）

```
zhouning@DESKTOP-681HT7R:~$ ls -l
total 2556
-rw-r--r-- 1 zhouning zhouning      43 Jan 26 14:46 text.txt
-rw-r--r-- 1 zhouning zhouning 2611663 Jan 26 14:28 红楼梦.txt
```

那么我们该怎么查看另外两个时间呢？我们man一下ls，着重看下`-c -u --time`发现是这样显示出来的

```
       -c     with  -lt:  sort  by,  and show, ctime (time of last modification of file status information); with -l:
              show ctime and sort by name; otherwise: sort by ctime, newest first
              
              
       --time=WORD
              with  -l, show time as WORD instead of default modification time: atime or access or use (-u); ctime or
              status (-c); also use specified time as sort key if --sort=time (newest first)
              
              
       -u     with  -lt:  sort by, and show, access time; with -l: show access time and sort by name; otherwise: sort
              by access time, newest first
              
```

所以可以这样查看

```
zhouning@DESKTOP-681HT7R:~$ ll text.txt
-rw-r--r-- 1 zhouning zhouning 43 Jan 26 14:46 text.txt--------------------mtime
zhouning@DESKTOP-681HT7R:~$ ll -u text.txt
-rw-r--r-- 1 zhouning zhouning 43 Jan 29 20:14 text.txt--------------------atime
zhouning@DESKTOP-681HT7R:~$ ll -c text.txt
-rw-r--r-- 1 zhouning zhouning 43 Jan 26 14:46 text.txt--------------------ctime
```

ps:后面发现直接使用stat就可以查看

```
zhouning@DESKTOP-681HT7R:~$ stat text.txt
  File: text.txt
  Size: 43              Blocks: 8          IO Block: 4096   regular file
Device: 810h/2064d      Inode: 2479        Links: 1
Access: (0644/-rw-r--r--)  Uid: ( 1000/zhouning)   Gid: ( 1000/zhouning)
Access: 2021-01-31 19:05:30.100000000 +0800
Modify: 2021-01-31 19:04:16.780000000 +0800
Change: 2021-01-31 19:04:16.780000000 +0800
 Birth: -
```

## touch改变时间

我们熟知的是touch是创建一个空文件，但是其实touch还可以改变mtime、atime，让其变到现在这个时间(为啥我的这个ctime也发生改变奇奇怪怪)

```
zhouning@DESKTOP-681HT7R:~$ touch text.txt
zhouning@DESKTOP-681HT7R:~$ ll text.txt
-rw-r--r-- 1 zhouning zhouning 43 Jan 31 19:04 text.txt
zhouning@DESKTOP-681HT7R:~$ ll -u text.txt
-rw-r--r-- 1 zhouning zhouning 43 Jan 31 19:04 text.txt
zhouning@DESKTOP-681HT7R:~$ ll -c text.txt
-rw-r--r-- 1 zhouning zhouning 43 Jan 31 19:04 text.txt
```

除此之外touch还是使用指定时间更改文件的相关时间不用改动现在这个时间。

总之touch 这个命令最常被使用的情况是：

- 创建一个空的文件；
- 将某个文件日期修订为目前 (mtime 与 atime)

