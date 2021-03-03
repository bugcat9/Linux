# useradd命令

## useradd使用

useradd的`--help`

```
[root@VM-0-12-centos ~]# useradd --help
Usage: useradd [options] LOGIN
       useradd -D
       useradd -D [options]

Options:
  -b, --base-dir BASE_DIR       base directory for the home directory of the
                                new account
  -c, --comment COMMENT         GECOS field of the new account
  -d, --home-dir HOME_DIR       home directory of the new account
  -D, --defaults                print or change default useradd configuration
  -e, --expiredate EXPIRE_DATE  expiration date of the new account
  -f, --inactive INACTIVE       password inactivity period of the new account
  -g, --gid GROUP               name or ID of the primary group of the new
                                account
  -G, --groups GROUPS           list of supplementary groups of the new
                                account
  -h, --help                    display this help message and exit
  -k, --skel SKEL_DIR           use this alternative skeleton directory
  -K, --key KEY=VALUE           override /etc/login.defs defaults
  -l, --no-log-init             do not add the user to the lastlog and
                                faillog databases
  -m, --create-home             create the user's home directory
  -M, --no-create-home          do not create the user's home directory
  -N, --no-user-group           do not create a group with the same name as
                                the user
  -o, --non-unique              allow to create users with duplicate
                                (non-unique) UID
  -p, --password PASSWORD       encrypted password of the new account
  -r, --system                  create a system account
  -R, --root CHROOT_DIR         directory to chroot into
  -P, --prefix PREFIX_DIR       prefix directory where are located the /etc/* files
  -s, --shell SHELL             login shell of the new account
  -u, --uid UID                 user ID of the new account
  -U, --user-group              create a group with the same name as the user
  -Z, --selinux-user SEUSER     use a specific SEUSER for the SELinux user mapping

```

简单来说就是

```
useradd [-u UID] [-g 初始群组] [-G 次要群组] [-mM]  [-c 说明栏] [-d 家目录绝对路径] [-s shell] 使用者账号名
```

但是其实我们平时直接

```
useradd 使用者账号名
```

比如：`useradd zhouning`，其他的都会由系统的默认值帮助我们创建。系统会根据默认值帮我们做下面这几件事：

- 在 /etc/passwd 里面创建一行与账号相关的数据，包括创建 UID/GID/家目录等；
- 在 /etc/shadow 里面将此账号的口令相关参数填入，但是尚未有口令；
- 在 /etc/group 里面加入一个与账号名称一模一样的组名；
- 在 /home 底下创建一个与账号同名的目录作为用户家目录，且权限为 700

不过这个时候其实这些账号没有密码还不能登录，需要使用passwd加密码之后再登录

## 默认值以及相关文件

我们可以使用-D或者--defaults 来查看默认值

```
[root@VM-0-12-centos ~]# useradd -D
GROUP=100		<==默认的群组
HOME=/home		<==默认的家目录所在目录
INACTIVE=-1		<==口令失效日，在 shadow 内的第 7 部分
EXPIRE=			<==账号失效日，在 shadow 内的第 8 部分
SHELL=/bin/bash		<==默认的 shell
SKEL=/etc/skel		<==用户家目录的内容数据参考目录
CREATE_MAIL_SPOOL=yes   <==是否主动帮使用者创建邮件信箱(mailbox)
```

这个数据其实是由 /etc/default/useradd 呼叫出来的！你可以自行用 vim 去观察该文件的内容，当然也可以进行修改。

- GROUP=100：新建账号的初始群组使用 GID 为 100 者

  系统上面 GID 为 100 者即是 users 这个群组，此配置项目指的就是让新设使用者账号的初始群组为 users 这一个的意思。 但是我们知道 CentOS 上面并不是这样的，在 CentOS 上面

  默认的群组为与账号名相同的群组

  。 举例来说， vbird1 的初始群组为 vbird1 。怎么会这样啊？这是因为针对群组的角度有两种不同的机制所致， 这两种机制分别是：

  - 私有群组机制：系统会创建一个与账号一样的群组给使用者作为初始群组。 这种群组的配置机制会比较有保密性，这是因为使用者都有自己的群组，而且家目录权限将会配置为 700 (仅有自己可进入自己的家目录) 之故。使用这种机制将不会参考 GROUP=100 这个配置值。代表性的 distributions 有 RHEL, Fedora, CentOS 等；
  - 公共群组机制：就是以 GROUP=100 这个配置值作为新建账号的初始群组，因此每个账号都属于 users 这个群组， 且默认家目录通常的权限会是『 drwxr-xr-x ... username users ... 』，由于每个账号都属于 users 群组，因此大家都可以互相分享家目录内的数据之故。代表 distributions 如 SuSE等。

  由于我们的 CentOS 使用私有群组机制，因此这个配置项目是不会生效的！不要太紧张啊！

