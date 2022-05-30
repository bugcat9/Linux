# top命令

ps命令是截取一个世界点的程序状态，而top可以持续侦测程序运行的状态。同样top命令也有非常多的参数，所以也只能列举一些简单的

## top参数

```
[root@www ~]# top [-d 数字] | top [-bnp]
选项与参数：
-d  ：后面可以接秒数，就是整个程序画面升级的秒数。默认是 5 秒；
-b  ：以批量的方式运行 top ，还有更多的参数可以使用喔！
      通常会搭配数据流重导向来将批量的结果输出成为文件。
-n  ：与 -b 搭配，意义是，需要进行几次 top 的输出结果。
-p  ：指定某些个 PID 来进行观察监测而已。
在 top 运行过程当中可以使用的按键命令：
	? ：显示在 top 当中可以输入的按键命令；
	P ：以 CPU 的使用资源排序显示；
	M ：以 Memory 的使用资源排序显示；
	N ：以 PID 来排序喔！
	T ：由该 Process 使用的 CPU 时间累积 (TIME+) 排序。
	k ：给予某个 PID 一个讯号  (signal)
	r ：给予某个 PID 重新制订一个 nice 值。
	q ：离开 top 软件的按键。
```

范例一：每两秒钟升级一次 top ，观察整体资讯：

```
[root@www ~]# top -d 2
top - 17:03:09 up 7 days, 16:16,  1 user,  load average: 0.00, 0.00, 0.00
Tasks:  80 total,   1 running,  79 sleeping,   0 stopped,   0 zombie
Cpu(s):  0.5%us,  0.5%sy,  0.0%ni, 99.0%id,  0.0%wa,  0.0%hi,  0.0%si,  0.0%st
Mem:    742664k total,   681672k used,    60992k free,   125336k buffers
Swap:  1020088k total,       28k used,  1020060k free,   311156k cached
    <==如果加入 k 或 r 时，就会有相关的字样出现在这里喔！
  PID USER      PR  NI  VIRT  RES  SHR S %CPU %MEM    TIME+  COMMAND     
14398 root      15   0  2188 1012  816 R  0.5  0.1   0:00.05 top
    1 root      15   0  2064  616  528 S  0.0  0.1   0:01.38 init
    2 root      RT  -5     0    0    0 S  0.0  0.0   0:00.00 migration/0
    3 root      34  19     0    0    0 S  0.0  0.0   0:00.00 ksoftirqd/0
```

top 也是个挺不错的程序观察工具！但不同於 ps 是静态的结果输出， top 这个程序可以持续的监测整个系统的程序工作状态。 在默认的情况下，每次升级程序资源的时间为 5 秒，不过，可以使用 -d 来进行修改。 top 主要分为两个画面，上面的画面为整个系统的资源使用状态，基本上总共有六行，显示的内容依序是：

