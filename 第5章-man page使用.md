# man page使用

命令不会找男人（man）

## 文档总体介绍

以date的文档为介绍总体

```
DATE(1)                          User Commands                         DATE(1) 
# 请注意上面这个括号内的数字 
NAME  <==这个命令的完整全名，如下所示为date且说明简单用途为配置与显示日期/时间 
       date - print or set the system date and time 
 
SYNOPSIS  <==这个命令的基本语法如下所示 
       date [OPTION]... [+FORMAT] 
       date [-u|--utc|--universal] [MMDDhhmm[[CC]YY][.ss]] 
 
DESCRIPTION  <==详细说明刚刚语法谈到的选项与参数的用法 
       Display  the  current  time  in  the given FORMAT, or set the system 
       date. 
 
       -d, --date=STRING  <==左边-d为短选项名称，右边--date为完整选项名称 
              display time described by STRING, not 'now' 
 
       -f, --file=DATEFILE 
              like --date once for each line of DATEFILE 
 
       -r, --reference=FILE 
              display the last modification time of FILE 
....(中间省略).... 
       # 找到了！底下就是格式化输出的详细数据！ 
       FORMAT controls the output.  The only valid option  for  the  second 
       form  specifies  Coordinated  Universal Time.  Interpreted sequences 
       are: 
 
       %%     a literal % 
 
       %a     locale's abbreviated weekday name (e.g., Sun) 
 
       %A     locale's full weekday name (e.g., Sunday) 
....(中间省略).... 
ENVIRONMENT  <==与这个命令相关的环境参数有如下的说明 
       TZ     Specifies the timezone, unless  overridden  by  command  line 
              parameters.   If  neither  is  specified,  the  setting  from 
              /etc/localtime is used. 
 
AUTHOR  <==这个命令的作者啦！ 
       Written by David MacKenzie. 
 
REPORTING BUGS  <==有问题请留言给底下的email的意思！ 
       Report bugs to <bug-coreutils@gnu.org>. 
 
COPYRIGHT  <==受到著作权法的保护！用的就是 GPL 了！ 
       Copyright ? 2006 Free Software Foundation, Inc. 
       This is free software.  You may redistribute copies of it under  the 
       terms      of      the      GNU      General      Public     License 
       <http://www.gnu.org/licenses/gpl.html>.  There is  NO  WARRANTY,  to 
       the extent permitted by law. 
 
SEE ALSO  <==这个重要，你还可以从哪里查到与date相关的说明文件之意 
       The  full  documentation for date is maintained as a Texinfo manual. 
       If the info and date programs are properly installed at  your  site, 
       the command 
 
              info date 
 
       should give you access to the complete manual. 
 
date 5.97                          May 2006                            DATE(1)
```

man page 页面第一行的DATE(1) 的意义

| 代号 | 代表内容                                                     |
| ---- | ------------------------------------------------------------ |
| 1    | **使用者在shell环境中可以操作的命令或可运行文件**            |
| 2    | 系统核心可呼叫的函数与工具等                                 |
| 3    | 一些常用的函数(function)与函式库(library)，大部分为C的函式库(libc) |
| 4    | 装置文件的说明，通常在/dev下的文件                           |
| 5    | **配置文件或者是某些文件的格式**                             |
| 6    | 游戏(games)                                                  |
| 7    | 惯例与协议等，例如Linux文件系统、网络协议、ASCII code等等的说明 |
| 8    | **系统管理员可用的管理命令**                                 |
| 9    | 跟kernel有关的文件                                           |

其中1, 5, 8这三个号码特别重要

man page 中的内容的几部分

| 代号        | 内容说明                                                     |
| ----------- | ------------------------------------------------------------ |
| NAME        | 简短的命令、数据名称说明                                     |
| SYNOPSIS    | 简短的命令下达语法(syntax)简介                               |
| DESCRIPTION | 较为完整的说明，这部分最好仔细看看！                         |
| OPTIONS     | 针对 SYNOPSIS 部分中，有列举的所有可用的选项说明             |
| COMMANDS    | 当这个程序(软件)在运行的时候，可以在此程序(软件)中下达的命令 |
| FILES       | 这个程序或数据所使用或参考或连结到的某些文件                 |
| SEE ALSO    | 可以参考的，跟这个命令或数据有相关的其他说明！               |
| EXAMPLE     | 一些可以参考的范例                                           |
| BUGS        | 是否有相关的臭虫！                                           |

