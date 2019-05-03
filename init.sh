#!/bin/sh

tar -zxvf src.3e.tar.gz -C /tmp
cd /tmp/apue.3e
cp include/apue.h /usr/include
cp lib/error.c /usr/include

# 然后打开/usr/include/apue.h，在文件最后#endif前加上包含error.c的代码：
# `#include "error.c";`
