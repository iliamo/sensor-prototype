NEXT-NDNSENSOR: NDN Sensor Project based on Consumer/Producer API
==

Prerequisites
==
These are prerequisites to build NEXT-NDNSENSOR.

**Required:**
* [NDN-CXX](https://github.com/named-data/ndn-cxx.git)
* [NFD](https://github.com/named-data/NFD.git)
* [consumer-producer-api](git@git.irl.cs.ucla.edu:ndn/consumer-producer-api.git)
* [repo-ng](https://github.com/named-data/repo-ng.git)
* [screenbrightness](https://github.com/jmstacey/screenbrightness.git)

Prerequisites build instructions
==

MacOS build considerations
--

NDN-CXX & NFD
--
First install NDN-CXX, then install NFD.

consumer-producer-api
--
Only after NDN-CXX & NFD installation, build and install this API.

repo-ng
--
copy the repo-ng.config into ${SYSCONFDIR}/ndn(default is /usr/local/etc).

screenbrightness
--
brew install screenbrightness


NEXT_NDNSENSOR build instructions
==
<pre>
$ ./waf configure
$ ./waf
</pre>


NEXT_NDNSENSOR run instructions
==
Terminal Zero  
<pre>
$ nfd-start
$ ndn-repo-ng
</pre>

Terminal One (Producer Part)
<pre>
$ ./producer 
</pre>

Terminal Two (Consumer Part)
<pre>
$ ./consumer
or
$ ./consumer on or off or otherExecutableCommand
or 
$ ./consumer ExecutableCommand UserIdentiy
for e.g. ./consumer off myName.
</pre>

command "on" stands for lighting the screen
command "off" stands for diming the screen
