# FramelessWindow-Qt
自定义无边框窗体，对话框和提示框，添加边框阴影，同时支持Winndows和Ubuntu系统。Windows系统下支持部分Aero效果。

FlyWM_
GitHub: https://github.com/FlyWM
CSDN: https://blog.csdn.net/a844651990

# 使用方法
1. 只需要包含头文件 MuCustomWindow.h 即可。
2. 设置客户区域的widget调用函数 void setClientWidget(QWidget *client)或者调用QLayout* clientLayout()函数去添加自己需要的widget。
3. 获取标题栏MuTitleBar *titleBar() const，然后可以获取标题栏的各个部分。
4. 如果想要在标题栏添加选项，可以调用titleBar()->customWidget()获取出去按钮、图标和标题之外的widget。


# 效果图：
### Window
![image](https://github.com/FlyWM/FramelessWindow-Qt/blob/master/samples/CustomWindow.png)

### Dialog
![image](https://github.com/FlyWM/FramelessWindow-Qt/blob/master/samples/CustomDialog.png)

### Information MessageBox
![image](https://github.com/FlyWM/FramelessWindow-Qt/blob/master/samples/CustomInformationMessagBox.png)

### Success MessageBox
![image](https://github.com/FlyWM/FramelessWindow-Qt/blob/master/samples/CustomSuccessMessageBox.png)

### Aero Window 目前只支持最大化和还原时的动态效果
![image](https://github.com/FlyWM/FramelessWindow-Qt/blob/master/samples/AeroWindow.png)

### 拖动窗口变大，不带橡皮筋效果
![image](https://github.com/FlyWM/FramelessWindow-Qt/blob/master/samples/scaleAndMove_noRubber.gif)

### 拖动窗口变大，带橡皮筋效果
![image](https://github.com/FlyWM/FramelessWindow-Qt/blob/master/samples/scaleAndMove_withRubber.gif)