有时候除了这些外，还可能会看到Authors与Copyright等，不过也有很多时候仅有NAME与DESCRIPTION等部分。

ps：通过上面我们知道数字的含义，以及各个段落的含义，我们能够知道date(1)大致的作用以及用法

## 查找特定命令

### 特定搜索：

```
man -f [命令]
```

eg：

查找出man命令，可以看到相关的有两个

```sh
zhouning@DESKTOP-681HT7R:~$ man -f man
man (1)              - an interface to the on-line reference manuals
man (7)              - macros to format man pages
```

这样就引起了我的好奇，为啥`man man`命令都是显示`man(1)`不显示其他的呢？后来在网上查到man在没有指定板块时，将使用一种默认的顺序查找这些板块中的命令，只返回含有该命令的第一个文档。当指定板块时，只从该板块中查找。所以，当我们man得不到想要的文档时，就要给出板块号了。

### 模糊搜索：

```
man -k [命令]
```

eg：

查找出带`man`的命令

```
zhouning@DESKTOP-681HT7R:~$ man -k man
accessdb (8)         - dumps the content of a man-db database in a human readable format
add_key (2)          - add a key to the kernel's key management facility
apropos (1)          - search the manual page names and descriptions
apt (8)              - command-line interface
apt-cdrom (8)        - APT CD-ROM management utility
apt-get (8)          - APT package handling utility - - command-line interface
apt-key (8)          - APT key management utility
arp (8)              - manipulate the system ARP cache
bash-builtins (7)    - bash built-in commands, see bash(1)
blockdev (8)         - call block device ioctls from the command line
。。。。下面省略
```



## 更多例子

上面使用鸟哥私房菜的内容讲解了一下数字和段落的含义，但是其实看起来还是懵懵懂懂的，下面使用mkdir举一个简单的例子。

首先我们使用特定查找，查找下mkdir有几种

```
zhouning@DESKTOP-681HT7R:~$ man -f mkdir
mkdir (1)            - make directories
mkdir (2)            - create a directory
```

可以看到有两个`mkdir`,结合前面文档总体的介绍，知道了`mkdir`有两种，一个是shell环境中可以使用的命令或者文件，一个是系统核心可以呼叫和调用的函数。

### `man 1 mkdir`

我们查看第一个，使用命令`man 1 mkdir`,得到

```
MKDIR(1)                                                                              User Commands                                                                             MKDIR(1)

NAME
       mkdir - make directories

SYNOPSIS
       mkdir [OPTION]... DIRECTORY...

DESCRIPTION
       Create the DIRECTORY(ies), if they do not already exist.

       Mandatory arguments to long options are mandatory for short options too.

       -m, --mode=MODE
              set file mode (as in chmod), not a=rwx - umask

       -p, --parents
              no error if existing, make parent directories as needed

       -v, --verbose
              print a message for each created directory

       -Z     set SELinux security context of each created directory to the default type

       --context[=CTX]
              like -Z, or if CTX is specified then set the SELinux or SMACK security context to CTX

       --help display this help and exit

       --version
              output version information and exit

AUTHOR
       Written by David MacKenzie.

REPORTING BUGS
       GNU coreutils online help: <http://www.gnu.org/software/coreutils/>
       Report mkdir translation bugs to <http://translationproject.org/team/>

COPYRIGHT
       Copyright © 2017 Free Software Foundation, Inc.  License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>.
       This is free software: you are free to change and redistribute it.  There is NO WARRANTY, to the extent permitted by law.

SEE ALSO
       mkdir(2)

       Full documentation at: <http://www.gnu.org/software/coreutils/mkdir>
       or available locally via: info '(coreutils) mkdir invocation'
GNU coreutils 8.28                                                                    January 2018                                                                              MKDIR(1)
```

首先看name

```
NAME
       mkdir - make directories
```

知道了是创建文件夹

再看SYNOPSIS

```
SYNOPSIS
       mkdir [OPTION]... DIRECTORY...
```

mkdir后面加可可选的命令，然后接DIRECTORY，看`.... DIRECTORY.....`知道DIRECTORY可以多个

最好看DESCRIPTION