- **HOME=/home：用户家目录的基准目录(basedir)**

  用户的家目录通常是与账号同名的目录，这个目录将会摆放在此配置值的目录后。所以 vbird1 的家目录就会在 /home/vbird1/ 了！很容易理解吧！

- **INACTIVE=-1：口令过期后是否会失效的配置值**

  我们在 [shadow](http://cn.linux.vbird.org/linux_basic/0410accountmanager_2.php#shadow_file) 文件结构当中谈过，第七个字段的配置值将会影响到口令过期后， 在多久时间内还可使用旧口令登陆。这个项目就是在指定该日数啦！如果是 0 代表口令过期立刻失效， 如果是 -1 则是代表口令永远不会失效，如果是数字，如 30 ，则代表过期 30 天后才失效。

- **EXPIRE=：账号失效的日期**

  就是 [shadow](http://cn.linux.vbird.org/linux_basic/0410accountmanager_2.php#shadow_file) 内的第八字段，你可以直接配置账号在哪个日期后就直接失效，而不理会口令的问题。 通常不会配置此项目，但如果是付费的会员制系统，或许这个字段可以配置喔！

- **SHELL=/bin/bash：默认使用的 shell 程序文件名**

  系统默认的 shell 就写在这里。假如你的系统为 mail server ，你希望每个账号都只能使用 email 的收发信件功能， 而不许用户登陆系统取得 shell ，那么可以将这里配置为 /sbin/nologin ，如此一来，新建的使用者默认就无法登陆！ 也免去后续使用 [usermod](http://cn.linux.vbird.org/linux_basic/0410accountmanager_2.php#usermod) 进行修改的手续！

- **SKEL=/etc/skel：用户家目录参考基准目录**

  这个咚咚就是指定用户家目录的参考基准目录啰～举我们的范例一为例， vbird1 家目录 /home/vbird1 内的各项数据，都是由 /etc/skel 所复制过去的～所以呢，未来如果我想要让新增使用者时，该用户的环境变量 ~/.bashrc 就配置妥当的话，您可以到 /etc/skel/.bashrc 去编辑一下，也可以创建 /etc/skel/www 这个目录，那么未来新增使用者后，在他的家目录下就会有 www 那个目录了！这样瞭呼？

- **CREATE_MAIL_SPOOL=yes：创建使用者的 mailbox**

  你可以使用『 ll /var/spool/mail/vbird1 』看一下，会发现有这个文件的存在喔！这就是使用者的邮件信箱！

出了这些基本的账号配置之外，UID/GID 还有口令参数是参考/etc/login.defs这个文件

```
[root@VM-0-12-centos ~]# cat /etc/login.defs
#
# Please note that the parameters in this configuration file control the
# behavior of the tools from the shadow-utils component. None of these
# tools uses the PAM mechanism, and the utilities that use PAM (such as the
# passwd command) should therefore be configured elsewhere. Refer to
# /etc/pam.d/system-auth for more information.
#

# *REQUIRED*
#   Directory where mailboxes reside, _or_ name of file, relative to the
#   home directory.  If you _do_ define both, MAIL_DIR takes precedence.
#   QMAIL_DIR is for Qmail
#
#QMAIL_DIR	Maildir
MAIL_DIR	/var/spool/mail		<==用户默认邮件信箱放置目录
#MAIL_FILE	.mail

# Password aging controls:
#
#	PASS_MAX_DAYS	Maximum number of days a password may be used.
#	PASS_MIN_DAYS	Minimum number of days allowed between password changes.
#	PASS_MIN_LEN	Minimum acceptable password length.
#	PASS_WARN_AGE	Number of days warning given before a password expires.
#
PASS_MAX_DAYS	99999		<==/etc/shadow 内的第 5 栏，多久需变更口令日数
PASS_MIN_DAYS	0			<==/etc/shadow 内的第 4 栏，多久不可重新配置口令日数
PASS_MIN_LEN    8			<==口令最短的字符长度，已被 pam 模块取代，失去效用！
PASS_WARN_AGE	7			<==/etc/shadow 内的第 6 栏，过期前会警告的日数

#
# Min/max values for automatic uid selection in useradd
#
UID_MIN                  1000		<==使用者最小的 UID，意即小于 500 的 UID 为系统保留
UID_MAX                 60000		<==使用者能够用的最大 UID
# System accounts
SYS_UID_MIN               201
SYS_UID_MAX               999

#
# Min/max values for automatic gid selection in groupadd
#
GID_MIN                  1000		<==使用者自定义组的最小 GID，小于 1000为系统保留
GID_MAX                 60000		<==使用者自定义组的最大 GID
# System accounts
SYS_GID_MIN               201
SYS_GID_MAX               999

#
# If defined, this command is run when removing a user.
# It should remove any at/cron/print jobs etc. owned by
# the user to be removed (passed as the first argument).
#
#USERDEL_CMD	/usr/sbin/userdel_local

#
# If useradd should create home directories for users by default
# On RH systems, we do. This option is overridden with the -m flag on
# useradd command line.
#
CREATE_HOME	yes 	<==在不加 -M 及 -m 时，是否主动创建用户家目录？

# The permission mask is initialized to this value. If not specified, 
# the permission mask will be initialized to 022.
UMASK           077		<==用户家目录创建的 umask ，因此权限会是 700

# This enables userdel to remove user groups if no members exist.
#
USERGROUPS_ENAB yes		<==使用 userdel 删除时，是否会删除初始群组

# Use SHA512 to encrypt password.
ENCRYPT_METHOD SHA512
```

其中规则如下：

- mailbox 所在目录：
  用户的默认 mailbox 文件放置的目录在 /var/spool/mail，所以 vbird1 的 mailbox 就是在 /var/spool/mail/vbird1 啰！

- shadow 口令第 4, 5, 6 字段内容：
  透过 PASS_MAX_DAYS 等等配置值来指定的！所以你知道为何默认的 /etc/shadow 内每一行都会有『 0:99999:7 』的存在了吗？^_^！不过要注意的是，由于目前我们登陆时改用 PAM 模块来进行口令检验，所以那个 PASS_MIN_LEN 是失效的！

- UID/GID 指定数值：
  虽然 Linux 核心支持的账号可高达 232 这么多个，不过一部主机要作出这么多账号在管理上也是很麻烦的！ 所以在这里就针对 UID/GID 的范围进行规范就是了。上表中的 UID_MIN 指的就是可登陆系统的一般账号的最小 UID ，至于 UID_MAX 则是最大 UID 之意。

  要注意的是，系统给予一个账号 UID 时，他是 (1)先参考 UID_MIN 配置值取得最小数值； (2)由 /etc/passwd 搜寻最大的 UID 数值， 将 (1) 与 (2) 相比，找出最大的那个再加一就是新账号的 UID 了。我们上面已经作出 UID 为 700 的 vbird2 ， 如果再使用『 useradd vbird4 』时，你猜 vbird4 的 UID 会是多少？答案是： 701 。 所以中间的 505~699 的号码就空下来啦！

  而如果我是想要创建系统用的账号，所以使用 useradd -r sysaccount 这个 -r 的选项时，就会找『比 500 小的最大的那个 UID + 1 』就是了。 

- 用户家目录配置值：
  为何我们系统默认会帮用户创建家目录？就是这个『CREATE_HOME = yes』的配置值啦！这个配置值会让你在使用 useradd 时， 主动加入『 -m 』这个产生家目录的选项啊！如果不想要创建用户家目录，就只能强制加上『 -M 』的选项在 useradd 命令运行时啦！至于创建家目录的权限配置呢？就透过 [umask](http://cn.linux.vbird.org/linux_basic/0220filemanager.php#umask) 这个配置值啊！因为是 077 的默认配置，因此用户家目录默认权限才会是『 drwx------ 』哩！

- 用户删除与口令配置值：
  使用『USERGROUPS_ENAB yes』这个配置值的功能是： 如果使用 userdel 去删除一个账号时，且该账号所属的初始群组已经没有人隶属于该群组了， 那么就删除掉该群组，举例来说，我们刚刚有创建 vbird4 这个账号，他会主动创建 vbird4 这个群组。 若 vbird4 这个群组并没有其他账号将他加入支持的情况下，若使用 userdel vbird4 时，该群组也会被删除的意思。 至于『MD5_CRYPT_ENAB yes』则表示使用 MD5 来加密口令明文，而不使用旧式的 DES([注2](http://cn.linux.vbird.org/linux_basic/0410accountmanager_2.php#ps2)) 。

现在你知道啦，使用 useradd 这支程序在创建 Linux 上的账号时，至少会参考：

- /etc/default/useradd
- /etc/login.defs
- /etc/skel/*

这些文件，不过，最重要的其实是创建 /etc/passwd, /etc/shadow, /etc/group, /etc/gshadow 还有用户家目录就是了～所以，如果你了解整个系统运行的状态，也是可以手动直接修改这几个文件就是了。 