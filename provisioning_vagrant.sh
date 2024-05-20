#!/usr/bin/env bash

sudo apt update
sudo apt install -y xfce4 gtk2-engines-pixbuf gtk2-engines-pixbuf:i386
sudo apt install -y virtualbox-guest-dkms virtualbox-guest-utils virtualbox-guest-x11
sudo sed -i 's/allowed_users=.*$/allowed_users=anybody/' /etc/X11/Xwrapper.config

sudo /vagrant/setup.sh
sudo /vagrant/build_vagrant.sh

sudo startxfce4