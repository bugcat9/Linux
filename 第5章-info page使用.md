# info page使用

info是和man差不多的一个查询命令方法。

支持info功能的命令的文件都在/usr/share/info/这个目录当中的

我们先去这个文件夹下看看有多少支持的命令

```
zhouning@DESKTOP-681HT7R:~$ cd /usr/share/info/
zhouning@DESKTOP-681HT7R:/usr/share/info$ ll
total 1000
drwxr-xr-x   2 root root   4096 Jan 18 22:40 ./
drwxr-xr-x 111 root root   4096 Jan 18 22:24 ../
-rw-r--r--   1 root root  12481 Mar 23  2018 bc.info.gz
-rw-r--r--   1 root root 222504 Jan 18  2018 coreutils.info.gz
-rw-r--r--   1 root root  61183 Aug  5  2017 diffutils.info.gz
-rw-r--r--   1 root root  10939 Jan 18 22:40 dir
-rw-r--r--   1 root root  10939 Jan 18 22:40 dir.old
-rw-r--r--   1 root root  19022 Apr 27  2016 ed.info.gz
-rw-r--r--   1 root root  23655 Nov  6  2017 find-maint.info.gz
-rw-r--r--   1 root root  92415 Nov  6  2017 find.info.gz
-rw-r--r--   1 root root   7094 Sep 17 21:57 gnupg-card-architecture.png
-rw-r--r--   1 root root  46691 Sep 17 21:57 gnupg-module-overview.png
-rw-r--r--   1 root root  92738 Sep 17 21:57 gnupg.info-1.gz
-rw-r--r--   1 root root  61362 Sep 17 21:57 gnupg.info-2.gz
-rw-r--r--   1 root root   2830 Sep 17 21:57 gnupg.info.gz
-rw-r--r--   1 root root  29826 Sep 18  2019 grep.info.gz
-rw-r--r--   1 root root  14828 Apr 28  2017 gzip.info.gz
-rw-r--r--   1 root root  17426 Mar  6  2018 nano.info.gz
-rw-r--r--   1 root root  24906 May 16  2017 rluserman.info.gz
-rw-r--r--   1 root root  16007 Jul 20  2018 screen.info-1.gz
-rw-r--r--   1 root root  16310 Jul 20  2018 screen.info-2.gz
-rw-r--r--   1 root root  13140 Jul 20  2018 screen.info-3.gz
-rw-r--r--   1 root root  16704 Jul 20  2018 screen.info-4.gz
-rw-r--r--   1 root root  16549 Jul 20  2018 screen.info-5.gz
-rw-r--r--   1 root root   1384 Jul 20  2018 screen.info-6.gz
-rw-r--r--   1 root root   2264 Jul 20  2018 screen.info.gz
-rw-r--r--   1 root root  52258 Jan 30  2018 sed.info.gz
-rw-r--r--   1 root root   5323 Apr 22  2017 time.info.gz
-rw-r--r--   1 root root  71201 Apr  9  2019 wget.info.gz
```

ps：我是使用的wsl，发现里面支持info命令的文件不太多

我们使用`info gzip`（找个简单的）

```
Next: Overview,  Up: (dir)

GNU Gzip: General file (de)compression
**************************************

This manual is for GNU Gzip (version 1.6), and documents commands for
compressing and decompressing data.

   Copyright (C) 1998-1999, 2001-2002, 2006-2007, 2009-2013 Free
Software Foundation, Inc.

   Copyright (C) 1992, 1993 Jean-loup Gailly

     Permission is granted to copy, distribute and/or modify this
     document under the terms of the GNU Free Documentation License,
     Version 1.3 or any later version published by the Free Software
     Foundation; with no Invariant Sections, with no Front-Cover Texts,
     and with no Back-Cover Texts.  A copy of the license is included in
     the section entitled "GNU Free Documentation License".

* Menu:

* Overview::            Preliminary information.
* Sample::              Sample output from 'gzip'.
* Invoking gzip::       How to run 'gzip'.
* Advanced usage::      Concatenated files.
* Environment::         The 'GZIP' environment variable
* Tapes::               Using 'gzip' on tapes.
* Problems::            Reporting bugs.
* GNU Free Documentation License:: Copying and sharing this manual.
* Concept index::       Index of concepts.
```

仔细的看到上面这个显示的结果，里面的第一行显示了很多的信息喔！第一行里面的数据意义为：

- Next：下一个节点的名称为Getting Started，你也可以按『N』到下个节点去；
- Up：回到上一层的节点总揽画面，你也可以按下『U』回到上一层；
- Prev：前一个节点。但由于我们在top页面，也就是第一个节点，所以上面没有前一个节点的信息。

从第一行你可以知道这个节点的内容、来源与相关链接的信息。更有用的信息是，你可以透过直接按下N, P, U来去到下一个、上一个与上一层的节点(node)！非常的方便！ 第一行之后就是针对这个节点的说明。在上表的范例中，第二行以后的说明就是针对info.info内的Top这个节点所做的。

再来，你也会看到有『Menu』那个咚咚吧！底下共分为四小节，分别是Getting Started等等的，我们可以使用上下左右按键来将光标移动到该文字或者『 * 』上面，按下Enter， 就可以前往该小节了！另外，也可以按下[Tab]按键，就可以快速的将光标在上表的画面中的node间移动， 真的是非常的方便好用。如果将info.info内的各个节点串在一起并绘制成图表的话，情况有点像底下这样：

我们可以进入`Sample`

```
Next: Invoking gzip,  Prev: Overview,  Up: Top

2 Sample output
***************

Here are some realistic examples of running 'gzip'.

   This is the output of the command 'gzip -h':

     Usage: gzip [OPTION]... [FILE]...
     Compress or uncompress FILEs (by default, compress FILES in-place).

     Mandatory arguments to long options are mandatory for short options too.

       -c, --stdout      write on standard output, keep original files unchanged
       -d, --decompress  decompress
       -f, --force       force overwrite of output file and compress links
       -h, --help        give this help
       -k, --keep        keep (don't delete) input files
       -l, --list        list compressed file contents
       -L, --license     display software license
       -n, --no-name     do not save or restore the original name and time stamp
       -N, --name        save or restore the original name and time stamp
       -q, --quiet       suppress all warnings
       -r, --recursive   operate recursively on directories
       -S, --suffix=SUF  use suffix SUF on compressed files
       -t, --test        test compressed file integrity
       -v, --verbose     verbose mode
       -V, --version     display version number
       -1, --fast        compress faster
       -9, --best        compress better
         --rsyncable   Make rsync-friendly archive

     With no FILE, or when FILE is -, read standard input.

     Report bugs to <bug-gzip@gnu.org>.

   This is the output of the command 'gzip -v texinfo.tex':

     texinfo.tex:     69.3% -- replaced with texinfo.tex.gz

   The following command will find all regular '.gz' files in the
current directory and subdirectories (skipping file names that contain
newlines), and extract them in place without destroying the original,
stopping on the first failure:

     find . -name '*
     *' -prune -o -name '*.gz' -type f -print |
```

可以看到一些使用方法，结合man的使用看起来还是比较简单的