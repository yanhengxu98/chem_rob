# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'interface.ui'
#
# Created by: PyQt5 UI code generator 5.11.3
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets
import serial
import time


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("化学机器人")
        MainWindow.resize(1178, 780)

        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.tabWidget = QtWidgets.QTabWidget(self.centralwidget)
        self.tabWidget.setGeometry(QtCore.QRect(0, -1, 1651, 751))
        self.tabWidget.setObjectName("tabWidget")
        self.tab = QtWidgets.QWidget()
        self.tab.setObjectName("tab")
        self.groupBox = QtWidgets.QGroupBox(self.tab)
        self.groupBox.setGeometry(QtCore.QRect(10, 0, 691, 721))
        self.groupBox.setObjectName("groupBox")
        self.label = QtWidgets.QLabel(self.groupBox)
        self.label.setGeometry(QtCore.QRect(20, 57, 101, 31))
        font = QtGui.QFont()
        font.setFamily("Agency FB")
        font.setPointSize(12)
        self.label.setFont(font)
        self.label.setTextFormat(QtCore.Qt.AutoText)
        self.label.setWordWrap(False)
        self.label.setObjectName("label")
        self.dial = QtWidgets.QDial(self.groupBox)
        self.dial.setGeometry(QtCore.QRect(200, 20, 141, 91))
        self.dial.setMinimum(1)
        self.dial.setMaximum(4000)
        self.dial.setSingleStep(200)
        self.dial.setObjectName("dial")
        self.lcdNumber = QtWidgets.QLCDNumber(self.groupBox)
        self.lcdNumber.setGeometry(QtCore.QRect(420, 30, 191, 71))
        self.lcdNumber.setObjectName("lcdNumber")
        self.label_2 = QtWidgets.QLabel(self.groupBox)
        self.label_2.setGeometry(QtCore.QRect(20, 160, 101, 31))
        font = QtGui.QFont()
        font.setFamily("Agency FB")
        font.setPointSize(12)
        self.label_2.setFont(font)
        self.label_2.setTextFormat(QtCore.Qt.AutoText)
        self.label_2.setWordWrap(False)
        self.label_2.setObjectName("label_2")
        self.dial_2 = QtWidgets.QDial(self.groupBox)
        self.dial_2.setGeometry(QtCore.QRect(210, 130, 131, 91))
        self.dial_2.setMinimum(1)
        self.dial_2.setMaximum(4000)
        self.dial_2.setSingleStep(200)
        self.dial_2.setObjectName("dial_2")
        self.lcdNumber_2 = QtWidgets.QLCDNumber(self.groupBox)
        self.lcdNumber_2.setGeometry(QtCore.QRect(420, 150, 191, 71))
        self.lcdNumber_2.setObjectName("lcdNumber_2")
        self.label_3 = QtWidgets.QLabel(self.groupBox)
        self.label_3.setGeometry(QtCore.QRect(20, 290, 111, 31))
        font = QtGui.QFont()
        font.setFamily("Agency FB")
        font.setPointSize(12)
        self.label_3.setFont(font)
        self.label_3.setObjectName("label_3")
        self.horizontalSlider = QtWidgets.QSlider(self.groupBox)
        self.horizontalSlider.setGeometry(QtCore.QRect(170, 290, 221, 21))
        self.horizontalSlider.setMinimum(1)
        self.horizontalSlider.setMaximum(3000)
        self.horizontalSlider.setOrientation(QtCore.Qt.Horizontal)
        self.horizontalSlider.setObjectName("horizontalSlider")
        self.lcdNumber_3 = QtWidgets.QLCDNumber(self.groupBox)
        self.lcdNumber_3.setGeometry(QtCore.QRect(420, 270, 191, 71))
        self.lcdNumber_3.setObjectName("lcdNumber_3")
        self.label_4 = QtWidgets.QLabel(self.groupBox)
        self.label_4.setGeometry(QtCore.QRect(20, 400, 111, 31))
        font = QtGui.QFont()
        font.setFamily("Agency FB")
        font.setPointSize(12)

        self.label_4.setFont(font)
        self.label_4.setObjectName("label_4")
        self.horizontalSlider_2 = QtWidgets.QSlider(self.groupBox)
        self.horizontalSlider_2.setGeometry(QtCore.QRect(170, 410, 221, 21))
        self.horizontalSlider_2.setMinimum(1)
        self.horizontalSlider_2.setMaximum(30)
        self.horizontalSlider_2.setOrientation(QtCore.Qt.Horizontal)
        self.horizontalSlider_2.setObjectName("horizontalSlider_2")
        self.lcdNumber_4 = QtWidgets.QLCDNumber(self.groupBox)
        self.lcdNumber_4.setGeometry(QtCore.QRect(420, 390, 191, 71))
        self.lcdNumber_4.setObjectName("lcdNumber_4")

        self.pushButton = QtWidgets.QPushButton(self.groupBox)
        self.pushButton.setGeometry(QtCore.QRect(60, 540, 112, 34))
        self.pushButton.setObjectName("pushButton")

        self.pushButton_2 = QtWidgets.QPushButton(self.groupBox)
        self.pushButton_2.setGeometry(QtCore.QRect(280, 540, 112, 34))
        self.pushButton_2.setObjectName("pushButton_2")

        self.pushButton_3 = QtWidgets.QPushButton(self.groupBox)
        self.pushButton_3.setGeometry(QtCore.QRect(520, 540, 112, 34))
        self.pushButton_3.setObjectName("pushButton_3")

        self.pushButton_4 = QtWidgets.QPushButton(self.groupBox)
        self.pushButton_4.setGeometry(QtCore.QRect(20, 600, 112, 34))
        self.pushButton_4.setObjectName("pushButton_4")

        self.pushButton_5 = QtWidgets.QPushButton(self.groupBox)
        self.pushButton_5.setGeometry(QtCore.QRect(200, 600, 112, 34))
        self.pushButton_5.setObjectName("pushButton_5")

        self.pushButton_6 = QtWidgets.QPushButton(self.groupBox)
        self.pushButton_6.setGeometry(QtCore.QRect(380, 600, 112, 34))
        self.pushButton_6.setObjectName("pushButton_6")

        self.pushButton_7 = QtWidgets.QPushButton(self.groupBox)
        self.pushButton_7.setGeometry(QtCore.QRect(560, 600, 112, 34))
        self.pushButton_7.setObjectName("pushButton_7")

        self.groupBox_2 = QtWidgets.QGroupBox(self.tab)
        self.groupBox_2.setGeometry(QtCore.QRect(720, 10, 441, 681))
        self.groupBox_2.setObjectName("groupBox_2")

        self.label_5 = QtWidgets.QLabel(self.groupBox_2)
        self.label_5.setGeometry(QtCore.QRect(50, 50, 91, 51))
        font = QtGui.QFont()
        font.setFamily("Agency FB")
        font.setPointSize(12)
        self.label_5.setFont(font)
        self.label_5.setObjectName("label_5")
        self.spinBox = QtWidgets.QSpinBox(self.groupBox_2)
        self.spinBox.setGeometry(QtCore.QRect(190, 60, 71, 31))
        font = QtGui.QFont()
        font.setFamily("Arial")
        font.setPointSize(12)
        self.spinBox.setFont(font)
        self.spinBox.setMinimum(1)
        self.spinBox.setMaximum(4)
        self.spinBox.setObjectName("spinBox")

        self.label_6 = QtWidgets.QLabel(self.groupBox_2)
        self.label_6.setGeometry(QtCore.QRect(50, 120, 81, 41))
        font = QtGui.QFont()
        font.setFamily("Agency FB")
        font.setPointSize(12)
        self.label_6.setFont(font)
        self.label_6.setObjectName("label_6")
        self.spinBox_2 = QtWidgets.QSpinBox(self.groupBox_2)
        self.spinBox_2.setGeometry(QtCore.QRect(190, 130, 71, 31))
        font = QtGui.QFont()
        font.setFamily("Arial")
        font.setPointSize(12)
        self.spinBox_2.setFont(font)
        self.spinBox_2.setMinimum(0)
        self.spinBox_2.setMaximum(20)
        self.spinBox_2.setObjectName("spinBox_2")
        self.tabWidget.addTab(self.tab, "")

        self.label_7 = QtWidgets.QLabel(self.groupBox_2)
        self.label_7.setGeometry(QtCore.QRect(50, 190, 81, 41))
        font = QtGui.QFont()
        font.setFamily("Agency FB")
        font.setPointSize(12)
        self.label_7.setFont(font)
        self.label_7.setObjectName("label_5")
        self.spinBox_3 = QtWidgets.QSpinBox(self.groupBox_2)
        self.spinBox_3.setGeometry(QtCore.QRect(190, 200, 71, 31))
        font = QtGui.QFont()
        font.setFamily("Arial")
        font.setPointSize(12)
        self.spinBox_3.setFont(font)
        self.spinBox_3.setMinimum(0)
        self.spinBox_3.setMaximum(20)
        self.spinBox_3.setObjectName("spinBox")

        self.tab_2 = QtWidgets.QWidget()
        self.tab_2.setObjectName("tab_2")
        self.tabWidget.addTab(self.tab_2, "")
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 1178, 30))
        self.menubar.setObjectName("menubar")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)
        self.tabWidget.setCurrentIndex(0)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "化学机器人"))
        self.groupBox.setTitle(_translate("MainWindow", "指令发送"))
        self.label.setText(_translate("MainWindow", "抽取速度"))
        self.label_2.setText(_translate("MainWindow", "排出速度"))
        self.label_3.setText(_translate("MainWindow", "抽取体积"))
        self.label_4.setText(_translate("MainWindow", "循环次数"))
        self.pushButton.setText(_translate("MainWindow", "初始化"))
        self.pushButton_2.setText(_translate("MainWindow", "停止"))
        self.pushButton_3.setText(_translate("MainWindow", "执行"))
        self.pushButton_4.setText(_translate("MainWindow", "蠕动泵1"))
        self.pushButton_5.setText(_translate("MainWindow", "蠕动泵2"))
        self.pushButton_6.setText(_translate("MainWindow", "蠕动泵3"))
        self.pushButton_7.setText(_translate("MainWindow", "蠕动泵4"))
        self.groupBox_2.setTitle(_translate("MainWindow", "泵切换与端口控制"))
        self.label_5.setText(_translate("MainWindow", "泵编号"))
        self.label_6.setText(_translate("MainWindow", "端口号"))
        self.label_7.setText(_translate("MainWindow", "蠕动泵"))

        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab), _translate("MainWindow", "手动"))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab_2), _translate("MainWindow", "自动"))

    def parity(self, msg):
        parity = ord(msg[0])
        for i in range(1, len(msg)):
            parity = parity ^ ord(msg[i])

        return str(chr(parity))

    def open_serial(self):
        try:
            # 端口，GNU / Linux上的/ dev / ttyUSB0 等 或 Windows上的 COM3 等
            portx = "com" + str(self.spinBox_2.value())
            # portx = "com15"
            # 波特率，标准值之一：50,75,110,134,150,200,300,600,1200,1800,2400,4800,9600,19200,38400,57600,115200
            bps = 9600
            # 超时设置,None：永远等待操作，0为立即返回请求结果，其他值为等待超时时间(单位为秒）
            timex = 0
            # 打开串口，并得到串口对象
            ser = serial.Serial(portx, bps, timeout=timex)
            print("串口详情参数：", ser)
            return ser
        except Exception as e:
            print("---异常---：", e)

    def open_pump_serial(self):
        try:
            # 端口，GNU / Linux上的/ dev / ttyUSB0 等 或 Windows上的 COM3 等
            portx = "com" + str(self.spinBox_3.value())
            # portx = "com15"
            # 波特率，标准值之一：50,75,110,134,150,200,300,600,1200,1800,2400,4800,9600,19200,38400,57600,115200
            bps = 9600
            # 超时设置,None：永远等待操作，0为立即返回请求结果，其他值为等待超时时间(单位为秒）
            timex = 0
            # 打开串口，并得到串口对象
            ser = serial.Serial(portx, bps, timeout=timex)
            print("串口详情参数：", ser)
            return ser
        except Exception as e:
            print("---异常---：", e)

    def generateInitializeCommand(self):
        command = "\x02" + str(self.spinBox.value()) + "1" + "ZR" + "\x03"
        print(self.spinBox.value())
        command += self.parity(command)
        return command

    def generateStopCommand(self):
        command = "\x02" + str(self.spinBox.value()) + "1" + "T" + "\x03"
        command += self.parity(command)
        return command

    def generateExecuteCommand(self):
        speed1 = self.dial.value()
        speed2 = self.dial_2.value()
        dest = self.horizontalSlider.value()
        count = self.horizontalSlider_2.value()

        command = "\x02" + str(self.spinBox.value()) + "1" + "gV" + str(speed1) + "IA" + str(dest) +  "OV" + str(speed2) + "A0G" + str(
            count) + "R" + "\x03"
        command += self.parity(command)
        return command

    def initialize(self):
        ser = self.open_serial()
        command = self.generateInitializeCommand()
        result = ser.write(command.encode("gb2312"))
        time.sleep(1)
        result1 = ser.write(command.encode("gb2312"))
        print("微流管-写总字节数:", result)
        ser2 = self.open_pump_serial()
        command = self.generateInitializeCommand()
        result = ser2.write(command.encode("gb2312"))
        time.sleep(1)
        result1 = ser2.write(command.encode("gb2312"))
        print("蠕动泵-写总字节数:", result)

        ser.close()  # 关闭串口

    def pump_ini(self):
        ser2 = self.open_pump_serial()
        command = self.generateInitializeCommand()
        result = ser2.write(command.encode("gb2312"))
        time.sleep(1)
        result1 = ser2.write(command.encode("gb2312"))
        print("蠕动泵-写总字节数:", result)

    def stop(self):
        ser = self.open_serial()
        command = self.generateStopCommand()
        result = ser.write(command.encode("gb2312"))
        print("写总字节数:", result)
        time.sleep(1)
        result1 = ser.write(command.encode("gb2312"))

        ser.close()  # 关闭串口

    def execute(self):
        ser = self.open_serial()
        command = self.generateExecuteCommand()
        print(command)
        result = ser.write(command.encode("gb2312"))
        time.sleep(1)
        result1 = ser.write(command.encode("gb2312"))

        print("写总字节数:", result)

        ser.close()  # 关闭串口

    def run_pump_1(self):
        ser = self.open_pump_serial()
        order = "p1"
        result = ser.write(order.encode("gb2312"))
        time.sleep(1)
        result1 = ser.write(order.encode("gb2312"))
        print("写字节总数：", result)

    def run_pump_2(self):
        ser = self.open_pump_serial()
        order = "p2"
        result = ser.write(order.encode("gb2312"))
        time.sleep(1)
        result1 = ser.write(order.encode("gb2312"))
        print("写字节总数：", result)

    def run_pump_3(self):
        ser = self.open_pump_serial()
        order = "p3"
        result = ser.write(order.encode("gb2312"))
        time.sleep(1)
        result1 = ser.write(order.encode("gb2312"))
        print("写字节总数：", result)

    def run_pump_4(self):
        ser = self.open_pump_serial()
        order = "p4"
        result = ser.write(order.encode("gb2312"))
        time.sleep(1)
        result1 = ser.write(order.encode("gb2312"))
        print("写字节总数：", result)





