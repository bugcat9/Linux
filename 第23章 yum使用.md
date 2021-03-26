# yum使用

yum（ Yellow dog Updater, Modified）是一个在 Fedora 和 RedHat 以及 SUSE 中的 Shell 前端软件包管理器。

基于 RPM 包管理，能够从指定的服务器自动下载 RPM 包并且安装，可以自动处理依赖性关系，并且一次安装所有依赖的软体包，无须繁琐地一次次下载、安装。

yum 提供了查找、安装、删除某一个、一组甚至全部软件包的命令，而且命令简洁而又好记。

## 查询功能：yum [list|info|search|provides|whatprovides] 参数

```
[root@www ~]# yum [option] [查询工作项目] [相关参数]
选项与参数：
[option]：主要的选项，包括有：
  -y ：当 yum 要等待使用者输入时，这个选项可以自动提供 yes 的回应；
  --installroot=/some/path ：将该软件安装在 /some/path 而不使用默认路径
[查询工作项目] [相关参数]：这方面的参数有：
  search  ：搜寻某个软件名称或者是描述 (description) 的重要关键字；
  list    ：列出目前 yum 所管理的所有的软件名称与版本，有点类似 rpm -qa；
  info    ：同上，不过有点类似 rpm -qai 的运行结果；
  provides：从文件去搜寻软件！类似 rpm -qf 的功能！
```

范例一：搜寻磁盘阵列 (raid) 相关的软件有哪些？

```
[root@VM-0-12-centos ~]# yum search raid
Repository AppStream is listed more than once in the configuration
Repository extras is listed more than once in the configuration
Repository PowerTools is listed more than once in the configuration
Repository centosplus is listed more than once in the configuration
Last metadata expiration check: 0:14:31 ago on Fri 26 Mar 2021 07:38:44 PM CST.
============================================================================== Name & Summary Matched: raid ===============================================================================
libblockdev-mdraid.i686 : The MD RAID plugin for the libblockdev library
libblockdev-mdraid.x86_64 : The MD RAID plugin for the libblockdev library
libstoragemgmt-megaraid-plugin.noarch : Files for LSI MegaRAID support for libstoragemgmt
================================================================================== Summary Matched: raid ==================================================================================
iprutils.x86_64 : Utilities for the IBM Power Linux RAID adapters
mdadm.x86_64 : The mdadm program controls Linux md devices (software RAID arrays)
```

范例二：找出 mdadm 这个软件的功能为何

```
[root@VM-0-12-centos ~]# yum info mdadm
Repository AppStream is listed more than once in the configuration
Repository extras is listed more than once in the configuration
Repository PowerTools is listed more than once in the configuration
Repository centosplus is listed more than once in the configuration
Last metadata expiration check: 0:15:21 ago on Fri 26 Mar 2021 07:38:44 PM CST.
Available Packages
Name         : mdadm
Version      : 4.1
Release      : 14.el8
Architecture : x86_64
Size         : 453 k
Source       : mdadm-4.1-14.el8.src.rpm
Repository   : BaseOS
Summary      : The mdadm program controls Linux md devices (software RAID arrays)
URL          : http://www.kernel.org/pub/linux/utils/raid/mdadm/
License      : GPLv2+
Description  : The mdadm program is used to create, manage, and monitor Linux MD (software
             : RAID) devices.  As such, it provides similar functionality to the raidtools
             : package.  However, mdadm is a single program, and it can perform
             : almost all functions without a configuration file, though a configuration
             : file can be used to help with some common tasks.
```

范例三：列出 yum 服务器上面提供的所有软件名称

```
[root@VM-0-12-centos ~]# yum list
```

范例四：列出目前服务器上可供本机进行升级的软件有哪些？

```
[root@VM-0-12-centos ~]# yum list updates
```

范例五：列出提供 passwd 这个文件的软件有哪些

```
[root@www ~]# yum provides passwd
```

范例六：找出以 pam 为开头的软件名称有哪些

```
[root@VM-0-12-centos ~]# yum list pam*
Repository AppStream is listed more than once in the configuration
Repository extras is listed more than once in the configuration
Repository PowerTools is listed more than once in the configuration
Repository centosplus is listed more than once in the configuration
Last metadata expiration check: 0:23:19 ago on Fri 26 Mar 2021 07:38:44 PM CST.
Installed Packages
pam.x86_64                                                                                     1.3.1-8.el8                                                                          @BaseOS
Available Packages
pam.i686                                                                                       1.3.1-11.el8                                                                         BaseOS 
pam.x86_64                                                                                     1.3.1-11.el8                                                                         BaseOS 
pam-devel.i686                                                                                 1.3.1-11.el8                                                                         BaseOS 
pam-devel.x86_64                                                                               1.3.1-11.el8                                                                         BaseOS 
pam-kwallet.x86_64                                                                             5.18.4-1.el8.1                                                                       epel   
pam_2fa.x86_64                                                                                 1.0-4.el8                                                                            epel   
pam_cifscreds.x86_64                                                                           6.8-3.el8                                                                            BaseOS 
pam_mount.x86_64                                                                               2.16-10.el8                                                                          epel   
pam_oath.x86_64                                                                                2.6.2-3.el8                                                                          epel   
pam_radius.x86_64                                                                              1.4.0-15.el8                                                                         epel   
pam_script.x86_64                                                                              1.1.9-7.el8                                                                          epel   
pam_ssh.x86_64                                                                                 2.3-2.el8                                                                            epel   
pam_ssh_agent_auth.x86_64                                                                      0.10.3-7.5.el8                                                                       BaseOS 
pam_ssh_user_auth.x86_64                                                                       1.0-4.el8                                                                            epel   
pam_url.x86_64                                                                                 1:0.3.3-12.el8                                                                       epel   
pam_yubico.x86_64                                                                              2.26-4.el8                                                                           epel   
pamtester.x86_64                                                                               0.1.2-14.el8                                                                         epel   
```

