# shell脚本中的默认变量

script 针对参数已经有配置好一些变量名称

```
/path/to/scriptname  opt1  opt2  opt3  opt4 
       $0             $1    $2    $3    $4
```

除此之外还有一些特殊参数

- $# ：代表后接的参数『个数』，以上表为例这里显示为『 4 』；

- \$@ ：代表『 "\$1" "\$2" "\$3" "$4" 』之意，每个变量是独立的(用双引号括起来)；

- \$* ：代表『 "\$1c\$2c\$3c\$4" 』，其中 c 为分隔字节，默认为空白键， 所以本例中代表『 "\$1 \$2 \$3 \$4" 』之意。

  那个 \$@ 与 \$* 基本上还是有所不同啦！不过，一般使用情况下可以直接记忆 $@ 即可

编写一个脚本实现

- 程序的档名为何？
- 共有几个参数？
- 若参数的个数小於 2 则告知使用者参数数量太少
- 全部的参数内容为何？
- 第一个参数为何？
- 第二个参数为何

```
[root@www scripts]# vim sh07.sh
#!/bin/bash
# Program:
#	Program shows the script name, parameters...
# History:
# 2009/02/17	VBird	First release
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
export PATH

echo "The script name is        ==> $0"
echo "Total parameter number is ==> $#"
[ "$#" -lt 2 ] && echo "The number of parameter is less than 2.  Stop here." \
	&& exit 0
echo "Your whole parameter is   ==> '$@'"
echo "The 1st parameter         ==> $1"
echo "The 2nd parameter         ==> $2"
```

运行结果

```
zhouning@DESKTOP-681HT7R:~/scripts$ sh sh07.sh theone haha quot
The script name is        ==> sh07.sh
Total parameter number is ==> 3
Your whole parameter is   ==> 'theone haha quot'
The 1st parameter         ==> theone
The 2nd parameter         ==> haha
zhouning@DESKTOP-681HT7R:~/scripts$ sh sh07.sh theone haha
The script name is        ==> sh07.sh
Total parameter number is ==> 2
Your whole parameter is   ==> 'theone haha'
The 1st parameter         ==> theone
The 2nd parameter         ==> haha
zhouning@DESKTOP-681HT7R:~/scripts$ sh sh07.sh theone
The script name is        ==> sh07.sh
Total parameter number is ==> 1
The number of parameter is less than 2.  Stop here.
```

