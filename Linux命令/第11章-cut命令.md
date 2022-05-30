### cut

cut命令可以将一段信息的某一段截取出来，看看`--help`，可以知道其实cut是可以处理文件和标准输入流的，然后从中截取信息

```
zhouning@DESKTOP-681HT7R:~$ cut --help
Usage: cut OPTION... [FILE]...
Print selected parts of lines from each FILE to standard output.

With no FILE, or when FILE is -, read standard input.

Mandatory arguments to long options are mandatory for short options too.
  -b, --bytes=LIST        select only these bytes
  -c, --characters=LIST   select only these characters
  -d, --delimiter=DELIM   use DELIM instead of TAB for field delimiter
  -f, --fields=LIST       select only these fields;  also print any line
                            that contains no delimiter character, unless
                            the -s option is specified
  -n                      (ignored)
      --complement        complement the set of selected bytes, characters
                            or fields
  -s, --only-delimited    do not print lines not containing delimiters
      --output-delimiter=STRING  use STRING as the output delimiter
                            the default is to use the input delimiter
  -z, --zero-terminated    line delimiter is NUL, not newline
      --help     display this help and exit
      --version  output version information and exit

Use one, and only one of -b, -c or -f.  Each LIST is made up of one
range, or many ranges separated by commas.  Selected input is written
in the same order that it is read, and is written exactly once.
Each range is one of:

  N     N'th byte, character or field, counted from 1
  N-    from N'th byte, character or field, to end of line
  N-M   from N'th to M'th (included) byte, character or field
  -M    from first to M'th (included) byte, character or field

GNU coreutils online help: <http://www.gnu.org/software/coreutils/>
Report cut translation bugs to <http://translationproject.org/team/>
Full documentation at: <http://www.gnu.org/software/coreutils/cut>
or available locally via: info '(coreutils) cut invocation'
```

###  -b, --bytes=LIST        select only these bytes，按照字节的形式来来抽取，LIST表示按照升序，提取的是每一行的数据

查看环境变量

