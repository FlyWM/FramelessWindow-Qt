#---------------------------------------------
# 自定义无边框窗体、对话框和提示框
#
# projectFramelessWindow.pro
# 工程文件
#
# FlyWM_
# GitHub: https://github.com/FlyWM
# CSDN: https://blog.csdn.net/a844651990
#
#---------------------------------------------

TEMPLATE = subdirs

# 当使用subdirs模板时，此选项指定应按给出目录的顺序处理列出的目录
CONFIG += ordered

SUBDIRS += libTest \
        libFramelessWindow

