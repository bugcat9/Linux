# sed命令

sed可以对数据进行取代、删除、新增、搜索等

查看一下`--help`

```
zhouning@DESKTOP-681HT7R:~$ sed --help
Usage: sed [OPTION]... {script-only-if-no-other-script} [input-file]...

  -n, --quiet, --silent
                 suppress automatic printing of pattern space
  -e script, --expression=script
                 add the script to the commands to be executed
  -f script-file, --file=script-file
                 add the contents of script-file to the commands to be executed
  --follow-symlinks
                 follow symlinks when processing in place
  -i[SUFFIX], --in-place[=SUFFIX]
                 edit files in place (makes backup if SUFFIX supplied)
  -l N, --line-length=N
                 specify the desired line-wrap length for the `l' command
  --posix
                 disable all GNU extensions.
  -E, -r, --regexp-extended
                 use extended regular expressions in the script
                 (for portability use POSIX -E).
  -s, --separate
                 consider files as separate rather than as a single,
                 continuous long stream.
      --sandbox
                 operate in sandbox mode.
  -u, --unbuffered
                 load minimal amounts of data from the input files and flush
                 the output buffers more often
  -z, --null-data
                 separate lines by NUL characters
      --help     display this help and exit
      --version  output version information and exit

If no -e, --expression, -f, or --file option is given, then the first
non-option argument is taken as the sed script to interpret.  All
remaining arguments are names of input files; if no input files are
specified, then the standard input is read.

GNU sed home page: <http://www.gnu.org/software/sed/>.
General help using GNU software: <http://www.gnu.org/gethelp/>.
E-mail bug reports to: <bug-sed@gnu.org>.
```

## 以行为单位的新增、删除功能

删除2到5行

```
zhouning@DESKTOP-681HT7R:~$ nl /etc/passwd | sed '2,5d'
     1  root:x:0:0:root:/root:/bin/bash
     6  games:x:5:60:games:/usr/games:/usr/sbin/nologin
     7  man:x:6:12:man:/var/cache/man:/usr/sbin/nologin
     8  lp:x:7:7:lp:/var/spool/lpd:/usr/sbin/nologin
     9  mail:x:8:8:mail:/var/mail:/usr/sbin/nologin
    10  news:x:9:9:news:/var/spool/news:/usr/sbin/nologin
    11  uucp:x:10:10:uucp:/var/spool/uucp:/usr/sbin/nologin
    12  proxy:x:13:13:proxy:/bin:/usr/sbin/nologin
    13  www-data:x:33:33:www-data:/var/www:/usr/sbin/nologin
    14  backup:x:34:34:backup:/var/backups:/usr/sbin/nologin
    15  list:x:38:38:Mailing List Manager:/var/list:/usr/sbin/nologin
    16  irc:x:39:39:ircd:/var/run/ircd:/usr/sbin/nologin
    17  gnats:x:41:41:Gnats Bug-Reporting System (admin):/var/lib/gnats:/usr/sbin/nologin
    18  nobody:x:65534:65534:nobody:/nonexistent:/usr/sbin/nologin
    19  systemd-network:x:100:102:systemd Network Management,,,:/run/systemd/netif:/usr/sbin/nologin
    20  systemd-resolve:x:101:103:systemd Resolver,,,:/run/systemd/resolve:/usr/sbin/nologin
    21  syslog:x:102:106::/home/syslog:/usr/sbin/nologin
    22  messagebus:x:103:107::/nonexistent:/usr/sbin/nologin
    23  _apt:x:104:65534::/nonexistent:/usr/sbin/nologin
    24  lxd:x:105:65534::/var/lib/lxd/:/bin/false
    25  uuidd:x:106:110::/run/uuidd:/usr/sbin/nologin
    26  dnsmasq:x:107:65534:dnsmasq,,,:/var/lib/misc:/usr/sbin/nologin
    27  landscape:x:108:112::/var/lib/landscape:/usr/sbin/nologin
    28  sshd:x:109:65534::/run/sshd:/usr/sbin/nologin
    29  pollinate:x:110:1::/var/cache/pollinate:/bin/false
    30  zhouning:x:1000:1000:,,,:/home/zhouning:/bin/bash
```

如果只要删除第 2 行，可以使用『 nl /etc/passwd | sed '2d' 』来达成， 至於若是要删除第 3 到最后一行，则是『 nl /etc/passwd | sed '3,$d' 』的啦，那个钱字号『 $ 』代表最后一行！

在第二行后面加drink tea

```
zhouning@DESKTOP-681HT7R:~$  nl /etc/passwd | sed '2a drink tea'
     1  root:x:0:0:root:/root:/bin/bash
     2  daemon:x:1:1:daemon:/usr/sbin:/usr/sbin/nologin
