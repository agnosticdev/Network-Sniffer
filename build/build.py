# -*- coding: utf-8 -*-
#
# Network Sniffer Build Script 
# Script to execute cmake commands needed to compile NetworkSniffer.
#

import os, sys

print("******************* Building Network Sniffer *************************")

os.system("cmake .")

os.system("make")

os.system("./include/NetworkSniffer")
