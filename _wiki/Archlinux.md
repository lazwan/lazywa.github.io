---
layout: wiki
title: Archlinux
categories: Linux
description: 我的 Linux 配置方法
keywords: Linux config
---

重装系统后需要做的事情！！！

一些配置文件放在 [https://github.com/ZhWing/zhwing.github.io/tree/master/_wiki/config](https://github.com/ZhWing/zhwing.github.io/tree/master/_wiki/config)

## 安装常用软件

- **Chrome**: `sudo pacman -S google-chrome`
- **VSCode**: `sudo pacman -S visual-studio-code-bin`
- **IntelliJ IDEA**: `sudo pacman -S intellij-idea-community-edition`
- **PyCharm**: `sudo pacman -S pycharm-community-edition`
- **Typora**: `sudo pacman -S typora`
- **网易云音乐**: `sudo pacman -S netease-cloud-music`
- **Virtualbox**: `sudo pacman -S virtualbox`
- **optimus-manager**: `sudo pacman -S optimus-manager optimus-manager-qt`
- **Latte**: `sudo pacman -S latte-dock`
- **WPS**: `sudo pacman -S wps-office-cn ttf-wps-fonts wps-office-mui-zh-cn`

## 配置终端

```shell
# 安装 oh-my-zsh
sudo pacman -S zsh
sh -c "$(curl -fsSL https://raw.githubusercontent.com/robbyrussell/oh-my-zsh/master/tools/install.sh)"

# 设置为默认终端
chsh -s /bin/zsh `whoami`
chsh -s /bin/zsh root

# 安装 zsh-autosuggestions
git clone git://github.com/zsh-users/zsh-autosuggestions $ZSH_CUSTOM/plugins/zsh-autosuggestions

# 安装 zsh-syntax-highlighting
git clone https://github.com/zsh-users/zsh-syntax-highlighting.git ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-syntax-highlighting

# 配置 .zshrc
ZSH_THEME="ys" # 
plugins=(git zsh-syntax-highlighting zsh-autosuggestions sudo wd z) # 插件

source .zshrc
```

## 配置 Git

### 基本配置

```shell
ssh-keygen -t rsa -C "1065423410@qq.com"

git config --global user.name ZhW
git config --global user.email 1065423410@qq.com
```

### 代理配置

- Git http 代理

  ```shell
  git config --global http.proxy socks5://192.168.0.254:1080
  git config --global https.proxy socks5://192.168.0.254:1080
  ```

- Git SSH 代理

  在用户目录下建立如下文件 `~/.ssh/config`，对 GitHub 的域名做单独的处理

  ```shell
  Host github.com
      HostName github.com
      User git
      # ProxyCommand socat - PROXY:127.0.0.1:%h:%p,proxyport=1080
      # ProxyCommand nc -v -x 192.168.0.254:1080 %h %p
  ```

  使用 HTTP 代理取消倒数第二行注释，安装 socat; 使用 SOCKS5 代理取消最后一行注释，安装 netcat。

## 代理工具

- elecrton-ssr

  - 安装方法：

    ```shell
    sudo pacman -S electron-ssr
    ```

  - 仓库地址: [electron-ssr-backup](https://github.com/qingshuisiyuan/electron-ssr-backup)

- Clashy

  - 仓库地址: [Clashy](https://github.com/SpongeNobody/Clashy)

  - 下载 Appimage 包

  - desktop 配置文件

    ```
    #!/usr/bin/env xdg-open
    [Desktop Entry]
    Version=1.0
    Type=Application
    Name=Clashy 
    GenericName=Clashy
    Exec=/home/zhw/Apps/Clashy/Clashy-0.1.11.AppImage
    Icon=/home/zhw/Apps/Clashy/Clashy.png
    Terminal=false
    Categories=Application
    ```

    ![image](/images/wiki/Clashy.png)

### 配置输入法

- Fcitx

  ```shell
  sudo pacman -S fcitx fcitx-im kcm-fcitx fcitx-googlepinyin fcitx-sunpinyin
  
  vim ~/.xprofile
  
  # 编辑 .xprofile 添加以下内容
  export GTK_IM_MODULE=fcitx
  export QT_IM_MODULE=fcitx
  export XMODIFIERS="@im=fcitx"
  
  # 重新登出登录后即可生效
  ```

## Anaconda

- 清华源下载安装：

  ```shell
  wget https://mirrors.tuna.tsinghua.edu.cn/anaconda/archive/Anaconda3-2019.10-Linux-x86_64.sh
  chmod u+x Anaconda3-2019.10-Linux-x86_64.sh
  ./Anaconda3-2019.10-Linux-x86_64.sh
  ```
## 配置源

- [Conda 源](https://mirrors.tuna.tsinghua.edu.cn/help/anaconda/)
  
  ```shell
  vim ~/.condarc
  
  # 清华大学源
  channels:
    - defaults
  show_channel_urls: true
  default_channels:
    - https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/main
    - https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/free
    - https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/r
  custom_channels:
    conda-forge: https://mirrors.tuna.tsinghua.edu.cn/anaconda/cloud
    msys2: https://mirrors.tuna.tsinghua.edu.cn/anaconda/cloud
    bioconda: https://mirrors.tuna.tsinghua.edu.cn/anaconda/cloud
    menpo: https://mirrors.tuna.tsinghua.edu.cn/anaconda/cloud
    pytorch: https://mirrors.tuna.tsinghua.edu.cn/anaconda/cloud
  simpleitk: https://mirrors.tuna.tsinghua.edu.cn/anaconda/cloud
  ```
  
- pip 源

  ```shell
  vim ~/.pip/pip.conf
  
  # 豆瓣
  [global]
  index-url = https://pypi.tuna.tsinghua.edu.cn/simple
  [install]
  trusted-host = https://pypi.tuna.tsinghua.edu.cn
  # 中国科学技术大学
  https://pypi.mirrors.ustc.edu.cn/simple/
  # 阿里云
  http://mirrors.aliyun.com/pypi/simple/
  # 清华大学
  https://pypi.tuna.tsinghua.edu.cn/simple/
  # 华中科技大学
  http://pypi.hustunique.com/
  ```


- [AUR 源](https://mirrors.tuna.tsinghua.edu.cn/help/archlinuxcn/)

  ```shell
  vim /etc/pacman.conf
  
  # 清华大学源
  [archlinuxcn]
  Server = https://mirrors.tuna.tsinghua.edu.cn/archlinuxcn/$arch
  
  # 安装 archlinuxcn-keyring 包导入 GPG key
  sudo pacman -Syy
  sudo pacman -S archlinuxcn-keyring
  ```
