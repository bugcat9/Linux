# passwd命令

介绍useradd的时候，说过刚创建的用户的时候一般是没有密码的，也就无法登录，我们可以通过passwd配置密码，让账号能够登录

## 用法

简单的看看help

```
[root@VM-0-12-centos ~]# passwd --help
Usage: passwd [OPTION...] <accountName>
  -k, --keep-tokens       keep non-expired authentication tokens
  -d, --delete            delete the password for the named account (root only); also removes password lock if any
  -l, --lock              lock the password for the named account (root only)
  -u, --unlock            unlock the password for the named account (root only)
  -e, --expire            expire the password for the named account (root only)
  -f, --force             force operation
  -x, --maximum=DAYS      maximum password lifetime (root only)
  -n, --minimum=DAYS      minimum password lifetime (root only)
  -w, --warning=DAYS      number of days warning users receives before password expiration (root only)
  -i, --inactive=DAYS     number of days after password expiration when an account becomes disabled (root only)
  -S, --status            report password status on the named account (root only)
      --stdin             read new tokens from stdin (root only)

Help options:
  -?, --help              Show this help message
      --usage             Display brief usage message

```

一般来说用起来还是比较简单的，改自己密直接运行`passswd`

改别人代码直接`passwd 用户名`

除此之外其实还可以设置失效时间什么的，但是个人感觉用的不多，等用了再查也可以

除此之外还有一个简单的方法-S来查看用户状态

```
[root@VM-0-12-centos ~]# passwd -S zhouning
zhouning PS 2021-03-01 0 99999 7 -1 (Password set, SHA512 crypt.)
```

-S内容依次可以看man讲解

```
-S, --status
              This will output a short information about the status of the password for a given account. The status information consists of 7 fields. The first field  is  the  user's
              login  name.  The  second field indicates if the user account has a locked password (LK), has no password (NP), or has a usable password (PS). The third field gives the
              date of the last password change. The next four fields are the minimum age, maximum age, warning period,  and  inactivity  period  for  the  password.  These  ages  are
              expressed in days.

              Notes:  The  date of the last password change is stored as a number of days since epoch. Depending on the current time zone, the passwd -S username may show the date of
              the last password change that is different from the real date of the last password change by ±1 day.

              This option is available to root only.

```

翻译一下

```
这将输出有关给定帐户密码状态的简短信息。状态信息包含7个字段。第一个字段是用户的登录名。第二个字段指示用户帐户是否具有锁定密码（LK），没有密码（NP）或具有可用密码（PS）。第三个字段给出上次密码更改的日期。接下来的四个字段是密码的最小期限，最大期限，警告期限和不活动期限。这些年龄是以天表示。注意：上次密码更改的日期存储为自纪元以来的天数。根据当前时区，passwd -S用户名可能会显示日期最后一次密码更改与最后一次密码更改的实际日期相差±1天。此选项仅对root用户可用。
```

