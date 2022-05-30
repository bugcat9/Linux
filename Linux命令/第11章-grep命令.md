# grep命令

Linux系统中grep命令是一种强大的文本搜索工具，它能使用正则表达式搜索文本，并把匹 配的行打印出来。grep全称是Global Regular Expression Print，表示全局正则表达式版本，它的使用权限是所有用户。

命令格式

```
grep [option] pattern file
```

命令功能

用于过滤/搜索的特定字符。可使用正则表达式能多种命令配合使用，使用上十分灵活。

命令参数

```
-a   --text   #不要忽略二进制的数据，简单说将 binary 文件以 text 文件的方式搜寻数据

-A<显示行数>   --after-context=<显示行数>   #除了显示符合范本样式的那一列之外，并显示该行之后的内容。   

-b   --byte-offset   #在显示符合样式的那一行之前，标示出该行第一个字符的编号。   

-B<显示行数>   --before-context=<显示行数>   #除了显示符合样式的那一行之外，并显示该行之前的内容。   

-c    --count   #计算符合样式的列数。   

-C<显示行数>    --context=<显示行数>或-<显示行数>   #除了显示符合样式的那一行之外，并显示该行之前后的内容。   

-d <动作>      --directories=<动作>   #当指定要查找的是目录而非文件时，必须使用这项参数，否则grep指令将回报信息并停止动作。   

-e<范本样式>  --regexp=<范本样式>   #指定字符串做为查找文件内容的样式。   

-E      --extended-regexp   #将样式为延伸的普通表示法来使用。   

-f<规则文件>  --file=<规则文件>   #指定规则文件，其内容含有一个或多个规则样式，让grep查找符合规则条件的文件内容，格式为每行一个规则样式。   

-F   --fixed-regexp   #将样式视为固定字符串的列表。   

-G   --basic-regexp   #将样式视为普通的表示法来使用。   

-h   --no-filename   #在显示符合样式的那一行之前，不标示该行所属的文件名称。   

-H   --with-filename   #在显示符合样式的那一行之前，表示该行所属的文件名称。   

-i    --ignore-case   #忽略字符大小写的差别。   

-l    --file-with-matches   #列出文件内容符合指定的样式的文件名称。   

-L   --files-without-match   #列出文件内容不符合指定的样式的文件名称。   

-n   --line-number   #在显示符合样式的那一行之前，标示出该行的列数编号。   

-q   --quiet或--silent   #不显示任何信息。   

-r   --recursive   #此参数的效果和指定“-d recurse”参数相同。   

-s   --no-messages   #不显示错误信息。   

-v   --revert-match   #显示不包含匹配文本的所有行。   

-V   --version   #显示版本信息。   

-w   --word-regexp   #只显示全字符合的列。   

-x    --line-regexp   #只显示全列符合的列。   

-y   #此参数的效果和指定“-i”参数相同。
```

搜先vim一个文本，然后在里面随便写一些东西

```
zhouning@DESKTOP-681HT7R:~$ vim test.txt
zhouning@DESKTOP-681HT7R:~$ cat test.txt
aaa
bbbbb
AAAaaa
BBBBASDABBDA
```

-A，除了显示符合范本样式的那一列之外，并显示该行之后的内容。

```
zhouning@DESKTOP-681HT7R:~$ grep -A1 b test.txt
bbbbb
AAAaaa
zhouning@DESKTOP-681HT7R:~$ grep -A2 b test.txt
bbbbb
AAAaaa
BBBBASDABBDA
```

![image-20210209161731128](%E7%AC%AC11%E7%AB%A0-grep%E5%91%BD%E4%BB%A4.assets/image-20210209161731128.png)

![image-20210209161756967](%E7%AC%AC11%E7%AB%A0-grep%E5%91%BD%E4%BB%A4.assets/image-20210209161756967.png)



-B，除了显示符合样式的那一行之外，并显示该行之前的内容。

```
zhouning@DESKTOP-681HT7R:~$ grep -B1 b test.txt
aaa
bbbbb
```

![image-20210209161829500](%E7%AC%AC11%E7%AB%A0-grep%E5%91%BD%E4%BB%A4.assets/image-20210209161829500.png)

-C，除了显示符合样式的那一行之外，并显示该行之前后的内容。

![image-20210209161711323](%E7%AC%AC11%E7%AB%A0-grep%E5%91%BD%E4%BB%A4.assets/image-20210209161711323.png)

-c,计算符合样式的列数。

```
计算符合样式的列数。
```

-e,

```
zhouning@DESKTOP-681HT7R:~$ grep -e AAA -e bbb test.txt
bbbbb
AAAaaa
```

![image-20210209163203995](%E7%AC%AC11%E7%AB%A0-grep%E5%91%BD%E4%BB%A4.assets/image-20210209163203995.png)

目前就写这么多等学会正则表达式再写下面内容