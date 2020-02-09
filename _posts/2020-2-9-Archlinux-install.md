---
layout: post
title: 『我的 Archlinux 安装』
categories: Blog
description: 安装 Archlinux
keywords: Linux, Note
---

最近没啥事，装一下 Archlinux。

## 1、Archlinux 安装部分

### 1.1、验证启动模式(EFI/BIOS)

```shell
ls /sys/firmware/efi/efivars
```

### 1.2、调整一下难受的字体

```shell
setfont /usr/share/kbd/consolefonts/LatGrkCyr-12x22.psfu.gz
```

### 1.3、配置一下软件源，将 China 源放在前面，同步软件源

```shell
vim /etc/pacman.d/mirrorlist

pacman -Syy
```

###　1.4、更新系统时间

```shell
timedatectl set-ntp true
```

### 1.5、创建系统分区

```shell
# 查看电脑硬盘分区
fdisk - l

# 自己滚局需要进行分区
cfdisk

#　举个栗子
/dev/sda1   # EFI
/dev/sda2   # Swap
/dev/sda2   # Linux
```

### 1.6、格式化分区

```shell
mkfs.vfat /dev/sda1
mkswap /dev/sda2
mkfs.ext4 /dev/sda3
```

### 1.7、挂载分区

```shell
# 挂载 Swap 分区
swapon /dev/sda2

# 挂载 / 和 EFI分区
mount /dev/sda3 /mnt
mkdir /mnt/boot
mount /dev/sda1 /mnt/boot
```

### 1.8、安装系统以及一些软件

```shell
pacstrap /mnt base base-devel linux linux-firmware dhcpcd dhclient netctl iw wpa_supplicant nano vim efibootmgr grub dialog
```

### 1.9、生成 fatab，检查是否挂在成功

```shell
genfstab -U /mnt >> /mnt/etc/fstab
```

### 1.10、进入 Archlinux

```shell
arch-chroot /mnt
```

## 2、Archlinux 配置部分

### 2.1、修改时区、同步时间

```shell
ln -sf /usr/share/zoneinfo/Asia/Shanghai /etc/localtime

hwclock --systohc
```

### 2.2、配置语言

```shell
echo LANG=en_US.utf-8 > /etc/locale.conf

# 修改 /etc/locale.gen 取消以下批注
vim /etc/locale.gen
en_US.UTF-8 UTF-8
zh_CN.UTF-8 UTF-8

# 同步一下
locale-gen
```

### 2.3、配置网络

```shell
# 修改dns
vim /etc/resolv.conf
223.5.5.5

# 修改 hosts
echo hp > /etc/hostname
vim /etc/hosts
127.0.0.1	localhost
::1			localhost
127.0.1.1	hp.localdomain	hp
```

### 2.4、配置用户

```shell
# 添加 root 密码
passwd root

# 创建用户
useradd -g wheel -m zhw
passwd zhw

# 添加 sudo 权限
vim /etc/sudoers
%wheel

# 添加　zhw 密码
passwd zhw
```

## 3、Archlinux 图形化界面安装(kde)

### 3.1、xorg、kde

```shell
pacman -S xorg xorg-xinit
pacman -S plasma kde-applications
pacman -S sddm sddm-kcm
systemctl enable sddm
```

### 3.2、驱动安装

```shell
# 显卡驱动(AMD 自行解决)
pacman -S nvidia nvidia-setting

#　触控板驱动
pacman -S xf86-input-synaptics

# 蓝牙驱动
pacman -S bluez bluez-utils bluedevil
systemctl enable bluetooth

# 声卡驱动
pacman -S alsa-utils
amixer sset Master unmute
```

### 3.3、中文字体

```shell
pacman -S ttf-dejavu wqy-microhei wqy-microhei-lite wqy-bitmapfont wqy-zenhei ttf-arphic-ukai ttf-arphic-uming adobe-source-han-sans-cn-fonts adobe-source-han-serif-cn-fonts noto-fonts-cjk
```

### 3.4、网络

```shell
pacman -S networkmanager net-tools
systemctl enable NetworkManager
systemctl enable dhcpcd
```

### 3.6、一些其他软件

```shell
openssh firefox intel-ucode zsh
```

### 3.7、安装Grub

```shell
# 安装 os-prober 和 ntfs-3g 识别多系统
pacman -S os-prober ntfs-3g

# 安装 grub
grub-install --target=x86_64-efi --efi-directory=/boot --bootloader-id=Archlinux

# 生成 grub 配置
grub-mkconfig -o /boot/grub/grub.cfg
```

## 4、重启，安装完成!

我的 Archlinux 桌面配置：

![shell](/images/blog/Archlinux-install/shell.png)

![desktop](/images/blog/Archlinux-install/Archlinux-desktop.png)
![theme](/images/blog/Archlinux-install/theme.png)

![windows](/images/blog/Archlinux-install/windows.png)
![icons](/images/blog/Archlinux-install/icons.png)