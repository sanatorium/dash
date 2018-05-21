![GitHub Logo](images/sanity_logo_horizontal.png)

## install masternode

setup instructions to install a remote `sanitycore masternode` on a vps running ubuntu v16.04 - 64bit, controlled by a `sanitycore cold-wallet` on a windows-system

requirements (local system):
- windows 10, 64 bit
- `sanitycore wallet` with 10,000.10 SANITY

technical requirements (remote system):
- ubuntu 16, 64 bit
- 1 core
- 2 GB ram
- 20 GB diskspace
- 1 dedicated IP (per masternode)

![GitHub Logo](images/splash.png)


## configure local system (cold wallet): windows 10 64bit

### download wallet (zip)

*download wallet, unpack, run sanity-qt.exe and wait for sync*

>https://github.com/sanatorium/sanity/releases/download/v1.12.2.3/sanitycore-1.12.2-win64.zip

Menu -> Settings -> Options -> Wallet -> __Show Masternode Tab__

Menu -> Settings -> Options -> Wallet -> __Enable coin control features__

Menu -> File -> Receiving addresses... -> new -> label: **mn0** => _**mn0address**_

>STd4s1YLC2qu9j6jktHwGBUCGgJdYdJjvy

Send yourself exactly 10000 SANITY to _**mn0address**_ (STd4s1YLC2qu9j6jktHwGBUCGgJdYdJjvy)

*open the debug-console*: Menu -> Tools -> __Debug Console__

get the tx-id of the 10000 SANITY transaction
    > masternode outputs

>{"b79c0b19401bd68ff27aace31c9aeb04616d5ed116169fcd865cd7e2fc01af57": "1"}

create a masternode private key (just a random key to connect cold wallet with remote masternode)
    > masternode genkey

>5DUUcTpsnbReQoDVhriqPWnyX3jS34Jy85AGYfYFEtbStTbGwDz

Menu -> Tools -> Open Masternode Configuration File
> #alias IP-of-your-VPS:9999 masternodeprivkey collateral_output_txid collateral_output_index
> mn0 111.222.333.444:9999 5DUUcTpsnbReQoDVhriqPWnyX3jS34Jy85AGYfYFEtbStTbGwDz b79c0b19401bd68ff27aace31c9aeb04616d5ed116169fcd865cd7e2fc01af57 1

*close wallet and restart*

Masternodes-Tab -> My Masternodes -> Start all


## configure remote system (masternode): ubuntu 16 VPS

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

### download wallet (tar)

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

### configurate masternode

*add masternode private key to config*
```bash
nano ~/.sanitycore/sanity.conf
```
>```bash
>rpcuser=prc_anyusername_
>rpcpassword=prc_chooseanyrandompassword_
>rpcallowip=127.0.0.1
>rpcthreads=8
>listen=1
>server=1
>discover=1
>masternode=1
>masternodeprivkey=5DUUcTpsnbReQoDVhriqPWnyX3jS34Jy85AGYfYFEtbStTbGwDz
>```

### run headless masternode on vps

*start masternode deamon*
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

*check masternode and wait for sync*
```bash
~/.sanitycore/sanity-cli getinfo
```

*check masternode status (after some hours)*
```bash
~/.sanitycore/sanity-cli masternode status
```

### optional (at the moment) install sentinel

at the moment the sentinel is not required for masternode payments.
at a later stage this might change.
anyway you can install the sentinel following the instructions here:

https://github.com/sanatorium/sentinel
