NEXT-NDNSENSOR
----

NDN Sensor Project based on Consumer/Producer API

For license information see LICENSE.

http://named-data.net/

Description
----

NDN-based Sensor Project using Consumer/Producer API. 

Project contains two kinds of producers and consumers. 

The CPU-Sensor Producer keeps detecting the CPU temperatrue every 60 seconds and writing it into repo-ng, which is the NDN repository. The consumer can consume the Name(like /ndn/ucla/cpu/temp) to get the latest CPU temperatrue from the repo.

The Light-Control Consumer can send the command(inside the interest with consumers' signature) to control the screen light of the Producer. Producer will verify the interest, run the control command if signature proved and return the sucessful status to the Consumer with producers' signature. If verification failed, Producer would return NACK with NO-DATA signal to the Consumer. Consumer could check the status it gets from the Producer and verify the signature。

Structure
----

The directory structure is as follows:

* **/root**
    * **src/** *-- source code*
    * **waf** *-- binary waf file*
    * **wscript** *-- waf instruction file*
    * **.waf-tools/** *-- additional waf tools*
    * **repo-ng.config** *-- repo-ng config file*
    * **LICENSE**
    * **README.md**
    * **INSTALL.md**

Building instructions
----
Please, see the [INSTALL.md](INSTALL.md) for build and install instructions.

License
---
This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version, with the additional exemption that compiling, linking, and/or using OpenSSL is allowed.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
