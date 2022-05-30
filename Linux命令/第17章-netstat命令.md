# netstat命令

netstat命令主要用于网络监控

参数查看

```
[root@VM-0-12-centos ~]# netstat --help
usage: netstat [-vWeenNcCF] [<Af>] -r         netstat {-V|--version|-h|--help}
       netstat [-vWnNcaeol] [<Socket> ...]
       netstat { [-vWeenNac] -I[<Iface>] | [-veenNac] -i | [-cnNe] -M | -s [-6tuw] } [delay]

        -r, --route              display routing table
        -I, --interfaces=<Iface> display interface table for <Iface>
        -i, --interfaces         display interface table
        -g, --groups             display multicast group memberships
        -s, --statistics         display networking statistics (like SNMP)
        -M, --masquerade         display masqueraded connections

        -v, --verbose            be verbose
        -W, --wide               don't truncate IP addresses
        -n, --numeric            don't resolve names
        --numeric-hosts          don't resolve host names
        --numeric-ports          don't resolve port names
        --numeric-users          don't resolve user names
        -N, --symbolic           resolve hardware names
        -e, --extend             display other/more information
        -p, --programs           display PID/Program name for sockets
        -o, --timers             display timers
        -c, --continuous         continuous listing

        -l, --listening          display listening server sockets
        -a, --all                display all sockets (default: connected)
        -F, --fib                display Forwarding Information Base (default)
        -C, --cache              display routing cache instead of FIB
        -Z, --context            display SELinux security context for sockets

  <Socket>={-t|--tcp} {-u|--udp} {-U|--udplite} {-S|--sctp} {-w|--raw}
           {-x|--unix} --ax25 --ipx --netrom
  <AF>=Use '-6|-4' or '-A <af>' or '--<af>'; default: inet
  List of possible address families (which support routing):
    inet (DARPA Internet) inet6 (IPv6) ax25 (AMPR AX.25) 
    netrom (AMPR NET/ROM) ipx (Novell IPX) ddp (Appletalk DDP) 
    x25 (CCITT X.25) 
```

参数还是挺多的

简单使用

```
[root@VM-0-12-centos ~]# netstat 
Active Internet connections (w/o servers)
Proto Recv-Q Send-Q Local Address           Foreign Address         State      
tcp        0     36 VM-0-12-centos:ssh      59.37.125.34:13590      ESTABLISHED
tcp        0      0 VM-0-12-centos:43066    169.254.0.55:lsi-bobcat ESTABLISHED
udp        0      0 VM-0-12-centos:bootpc   _gateway:bootps         ESTABLISHED
Active UNIX domain sockets (w/o servers)
Proto RefCnt Flags       Type       State         I-Node   Path
unix  2      [ ]         DGRAM                    12118825 /run/user/0/systemd/notify
unix  3      [ ]         DGRAM                    11108    /run/systemd/notify
unix  2      [ ]         DGRAM                    17509    /var/run/chrony/chronyd.sock
unix  2      [ ]         DGRAM                    11110    /run/systemd/cgroups-agent
。。。省略
```

在上面的结果当中，显示了两个部分，分别是网络的连线以及 linux 上面的 socket 程序相关性部分。 我们先来看看网际网络连线情况的部分：

- Proto ：网络的封包协议，主要分为 TCP 与 UDP 封包
- Recv-Q：非由使用者程序连结到此 socket 的复制的总 bytes 数；
- Send-Q：非由远程主机传送过来的 acknowledged 总 bytes 数；
- Local Address ：本地端的 IP:port 情况
- Foreign Address：远程主机的 IP:port 情况
- State ：连线状态，主要有创建(ESTABLISED)及监听(LISTEN)；

我们可以看到有一个ssh链接，通过外来地址连接过来

除了网络上的连线之外，其实 Linux 系统上面的程序是可以接收不同程序所发送来的资讯，那就是 Linux 上头的插槽档 (socket file)。我们在[第六章的文件种类](http://cn.linux.vbird.org/linux_basic/0210filepermission.php#filepermission_type)有稍微提到 socket 文件， 但当时未谈到程序的概念，所以没有深入谈论。socket file 可以沟通两个程序之间的资讯，因此程序可以取得对方传送过来的数据。 由於有 socket file，因此类似 X Window 这种需要透过网络连接的软件，目前新版的 distributions 就以 socket 来进行窗口介面的连线沟通了。上表中 socket file 的输出栏位有：

- Proto ：一般就是 unix 啦；
- RefCnt：连接到此 socket 的程序数量；
- Flags ：连线的旗标；
- Type ：socket 存取的类型。主要有确认连线的 STREAM 与不需确认的 DGRAM 两种；
- State ：若为 CONNECTED 表示多个程序之间已经连线创建。
- Path ：连接到此 socket 的相关程序的路径！或者是相关数据输出的路径。

查看tcp的端口或者进程详情

```
[root@VM-0-12-centos ~]# netstat -tlnp
Active Internet connections (only servers)
Proto Recv-Q Send-Q Local Address           Foreign Address         State       PID/Program name    
tcp        0      0 0.0.0.0:5355            0.0.0.0:*               LISTEN      1043/systemd-resolv 
tcp        0      0 0.0.0.0:22              0.0.0.0:*               LISTEN      1726/sshd           
tcp6       0      0 :::5355                 :::*                    LISTEN      1043/systemd-resolv 
```

如果要查找相应的端口我们可以使用grep进行配合

```
[root@VM-0-12-centos ~]# netstat -tlnp | grep 22
tcp        0      0 0.0.0.0:22              0.0.0.0:*               LISTEN      1726/sshd 
```

这样就很容易找到被占用的端口并且杀死该进程