```
zhouning@DESKTOP-681HT7R:~$ export
declare -x HOME="/home/zhouning"
declare -x HOSTTYPE="x86_64"
declare -x LANG="C.UTF-8"
declare -x LESSCLOSE="/usr/bin/lesspipe %s %s"
declare -x LESSOPEN="| /usr/bin/lesspipe %s"
declare -x LOGNAME="zhouning"
declare -x LS_COLORS="rs=0:di=01;34:ln=01;36:mh=00:pi=40;33:so=01;35:do=01;35:bd=40;33;01:cd=40;33;01:or=40;31;01:mi=00:su=37;41:sg=30;43:ca=30;41:tw=30;42:ow=34;42:st=37;44:ex=01;32:*.tar=01;31:*.tgz=01;31:*.arc=01;31:*.arj=01;31:*.taz=01;31:*.lha=01;31:*.lz4=01;31:*.lzh=01;31:*.lzma=01;31:*.tlz=01;31:*.txz=01;31:*.tzo=01;31:*.t7z=01;31:*.zip=01;31:*.z=01;31:*.Z=01;31:*.dz=01;31:*.gz=01;31:*.lrz=01;31:*.lz=01;31:*.lzo=01;31:*.xz=01;31:*.zst=01;31:*.tzst=01;31:*.bz2=01;31:*.bz=01;31:*.tbz=01;31:*.tbz2=01;31:*.tz=01;31:*.deb=01;31:*.rpm=01;31:*.jar=01;31:*.war=01;31:*.ear=01;31:*.sar=01;31:*.rar=01;31:*.alz=01;31:*.ace=01;31:*.zoo=01;31:*.cpio=01;31:*.7z=01;31:*.rz=01;31:*.cab=01;31:*.wim=01;31:*.swm=01;31:*.dwm=01;31:*.esd=01;31:*.jpg=01;35:*.jpeg=01;35:*.mjpg=01;35:*.mjpeg=01;35:*.gif=01;35:*.bmp=01;35:*.pbm=01;35:*.pgm=01;35:*.ppm=01;35:*.tga=01;35:*.xbm=01;35:*.xpm=01;35:*.tif=01;35:*.tiff=01;35:*.png=01;35:*.svg=01;35:*.svgz=01;35:*.mng=01;35:*.pcx=01;35:*.mov=01;35:*.mpg=01;35:*.mpeg=01;35:*.m2v=01;35:*.mkv=01;35:*.webm=01;35:*.ogm=01;35:*.mp4=01;35:*.m4v=01;35:*.mp4v=01;35:*.vob=01;35:*.qt=01;35:*.nuv=01;35:*.wmv=01;35:*.asf=01;35:*.rm=01;35:*.rmvb=01;35:*.flc=01;35:*.avi=01;35:*.fli=01;35:*.flv=01;35:*.gl=01;35:*.dl=01;35:*.xcf=01;35:*.xwd=01;35:*.yuv=01;35:*.cgm=01;35:*.emf=01;35:*.ogv=01;35:*.ogx=01;35:*.aac=00;36:*.au=00;36:*.flac=00;36:*.m4a=00;36:*.mid=00;36:*.midi=00;36:*.mka=00;36:*.mp3=00;36:*.mpc=00;36:*.ogg=00;36:*.ra=00;36:*.wav=00;36:*.oga=00;36:*.opus=00;36:*.spx=00;36:*.xspf=00;36:"
declare -x NAME="DESKTOP-681HT7R"
declare -x OLDPWD
declare -x PATH="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/mnt/d/Program Files/NVIDIA/CUDA/v10.2/bin:/mnt/d/Program Files/NVIDIA/CUDA/v10.2/libnvvp:/mnt/c/Windows/system32:/mnt/c/Windows:/mnt/c/Windows/System32/Wbem:/mnt/c/Windows/System32/WindowsPowerShell/v1.0/:/mnt/c/Windows/System32/OpenSSH/:/mnt/d/Program Files/Git/cmd:/mnt/d/Program Files/Java/jdk1.8.0_261/bin:/mnt/d/Program Files/apache-maven-3.6.3/bin:/mnt/c/Program Files (x86)/NVIDIA Corporation/PhysX/Common:/mnt/c/Program Files/NVIDIA Corporation/NVIDIA NvDLISR:/mnt/c/Program Files/Docker/Docker/resources/bin:/mnt/c/ProgramData/DockerDesktop/version-bin:/mnt/c/WINDOWS/system32:/mnt/c/WINDOWS:/mnt/c/WINDOWS/System32/Wbem:/mnt/c/WINDOWS/System32/WindowsPowerShell/v1.0/:/mnt/c/WINDOWS/System32/OpenSSH/:/mnt/d/Program Files/nodejs/:/mnt/d/Program Files/TortoiseGit/bin:/mnt/d/ProgramData/Anaconda3:/mnt/d/ProgramData/Anaconda3/Scripts:/mnt/d/ProgramData/Anaconda3/Library/mingw-w64/bin:/mnt/d/ProgramData/Anaconda3/Library/bin:/mnt/c/Program Files/NVIDIA Corporation/Nsight Compute 2019.5.0/:/mnt/d/scoop/shims:/mnt/c/Users/Administrator/AppData/Local/Microsoft/WindowsApps:/mnt/d/Users/Administrator/AppData/Local/Programs/Microsoft VS Code/bin:/mnt/c/Users/Administrator/AppData/Local/Microsoft/WindowsApps:/mnt/c/Users/Administrator/AppData/Roaming/npm:/snap/bin"
declare -x PWD="/home/zhouning"
declare -x SHELL="/bin/bash"
declare -x SHLVL="1"
declare -x TERM="xterm-256color"
declare -x USER="zhouning"
declare -x WSLENV=""
declare -x WSL_DISTRO_NAME="Ubuntu-18.04"
declare -x WSL_INTEROP="/run/WSL/9_interop"
declare -x XDG_DATA_DIRS="/usr/local/share:/usr/share:/var/lib/snapd/desktop"
```

提取每行第3个字节

```
zhouning@DESKTOP-681HT7R:~$ export | cut -b 3
c
c
c
c
c
c
c
c
c
c
c
c
c
c
c
c
c
c
c
```

