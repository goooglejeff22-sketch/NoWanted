LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := NoWanted
LOCAL_SRC_FILES := main.cpp
LOCAL_C_INCLUDES += $(LOCAL_PATH)
LOCAL_CPPFLAGS  += -std=c++17 -O2 -DNDEBUG -fno-rtti -fno-exceptions
LOCAL_LDLIBS    += -llog
include $(BUILD_SHARED_LIBRARY)
