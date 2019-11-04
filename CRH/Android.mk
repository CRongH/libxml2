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
