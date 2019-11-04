# Libxml2 - 编译篇

```
    Note: 1. 记录 编译 libxml2 (版本 2.9.10 release) 过程, 
          2. 两个平台: linux, Android NDK
          3. 测试 读写 xml
          
    Time: 2019-11-13 
    Author: CRH

```

## 获取 源码

### 官方源码
```
    https://gitlab.gnome.org/GNOME/libxml2.git
```

### CRH Github 基于版本: 2.9.10 release
```
    git@github.com:CRongH/libxml2.git
```



## Ubuntu 环境 搭建

### 查看 readme

```
To build on an Unixised setup:
    ./configure ; make ; make install
    if the ./configure file does not exist, run ./autogen.sh instead.
```
`在根目录下 只有 ./autogen.sh`

### 执行 ./autogen.sh

```
$ ./autogen.sh

You must have autoconf installed to compile libxml.
Download the appropriate package for your distribution,
or see http://www.gnu.org/software/autoconf

You must have libtool installed to compile libxml.
Download the appropriate package for your distribution,
or see http://www.gnu.org/software/libtool

You must have automake installed to compile libxml.
Download the appropriate package for your distribution,
or see http://www.gnu.org/software/automake
```
`编译该工程 需要的依赖库 autoconf libtool automake`

### 安装 依赖库


`sudo apt-get install autoconf libtool automake pkg-config python-dev`

```
pkg-config 也是编译的必须库 
    不安装 Run ./autogen.sh 报如下错误:
    Couldn't find pkg.m4 from pkg-config. Install the appropriate package for
    your distribution or set ACLOCAL_PATH to the directory containing pkg.m4.   

```

## Linux 版本 编译

### Run ./autogen.sh
```
# ./autogen.sh
I am going to run ./configure with no arguments - if you wish
to pass any to it, please specify them on the ./autogen.sh command line.
configure.ac:53: warning: AM_INIT_AUTOMAKE: two- and three-arguments forms are deprecated.
aclocal.m4:9761: AM_INIT_AUTOMAKE is expanded from...
configure.ac:53: the top level
configure.ac:1506: warning: The macro `AC_TRY_LINK' is obsolete.
configure.ac:1506: You should run autoupdate.
../../lib/autoconf/general.m4:2698: AC_TRY_LINK is expanded from...
configure.ac:1506: the top level
configure.ac:1506: warning: The macro `AC_TRY_LINK' is obsolete.
configure.ac:1506: You should run autoupdate.

    ...

config.status: creating python/setup.py
config.status: creating xml2-config
config.status: creating config.h
config.status: executing depfiles commands
config.status: executing libtool commands
Done configuring

Now type 'make' to compile libxml2.
```


### Run make

#### 报错--> libxml.c:14:20: fatal error: Python.h: No such file or directory:
```
libxml.c:14:20: fatal error: Python.h: No such file or directory
compilation terminated.
Makefile:626: recipe for target 'libxml.lo' failed
make[4]: *** [libxml.lo] Error 1
make[4]: Leaving directory '/home/crh/libxml2/libxml2/python'
Makefile:687: recipe for target 'all-recursive' failed
make[3]: *** [all-recursive] Error 1
make[3]: Leaving directory '/home/crh/libxml2/libxml2/python'
Makefile:527: recipe for target 'all' failed
make[2]: *** [all] Error 2
make[2]: Leaving directory '/home/crh/libxml2/libxml2/python'
Makefile:1439: recipe for target 'all-recursive' failed
make[1]: *** [all-recursive] Error 1
make[1]: Leaving directory '/home/crh/libxml2/libxml2'
Makefile:859: recipe for target 'all' failed
make: *** [all] Error 2
```
#### 解决--> sudo apt-get install python-dev