```
DESCRIPTION
       Create the DIRECTORY(ies), if they do not already exist.

       Mandatory arguments to long options are mandatory for short options too.

       -m, --mode=MODE
              set file mode (as in chmod), not a=rwx - umask

       -p, --parents
              no error if existing, make parent directories as needed

       -v, --verbose
              print a message for each created directory

       -Z     set SELinux security context of each created directory to the default type

       --context[=CTX]
              like -Z, or if CTX is specified then set the SELinux or SMACK security context to CTX

       --help display this help and exit

       --version
              output version information and exit
```

前面两句话翻译一下就是`如果目录不存在，则创建目录。长选项的强制性参数对于短选项也是必需的`

然后看了一下后面的内容应该是[OPTION]相关内容

所以我尝试了一下最简单的help

```
zhouning@DESKTOP-681HT7R:~$ mkdir --help
Usage: mkdir [OPTION]... DIRECTORY...
Create the DIRECTORY(ies), if they do not already exist.

Mandatory arguments to long options are mandatory for short options too.
  -m, --mode=MODE   set file mode (as in chmod), not a=rwx - umask
  -p, --parents     no error if existing, make parent directories as needed
  -v, --verbose     print a message for each created directory
  -Z                   set SELinux security context of each created directory
                         to the default type
      --context[=CTX]  like -Z, or if CTX is specified then set the SELinux
                         or SMACK security context to CTX
      --help     display this help and exit
      --version  output version information and exit

GNU coreutils online help: <http://www.gnu.org/software/coreutils/>
Report mkdir translation bugs to <http://translationproject.org/team/>
Full documentation at: <http://www.gnu.org/software/coreutils/mkdir>
or available locally via: info '(coreutils) mkdir invocation'
```

嗯，跟文档内容相似

### `man 2 mkdir`

我们查看第二个，使用命令`man 2 mkdir`,得到

```
MKDIR(2)                                                                        Linux Programmer's Manual                                                                       MKDIR(2)

NAME
       mkdir, mkdirat - create a directory

SYNOPSIS
       #include <sys/stat.h>
       #include <sys/types.h>

       int mkdir(const char *pathname, mode_t mode);

       #include <fcntl.h>           /* Definition of AT_* constants */
       #include <sys/stat.h>

       int mkdirat(int dirfd, const char *pathname, mode_t mode);

   Feature Test Macro Requirements for glibc (see feature_test_macros(7)):

       mkdirat():
           Since glibc 2.10:
               _POSIX_C_SOURCE >= 200809L
           Before glibc 2.10:
               _ATFILE_SOURCE

DESCRIPTION
       mkdir() attempts to create a directory named pathname.

       The  argument mode specifies the mode for the new directory (see inode(7)).  It is modified by the process's umask in the usual way: in the absence of a default ACL, the mode of
       the created directory is (mode & ~umask & 0777).  Whether other mode bits are honored for the created directory depends on the operating system.  For Linux, see NOTES below.

       The newly created directory will be owned by the effective user ID of the process.  If the directory containing the file has the set-group-ID bit set, or if  the  filesystem  is
       mounted  with  BSD group semantics (mount -o bsdgroups or, synonymously mount -o grpid), the new directory will inherit the group ownership from its parent; otherwise it will be
       owned by the effective group ID of the process.

       If the parent directory has the set-group-ID bit set, then so will the newly created directory.

   mkdirat()
       The mkdirat() system call operates in exactly the same way as mkdir(), except for the differences described here.

       If the pathname given in pathname is relative, then it is interpreted relative to the directory referred to by the file descriptor dirfd (rather than  relative  to  the  current
       working directory of the calling process, as is done by mkdir() for a relative pathname).

       If pathname is relative and dirfd is the special value AT_FDCWD, then pathname is interpreted relative to the current working directory of the calling process (like mkdir()).

       If pathname is absolute, then dirfd is ignored.

       See openat(2) for an explanation of the need for mkdirat().
RETURN VALUE
       mkdir() and mkdirat() return zero on success, or -1 if an error occurred (in which case, errno is set appropriately).
。。。。下面省略
```

2类型是系统核心可以呼叫的函数和工具，从这SYNOPSIS当中的代码看出，然后还看到返回值，基本上也可以猜到，调用这个函数会创建文件夹，然后返回0是创建成功返回-1创建失败。



## 小结

man命令还是挺好用的，我觉得程序员学会看文档是一个能力，所以为了学man还是花了一些小时间，不过物超所值。

## 参考

* http://cn.linux.vbird.org/linux_basic/0160startlinux_3.php
* https://blog.csdn.net/ac_dao_di/article/details/54718710
* https://zhuanlan.zhihu.com/p/73569548