##Cool Blink

This is my first Arduino project.  The .ino file can be opened vio Aruino's official IDE and flashed to an Arduino Uno, but the clever way to deploy this code is with platformio which works on linux and can flash the Pro Trinket just fine.  Look at all the [boards](http://docs.platformio.org/en/latest/platforms/atmelavr.html) to choose from!  

##Deploy This Code in a Snap

Require's platformio is setup

    $  git clone https://github.com/TheNotary/cool_blink.git
    $  cd cool_blink
       # push bootloader button on the trinket
    $  platformio run


##Installing Platformio

Notes can be found at [platformio.org](http://docs.platformio.org/en/latest/quickstart.html)... 

    $  sudo python -c "$(curl -fsSL https://raw.githubusercontent.com/platformio/platformio/master/scripts/get-platformio.py)"

Then the project structure can be generated that will upload to the two board (uno and protrinket) via

    $  mkdir /tmp/cool_blink && cd /tmp/cool_blink
    $  platformio init --board=protrinket5 --board=uno

That will make your project all set to deploy to protrinkets (5v) and Arduino Uno boards.  You'll have to specifically choose the 'yes' option as it builds the project structure.  

Once that's done, you can drop your source code files into the 'src' directory and build your project with (the sudo is required until you grant your user access to )

    $  sudo platformio run

Your deploy targets are specified in `platformio.ini`, and platformio will automatically look to see if the devices are attached and try to flash to them.  

Compilation artifacts and binaries can be found in the hidden folder `.pioenvs`


##Removing need for sudo

You don't need to do this part, but you can.  It's specific to Linux Mint, a debian based linux systems.

The problem is that linux protects USB devices from being written to unless you have been granted the privledge to do so.  You need to add your user to the dialout group and privledge that group with write access to the USBtinyISP interface to allow you to write to the chip.  To do this in Debian based distros, you need to create a new rule file in `/etc/udev/rules.d/30-allow_USBtinyISP.rules`.  Each flavor of Debian, may use differnt code words, but linux Mint 17 definately uses "ATTRS" as apposed to alternatives, such as Ubuntu 9.10's "SYSFS", and "ATTR" varients.  You might need to play around with it, google doesn't chart this domain very well and it may be time consuming to get everything perfect, but it should be done, and your OS providers should be informed of the issue.  In principal, in software development, you should not need to use the 'sudo' command on your development machine for TONS of reasons, including 'sudo' can create files as root that you then lose access to as a normal user, sudo runs as root creating a security vulnerability, and including the word sudo simply makes the command look more nasty than it needs to be.  

(/etc/udev/rules.d/30-allow_trinket.rules)
    
    SUBSYSTEM=="usb", ATTRS{idVendor}=="1781", ATTRS{idProduct}=="0c9f", GROUP="dialout", MODE="0664"

REQUIRED:  The command to allow members of the dialout group access to that trinket when your trinket is plugged in is.  It's needlessly huge because I'm awesome (eg replace USBtiny with another USB device giving you this kind of USB write error):

    $  arr=$(lsusb |grep USBtiny | awk ' { print $6 }' | tr ":" " ") && \
       usb_v_id=$(echo $arr |awk ' { print $1 } ') && \
       usb_p_id=$(echo $arr |awk ' { print $2 } ') && \
       echo "SUBSYSTEM==\"usb\", ATTRS{idVendor}==\"$usb_v_id\", ATTRS{idProduct}==\"$usb_p_id\", GROUP=\"dialout\", MODE=\"0664\" " | \
       sudo tee --append /etc/udev/rules.d/30-allow_trinket.rules

    $  sudo restart udev
    

REQUIRED:  To add your current user to the dialout group, do the below command and then log out and back in again.  
    
    $  sudo usermod -aG dialout $(whoami)
    
Btw, the dialout group automatically gets tty access, so you'll be able to upload to the Arduino Uno without sudo now too.  




