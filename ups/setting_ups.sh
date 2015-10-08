cd ~/develop-subject/ups

sudo apt-get install i2c-tools

cp picofssd.py ~
sudo mv /etc/rc.local /etc/rc.local_old
sudo cp rc.local /etc

echo "
i2c-bcm2708
i2c-dev
rtc-ds1307" | sudo tee -a /etc/modules

sudo i2cset -y 1 0x6B 9 30

sudo raspi-config
cat << EOT
“Internationalisation Options” > “Advanced Options” > enable the ARM I2C
Please reboot
EOT

sudo reboot