# shell中的变量使用

变量取用，使用类似于`echo $HOME`、`echo ${HOME}`

```
zhouning@DESKTOP-681HT7R:~$ echo $HOME
/home/zhouning
zhouning@DESKTOP-681HT7R:~$ echo ${HOME}
/home/zhouning
```

鸟哥当中变量配置规则

1. 变量与变量内容以一个等号『=』来连结，如下所示：
   『myname=VBird』

   

2. 等号两边不能直接接空格符，如下所示为错误：
   『myname = VBird』或『myname=VBird Tsai』

   

3. 变量名称只能是英文字母与数字，但是开头字符不能是数字，如下为错误：
   『2myname=VBird』

   

4. 变量内容若有空格符可使用双引号『"』或单引号『'』将变量内容结合起来，但

   - 双引号内的特殊字符如 $ 等，可以保有原本的特性，如下所示：
     『var="lang is $LANG"』则『echo $var』可得『lang is en_US』
   - 单引号内的特殊字符则仅为一般字符 (纯文本)，如下所示：
     『var='lang is $LANG'』则『echo $var』可得『lang is $LANG』

5. 可用跳脱字符『 \ 』将特殊符号(如 [Enter], $, \, 空格符, '等)变成一般字符；

   

6. 在一串命令中，还需要藉由其他的命令提供的信息，可以使用反单引号『`命令`』或 『$(命令)』。特别注意，那个 ` 是键盘上方的数字键 1 左边那个按键，而不是单引号！ 例如想要取得核心版本的配置：
   『version=$(uname -r)』再『echo $version』可得『2.6.18-128.el5』

   

7. 若该变量为扩增变量内容时，则可用 "$变量名称" 或 ${变量} 累加内容，如下所示：
   『PATH="$PATH":/home/bin』

   

8. 若该变量需要在其他子程序运行，则需要以 export 来使变量变成环境变量：
   『export PATH』

   

9. 通常大写字符为系统默认变量，自行配置变量可以使用小写字符，方便判断 (纯粹依照使用者兴趣与嗜好) ；

   

10. 取消变量的方法为使用 unset ：『unset 变量名称』例如取消 myname 的配置：
    『unset myname』



## 环境变量

env查看所有环境变量

```
zhouning@DESKTOP-681HT7R:~$ env
LS_COLORS=rs=0:di=01;34:ln=01;36:mh=00:pi=40;33:so=01;35:do=01;35:bd=40;33;01:cd=40;33;01:or=40;31;01:mi=00:su=37;41:sg=30;43:ca=30;41:tw=30;42:ow=34;42:st=37;44:ex=01;32:*.tar=01;31:*.tgz=01;31:*.arc=01;31:*.arj=01;31:*.taz=01;31:*.lha=01;31:*.lz4=01;31:*.lzh=01;31:*.lzma=01;31:*.tlz=01;31:*.txz=01;31:*.tzo=01;31:*.t7z=01;31:*.zip=01;31:*.z=01;31:*.Z=01;31:*.dz=01;31:*.gz=01;31:*.lrz=01;31:*.lz=01;31:*.lzo=01;31:*.xz=01;31:*.zst=01;31:*.tzst=01;31:*.bz2=01;31:*.bz=01;31:*.tbz=01;31:*.tbz2=01;31:*.tz=01;31:*.deb=01;31:*.rpm=01;31:*.jar=01;31:*.war=01;31:*.ear=01;31:*.sar=01;31:*.rar=01;31:*.alz=01;31:*.ace=01;31:*.zoo=01;31:*.cpio=01;31:*.7z=01;31:*.rz=01;31:*.cab=01;31:*.wim=01;31:*.swm=01;31:*.dwm=01;31:*.esd=01;31:*.jpg=01;35:*.jpeg=01;35:*.mjpg=01;35:*.mjpeg=01;35:*.gif=01;35:*.bmp=01;35:*.pbm=01;35:*.pgm=01;35:*.ppm=01;35:*.tga=01;35:*.xbm=01;35:*.xpm=01;35:*.tif=01;35:*.tiff=01;35:*.png=01;35:*.svg=01;35:*.svgz=01;35:*.mng=01;35:*.pcx=01;35:*.mov=01;35:*.mpg=01;35:*.mpeg=01;35:*.m2v=01;35:*.mkv=01;35:*.webm=01;35:*.ogm=01;35:*.mp4=01;35:*.m4v=01;35:*.mp4v=01;35:*.vob=01;35:*.qt=01;35:*.nuv=01;35:*.wmv=01;35:*.asf=01;35:*.rm=01;35:*.rmvb=01;35:*.flc=01;35:*.avi=01;35:*.fli=01;35:*.flv=01;35:*.gl=01;35:*.dl=01;35:*.xcf=01;35:*.xwd=01;35:*.yuv=01;35:*.cgm=01;35:*.emf=01;35:*.ogv=01;35:*.ogx=01;35:*.aac=00;36:*.au=00;36:*.flac=00;36:*.m4a=00;36:*.mid=00;36:*.midi=00;36:*.mka=00;36:*.mp3=00;36:*.mpc=00;36:*.ogg=00;36:*.ra=00;36:*.wav=00;36:*.oga=00;36:*.opus=00;36:*.spx=00;36:*.xspf=00;36:
HOSTTYPE=x86_64
LESSCLOSE=/usr/bin/lesspipe %s %s
LANG=C.UTF-8
WSL_INTEROP=/run/WSL/9_interop
WSL_DISTRO_NAME=Ubuntu-18.04
USER=zhouning
PWD=/home/zhouning
HOME=/home/zhouning
NAME=DESKTOP-681HT7R
XDG_DATA_DIRS=/usr/local/share:/usr/share:/var/lib/snapd/desktop
SHELL=/bin/bash
TERM=xterm-256color
SHLVL=1
LOGNAME=zhouning
PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/mnt/d/Program Files/NVIDIA/CUDA/v10.2/bin:/mnt/d/Program Files/NVIDIA/CUDA/v10.2/libnvvp:/mnt/c/Windows/system32:/mnt/c/Windows:/mnt/c/Windows/System32/Wbem:/mnt/c/Windows/System32/WindowsPowerShell/v1.0/:/mnt/c/Windows/System32/OpenSSH/:/mnt/d/Program Files/Git/cmd:/mnt/d/Program Files/Java/jdk1.8.0_261/bin:/mnt/d/Program Files/apache-maven-3.6.3/bin:/mnt/c/Program Files (x86)/NVIDIA Corporation/PhysX/Common:/mnt/c/Program Files/NVIDIA Corporation/NVIDIA NvDLISR:/mnt/c/Program Files/Docker/Docker/resources/bin:/mnt/c/ProgramData/DockerDesktop/version-bin:/mnt/c/WINDOWS/system32:/mnt/c/WINDOWS:/mnt/c/WINDOWS/System32/Wbem:/mnt/c/WINDOWS/System32/WindowsPowerShell/v1.0/:/mnt/c/WINDOWS/System32/OpenSSH/:/mnt/d/Program Files/nodejs/:/mnt/d/Program Files/TortoiseGit/bin:/mnt/d/ProgramData/Anaconda3:/mnt/d/ProgramData/Anaconda3/Scripts:/mnt/d/ProgramData/Anaconda3/Library/mingw-w64/bin:/mnt/d/ProgramData/Anaconda3/Library/bin:/mnt/c/Program Files/NVIDIA Corporation/Nsight Compute 2019.5.0/:/mnt/d/scoop/shims:/mnt/c/Users/Administrator/AppData/Local/Microsoft/WindowsApps:/mnt/d/Users/Administrator/AppData/Local/Programs/Microsoft VS Code/bin:/mnt/c/Users/Administrator/AppData/Local/Microsoft/WindowsApps:/mnt/c/Users/Administrator/AppData/Roaming/npm:/snap/bin
WSLENV=
LESSOPEN=| /usr/bin/lesspipe %s
_=/usr/bin/env
```

set查看所有变量，包括环境变量和自定义的变量

```
zhouning@DESKTOP-681HT7R:~$ set
BASH=/bin/bash
BASHOPTS=checkwinsize:cmdhist:complete_fullquote:expand_aliases:extglob:extquote:force_fignore:histappend:interactive_comments:login_shell:progcomp:promptvars:sourcepath
BASH_ALIASES=()
BASH_ARGC=()
BASH_ARGV=()
BASH_CMDS=()
BASH_COMPLETION_VERSINFO=([0]="2" [1]="8")
BASH_LINENO=()
BASH_REMATCH=()
BASH_SOURCE=()
BASH_VERSINFO=([0]="4" [1]="4" [2]="20" [3]="1" [4]="release" [5]="x86_64-pc-linux-gnu")
BASH_VERSION='4.4.20(1)-release'
COLUMNS=189
COMP_WORDBREAKS=$' \t\n"\'><=;|&(:'
DIRSTACK=()
EUID=1000
GROUPS=()
HISTCONTROL=ignoreboth
HISTFILE=/home/zhouning/.bash_history
HISTFILESIZE=2000
HISTSIZE=1000
HOME=/home/zhouning
HOSTNAME=DESKTOP-681HT7R
HOSTTYPE=x86_64
IFS=$' \t\n'
LANG=C.UTF-8
LESSCLOSE='/usr/bin/lesspipe %s %s'
LESSOPEN='| /usr/bin/lesspipe %s'
LINES=50
LOGNAME=zhouning
LS_COLORS='rs=0:di=01;34:ln=01;36:mh=00:pi=40;33:so=01;35:do=01;35:bd=40;33;01:cd=40;33;01:or=40;31;01:mi=00:su=37;41:sg=30;43:ca=30;41:tw=30;42:ow=34;42:st=37;44:ex=01;32:*.tar=01;31:*.tgz=01;31:*.arc=01;31:*.arj=01;31:*.taz=01;31:*.lha=01;31:*.lz4=01;31:*.lzh=01;31:*.lzma=01;31:*.tlz=01;31:*.txz=01;31:*.tzo=01;31:*.t7z=01;31:*.zip=01;31:*.z=01;31:*.Z=01;31:*.dz=01;31:*.gz=01;31:*.lrz=01;31:*.lz=01;31:*.lzo=01;31:*.xz=01;31:*.zst=01;31:*.tzst=01;31:*.bz2=01;31:*.bz=01;31:*.tbz=01;31:*.tbz2=01;31:*.tz=01;31:*.deb=01;31:*.rpm=01;31:*.jar=01;31:*.war=01;31:*.ear=01;31:*.sar=01;31:*.rar=01;31:*.alz=01;31:*.ace=01;31:*.zoo=01;31:*.cpio=01;31:*.7z=01;31:*.rz=01;31:*.cab=01;31:*.wim=01;31:*.swm=01;31:*.dwm=01;31:*.esd=01;31:*.jpg=01;35:*.jpeg=01;35:*.mjpg=01;35:*.mjpeg=01;35:*.gif=01;35:*.bmp=01;35:*.pbm=01;35:*.pgm=01;35:*.ppm=01;35:*.tga=01;35:*.xbm=01;35:*.xpm=01;35:*.tif=01;35:*.tiff=01;35:*.png=01;35:*.svg=01;35:*.svgz=01;35:*.mng=01;35:*.pcx=01;35:*.mov=01;35:*.mpg=01;35:*.mpeg=01;35:*.m2v=01;35:*.mkv=01;35:*.webm=01;35:*.ogm=01;35:*.mp4=01;35:*.m4v=01;35:*.mp4v=01;35:*.vob=01;35:*.qt=01;35:*.nuv=01;35:*.wmv=01;35:*.asf=01;35:*.rm=01;35:*.rmvb=01;35:*.flc=01;35:*.avi=01;35:*.fli=01;35:*.flv=01;35:*.gl=01;35:*.dl=01;35:*.xcf=01;35:*.xwd=01;35:*.yuv=01;35:*.cgm=01;35:*.emf=01;35:*.ogv=01;35:*.ogx=01;35:*.aac=00;36:*.au=00;36:*.flac=00;36:*.m4a=00;36:*.mid=00;36:*.midi=00;36:*.mka=00;36:*.mp3=00;36:*.mpc=00;36:*.ogg=00;36:*.ra=00;36:*.wav=00;36:*.oga=00;36:*.opus=00;36:*.spx=00;36:*.xspf=00;36:'
。。。。省略
```

## export作用

https://blog.csdn.net/wudinaniya/article/details/106445078

光export会把所有环境变量展示出来

## 变量键盘读取、数组与宣告： read, declare

### read

要读取来自键盘输入的变量，就是用 read 这个命令了。这个命令最常被用在 shell script 的撰写当中， 想要跟使用者对谈？用这个命令就对了。关于 script 的写法，我们会在第十三章介绍，底下先来瞧一瞧 read 的相关语法吧！

```
zhouning@DESKTOP-681HT7R:~$ read atest
this is a test
zhouning@DESKTOP-681HT7R:~$ echo $atest
this is a test
zhouning@DESKTOP-681HT7R:~$ read -p "Please keyin your name: " -t 30 named
Please keyin your name: zn
zhouning@DESKTOP-681HT7R:~$ echo $named
zn
```

read 之后不加任何参数，直接加上变量名称，那么底下就会主动出现一个空白行等待你的输入(如范例一)。 如果加上 -t 后面接秒数，例如上面的范例二，那么 30 秒之内没有任何动作时， 该命令就会自动略过了～如果是加上 -p ，嘿嘿！在输入的光标前就会有比较多可以用的提示字符给我们参考！ 在命令的下达里面，比较美观啦！ ^_^

### declare

declare 或 typeset 是一样的功能，就是在『宣告变量的类型』。如果使用 declare 后面并没有接任何参数，那么 bash 就会主动的将所有的变量名称与内容通通叫出来，就好像使用 set 一样啦！ 那么 declare 还有什么语法呢？看看先：

```
[root@www ~]# declare [-aixr] variable
选项与参数：
-a  ：将后面名为 variable 的变量定义成为数组 (array) 类型
-i  ：将后面名为 variable 的变量定义成为整数数字 (integer) 类型
-x  ：用法与 export 一样，就是将后面的 variable 变成环境变量；
-r  ：将变量配置成为 readonly 类型，该变量不可被更改内容，也不能 unset
```

```
zhouning@DESKTOP-681HT7R:~$ sum=100+300+50
zhouning@DESKTOP-681HT7R:~$ echo $sum
100+300+50
zhouning@DESKTOP-681HT7R:~$ declare -i sum=100+300+50
zhouning@DESKTOP-681HT7R:~$ echo $sum
450
```

-x：

```
zhouning@DESKTOP-681HT7R:~$ declare -x sum
zhouning@DESKTOP-681HT7R:~$ export | grep sum
declare -ix sum="450"
```

-r：

```
zhouning@DESKTOP-681HT7R:~$ declare -r sum
zhouning@DESKTOP-681HT7R:~$ sum=tesgting
-bash: sum: readonly variable
```

+x，变成非环境变量

```
zhouning@DESKTOP-681HT7R:~$ declare +x sum
zhouning@DESKTOP-681HT7R:~$ export | grep sum
```

-p

```
zhouning@DESKTOP-681HT7R:~$ declare -p sum
declare -ir sum="450"
```