提取每行1到12个字节

```
zhouning@DESKTOP-681HT7R:~$ export | cut -b 1-12
declare -x H
declare -x H
declare -x L
declare -x L
declare -x L
declare -x L
declare -x L
declare -x N
declare -x O
declare -x P
declare -x P
declare -x S
declare -x S
declare -x T
declare -x U
declare -x W
declare -x W
declare -x W
declare -x X
```

### -c, --characters=LIST   select only these characters以字符的形式提取信息

提取每行第3个字符

```
zhouning@DESKTOP-681HT7R:~$ export | cut -c 3
c
c
c
c
c
c
c
c
c
c
c
c
c
c
c
c
c
c
c
```

提取每行1-12个字符

```
zhouning@DESKTOP-681HT7R:~$ export | cut -c 1-12
declare -x H
declare -x H
declare -x L
declare -x L
declare -x L
declare -x L
declare -x L
declare -x N
declare -x O
declare -x P
declare -x P
declare -x S
declare -x S
declare -x T
declare -x U
declare -x W
declare -x W
declare -x W
declare -x X
```

这里跟上面相同emmm应该是因为是英文的原因，毕竟字节跟字符还是有不同的

### -d和-f

-d和-f一般是同时使用的，单独使用-d没有效果。-d后面接分割字符默认是“tab”，-f表示取出第几段

我们vim一个test.txt在里面写上`this	is	a	man`

因为默认以"tab"分段，所以取第一段

```
zhouning@DESKTOP-681HT7R:~$ cat test.txt
this    is      a       man
zhouning@DESKTOP-681HT7R:~$ cut -f 1 test.txt
this
```

取3到5个，取第3个和第5个

```
zhouning@DESKTOP-681HT7R:~$ echo $PATH
/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/mnt/d/Program Files/NVIDIA/CUDA/v10.2/bin:/mnt/d/Program Files/NVIDIA/CUDA/v10.2/libnvvp:/mnt/c/Windows/system32:/mnt/c/Windows:/mnt/c/Windows/System32/Wbem:/mnt/c/Windows/System32/WindowsPowerShell/v1.0/:/mnt/c/Windows/System32/OpenSSH/:/mnt/d/Program Files/Git/cmd:/mnt/d/Program Files/Java/jdk1.8.0_261/bin:/mnt/d/Program Files/apache-maven-3.6.3/bin:/mnt/c/Program Files (x86)/NVIDIA Corporation/PhysX/Common:/mnt/c/Program Files/NVIDIA Corporation/NVIDIA NvDLISR:/mnt/c/Program Files/Docker/Docker/resources/bin:/mnt/c/ProgramData/DockerDesktop/version-bin:/mnt/c/WINDOWS/system32:/mnt/c/WINDOWS:/mnt/c/WINDOWS/System32/Wbem:/mnt/c/WINDOWS/System32/WindowsPowerShell/v1.0/:/mnt/c/WINDOWS/System32/OpenSSH/:/mnt/d/Program Files/nodejs/:/mnt/d/Program Files/TortoiseGit/bin:/mnt/d/ProgramData/Anaconda3:/mnt/d/ProgramData/Anaconda3/Scripts:/mnt/d/ProgramData/Anaconda3/Library/mingw-w64/bin:/mnt/d/ProgramData/Anaconda3/Library/bin:/mnt/c/Program Files/NVIDIA Corporation/Nsight Compute 2019.5.0/:/mnt/d/scoop/shims:/mnt/c/Users/Administrator/AppData/Local/Microsoft/WindowsApps:/mnt/d/Users/Administrator/AppData/Local/Programs/Microsoft VS Code/bin:/mnt/c/Users/Administrator/AppData/Local/Microsoft/WindowsApps:/mnt/c/Users/Administrator/AppData/Roaming/npm:/snap/bin
zhouning@DESKTOP-681HT7R:~$ echo $PATH | cut -d : -f 3-5
/usr/sbin:/usr/bin:/sbin
zhouning@DESKTOP-681HT7R:~$ echo $PATH | cut -d : -f 3,5
/usr/sbin:/sbin
```

