#!/bin/bash
#take care use gopass for webserver passoword
#gopass --cipher md5  --password 123456 example.com stzn administrator,purchase
#you may be modify 123456(password),stzn(name) and replace auth.txt password
source /opt/fsl-imx-fb/4.1.15-1.0.0/environment-setup-cortexa7hf-vfp-neon-poky-linux-gnueabi
make
cp build/linux-arm-static/bin/goahead ./test/ -fr
sync
