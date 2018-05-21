![GitHub Logo](images/sanity_logo_horizontal.png)

## install from TAR on a linux vps

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


### download tar

```bash
wget https://github.com/sanatorium/sanity/releases/download/v1.12.2.3/sanitycore-1.12.2-linux64.tar.gz
```


### unpack binaries

```bash
tar xvzf sanitycore-1.12.2-linux64.tar.gz
rm ~/sanitycore-1.12.2-linux64.tar.gz
mkdir ~/.sanitycore
cp ~/sanitycore-1.12.2/bin/* ~/.sanitycore
rm -rf ~/sanitycore-1.12.2
```


### run headless wallet on vps

*start wallet deamon*
```bash
~/.sanitycore/sanityd -daemon
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
