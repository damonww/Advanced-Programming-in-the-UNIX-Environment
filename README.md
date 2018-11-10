# Advanced-Programming-in-the-UNIX-Environment
需要下载相关的库文件，下载链接：http://www.apuebook.com/src.3e.tar.gz
``` bash
$ tar -zxvf src.3e.tar.gz
$ cd apue.3e
$ cp include/apue.h /usr/include
$ cp lib/error.c /usr/include
```
然后打开/usr/include/apue.h，在文件最后#endif前加上包含error.c的代码：
`#include "error.c";`