drink tea
     3  bin:x:2:2:bin:/bin:/usr/sbin/nologin
     4  sys:x:3:3:sys:/dev:/usr/sbin/nologin
     5  sync:x:4:65534:sync:/bin:/bin/sync
     6  games:x:5:60:games:/usr/games:/usr/sbin/nologin
     7  man:x:6:12:man:/var/cache/man:/usr/sbin/nologin
     8  lp:x:7:7:lp:/var/spool/lpd:/usr/sbin/nologin
     9  mail:x:8:8:mail:/var/mail:/usr/sbin/nologin
    10  news:x:9:9:news:/var/spool/news:/usr/sbin/nologin
    11  uucp:x:10:10:uucp:/var/spool/uucp:/usr/sbin/nologin
    12  proxy:x:13:13:proxy:/bin:/usr/sbin/nologin
    13  www-data:x:33:33:www-data:/var/www:/usr/sbin/nologin
    14  backup:x:34:34:backup:/var/backups:/usr/sbin/nologin
    15  list:x:38:38:Mailing List Manager:/var/list:/usr/sbin/nologin
    16  irc:x:39:39:ircd:/var/run/ircd:/usr/sbin/nologin
    17  gnats:x:41:41:Gnats Bug-Reporting System (admin):/var/lib/gnats:/usr/sbin/nologin
    18  nobody:x:65534:65534:nobody:/nonexistent:/usr/sbin/nologin
    19  systemd-network:x:100:102:systemd Network Management,,,:/run/systemd/netif:/usr/sbin/nologin
    20  systemd-resolve:x:101:103:systemd Resolver,,,:/run/systemd/resolve:/usr/sbin/nologin
    21  syslog:x:102:106::/home/syslog:/usr/sbin/nologin
    22  messagebus:x:103:107::/nonexistent:/usr/sbin/nologin
    23  _apt:x:104:65534::/nonexistent:/usr/sbin/nologin
    24  lxd:x:105:65534::/var/lib/lxd/:/bin/false
    25  uuidd:x:106:110::/run/uuidd:/usr/sbin/nologin
    26  dnsmasq:x:107:65534:dnsmasq,,,:/var/lib/misc:/usr/sbin/nologin
    27  landscape:x:108:112::/var/lib/landscape:/usr/sbin/nologin
    28  sshd:x:109:65534::/run/sshd:/usr/sbin/nologin
    29  pollinate:x:110:1::/var/cache/pollinate:/bin/false
    30  zhouning:x:1000:1000:,,,:/home/zhouning:/bin/bash
```

在 a 后面加上的字串就已将出现在第二行后面罗！那如果是要在第二行前呢？『 nl /etc/passwd | sed '2i drink tea' 』就对啦！就是将『 a 』变成『 i 』即可

## 以行为单位取代与显示功能

将第2-5行的内容取代成为『No 2-5 number』

```
zhouning@DESKTOP-681HT7R:~$ nl /etc/passwd | sed '2,5c No 2-5 number'
     1  root:x:0:0:root:/root:/bin/bash
No 2-5 number
     6  games:x:5:60:games:/usr/games:/usr/sbin/nologin
     7  man:x:6:12:man:/var/cache/man:/usr/sbin/nologin
     8  lp:x:7:7:lp:/var/spool/lpd:/usr/sbin/nologin
     9  mail:x:8:8:mail:/var/mail:/usr/sbin/nologin
    10  news:x:9:9:news:/var/spool/news:/usr/sbin/nologin
    11  uucp:x:10:10:uucp:/var/spool/uucp:/usr/sbin/nologin
    12  proxy:x:13:13:proxy:/bin:/usr/sbin/nologin
    13  www-data:x:33:33:www-data:/var/www:/usr/sbin/nologin
    14  backup:x:34:34:backup:/var/backups:/usr/sbin/nologin
    15  list:x:38:38:Mailing List Manager:/var/list:/usr/sbin/nologin
    16  irc:x:39:39:ircd:/var/run/ircd:/usr/sbin/nologin
    17  gnats:x:41:41:Gnats Bug-Reporting System (admin):/var/lib/gnats:/usr/sbin/nologin
    18  nobody:x:65534:65534:nobody:/nonexistent:/usr/sbin/nologin
    19  systemd-network:x:100:102:systemd Network Management,,,:/run/systemd/netif:/usr/sbin/nologin
    20  systemd-resolve:x:101:103:systemd Resolver,,,:/run/systemd/resolve:/usr/sbin/nologin
    21  syslog:x:102:106::/home/syslog:/usr/sbin/nologin
    22  messagebus:x:103:107::/nonexistent:/usr/sbin/nologin
    23  _apt:x:104:65534::/nonexistent:/usr/sbin/nologin
    24  lxd:x:105:65534::/var/lib/lxd/:/bin/false
    25  uuidd:x:106:110::/run/uuidd:/usr/sbin/nologin
    26  dnsmasq:x:107:65534:dnsmasq,,,:/var/lib/misc:/usr/sbin/nologin
    27  landscape:x:108:112::/var/lib/landscape:/usr/sbin/nologin
    28  sshd:x:109:65534::/run/sshd:/usr/sbin/nologin
    29  pollinate:x:110:1::/var/cache/pollinate:/bin/false
    30  zhouning:x:1000:1000:,,,:/home/zhouning:/bin/bash
```

列出 /etc/passwd 文件内的第 5-7 行

```
zhouning@DESKTOP-681HT7R:~$ nl /etc/passwd | sed -n '5,7p'
     5  sync:x:4:65534:sync:/bin:/bin/sync
     6  games:x:5:60:games:/usr/games:/usr/sbin/nologin
     7  man:x:6:12:man:/var/cache/man:/usr/sbin/nologin
```

## 部分数据的搜索并取代功能

类似于这样

```
sed 's/要被取代的字串/新的字串/g'
```

直接修改文件，利用 sed 将 regular_express.txt 内每一行结尾若为 . 则换成 !

```
zhouning@DESKTOP-681HT7R:~$ sed -i 's/\.$/\!/g' regular_express.txt
zhouning@DESKTOP-681HT7R:~$ cat regular_express.txt
"Open ource" is a good mechanism to develop programs!
apple is my favorite food!
Football game is not use feet only!
this dress doesn't fit me!
However, this dress is about $ 3183 dollars.^M
GNU is free air not free beer.^M
Her hair is very beauty.^M
I can't finish the test.^M
Oh! The soup taste good.^M
motorcycle is cheap than car!
This window is clear!
the symbol '*' is represented as start!
Oh!     My god!
The gd software is a library for drafting programs.^M
You are the best is mean you are the no. 1!
The world <Happy> is the same with "glad"!
I like dog!
google is the best tools for search keyword!
goooooogle yes!
go! go! Let's go!
# I am VBird

```

