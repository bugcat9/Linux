# groupadd、groupmod和groupdel命令

groupadd、groupmod和groupdel命令跟群组创建有关

## groupadd

查看一下`help`

```
[root@VM-0-12-centos ~]# groupadd --help
Usage: groupadd [options] GROUP

Options:
  -f, --force                   exit successfully if the group already exists,
                                and cancel -g if the GID is already used
  -g, --gid GID                 use GID for the new group
  -h, --help                    display this help message and exit
  -K, --key KEY=VALUE           override /etc/login.defs defaults
  -o, --non-unique              allow to create groups with duplicate
                                (non-unique) GID
  -p, --password PASSWORD       use this encrypted password for the new group
  -r, --system                  create a system account
  -R, --root CHROOT_DIR         directory to chroot into
  -P, --prefix PREFIX_DIR       directory prefix
```

`groupadd`使用起来比较简单，我们只需要简单的使用group+组名就行

```
[root@VM-0-12-centos ~]# groupadd group1
[root@VM-0-12-centos ~]# grep group1 /etc/group /etc/gshadow
/etc/group:group1:x:1001:
/etc/gshadow:group1:!::
```

## groupmod

查看一下`help`

```
[root@VM-0-12-centos ~]# groupmod --help 
Usage: groupmod [options] GROUP

Options:
  -g, --gid GID                 change the group ID to GID
  -h, --help                    display this help message and exit
  -n, --new-name NEW_GROUP      change the name to NEW_GROUP
  -o, --non-unique              allow to use a duplicate (non-unique) GID
  -p, --password PASSWORD       change the password to this (encrypted)
                                PASSWORD
  -R, --root CHROOT_DIR         directory to chroot into
  -P, --prefix PREFIX_DIR       prefix directory where are located the /etc/* files

```

简单例子修改group1 名称改为 mygroup ， GID 为 1002

```
[root@VM-0-12-centos ~]# groupmod -g 1002 -n mygroup group1 
[root@VM-0-12-centos ~]# grep mygroup /etc/group /etc/gshadow
/etc/group:mygroup:x:1002:
/etc/gshadow:mygroup:!::
```

## groupdel

查看一下`help`

```
[root@VM-0-12-centos ~]# clear
[root@VM-0-12-centos ~]# groupdel --help
Usage: groupdel [options] GROUP

Options:
  -h, --help                    display this help message and exit
  -R, --root CHROOT_DIR         directory to chroot into
  -P, --prefix PREFIX_DIR       prefix directory where are located the /etc/* files
  -f, --force                   delete group even if it is the primary group of a user
```

简单例子删除mygroup

```
[root@VM-0-12-centos ~]# groupdel mygroup 
```

不过groupdel会存在一个问题，就是删除初始群组是不会成功的

```
[root@VM-0-12-centos ~]# groupdel zhouning 
groupdel: cannot remove the primary group of user 'zhouning'
```

因为用户zhouning的初始群组是zhouning所有删除不会成功，毕竟如果删除成功了，那么zhouning登录后发现找不到GID，会有许多问题

## gpasswd

查看`help`

```
[root@VM-0-12-centos ~]# gpasswd --help
Usage: gpasswd [option] GROUP

Options:
  -a, --add USER                add USER to GROUP
  -d, --delete USER             remove USER from GROUP
  -h, --help                    display this help message and exit
  -Q, --root CHROOT_DIR         directory to chroot into
  -r, --delete-password         remove the GROUP's password
  -R, --restrict                restrict access to GROUP to its members
  -M, --members USER,...        set the list of members of GROUP
  -A, --administrators ADMIN,...
                                set the list of administrators for GROUP
Except for the -A and -M options, the options cannot be combined.
```

gpasswd是创造群管理员用的，创建群管理员之后，创建群管理员之后，就可以利用管理员对群组进行管理，添加新的成员或者踢掉老成员，可以联想qq群。使用起来比较简单，这里就不举例了。