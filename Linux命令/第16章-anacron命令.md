# anacron命令

anacron 并不是用来取代 crontab 的，anacron 存在的目的就在於我们上头提到的，在处理非 24 小时一直启动的 Linux 系统的 crontab 的运行！所以 anacron 并不能指定何时运行某项任务， 而是以天为单位或者是在启动后立刻进行 anacron 的动作，他会去侦测停机期间应该进行但是并没有进行的 crontab 任务，并将该任务运行一遍后，anacron 就会自动停止了。

由於 anacron 会以一天、七天、一个月为期去侦测系统未进行的 crontab 任务，因此对於某些特殊的使用环境非常有帮助。 举例来说，如果你的 Linux 主机是放在公司给同仁使用的，因为周末假日大家都不在所以也没有必要开启， 因此你的 Linux 是周末都会关机两天的。但是 crontab 大多在每天的凌晨以及周日的早上进行各项任务， 偏偏你又关机了，此时系统很多 crontab 的任务就无法进行。 anacron 刚好可以解决这个问题！

那么 anacron 又是怎么知道我们的系统啥时关机的呢？这就得要使用 anacron 读取的时间记录档 (timestamps) 了！ anacron 会去分析现在的时间与时间记录档所记载的上次运行 anacron 的时间，两者比较后若发现有差异， 那就是在某些时刻没有进行 crontab 罗！此时 anacron 就会开始运行未进行的 crontab 任务了！ 所以 anacron 其实也是透过 crontab 来运行的！因此 anacron 运行的时间通常有两个，一个是系统启动期间运行，一个是写入 crontab 的排程中。 这样才能够在特定时间分析系统未进行的 crontab 工作嘛！了解乎！



## anacron和/etc/anacrontab

anacron 其实是一支程序并非一个服务！这支程序在 CentOS 当中已经进入 crontab 的排程喔！ 不相信吗？你可以这样追踪看看：

```
[root@VM-0-12-centos ~]# ll /etc/cron*/*ana*
-rwxr-xr-x 1 root root 575 Nov  9  2019 /etc/cron.hourly/0anacron
```



```
[root@VM-0-12-centos ~]# cat /etc/cron.hourly/0anacron 
#!/bin/sh
# Check whether 0anacron was run today already
if test -r /var/spool/anacron/cron.daily; then
    day=`cat /var/spool/anacron/cron.daily`
fi
if [ `date +%Y%m%d` = "$day" ]; then
    exit 0
fi

# Do not run jobs when on battery power
online=1
for psupply in AC ADP0 ; do
    sysfile="/sys/class/power_supply/$psupply/online"

    if [ -f $sysfile ] ; then
        if [ `cat $sysfile 2>/dev/null`x = 1x ]; then
            online=1
            break
        else
            online=0
        fi
    fi
done
if [ $online = 0 ]; then
    exit 0
fi
/usr/sbin/anacron -s
```

看起来 是以串代码最终是运行了`/usr/sbin/anacron -s`这个命令

简单的看了一下anacron 的语法

```
[root@www ~]# anacron [-sfn] [job]..
[root@www ~]# anacron -u [job]..
选项与参数：
-s  ：开始一连续的运行各项工作 (job)，会依据时间记录档的数据判断是否进行；
-f  ：强制进行，而不去判断时间记录档的时间戳记；
-n  ：立刻进行未进行的任务，而不延迟 (delay) 等待时间；
-u  ：仅升级时间记录档的时间戳记，不进行任何工作。
job ：由 /etc/anacrontab 定义的各项工作名称。
```

所以anacron -s是开始一系列的工作 

接着查看一下/etc/anacrontab

```
[root@VM-0-12-centos ~]# cat /etc/anacrontab 
# /etc/anacrontab: configuration file for anacron

# See anacron(8) and anacrontab(5) for details.

SHELL=/bin/sh
PATH=/sbin:/bin:/usr/sbin:/usr/bin
MAILTO=root
# the maximal random delay added to the base delay of the jobs
RANDOM_DELAY=45
# the jobs will be started during the following hours only
START_HOURS_RANGE=3-22

#period in days   delay in minutes   job-identifier   command
1	5	cron.daily		nice run-parts /etc/cron.daily
7	25	cron.weekly		nice run-parts /etc/cron.weekly
@monthly 45	cron.monthly		nice run-parts /etc/cron.monthly
天数   延迟时间 工作名称定义   实际要进行的命令串
# 天数单位为天；延迟时间单位为分钟；工作名称定义可自订；
# 命令串则通常与 crontab 的配置相同！
```

三个工作名称的时间记录档以及记录的时间戳记

```
[root@VM-0-12-centos ~]# more /var/spool/anacron/*
::::::::::::::
/var/spool/anacron/cron.daily
::::::::::::::
20210307
::::::::::::::
/var/spool/anacron/cron.monthly
::::::::::::::
20210301
::::::::::::::
/var/spool/anacron/cron.weekly
::::::::::::::
20210301

```

由於 /etc/cron.daily 内的任务比较多，因此我们使用每天进行的任务来解释一下 anacron 的运行情况好了。 anacron 若下达『 anacron -s cron.daily 』时，他会这样运行的：

1. 由 /etc/anacrontab 分析到 cron.daily 这项工作名称的天数为 1 天；
2. 由 /var/spool/anacron/cron.daily 取出最近一次运行 anacron 的时间戳记；
3. 由上个步骤与目前的时间比较，若差异天数为 1 天以上 (含 1 天)，就准备进行命令；
4. 若准备进行命令，根据 /etc/anacrontab 的配置，将延迟 65 分钟
5. 延迟时间过后，开始运行后续命令，亦即『 run-parts /etc/cron.daily 』这串命令；
6. 运行完毕后， anacron 程序结束。

所以说，时间戳记是非常重要的！anacron 是透过该记录与目前的时间差异，了解到是否应该要进行某项任务的工作！ 举例来说，如果我的主机在 2009/03/15(星期天) 18:00 关机，然后在 2009/03/16(星期一) 8:00 启动，由於我的 crontab 是在早上 04:00 左右进行各项任务，由於该时刻系统是关机的，因此时间戳记依旧为 20090315 (旧的时间)， 但是目前时间已经是 20090316 (新的时间)，因此 run-parts /etc/cron.daily 就会在启动过 65 分钟后开始运行了。

所以罗， anacron 并不需要额外的配置，使用默认值即可！只是我们的 CentOS 只有在启动时才会运行 anacron 就是了。如果要确定 anacron 是否启动时会主动的运行，你可以下达下列命令：

```
[root@www ~]# chkconfig --list anacron 
anacron      0:off   1:off   2:on    3:on    4:on    5:on    6:off 
# 详细的 chkconfig 说明我们会在后续章节提到，注意看 3, 5 
# 的项目，都是 on ！那就是有启动啦！启动时才会运行的意思！ 
```

现在你知道为什么隔了一阵子才将 CentOS 启动，启动过后约 1 小时左右系统会有一小段时间的忙碌！而且硬盘会跑个不停！那就是因为 anacron 正在运行过去 crontab 未进行的各项工作排程啦！这样对 anacron 有没有概念了呢？ \^_^