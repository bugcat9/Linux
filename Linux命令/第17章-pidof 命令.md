# **pidof** 命令

pidof主要用于找出某支正在运行的程序的 PID

## 介绍

```
[root@VM-0-12-centos ~]# pidof --help

Usage:
 pidof [options] [program [...]]

Options:
 -s, --single-shot         return one PID only
 -c, --check-root          omit processes with different root
 -x                        also find shells running the named scripts
 -o, --omit-pid <PID,...>  omit processes with PID
 -S, --separator SEP       use SEP as separator put between PIDs
 -h, --help     display this help and exit
 -V, --version  output version information and exit

For more details see pidof(1).

```

简单使用

```
[root@VM-0-12-centos ~]# pidof sshd
2608808 2608794 1726
```

