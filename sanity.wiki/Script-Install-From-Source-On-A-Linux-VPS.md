![GitHub Logo](images/sanity_logo_horizontal.png)

## install by script (from source) on a linux vps

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

### get install-script

```bash
sudo apt install -y git
git clone https://github.com/sanatorium/sanity-scripts.git && cd sanity-scripts
```

### install dependencies

```bash
./sanity.sh deps
```

### vps security

*install fail2ban and firewall*
```bash
./sanity.sh firewall
```

### create swap file

```bash
./sanity.sh swap
```

### clone source

*get source-code from github*
```bash
./sanity.sh clone
```

### build headless wallet for linux

*make binaries and copy binaries to ~/sanitybin*
```bash
./sanity.sh compilewallet
```

### optional: config for masternode

*make binaries and copy binaries to ~/sanitybin*
```bash
./sanity.sh configmn
```

### run headless wallet on vps

*start wallet deamon*
```bash
./sanity.sh startwallet
```

### alternative: run masternode on vps

*start wallet deamon*
```bash
./sanity.sh startmn
```

### make permanent / auto-restart on reboot

*add a cronjob*
```bash
crontab -e
```
>```bash
>@reboot sleep 15; /home/sanitycore/.sanitycore/sanityd -daemon
>```

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

### in-wallet mining (only for non-masternodes)

*stop deamon*
```bash
~/.sanitycore/sanity-cli stop
```

*edit sanity.conf*
```bash
nano ~/.sanitycore/sanity.conf
```
>```bash
>gen=1
>```

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
