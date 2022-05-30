# test命令

检测系统上面某些文件或者是相关的属性

```
zhouning@DESKTOP-681HT7R:~$ test -e /dmtsai && echo "exist" || echo "Not exist"
Not exist
```

我们可以通过这样来检测/dmtsai 是否存在

| 测试的标志                                                   | 代表意义                                                     |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| **1. 关於某个档名的『文件类型』判断，如 test -e filename 表示存在否** |                                                              |
| -e                                                           | 该『档名』是否存在？(常用)                                   |
| -f                                                           | 该『档名』是否存在且为文件(file)？(常用)                     |
| -d                                                           | 该『档名』是否存在且为目录(directory)？(常用)                |
| -b                                                           | 该『档名』是否存在且为一个 block device 装置？               |
| -c                                                           | 该『档名』是否存在且为一个 character device 装置？           |
| -S                                                           | 该『档名』是否存在且为一个 Socket 文件？                     |
| -p                                                           | 该『档名』是否存在且为一个 FIFO (pipe) 文件？                |
| -L                                                           | 该『档名』是否存在且为一个连结档？                           |
| **2. 关於文件的权限侦测，如 test -r filename 表示可读否 (但 root 权限常有例外)** |                                                              |
| -r                                                           | 侦测该档名是否存在且具有『可读』的权限？                     |
| -w                                                           | 侦测该档名是否存在且具有『可写』的权限？                     |
| -x                                                           | 侦测该档名是否存在且具有『可运行』的权限？                   |
| -u                                                           | 侦测该档名是否存在且具有『SUID』的属性？                     |
| -g                                                           | 侦测该档名是否存在且具有『SGID』的属性？                     |
| -k                                                           | 侦测该档名是否存在且具有『Sticky bit』的属性？               |
| -s                                                           | 侦测该档名是否存在且为『非空白文件』？                       |
| **3. 两个文件之间的比较，如： test file1 -nt file2**         |                                                              |
| -nt                                                          | (newer than)判断 file1 是否比 file2 新                       |
| -ot                                                          | (older than)判断 file1 是否比 file2 旧                       |
| -ef                                                          | 判断 file1 与 file2 是否为同一文件，可用在判断 hard link 的判定上。 主要意义在判定，两个文件是否均指向同一个 inode 哩！ |
| **4. 关於两个整数之间的判定，例如 test n1 -eq n2**           |                                                              |
| -eq                                                          | 两数值相等 (equal)                                           |
| -ne                                                          | 两数值不等 (not equal)                                       |
| -gt                                                          | n1 大於 n2 (greater than)                                    |
| -lt                                                          | n1 小於 n2 (less than)                                       |
| -ge                                                          | n1 大於等於 n2 (greater than or equal)                       |
| -le                                                          | n1 小於等於 n2 (less than or equal)                          |
| **5. 判定字串的数据**                                        |                                                              |
| test -z string                                               | 判定字串是否为 0 ？若 string 为空字串，则为 true             |
| test -n string                                               | 判定字串是否非为 0 ？若 string 为空字串，则为 false。 注： -n 亦可省略 |
| test str1 = str2                                             | 判定 str1 是否等於 str2 ，若相等，则回传 true                |
| test str1 != str2                                            | 判定 str1 是否不等於 str2 ，若相等，则回传 false             |
| **6. 多重条件判定，例如： test -r filename -a -x filename**  |                                                              |
| -a                                                           | (and)两状况同时成立！例如 test -r file -a -x file，则 file 同时具有 r 与 x 权限时，才回传 true。 |
| -o                                                           | (or)两状况任何一个成立！例如 test -r file -o -x file，则 file 具有 r 或 x 权限时，就可回传 true。 |
| !                                                            | 反相状态，如 test ! -x file ，当 file 不具有 x 时，回传 true |

利用 test 来帮我们写几个简单的例子。首先，判断一下，让使用者输入一个档名，我们判断：

1. 这个文件是否存在，若不存在则给予一个『Filename does not exist』的信息，并中断程序；
2. 若这个文件存在，则判断他是个文件或目录，结果输出『Filename is regular file』或 『Filename is directory』
3. 判断一下，运行者的身份对这个文件或目录所拥有的权限，并输出权限数据！

你可以先自行创作看看，然后再跟底下的结果讨论讨论。注意利用 test 与 && 还有 || 等标志！

```

[root@www scripts]# vim sh05.sh
#!/bin/bash
# Program:
#	User input a filename, program will check the flowing:
#	1.) exist? 2.) file/directory? 3.) file permissions 
# History:
# 2005/08/25	VBird	First release
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
export PATH

# 1. 让使用者输入档名，并且判断使用者是否真的有输入字串？
echo -e "Please input a filename, I will check the filename's type and \
permission. \n\n"
read -p "Input a filename : " filename
test -z $filename && echo "You MUST input a filename." && exit 0
# 2. 判断文件是否存在？若不存在则显示信息并结束脚本
test ! -e $filename && echo "The filename '$filename' DO NOT exist" && exit 0
# 3. 开始判断文件类型与属性
test -f $filename && filetype="regulare file"
test -d $filename && filetype="directory"
test -r $filename && perm="readable"
test -w $filename && perm="$perm writable"
test -x $filename && perm="$perm executable"
# 4. 开始输出资讯！
echo "The filename: $filename is a $filetype"
echo "And the permissions are : $perm"
```

运行

```
zhouning@DESKTOP-681HT7R:~/scripts$ sh sh05.sh
Please input a filename, I will check the filename's type and   permission.


Input a filename : /root
The filename: /root is a directory
And the permissions are :
```