## 安装和升级

```
[root@www ~]# yum [option] [查询工作项目] [相关参数]
选项与参数：
  install ：后面接要安装的软件！
  update  ：后面接要升级的软件，若要整个系统都升级，就直接 update 即可
```

范例一：将前一个练习找到的未安装的 pam-devel 安装起来

```
[root@VM-0-12-centos ~]# yum install pam-devel
Repository AppStream is listed more than once in the configuration
Repository extras is listed more than once in the configuration
Repository PowerTools is listed more than once in the configuration
Repository centosplus is listed more than once in the configuration
Last metadata expiration check: 0:24:31 ago on Fri 26 Mar 2021 07:38:44 PM CST.
Dependencies resolved.
===========================================================================================================================================================================================
 Package                                      Architecture                              Version                                            Repository                                 Size
===========================================================================================================================================================================================
Installing:
 pam-devel                                    x86_64                                    1.3.1-11.el8                                       BaseOS                                    209 k
Upgrading:
 pam                                          x86_64                                    1.3.1-11.el8                                       BaseOS                                    738 k

Transaction Summary
===========================================================================================================================================================================================
Install  1 Package
Upgrade  1 Package

Total download size: 947 k
Is this ok [y/N]: y
Downloading Packages:
(1/2): pam-devel-1.3.1-11.el8.x86_64.rpm                                                                                                                   706 kB/s | 209 kB     00:00    
(2/2): pam-1.3.1-11.el8.x86_64.rpm                                                                                                                         2.0 MB/s | 738 kB     00:00    
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Total                                                                                                                                                      2.5 MB/s | 947 kB     00:00     
Running transaction check
Transaction check succeeded.
Running transaction test
Transaction test succeeded.
Running transaction
  Preparing        :                                                                                                                                                                   1/1 
  Upgrading        : pam-1.3.1-11.el8.x86_64                                                                                                                                           1/3 
  Running scriptlet: pam-1.3.1-11.el8.x86_64                                                                                                                                           1/3 
  Installing       : pam-devel-1.3.1-11.el8.x86_64                                                                                                                                     2/3 
  Cleanup          : pam-1.3.1-8.el8.x86_64                                                                                                                                            3/3 
  Running scriptlet: pam-1.3.1-8.el8.x86_64                                                                                                                                            3/3 
  Verifying        : pam-devel-1.3.1-11.el8.x86_64                                                                                                                                     1/3 
  Verifying        : pam-1.3.1-11.el8.x86_64                                                                                                                                           2/3 
  Verifying        : pam-1.3.1-8.el8.x86_64                                                                                                                                            3/3 

Upgraded:
  pam-1.3.1-11.el8.x86_64                                                                                                                                                                  

Installed:
  pam-devel-1.3.1-11.el8.x86_64                                                                                                                                                            

Complete!
```

范例二：移除软件

```
[root@VM-0-12-centos ~]# yum remove pam-devel
Repository AppStream is listed more than once in the configuration
Repository extras is listed more than once in the configuration
Repository PowerTools is listed more than once in the configuration
Repository centosplus is listed more than once in the configuration
Dependencies resolved.
===========================================================================================================================================================================================
 Package                                      Architecture                              Version                                           Repository                                  Size
===========================================================================================================================================================================================
Removing:
 pam-devel                                    x86_64                                    1.3.1-11.el8                                      @BaseOS                                    593 k

Transaction Summary
===========================================================================================================================================================================================
Remove  1 Package

Freed space: 593 k
Is this ok [y/N]: y
Running transaction check
Transaction check succeeded.
Running transaction test
Transaction test succeeded.
Running transaction
  Preparing        :                                                                                                                                                                   1/1 
  Erasing          : pam-devel-1.3.1-11.el8.x86_64                                                                                                                                     1/1 
  Running scriptlet: pam-devel-1.3.1-11.el8.x86_64                                                                                                                                     1/1 
  Verifying        : pam-devel-1.3.1-11.el8.x86_64                                                                                                                                     1/1 

Removed:
  pam-devel-1.3.1-11.el8.x86_64                                                                                                                                                            

Complete!
```