#### 编译成功 log
```
ar: `u' modifier ignored since `D' is the default (see `U')
cat ./libxml.py `test -f libxml2class.py || echo ./`libxml2class.py > libxml2.py
make[4]: Leaving directory '/home/crh/libxml2/libxml2/python'
Making all in tests
make[4]: Entering directory '/home/crh/libxml2/libxml2/python/tests'
make[4]: Nothing to be done for 'all'.
make[4]: Leaving directory '/home/crh/libxml2/libxml2/python/tests'
make[3]: Leaving directory '/home/crh/libxml2/libxml2/python'
make[2]: Leaving directory '/home/crh/libxml2/libxml2/python'
make[1]: Leaving directory '/home/crh/libxml2/libxml2'

```

### Run make tests

```
## Module tests
Success!
Making all in .
Making all in tests
## running Python regression tests
  CC       io1.o
  CCLD     io1
  CC       io2.o
  CCLD     io2

    ...

  CCLD     xpath2
## examples regression tests

```
#### Demo 测试

`编译生成的 tests 在 ./doc/example 目录下`

```

The examples are stored per section depending on the main focus of the example:

xmlWriter :

testWriter.c: use various APIs for the xmlWriter
InputOutput :

io1.c: Example of custom Input/Output
io2.c: Output to char buffer
Tree :

tree2.c: Creates a tree
tree1.c: Navigates a tree to print element names
XPath :

xpath1.c: Evaluate XPath expression and prints result node set.
xpath2.c: Load a document, locate subelements with XPath, modify said elements and save the resulting document.
Parsing :

parse3.c: Parse an XML document in memory to a tree and free it
parse4.c: Parse an XML document chunk by chunk to a tree and free it
parse2.c: Parse and validate an XML file to a tree and free the result
parse1.c: Parse an XML file to a tree and free it
xmlReader :

reader2.c: Parse and validate an XML file with an xmlReader
reader1.c: Parse an XML file with an xmlReader
reader3.c: Show how to extract subdocuments with xmlReader
reader4.c: Parse multiple XML files reusing an xmlReader
```


1. 测试 写demo 
```
# cd  ./doc/exampels
# .testWriter
#cat writer1.tmp
#cat writer2.tmp
#cat writer3.tmp
#cat writer4.tmp
```

2. 测试 解析demo

```
# cd  ./doc/exampels

```

### 编写 demo 测试读写

1. libxml2-demo.c 源码
```
#include<stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

static void writeTest(void)
{
/* Write Test start*/
    //Define document pointer
    xmlDocPtr doc = xmlNewDoc(BAD_CAST"1.0");
     
    //Define node pointer
    xmlNodePtr root_node = xmlNewNode(NULL,BAD_CAST"root");

    //Set the root element of the document
    xmlDocSetRootElement(doc,root_node);

    xmlNewTextChild(root_node,NULL,BAD_CAST"newnode1",BAD_CAST"newnode1 content");
    xmlNewTextChild(root_node,NULL,BAD_CAST"newnode2",BAD_CAST"newnode2 content");

    xmlNodePtr node = xmlNewNode(NULL,BAD_CAST"node2");

    xmlNodePtr content = xmlNewText(BAD_CAST"NODE CONTENT");

    xmlAddChild(root_node,node);
    xmlAddChild(node,content);

    xmlNewProp(node,BAD_CAST"attribute",BAD_CAST"yes");

    node = xmlNewNode(NULL,BAD_CAST"son");
    xmlAddChild(root_node,node);
    xmlNodePtr grandson = xmlNewNode(NULL,BAD_CAST"grandson");
    xmlAddChild(node,grandson);
    xmlAddChild(grandson,xmlNewText(BAD_CAST"THis is a grandson node"));

    int nRel = xmlSaveFormatFile("libxml2-demo.xml", doc, 1);
    if(nRel != -1)
        printf("create xml %d byte!!\n",nRel);

    xmlFreeDoc(doc);
	
/* Write Test end*/	
	
}

static void parseTest(void)
{
	xmlKeepBlanksDefault (0); 
	xmlDocPtr doc = xmlParseFile("libxml2-demo.xml");
	if(doc == NULL)
	{
		printf("parse xml failed. \n");
		return;
	}
	
	xmlNodePtr curElement = xmlDocGetRootElement(doc);
	if(curElement == NULL)
	{
		printf("This xml file is empty. \n");
		return;
	}
	
	curElement = curElement->xmlChildrenNode;
	
	while(curElement != NULL) 
	{
		printf("curElement name:%s \n", curElement->name);
		
		xmlNodePtr curNode = curElement->xmlChildrenNode;
		while(curNode != NULL)
		{
			printf("	curNode name:%s, value:%s\n", curNode->name, xmlNodeGetContent(curNode));
			curNode = curNode->next;			
		}
		
		curElement = curElement->next;
	}
	
}

int main(int argc, char **argv)
{
	
	writeTest();

	parseTest();
	
    return 0;
}
```

2. 编译   
`在根目录下编译 `  
`gcc -o libxml2-demo ./doc/examples/libxml2-demo.c -I ./include -L .libs/ -lxml2`

3. 运行 ./libxml2-demo
```
.在 执行目录下 生成 libxml2-demo.xml

    <?xml version="1.0"?>
    <root>
    <newnode1>newnode1 content</newnode1>
    <newnode2>newnode2 content</newnode2>
    <node2 attribute="yes">NODE CONTENT</node2>
    <son>
        <grandson>THis is a grandson node</grandson>
    </son>
    </root>
. log 打印

$ ./libxml2-demo
    create xml 229 byte!!
    curElement name:newnode1
            curNode name:text, value:newnode1 content
    curElement name:newnode2
            curNode name:text, value:newnode2 content
    curElement name:node2
            curNode name:text, value:NODE CONTENT
    curElement name:son
            curNode name:grandson, value:THis is a grandson node
    crh@ubuntu:~/libxml2/libxml2$

```

## Android NDK 环境编译
`在编译 成 NDK 版本前 要执行 ./autogen.sh, 具体细节 查看文章前面 `

## NDK 环境搭建
`该部分 请自行 解决`

## 直接使用 CRH 目录下的文件 
```
拷贝 CRH/config.h 到根目录下
拷贝 CRH/Android.mk 到根目录下
拷贝 CRH/xmlversion.h 到 include/libxml 覆盖原有文件
拷贝 CRH/libxml2-demo.c 到 doc/examples 目录下
```

#### 编译
`ndk-build NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=./Android.mk  APP_ABI=arm64-v8a`

#### 测试
```
k71v1_64_bsp:/ # xml2-demo
create xml 229 byte!!
curElement name:newnode1
        curNode name:text, value:newnode1 content
curElement name:newnode2
        curNode name:text, value:newnode2 content
curElement name:node2
        curNode name:text, value:NODE CONTENT
curElement name:son
        curNode name:grandson, value:THis is a grandson node
        
k71v1_64_bsp:/ # cat CreatedXml.xml
<?xml version="1.0"?>
<root>
  <newnode1>newnode1 content</newnode1>
  <newnode2>newnode2 content</newnode2>
  <node2 attribute="yes">NODE CONTENT</node2>
  <son>
    <grandson>THis is a grandson node</grandson>
  </son>
</root>
k71v1_64_bsp:/ #
```



## 修改源码
### 编写 ANdroid.mk
```
LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

common_SRC_FILES := \
        SAX.c	\
        entities.c	\
        encoding.c \
        error.c		\
        parserInternals.c	\
        parser.c	\
        tree.c	\
        hash.c	\
        list.c	\
        xmlIO.c	\
        xmlmemory.c	\
        uri.c	\
        valid.c	\
        xlink.c	\
        debugXML.c	\
        xpath.c	\
        xpointer.c	\
        xinclude.c	\
        DOCBparser.c	\
        catalog.c	\
        globals.c	\
        threads.c	\
        c14n.c	\
        xmlstring.c	\
        buf.c	\
        xmlregexp.c	\
        xmlschemas.c	\
        xmlschemastypes.c	\
        xmlunicode.c	\
        xmlreader.c	\
        relaxng.c	\
        dict.c	\
        SAX2.c	\
        xmlwriter.c	\
        legacy.c	\
        chvalid.c	\
        pattern.c	\
        xmlsave.c	\
        xmlmodule.c	\
        schematron.c	\
		HTMLparser.c 	\
		HTMLtree.c \

common_C_INCLUDES += \
	$(LOCAL_PATH)/include	\

# Shared library
#=======================================================
include $(CLEAR_VARS)
LOCAL_MODULE:= libxml2
LOCAL_SRC_FILES := $(common_SRC_FILES)
LOCAL_C_INCLUDES := $(common_C_INCLUDES) 
LOCAL_SHARED_LIBRARIES := $(common_SHARED_LIBRARIES) #libdl
#LOCAL_CFLAGS := -DLIBXML_TREE_ENABLED
LOCAL_PRELINK_MODULE := false

include $(BUILD_SHARED_LIBRARY)


include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional

LOCAL_MODULE := libxml2-demo

LOCAL_SRC_FILES += \
        doc/examples/libxml2-demo.c \
		
LOCAL_C_INCLUDES +=	\
		$(LOCAL_PATH)/include	\

LOCAL_SHARED_LIBRARIES := libxml2

include $(BUILD_EXECUTABLE)

```

### 修改 config.h
`注释 以下两个宏定义`
```
/* Define if <pthread.h> is there */
/* #define HAVE_PTHREAD_H */

/* Define to 1 if you have the `rand_r' function. */
/* #define HAVE_RAND_R 1 */
```

### 修改 xmlversion.h

```

#if 0
#define LIBXML_THREAD_ENABLED
#endif

#if 0
#define LIBXML_FTP_ENABLED
#endif

#if 0
#define LIBXML_HTTP_ENABLED
#endif

#if 0
#define LIBXML_ICONV_ENABLED
#endif

#if 0
#define LIBXML_DEBUG_ENABLED
#endif

#if 0
#define LIBXML_ZLIB_ENABLED
#endif

```

### 编译 测试 (64位)

#### 编译
`ndk-build NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=./Android.mk  APP_ABI=arm64-v8a`

#### 测试
```
k71v1_64_bsp:/ # xml2-demo
create xml 229 byte!!
curElement name:newnode1
        curNode name:text, value:newnode1 content
curElement name:newnode2
        curNode name:text, value:newnode2 content
curElement name:node2
        curNode name:text, value:NODE CONTENT
curElement name:son
        curNode name:grandson, value:THis is a grandson node
        
k71v1_64_bsp:/ # cat CreatedXml.xml
<?xml version="1.0"?>
<root>
  <newnode1>newnode1 content</newnode1>
  <newnode2>newnode2 content</newnode2>
  <node2 attribute="yes">NODE CONTENT</node2>
  <son>
    <grandson>THis is a grandson node</grandson>
  </son>
</root>
k71v1_64_bsp:/ #
```


