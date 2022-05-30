# fuser命令

fuser可以显示出当前哪个程序在使用磁盘上的某个文件、挂载点、甚至网络端口，并给出程序进程的详细信息。

fuser显示使用指定文件或者文件系统的进程ID。

## 参数

```
[root@VM-0-12-centos ~]# fuser --help
fuser: Invalid option --help
Usage: fuser [-fIMuvw] [-a|-s] [-4|-6] [-c|-m|-n SPACE]
             [-k [-i] [-SIGNAL]] NAME...
       fuser -l
       fuser -V
Show which processes use the named files, sockets, or filesystems.

  -a,--all              display unused files too
  -i,--interactive      ask before killing (ignored without -k)
  -I,--inode            use always inodes to compare files
  -k,--kill             kill processes accessing the named file
  -l,--list-signals     list available signal names
  -m,--mount            show all processes using the named filesystems or
                        block device
  -M,--ismountpoint     fulfill request only if NAME is a mount point
  -n,--namespace SPACE  search in this name space (file, udp, or tcp)
  -s,--silent           silent operation
  -SIGNAL               send this signal instead of SIGKILL
  -u,--user             display user IDs
  -v,--verbose          verbose output
  -w,--writeonly        kill only processes with write access
  -V,--version          display version information
  -4,--ipv4             search IPv4 sockets only
  -6,--ipv6             search IPv6 sockets only
  -                     reset options

  udp/tcp names: [local_port][,[rmt_host][,[rmt_port]]]

```

## 例子

找出当前目录使用 pid、所属账号等

```
[root@VM-0-12-centos ~]# fuser -uv .
                     USER        PID ACCESS COMMAND
/root:               root      2403080 ..c.. (root)bash
```

看到输出的结果没？他说『.』底下有个 PID 为 2403080的程序，该程序属於 root 且命令为 bash 。 比较有趣的是那个 ACCESS 的项目，那个项目代表的意义为：

- c ：此程序在当前的目录下(非次目录)；
- e ：可被触发为运行状态；
- f ：是一个被开启的文件；
- r ：代表顶层目录 (root directory)；
- F ：该文件被开启了，不过在等待回应中；
- m ：可能为分享的动态函式库；

查阅某个文件系统底下有多少程序正在占用该文件系统时

```
[root@VM-0-12-centos ~]# fuser -mvu  .
                     USER        PID ACCESS COMMAND
/root:               root     kernel mount (root)/
                     root          1 .rce. (root)systemd
                     root          2 .rc.. (root)kthreadd
                     root          3 .rc.. (root)rcu_gp
                     root          4 .rc.. (root)rcu_par_gp
                     root          6 .rc.. (root)kworker/0:0H-kbl
                     root          8 .rc.. (root)mm_percpu_wq
                     root          9 .rc.. (root)ksoftirqd/0
                     root         10 .rc.. (root)rcu_sched
                     root         11 .rc.. (root)migration/0
                     。。。。省略
```

找出端口被占用

```
[root@VM-0-12-centos ~]# fuser -v -u -n tcp 22
                     USER        PID ACCESS COMMAND
22/tcp:              root       1726 F.... (root)sshd
                     root      2403061 F.... (root)sshd
                     root      2403079 F.... (root)sshd
```

