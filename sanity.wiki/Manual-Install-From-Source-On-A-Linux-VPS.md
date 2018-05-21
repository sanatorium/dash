![GitHub Logo](images/sanity_logo_horizontal.png)

## install manually from source on a linux vps

setup instructions to install `sanitycore` on a vps running ubuntu v16.04 - 64bit

technical requirements:
- ubuntu 16, 64 bit
- 1 core
- 2 GB ram
- 20 GB diskspace

additional requirements for master-nodes:
- 1 dedicated IP

![GitHub Logo](images/splash.png)


### create new user `sanitycore`

*log into your vps, you need root access*

```bash
sudo adduser sanitycore
sudo usermod -aG sudo sanitycore
su - sanitycore
```

### install dependencies

```bash
sudo apt update -y
sudo apt upgrade -y

# build requirements
sudo apt-get install -y build-essential libtool autotools-dev automake pkg-config libssl-dev libevent-dev bsdmainutils

# boost
sudo apt-get install -y libboost-system-dev libboost-filesystem-dev libboost-chrono-dev libboost-program-options-dev libboost-test-dev libboost-thread-dev

# bitcoin personal package archive
sudo apt-get install -y software-properties-common
sudo add-apt-repository -y ppa:bitcoin/bitcoin
sudo apt-get update -y

# db 4.8
sudo apt autoremove
sudo apt-get install -y libdb4.8-dev libdb4.8++-dev

# zqm
sudo apt-get install -y libzmq3-dev

# qt5
sudo apt-get install -y libqt5gui5 libqt5core5a libqt5dbus5 qttools5-dev qttools5-dev-tools libprotobuf-dev protobuf-compiler

# git
sudo apt install -y git

# dos2unix
sudo apt-get install -y dos2unix

#curl
sudo apt install -y curl
```

### vps security

*install firewall*
```bash
sudo apt-get -y install ufw
sudo ufw default deny incoming
sudo ufw default allow outgoing
sudo ufw allow ssh
sudo ufw limit ssh/tcp
sudo ufw allow 9999/tcp
sudo ufw logging on
sudo ufw enable
```

optional for RPC from outside: *sudo ufw allow 9998/tcp*


*install fail2ban*
```bash
sudo apt-get -y install fail2ban
sudo systemctl enable fail2ban
sudo systemctl start fail2ban
```

### create swap file

```bash
sudo dd if=/dev/zero of=/swapfile bs=1M count=2000
sudo mkswap /swapfile
sudo chown root:root /swapfile
sudo chmod 0600 /swapfile
sudo swapon /swapfile
```

### clone source

*get source-code from github*
```bash
cd ~/
git clone https://github.com/sanatorium/sanity
```

### optional: remove windows line-feeds

*convert CRFL to LF*
```bash
cd ~/sanity
find . -type f -not -path '*/\.*' -exec grep -Il '.' {} \; | xargs -d '\n' -L 1 sudo dos2unix -k
```

*fix PATH variable on LSW (linux subsystem on windows)*
```bash
PATH=$(echo "$PATH" | sed -e 's/:\/mnt.*//g')
```

### build headless wallet for linux

*make binaries*
```bash
cd ~/sanity
./autogen.sh
./configure --without-gui --disable-tests --disable-bench --disable-silent-rules
make
make install-strip DESTDIR=~/sanitybin
```

*copy binaries*
```bash
mkdir ~/.sanitycore
cp -uv ~/sanitybin/usr/local/bin/sanityd ~/.sanitycore
cp -uv ~/sanitybin/usr/local/bin/sanity-cli ~/.sanitycore
```

### run headless wallet on vps

*start deamon*
```bash
cd ~/.sanitycore
./sanityd -daemon
```

### make permanent / auto-restart on reboot

*add a cronjob*
```bash
crontab -e
    @reboot sleep 15; /home/sanitycore/.sanitycore/sanityd -daemon
```

*restart vps*
```bash
sudo reboot
```

*login as user `sanitycore` or switch to this user*
```bash
su - sanitycore
```

*check sanity wallet and wait for sync*
```bash
~/.sanitycore/sanity-cli getinfo
```

### in-wallet mining

*stop deamon*
```bash
~/.sanitycore/sanity-cli stop
```

*edit sanity.conf*
```bash
nano ~/.sanitycore/sanity.conf

    gen=1
```

*restart deamon*
```bash
~/.sanitycore/sanityd -daemon
```

### optional: remove source- and build code

*start deamon*
```bash
rm -rf ~/sanity
rm -rf ~/sanitybin
```
