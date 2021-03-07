## crontab命令

Linux当中crontab可以帮助我们完成某些定时任务

## crontab的配置

crontab跟at一样有一些限制。

- /etc/cron.allow：
  将可以使用 crontab 的帐号写入其中，若不在这个文件内的使用者则不可使用 crontab；
- /etc/cron.deny：
  将不可以使用 crontab 的帐号写入其中，若未记录到这个文件当中的使用者，就可以使用 crontab 。

与 at 很像吧！同样的，以优先顺序来说， /etc/cron.allow 比 /etc/cron.deny 要优先， 而判断上面，这两个文件只选择一个来限制而已，因此，建议你只要保留一个即可， 免得影响自己在配置上面的判断！一般来说，系统默认是保留 /etc/cron.deny ， 你可以将不想让他运行 crontab 的那个使用者写入 /etc/cron.deny 当中，一个帐号一行！

当使用者使用 crontab 这个命令来创建工作排程之后，该项工作就会被纪录到 /var/spool/cron/ 里面去了，而且是以帐号来作为判别的喔！举例来说， dmtsai 使用 crontab 后， 他的工作会被纪录到 /var/spool/cron/dmtsai 里头去！但请注意，不要使用 vi 直接编辑该文件， 因为可能由於输入语法错误，会导致无法运行 cron 喔！另外， cron 运行的每一项工作都会被纪录到 /var/log/cron 这个登录档中。

## crontab的简单使用

```
[root@www ~]# crontab [-u username] [-l|-e|-r]
选项与参数：
-u  ：只有 root 才能进行这个任务，亦即帮其他使用者创建/移除 crontab 工作排程；
-e  ：编辑 crontab 的工作内容
-l  ：查阅 crontab 的工作内容
-r  ：移除所有的 crontab 的工作内容，若仅要移除一项，请用 -e 去编辑。
```

案例一：每天的 12:00 发信给自己

```
[dmtsai@www ~]$ crontab -e
# 此时会进入 vi 的编辑画面让您编辑工作！注意到，每项工作都是一行。
0   12  *  *  * mail dmtsai -s "at 12:00" < /home/dmtsai/.bashrc
#分 时 日 月 周 |<==============命令串========================>|
```

默认情况下，任何使用者只要不被列入 /etc/cron.deny 当中，那么他就可以直接下达『 crontab -e 』去编辑自己的例行性命令了！整个过程就如同上面提到的，会进入 vi 的编辑画面， 然后以一个工作一行来编辑，编辑完毕之后输入『 :wq 』储存后离开 vi 就可以了！ 而每项工作 (每行) 的格式都是具有六个栏位，这六个栏位的意义为：

| 代表意义 | 分钟 | 小时 | 日期 | 月份 | 周   | 命令       |
| -------- | ---- | ---- | ---- | ---- | ---- | ---------- |
| 数字范围 | 0-59 | 0-23 | 1-31 | 1-12 | 0-7  | 呀就命令啊 |

比较有趣的是那个『周』喔！周的数字为 0 或 7 时，都代表『星期天』的意思！另外， 还有一些辅助的字符，大概有底下这些：

| 特殊字符 | 代表意义                                                     |
| -------- | ------------------------------------------------------------ |
| *(星号)  | 代表任何时刻都接受的意思！举例来说，范例一内那个日、月、周都是 * ， 就代表著『不论何月、何日的礼拜几的 12:00 都运行后续命令』的意思！ |
| ,(逗号)  | 代表分隔时段的意思。举例来说，如果要下达的工作是 3:00 与 6:00 时，就会是：0 3,6 * * * command时间参数还是有五栏，不过第二栏是 3,6 ，代表 3 与 6 都适用！ |
| -(减号)  | 代表一段时间范围内，举例来说， 8 点到 12 点之间的每小时的 20 分都进行一项工作：20 8-12 * * * command仔细看到第二栏变成 8-12 喔！代表 8,9,10,11,12 都适用的意思！ |
| /n(斜线) | 那个 n 代表数字，亦即是『每隔 n 单位间隔』的意思，例如每五分钟进行一次，则： */5 * * * * command很简单吧！用 * 与 /5 来搭配，也可以写成 0-59/5 ，相同意思！ |

查看crontab内容

```
[root@VM-0-12-centos ~]# crontab -l
*/5 * * * * flock -xn /tmp/stargate.lock -c '/usr/local/qcloud/stargate/admin/start.sh > /dev/null 2>&1 &'
0 12 * * * mail root -s "at 12:00" < /home/zhouning/.bashrc
```

 注意，若仅想要移除一项工作而已的话，必须要用 crontab -e 去编辑～
 如果想要全部的工作都移除，才使用 crontab -r 喔

```
[root@VM-0-12-centos ~]# crontab -r
[root@VM-0-12-centos ~]# crontab -l
no crontab for root
```

## 系统的配置档： /etc/crontab

这个『 crontab -e 』是针对使用者的 cron 来设计的，如果是『系统的例行性任务』时， 该怎么办呢？是否还是需要以 crontab -e 来管理你的例行性工作排程呢？当然不需要，你只要编辑 /etc/crontab 这个文件就可以啦！有一点需要特别注意喔！那就是 crontab -e 这个 crontab 其实是 /usr/bin/crontab 这个运行档，但是 /etc/crontab 可是一个『纯文字档』喔！你可以 root 的身份编辑一下这个文件哩！

基本上， cron 这个服务的最低侦测限制是『分钟』，所以『 cron 会每分钟去读取一次 /etc/crontab 与 /var/spool/cron 里面的数据内容 』，因此，只要你编辑完 /etc/crontab 这个文件，并且将他储存之后，那么 cron 的配置就自动的会来运行了！

查看你一下这个文件

```
[root@VM-0-12-centos ~]# cat /etc/crontab
SHELL=/bin/bash
PATH=/sbin:/bin:/usr/sbin:/usr/bin
MAILTO=root

# For details see man 4 crontabs

# Example of job definition:
# .---------------- minute (0 - 59)
# |  .------------- hour (0 - 23)
# |  |  .---------- day of month (1 - 31)
# |  |  |  .------- month (1 - 12) OR jan,feb,mar,apr ...
# |  |  |  |  .---- day of week (0 - 6) (Sunday=0 or 7) OR sun,mon,tue,wed,thu,fri,sat
# |  |  |  |  |
# *  *  *  *  * user-name  command to be executed
```

这个文件中的注释教了我们如何使用这个文件，跟crontab -e还挺像。

* **MAILTO=root**：

  这个项目是说，当 /etc/crontab 这个文件中的例行性工作的命令发生错误时，或者是该工作的运行结果有 STDOUT/STDERR 时，会将错误信息或者是萤幕显示的信息传给谁？默认当然是由系统直接寄发一封 mail 给 root 啦！不过， 由於 root 并无法在用户端中以 POP3 之类的软件收信，因此，鸟哥通常都将这个 e-mail 改成自己的帐号，好让我随时了解系统的状况！例如： MAILTO=dmtsai@my.host.name

* **PATH=....**

  输入运行档的搜寻路径！使用默认的路径配置就已经很足够了！

* **用法**：

  后面是分 时 日 月 周 运行者身份  命令串，感觉使用起来也比较简单