---
layout: post
title: 重装系统后需要做的事
subtitle: Linux Config
author: ZhW
header-style: text
mathjax: true
tags: 
    - Linux
    - Configs
    - wiki
---

重装系统后需要做的事情！！！

一些配置文件放在 [https://github.com/ZhWing/zhwing.github.io/tree/master/_wiki/config](https://github.com/ZhWing/zhwing.github.io/tree/master/_wiki/config)

## 安装常用软件

- **Chrome**
- **VSCode**：
- **IntelliJ IDEA**
- **PyCharm**
- **Typora**
- **网易云音乐**
- **Qv2ray**
- **proxychains**
- **Tray-Icons-Reloaded**

## 配置终端

```shell
# 安装 oh-my-zsh
sudo apt install zsh git
sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"

# 设置为默认终端
chsh -s /bin/zsh `whoami`
chsh -s /bin/zsh root

# 安装 zsh-autosuggestions
git clone https://github.com/zsh-users/zsh-autosuggestions $ZSH_CUSTOM/plugins/zsh-autosuggestions

# 安装 zsh-syntax-highlighting
git clone https://github.com/zsh-users/zsh-syntax-highlighting.git ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-syntax-highlighting

# 配置 .zshrc
ZSH_THEME="ys" # 
plugins=(git zsh-syntax-highlighting zsh-autosuggestions sudo) # 插件

# 配置指令别名
alias gpp="g++ -std=c++11"

alias proxy="export http_proxy=127.0.0.1:7890; export https_proxy=127.0.0.1:7890; curl ipinfo.io;"
alias unproxy="unset http_proxy; unset https_proxy; curl ipinfo.io;"
alias pcs="proxychains"

source .zshrc
```

## Ubuntu 图形界面

### 关闭用户图形界面

```shell
sudo systemctl set-default multi-user.target
sudo reboot
```

### 开启用户图形界面

```shell
sudo systemctl set-default graphical.target
sudo reboot
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
  git config --global http.proxy http://127.0.0.1:7890
  git config --global https.proxy https://127.0.0.1:7890
  ```

- Git SSH 代理

  在用户目录下建立如下文件 `~/.ssh/config`，对 GitHub 的域名做单独的处理

  ```shell
  Host github.com
      HostName github.com
      User git
      # ProxyCommand socat - PROXY:127.0.0.1:%h:%p,proxyport=7890
      # ProxyCommand nc -v -x 127.0.0.1:7890 %h %p
  ```

  使用 HTTP 代理取消倒数第二行注释，安装 socat; 使用 SOCKS5 代理取消最后一行注释，安装 netcat。

## 代理工具

- elecrton-ssr

  - 仓库地址: [electron-ssr-backup](https://github.com/qingshuisiyuan/electron-ssr-backup)

- Clashy

  - 仓库地址: [Clashy](https://github.com/SpongeNobody/Clashy)

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
  
    [Clashy.png](https://github.com/ZhWing/zhwing.github.io/blob/master/img/wiki/Clashy.png)

- Qv2ray

  - 仓库地址：[Qv2ray](https://github.com/Qv2ray/Qv2ray)
  - v2ray-core：[v2ray-core](https://github.com/v2ray/v2ray-core)

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
  channel_alias: https://mirrors.tuna.tsinghua.edu.cn/anaconda
  default_channels:
    - https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/main
    - https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/free
    - https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/r
    - https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/pro
    - https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/msys2
  custom_channels:
    conda-forge: https://mirrors.tuna.tsinghua.edu.cn/anaconda/cloud
    msys2: https://mirrors.tuna.tsinghua.edu.cn/anaconda/cloud
    bioconda: https://mirrors.tuna.tsinghua.edu.cn/anaconda/cloud
    menpo: https://mirrors.tuna.tsinghua.edu.cn/anaconda/cloud
    pytorch: https://mirrors.tuna.tsinghua.edu.cn/anaconda/cloud
    simpleitk: https://mirrors.tuna.tsinghua.edu.cn/anaconda/cloud
  ```
  
- pip 源
  
  - 使用 `pqi`换源
  
    ubuntu 需要在 `.zshrc`在中添加一个环境变量才能找到 `pqi` 指令 
  
    环境变量：`.local/bin`

    ```shell
    pip3 install pqi
    ```


- [Arch 的 AUR  源](https://mirrors.tuna.tsinghua.edu.cn/help/archlinuxcn/) (`vim /etc/pacman.conf`)

  ```shell
  # 清华大学源
  [archlinuxcn]
  Server = https://mirrors.tuna.tsinghua.edu.cn/archlinuxcn/$arch
  ```
  
  安装 `archlinuxcn-keyring` 包导入 `GPG key`
  
  ```shell
  sudo pacman -Syy
  sudo pacman -S archlinuxcn-keyring
  ```
