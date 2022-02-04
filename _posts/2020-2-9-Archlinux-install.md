---
layout: post
title: Archlinux 安装手册
categories: Archlinux 安装手册
author: ZhW
header-style: text
tags: 
    - Linux
    - Archlinux
    - wiki
---

最近没啥事，装一下 Archlinux。

## 1、Archlinux 安装部分

### 1、验证启动模式(EFI/BIOS)

```shell
ls /sys/firmware/efi/efivars
```

### 2、联网、配置一下软件源，将 China 源放在前面，同步软件源

~~~shell
rfkill unblock wifi # 取消禁用 wifi 设备
ip link set wlan0 up # 开启 wlan0
~~~

输入 `iwctl` 进入交互

~~~shell
station wlan0 scan
station wlan0 get_networks
station wlan0 connect <network_name>
station wlan0 show
exit
~~~

配置软件源

```shell
vim /etc/pacman.d/mirrorlist # 把 China 源放前面
pacman -Syy
```

###　3、更新系统时间

```shell
timedatectl set-ntp true
```

### 4、创建系统分区

```shell
fdisk - l # 查看电脑硬盘分区
cfdisk # 分区
```

### 5、格式化分区

```shell
mkfs.vfat /dev/sda1 # efi 分区
mkswap /dev/sda2 # 交换分区
mkfs.ext4 /dev/sda3 # /
```

### 6、挂载分区

```shell
swapon /dev/sda2 # 挂载 Swap 分区

mount /dev/sda3 /mnt # 挂载 / 和 EFI分区
mkdir /mnt/boot
mount /dev/sda1 /mnt/boot
```

### 7、安装系统以及一些软件

```shell
pacstrap /mnt base base-devel linux linux-firmware nano vim vi
```

### 8、生成 fatab，检查是否挂载成功

```shell
genfstab -U /mnt >> /mnt/etc/fstab
```

### 9、进入 Archlinux

```shell
arch-chroot /mnt
```

## 2、Archlinux 配置部分

### 1、修改时区、同步时间

```shell
ln -sf /usr/share/zoneinfo/Asia/Shanghai /etc/localtime

hwclock --systohc
```

### 2、配置语言

```shell
echo LANG=en_US.utf-8 > /etc/locale.conf

# 修改 /etc/locale.gen 取消以下批注
vim /etc/locale.gen
en_US.UTF-8 UTF-8
zh_CN.UTF-8 UTF-8

# 同步一下
locale-gen
```

### 3、配置网络

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

### 4、配置用户

```shell
# 添加 root 密码
passwd root

# 创建用户
useradd -g wheel -m lazywa

# 添加 sudo 权限
vim /etc/sudoers
%wheel

# 添加　zhw 密码
passwd lazywa
```

## 3、Archlinux 图形化界面安装(kde)

### 1、xorg、kde、gnome

```shell
pacman -S xorg xorg-xinit xorg-apps

pacman -S plasma kde-applications # ked 环境
pacman -S sddm sddm-kcm
systemctl enable sddm

pacman -S gnome gnome-extra # gnome 环境
```

### 2、驱动安装

```shell
# 显卡驱动(AMD 自行解决)
pacman -S nvidia nvidia-settings xf86-video-intel

#　触控板驱动
pacman -S xf86-input-synaptics

# 蓝牙驱动
pacman -S bluez bluez-utils bluedevil
systemctl enable bluetooth

# 声卡驱动
pacman -S alsa-utils sof-firmware
amixer sset Master unmute
```

### 3、中文字体

```shell
pacman -S noto-fonts-cjk
```

### 4、网络

```shell
pacman -S networkmanager nm-connection-editor network-manager-applet rp-pppoe net-tools

systemctl enable NetworkManager
```

### 5、输入法

```shell
pacman -S fcitx fcitx-configtool fcitx-sunpinyin
```

### 6、一些其他软件

```shell
openssh firefox intel-ucode zsh git
```

在虚拟机中使用 open-vm-tools 的必要软件
```shell
mesa lsb-release xf86-input-vmmouse xf86-video-vmware
```

### 7、安装Grub

```shell
# 安装 os-prober 和 ntfs-3g 识别多系统
pacman -S os-prober ntfs-3g efibootmgr grub

# 安装 grub
grub-install --target=x86_64-efi --efi-directory=/boot --bootloader-id=Archlinux

# 生成 grub 配置
grub-mkconfig -o /boot/grub/grub.cfg
```

## 4、dwm

### 1、安装

```shell
git clone https://github.com/lazywa/dwm.git
mv dwm .dwm
cd .dwm
sudo make clean install
```

```shell
git clone https://github.com/lazywa/st.git
mv st .st
cd .st
sudo make clean install
```

```shell
git clone https://git.suckless.org/dmenu
cd dmenu
sudo make clean install
```

### 2、需要安装的程序

```shell
sudo pacman -S feh acpitool bc alsa-utils trayer xcompmgr nerd-fonts-source-code-pro screenkey
```