- 第一行(top...)：这一行显示的资讯分别为：

  - 目前的时间，亦即是 17:03:09 那个项目；
  - 启动到目前为止所经过的时间，亦即是 up 7days, 16:16 那个项目；
  - 已经登陆系统的使用者人数，亦即是 1 user项目；
  - 系统在 1, 5, 15 分钟的平均工作负载。我们在[第十六章谈到的 batch](http://cn.linux.vbird.org/linux_basic/0430cron.php#batch) 工作方式为负载小於 0.8 就是这个负载罗！代表的是 1, 5, 15 分钟，系统平均要负责运行几个程序(工作)的意思。 越小代表系统越闲置，若高於 1 得要注意你的系统程序是否太过繁复了！

- 第二行(Tasks...)：显示的是目前程序的总量与个别程序在什么状态(running, sleeping, stopped, zombie)。 比较需要注意的是最后的 zombie 那个数值，如果不是 0 ！好好看看到底是那个 process 变成僵尸了吧？

  

- 第三行(Cpus...)：显示的是 CPU 的整体负载，每个项目可使用 ? 查阅。需要特别注意的是 %wa ，那个项目代表的是 I/O wait， 通常你的系统会变慢都是 I/O 产生的问题比较大！因此这里得要注意这个项目耗用 CPU 的资源喔！ 另外，如果是多核心的设备，可以按下数字键『1』来切换成不同 CPU 的负载率。

  

- 第四行与第五行：表示目前的实体内存与虚拟内存 (Mem/Swap) 的使用情况。 再次重申，要注意的是 swap 的使用量要尽量的少！如果 swap 被用的很大量，表示系统的实体内存实在不足！

  

- 第六行：这个是当在 top 程序当中输入命令时，显示状态的地方。

至於 top 下半部分的画面，则是每个 process 使用的资源情况。比较需要注意的是：

- PID ：每个 process 的 ID 啦！
- USER：该 process 所属的使用者；
- PR ：Priority 的简写，程序的优先运行顺序，越小越早被运行；
- NI ：Nice 的简写，与 Priority 有关，也是越小越早被运行；
- %CPU：CPU 的使用率；
- %MEM：内存的使用率；
- TIME+：CPU 使用时间的累加；

top 默认使用 CPU 使用率 (%CPU) 作为排序的重点，如果你想要使用内存使用率排序，则可以按下『M』， 若要回复则按下『P』即可。如果想要离开 top 则按下『 q 』吧！如果你想要将 top 的结果输出成为文件时， 可以这样做：

```
范例二：将 top 的资讯进行 2 次，然后将结果输出到 /tmp/top.txt
[root@www ~]# top -b -n 2 > /tmp/top.txt
# 这样一来，嘿嘿！就可以将 top 的资讯存到 /tmp/top.txt 文件中了。
```

这玩意儿很有趣！可以帮助你将某个时段 top 观察到的结果存成文件，可以用在你想要在系统背景底下运行。 由於是背景底下运行，与终端机的萤幕大小无关，因此可以得到全部的程序画面！那如果你想要观察的程序 CPU 与内存使用率都很低，结果老是无法在第一行显示时，该怎办？我们可以仅观察单一程序喔！如下所示：

```
范例三：我们自己的 bash PID 可由 $$ 变量取得，请使用 top 持续观察该 PID
[root@www ~]# echo $$
13639  <==就是这个数字！他是我们 bash 的 PID
[root@www ~]# top -d 2 -p 13639
top - 17:31:56 up 7 days, 16:45,  1 user,  load average: 0.00, 0.00, 0.00
Tasks:   1 total,   0 running,   1 sleeping,   0 stopped,   0 zombie
Cpu(s):  0.0%us,  0.0%sy,  0.0%ni,100.0%id,  0.0%wa,  0.0%hi,  0.0%si,  0.0%st
Mem:    742664k total,   682540k used,    60124k free,   126548k buffers
Swap:  1020088k total,       28k used,  1020060k free,   311276k cached

  PID USER      PR  NI  VIRT  RES  SHR S %CPU %MEM    TIME+  COMMAND
13639 root      15   0  5148 1508 1220 S  0.0  0.2   0:00.18 bash
```

看到没！就只会有一支程序给你看！很容易观察吧！好，那么如果我想要在 top 底下进行一些动作呢？ 比方说，修改 NI 这个数值呢？可以这样做：

```
范例四：承上题，上面的 NI 值是 0 ，想要改成 10 的话？
# 在范例三的 top 画面当中直接按下 r 之后，会出现如下的图样！
top - 17:34:24 up 7 days, 16:47,  1 user,  load average: 0.00, 0.00, 0.00
Tasks:   1 total,   0 running,   1 sleeping,   0 stopped,   0 zombie
Cpu(s):  0.0%us,  0.0%sy,  0.0%ni, 99.5%id,  0.0%wa,  0.0%hi,  0.5%si,  0.0%st
Mem:    742664k total,   682540k used,    60124k free,   126636k buffers
Swap:  1020088k total,       28k used,  1020060k free,   311276k cached
PID to renice: 13639  <==按下 r 然后输入这个 PID 号码
  PID USER      PR  NI  VIRT  RES  SHR S %CPU %MEM    TIME+  COMMAND
13639 root      15   0  5148 1508 1220 S  0.0  0.2   0:00.18 bash
```

在你完成上面的动作后，在状态列会出现如下的资讯：

```
Renice PID 13639 to value: 10   <==这是 nice 值
  PID USER      PR  NI  VIRT  RES  SHR S %CPU %MEM    TIME+  COMMAND
```

接下来你就会看到如下的显示画面！

```
top - 17:38:58 up 7 days, 16:52,  1 user,  load average: 0.00, 0.00, 0.00
Tasks:   1 total,   0 running,   1 sleeping,   0 stopped,   0 zombie
Cpu(s):  0.0%us,  0.0%sy,  0.0%ni,100.0%id,  0.0%wa,  0.0%hi,  0.0%si,  0.0%st
Mem:    742664k total,   682540k used,    60124k free,   126648k buffers
Swap:  1020088k total,       28k used,  1020060k free,   311276k cached

  PID USER      PR  NI  VIRT  RES  SHR S %CPU %MEM    TIME+  COMMAND
13639 root      26  10  5148 1508 1220 S  0.0  0.2   0:00.18 bash
```

看到不同处了吧？底线的地方就是修改了之后所产生的效果！一般来说，如果鸟哥想要找出最损耗 CPU 资源的那个程序时，大多使用的就是 top 这支程序啦！然后强制以 CPU 使用资源来排序 (在 top 当中按下 P 即可)， 就可以很快的知道啦！ ^_^。多多爱用这个好用的东西喔！