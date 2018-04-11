## Kernel Compile
>\# su root </br>
\# cd/usr/src </br>
\# apt-get update</br>
\# apt-get install build-essential bin86 kernel-package libncurses5-dev</br>
\# apt-get install libssl-dev </br>
\# wget -P /usr/src http://www.kernel.org/pub/linux/kernel/v4.x/linux-4.3.tar.gz </br>
\# tar zxvf linux-4.3.tar.gz </br>
\# ln -s /usr/src/linux-4.3 /usr/src/linux </br>
\# cd /usr/src/linux </br>
\# make-kpkg clean </br>
\# make-kpkg --initrd --revision=1pmfsnew kernel_image kernel_headers modules_image -j4 </br>
\# cd /usr/src</br>
\# dpkg -i linux*1pmfsnew*.deb </br>
\# reboot </br>
\# uname -a </br>


## Sendfile Client and Server
* 클라이언트 컴파일 : gcc -o sfc.out sendFileClient.c
* 서버 컴파일 : gcc -o sfs.out sendFileServer.c
* 서버 실행 : sfs.out [port]
* 클라이언트 실행 : sfc.out [ip] [port] [send file name]
