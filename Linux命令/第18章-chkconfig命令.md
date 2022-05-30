# chkconfig命令

chkconfig用来管理系统服务

```
[root@VM-0-12-centos ~]# chkconfig --help
chkconfig version 1.11 - Copyright (C) 1997-2000 Red Hat, Inc.
This may be freely redistributed under the terms of the GNU Public License.

usage:   chkconfig [--list] [--type <type>] [name]
         chkconfig --add <name>
         chkconfig --del <name>
         chkconfig --override <name>
         chkconfig [--level <levels>] [--type <type>] <name> <on|off|reset|resetpriorities>
```

列出目前系统上面所有被 chkconfig 管理的服务

```
[root@VM-0-12-centos ~]# chkconfig --list

Note: This output shows SysV services only and does not include native
      systemd services. SysV configuration data might be overridden by native
      systemd configuration.

      If you want to list systemd services use 'systemctl list-unit-files'.
      To see services enabled on particular target use
      'systemctl list-dependencies [target]'.


xinetd based services:
	chargen-dgram: 	off
	chargen-stream:	off
	daytime-dgram: 	off
	daytime-stream:	off
	discard-dgram: 	off
	discard-stream:	off
	echo-dgram:    	off
	echo-stream:   	off
	tcpmux-server: 	off
	time-dgram:    	off
	time-stream:   	off

```


你可以发现上面的表格有分为两个区块，一个具有 1, 2, 3 等数字（这里是有没有开启），一个则被 xinetd管理。没错！从这里我们就能够发现服务有 stand alone 与 super daemon 之分。

显示出目前在 run level 3 为启动的服务

```
范例二：显示出目前在 run level 3 为启动的服务
[root@www ~]# chkconfig --list | grep '3:on'

范例三：让 atd 这个服务在 run level 为 3, 4, 5 时启动：
[root@www ~]# chkconfig --level 345 atd on
```

## **配置自己的系统服务**

```
[root@www ~]# chkconfig [--add|--del] [服务名称]
选项与参数：
--add ：添加一个服务名称给 chkconfig 来管理，该服务名称必须在 /etc/init.d/ 内
--del ：删除一个给 chkconfig 管理的服务
```

现在你知道 chkconfig 是真好用的东西，那么如果我自己写了一个程序并且想要让该程序成为系统服务好让 chkconfig 来管理时， 可以怎么进行呢？只要将该服务加入 init 可以管理的 script 当中，亦即是 /etc/init.d/ 当中即可。 举个例子，我们在 /etc/init.d/ 里面创建一个 myzhouning 文件，该文件仅是一个简单的服务范例，基本上，没有任何用途.... 对于该文件的必须性是这样的：

- myzhouning  将在 run level 3 及 5 启动；
- myzhouning 在 /etc/rc.d/rc[35].d 当中启动时，以 80 顺位启动，以 70 顺位结束。

先写下

```
[root@VM-0-12-centos ~]# vim /etc/init.d/myzhouning
#!/bin/bash
# chkconfig: 35 80 70
# description: 没啥！只是用来作为练习之用的一个范例
echo "Nothing"
```

查看chkconfig

```
[root@VM-0-12-centos ~]# chkconfig --list myzhouning 

Note: This output shows SysV services only and does not include native
      systemd services. SysV configuration data might be overridden by native
      systemd configuration.

      If you want to list systemd services use 'systemctl list-unit-files'.
      To see services enabled on particular target use
      'systemctl list-dependencies [target]'.

service myzhouning supports chkconfig, but is not referenced in any runlevel (run 'chkconfig --add myzhouning')

```

发现还没有加进去，加入进去

```
[root@VM-0-12-centos ~]# chkconfig --add myzhouning 
[root@VM-0-12-centos ~]# chkconfig --list myzhouning

Note: This output shows SysV services only and does not include native
      systemd services. SysV configuration data might be overridden by native
      systemd configuration.

      If you want to list systemd services use 'systemctl list-unit-files'.
      To see services enabled on particular target use
      'systemctl list-dependencies [target]'.

myzhouning     	0:off	1:off	2:off	3:on	4:off	5:on	6:off
```

看起来很有意思

最后删除掉

```
[root@VM-0-12-centos ~]# chkconfig --del myzhouning 
[root@VM-0-12-centos ~]# rm /etc/init.d/myzhouning 
rm: remove regular file '/etc/init.d/myzhouning'? y
[root@VM-0-12-centos ~]# 
```

