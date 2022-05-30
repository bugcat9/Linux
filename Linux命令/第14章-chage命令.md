# chage命令

## 简单说明

查看了一下`--help`

```
[root@VM-0-12-centos ~]# chage --help
Usage: chage [options] LOGIN

Options:
  -d, --lastday LAST_DAY        set date of last password change to LAST_DAY
  -E, --expiredate EXPIRE_DATE  set account expiration date to EXPIRE_DATE
  -h, --help                    display this help message and exit
  -I, --inactive INACTIVE       set password inactive after expiration
                                to INACTIVE
  -l, --list                    show account aging information
  -m, --mindays MIN_DAYS        set minimum number of days before password
                                change to MIN_DAYS
  -M, --maxdays MAX_DAYS        set maximum number of days before password
                                change to MAX_DAYS
  -R, --root CHROOT_DIR         directory to chroot into
  -W, --warndays WARN_DAYS      set expiration warning days to WARN_DAYS
```

光看一下help就知道这个命令比较简单了，虽然不是中文的

## 使用

change命令使用起来感觉跟passwd差不多，但是感觉上更加简单，我们就不展示啥多的功能了，先展示一个展示所有信息：

```
[root@VM-0-12-centos ~]# chage -l root
Last password change					: Mar 01, 2021
Password expires					: never
Password inactive					: never
Account expires						: never
Minimum number of days between password change		: 0
Maximum number of days between password change		: 99999
Number of days of warning before password expires	: 7


[root@VM-0-12-centos ~]# chage --list zhouning
Last password change					: Mar 01, 2021
Password expires					: never
Password inactive					: never
Account expires						: never
Minimum number of days between password change		: 0
Maximum number of days between password change		: 99999
Number of days of warning before password expires	: 7
```

### 小栗子

功能：在使用agetest登录之后，强制他们更改密码然后再使用系统资源

我们创建agetest，然后使用agetest作为他的密码，并且设置密码创建时间为0

```
[root@VM-0-12-centos ~]# useradd agetest
[root@VM-0-12-centos ~]# echo "agetest" | passwd --stdin agetest
Changing password for user agetest.
passwd: all authentication tokens updated successfully.
[root@VM-0-12-centos ~]# chage -d 0 agetest 
```

然后agetest开始登录，会要求重新设置密码，设置完之后就自动断开需要新密码进行登录，当然我这里新密码设置为了原来的密码(皮了一下)，一般都是设置为其他的

```
You are required to change your password immediately (administrator enforced)
Activate the web console with: systemctl enable --now cockpit.socket

WARNING: Your password has expired.
You must change your password now and login again!
Changing password for user agetest.
Current password: 
New password: 
BAD PASSWORD: The password is the same as the old one
passwd: Authentication token manipulation error
Connection closing...Socket close.

Connection closed by foreign host.

Disconnected from remote host(agetest) at 14:48:19.

Type `help' to learn how to use Xshell prompt.
```

这个功能就像给你的了一个账号，然后账号密码就是账号名，登录上去之后需要进行更改密码，并且更改完需要重新登录，非常有趣且实用的例子