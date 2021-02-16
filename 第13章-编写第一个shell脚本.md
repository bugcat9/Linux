# 编写shell脚本的hello world

```
zhouning@DESKTOP-681HT7R:~$ mkdir scripts; cd scripts
zhouning@DESKTOP-681HT7R:~/scripts$ vim sh01.sh
#!/bin/bash
#Program
#       this program shows "hello world " in ypur screen
#History:
#2021/08/23 zhouning
#
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
export PATH
echo "hello world"
exit 0
```

1. 第一行 #!/bin/bash 在宣告这个 script 使用的 shell 名称：
   因为我们使用的是 bash ，所以，必须要以『 **#!/bin/bash** 』来宣告这个文件内的语法使用 bash 的语法！那么当这个程序被运行时，他就能够加载 bash 的相关环境配置档 (一般来说就是 [non-login shell 的 ~/.bashrc](http://cn.linux.vbird.org/linux_basic/0320bash.php#settings_bashrc_shell))， 并且运行 bash 来使我们底下的命令能够运行！这很重要的！(在很多状况中，如果没有配置好这一行， 那么该程序很可能会无法运行，因为系统可能无法判断该程序需要使用什么 shell 来运行啊！)

   

2. 程序内容的说明：
   整个 script 当中，除了第一行的『 #! 』是用来宣告 shell 的之外，其他的 # 都是『注解』用途！ 所以上面的程序当中，第二行以下就是用来说明整个程序的基本数据。一般来说， 建议你一定要养成说明该 script 的：1. 内容与功能； 2. 版本资讯； 3. 作者与联络方式； 4. 建档日期；5. 历史纪录 等等。这将有助於未来程序的改写与 debug 呢！

   

3. 主要环境变量的宣告：
   建议务必要将一些重要的环境变量配置好，鸟哥个人认为， PATH 与 LANG (如果有使用到输出相关的资讯时) 是当中最重要的！ 如此一来，则可让我们这支程序在进行时，可以直接下达一些外部命令，而不必写绝对路径呢！比较好啦！

   

4. 主要程序部分
   就将主要的程序写好即可！在这个例子当中，就是 echo 那一行啦！

   

5. 运行成果告知 (定义回传值)
   是否记得我们在[第十一章](http://cn.linux.vbird.org/linux_basic/0320bash.php)里面要讨论一个命令的运行成功与否，可以使用 [$?](http://cn.linux.vbird.org/linux_basic/0320bash.php#redirect_com) 这个变量来观察～ 那么我们也可以利用 exit 这个命令来让程序中断，并且回传一个数值给系统。 在我们这个例子当中，鸟哥使用 exit 0 ，这代表离开 script 并且回传一个 0 给系统， 所以我运行完这个 script 后，若接著下达 echo $? 则可得到 0 的值喔！ 更聪明的读者应该也知道了，呵呵！利用这个 exit n (n 是数字) 的功能，我们还可以自订错误信息， 让这支程序变得更加的 smart 呢！

运行结果

```
zhouning@DESKTOP-681HT7R:~/scripts$ sh sh01.sh
hello world
```

