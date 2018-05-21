sanitycore v1.12.2.3-80000
==========================

`master:` [![Build Status](https://travis-ci.org/sanatorium/sanity.svg?branch=master)](https://travis-ci.org/sanatorium/sanity)

https://www.sanity.mn
https://github.com/sanatorium/sanity/releases


What is Sanity?
----------------

Sanity is an experimental new digital currency that enables anonymous, instant
payments to anyone, anywhere in the world. Sanity uses peer-to-peer technology
to operate with no central authority: managing transactions and issuing money
are carried out collectively by the network. Sanitycore is the software which
enables the use of the currency SANITY.

For more information, as well as an immediately useable, binary version of
the Sanity core software, see https://www.sanity.mn.

WIKI
----------------

[Check the wiki for more information](sanity.wiki)

DOC
----------------

[Check the docs for more detailed informations](doc)

Quick install wallet - Ubuntu 16 64bit VPS
----------------

Log into your linux VPS as root and create a new user

    #create new user
    su
    adduser sanitycore
    usermod -aG sudo sanitycore
    su - sanitycore

Download wallet, configure, make permanent and start wallet with mining (gen=1)

    #download wallet
    sudo apt-get install -y wget
    cd ~/ && wget https://github.com/sanatorium/sanity/releases/download/v1.12.2.3/sanitycore-1.12.2-linux64.tar.gz
    tar xvzf sanitycore-1.12.2-linux64.tar.gz && rm ~/sanitycore-1.12.2-linux64.tar.gz
    mkdir ~/.sanitycore && cp ~/sanitycore-1.12.2/bin/* ~/.sanitycore && rm -rf ~/sanitycore-1.12.2

    #configure sanity for in-wallet-mining
    echo -e "rpcport=9988\nport=9989\ngen=1\ntxindex=1\naddressindex=1\ntimestampindex=1\nspentindex=1\nlogtimestamps=1" > ~/.sanitycore/sanity.conf

    #restart wallet on system restarts
    (crontab -l 2>/dev/null; echo "@reboot sleep 15; /home/sanitycore/.sanitycore/sanityd -daemon") | crontab -

    #reboot server
    sudo reboot

    #check wallet
    su -sanitycore
    cd ~/.sanitycore
    ./sanity-cli getinfo
    ./sanity-cli getwalletinfo
    ./sanity-cli getmininginfo
    ./sanity-cli listaccounts


Quick update a previous installed wallet
----------------

Log into your linux VPS

    su - sanitycore

Remove old core, download new version, restart wallet

    cd
    rm -rf ~/sanitycore-*
    ~/.sanitycore/sanity-cli stop
    wget https://github.com/sanatorium/sanity/releases/download/v1.12.2.3/sanitycore-1.12.2-linux64.tar.gz
    tar xvzf sanitycore-1.12.2-linux64.tar.gz && rm ~/sanitycore-1.12.2-linux64.tar.gz
    rm -rf ~/.sanitycore/sanity-cli && rm -rf ~/.sanitycore/sanityd && rm -rf ~/.sanitycore/sanity-qt && rm -rf ~/.sanitycore/sanity-tx && rm -rf ~/.sanitycore/test_sanity
    cp ~/sanitycore-1.12.2/bin/* ~/.sanitycore && rm -rf ~/sanitycore-1.12.2
    ~/.sanitycore/sanityd -daemon
    ls -al ~/.sanitycore
    ~/.sanitycore/sanity-cli getinfo


License
-------

Sanity's core is released under the terms of the MIT license. See [COPYING](COPYING) for more
information or see https://opensource.org/licenses/MIT.

Development Process
-------------------

The `master` branch is meant to be stable. Development is normally done in separate branches.
[Tags](https://github.com/sanatorium/sanity/tags) are created to indicate new official,
stable release versions of Sanitycore.
