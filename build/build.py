# -*- coding: utf-8 -*-
#
# Network Sniffer Build Script 
# Script to execute cmake commands needed to compile NetworkSniffer.
#

import os, sys

print("******************* Building Network Sniffer *************************")

os.system("rm -rf /include/NetworkSniffer")

os.system("cmake .")

os.system("make")

# Use sudo because opening a raw socket requires elevated permissions.
os.system("sudo ./include/NetworkSniffer")
