#!/usr/bin/env python
# -*- coding: utf-8 -*-

from PyQt5.QtWidgets import QApplication, QWidget, QLineEdit, QInputDialog, QGridLayout, QLabel, QPushButton, QFrame
import serial
import time


class InputDialog(QWidget):
    def __init__(self):
        super(InputDialog,self).__init__()
        self.initUi()
        self.speed1 = 2000
        self.speed2 = 2000
        self.recursionCount = 1

    def initUi(self):
        self.setWindowTitle("化学机器人")
        self.setGeometry(500, 500, 400, 500)

        label1 = QLabel("抽取速度:")
        label2 = QLabel("排出速度:")
        label3 = QLabel("循环次数:")

        self.speedLabel1 = QLabel("2000")
        self.speedLabel1.setFrameStyle(QFrame.Panel|QFrame.Sunken)

        self.speedLabel2 = QLabel("2000")
        self.speedLabel2.setFrameStyle(QFrame.Panel | QFrame.Sunken)

        self.recursionCountLabel = QLabel("1")
        self.recursionCountLabel.setFrameStyle(QFrame.Panel|QFrame.Sunken)

        self.numberLable = QLabel("5")
        self.numberLable.setFrameStyle(QFrame.Panel|QFrame.Sunken)

        self.costLable = QLabel("0")
        self.costLable.setFrameStyle(QFrame.Panel|QFrame.Sunken)

        self.introductionLable = QLabel("0")
        self.introductionLable.setFrameStyle(QFrame.Panel|QFrame.Sunken)

        self.commandLable = QLabel("")
        self.commandLable.setFrameStyle(QFrame.Panel | QFrame.Sunken)

        speedButton1 = QPushButton("设置抽取液体速度")
        speedButton1.clicked.connect(self.setSpeed1)

        speedButton2 = QPushButton("设置推出液体速度")
        speedButton2.clicked.connect(self.setSpeed2)

        countButton = QPushButton("设置循环次数")
        countButton.clicked.connect(self.setCount)

        executeButton = QPushButton("执行")
        executeButton.clicked.connect(self.execute)

        stopButton = QPushButton("停止")
        stopButton.clicked.connect(self.stop)

        initButton = QPushButton("初始化")
        initButton.clicked.connect(initialize)

        pump_button1 = QPushButton("蠕动泵1")
        initButton.clicked.connect(self.run_pump_1)


        mainLayout=QGridLayout()
        mainLayout.addWidget(label1, 0, 0)
        mainLayout.addWidget(self.speedLabel1,0,1)
        mainLayout.addWidget(speedButton1,0,2)
        mainLayout.addWidget(label2, 1, 0)
        mainLayout.addWidget(self.speedLabel2, 1, 1)
        mainLayout.addWidget(speedButton2, 1, 2)
        mainLayout.addWidget(label3, 2, 0)
        mainLayout.addWidget(self.recursionCountLabel,2,1)
        mainLayout.addWidget(countButton,2,2)
        mainLayout.addWidget(executeButton, 3, 1)
        mainLayout.addWidget(stopButton, 4, 1)
        mainLayout.addWidget(initButton, 5, 1)
        mainLayout.addWidget(pump_button1, 6, 1)

        self.setLayout(mainLayout)


    def setSpeed1(self):
        number, ok = QInputDialog.getInt(self, "速度1", "请设置速度：", int(self.speedLabel1.text()), 200, 3000, 500)
        if ok:
            self.speed1 = number
            self.speedLabel1.setText(str(number))

    def setSpeed2(self):
        number, ok = QInputDialog.getInt(self, "速度2", "请设置速度：", int(self.speedLabel2.text()), 200, 3000, 500)
        if ok:
            self.speed2 = number
            self.speedLabel2.setText(str(number))

    def setCount(self):

        number, ok = QInputDialog.getInt(self, "循环次数", "请设置循环次数：", int(self.numberLable.text()), 1, 100, 1)
        if ok:
            self.recursionCount = number
            self.recursionCountLabel.setText(str(number))

    def stop(self):
        ser = open_serial()
        result = ser.write('\x02\x31\x31\x54\x03\x55'.encode("gb2312"))  # 写数据
        time.sleep(1)
        ser.write('\x02\x31\x31\x54\x03\x55'.encode("gb2312"))  # 写数据
        print("写总字节数:", result)
        ser.close()  # 关闭串口
        print("停止成功")

    def execute(self):
        ser = open_serial()

        # 生成命令
        prefix = '11'.encode('utf-8').hex()
        command = "\x02" + "11" + "gV" + str(self.speed1) + "IA3000OV" + str(self.speed2) + "A0G" + str(self.recursionCount) + "R" + "\x03"
        command += parity(command)
        # command = command.encode('utf-8')



        # converted = command.hex()
        # print("converted: " + converted)
        # msg = "02" + prefix + converted + "03"
        # msg = msg + parity(msg)[2:4]
        # msg_hex = r"\x" + r"\x".join(msg[n: n + 2] for n in range(0, len(msg), 2))
        # print(msg_hex)


        # verify = stx^address^index^command_hex^etx depict

        example = '\x02\x31\x31\x67\x56\x32\x30\x30\x30\x49\x41\x33\x30\x30\x30\x4f\x56\x32\x30\x30\x30\x41\x30\x47\x35\x52\x03\x73'
        if example == command:
            print("they are equal")
        else:
            print("example: ", example)
            print("command: ", command)
            print("example type: ", type(example))
            print("command type: ", type(command))

        # 写数据
        # result = ser.write(msg_hex.encode("gb2312"))  # 写数据
        result = ser.write(command.encode("gb2312"))  # 写数据
        time.sleep(1)
        result1 = ser.write(command.encode("gb2312"))
        # result1 = ser.write(msg_hex.encode("gb2312"))  # 写数据
        print("写总字节数:", result)

        ser.close()  # 关闭串口

    def run_pump_2(self):
        order = "p2"
        result = ser.write(order.encode("gb2312"))
        print("写字节总数：", result)

    def run_pump_3(self):
        order = "p3"
        result = ser.write(order.encode("gb2312"))
        print("写字节总数：", result)

    def run_pump_4(self):
        order = "p4"
        result = ser.write(order.encode("gb2312"))
        print("写字节总数：", result)

def open_serial():
    # 端口，GNU / Linux上的/ dev / ttyUSB0 等 或 Windows上的 COM3 等
    portx = "com6"
    # 波特率，标准值之一：50,75,110,134,150,200,300,600,1200,1800,2400,4800,9600,19200,38400,57600,115200
    bps = 9600
    # 超时设置,None：永远等待操作，0为立即返回请求结果，其他值为等待超时时间(单位为秒）
    timex = 0
    # 打开串口，并得到串口对象
    ser = serial.Serial(portx, bps, timeout=timex)
    print("串口详情参数：", ser)
    return ser


def initialize():
    ser = open_serial()
    # 写数据
    result = ser.write('\x02\x31\x31\x5A\x52\x03\x09'.encode("gb2312"))  # 写数据
    time.sleep(1)
    ser.write('\x02\x31\x31\x5A\x52\x03\x09'.encode("gb2312"))  # 写数据
    print("写总字节数:", result)

    ser.close()  # 关闭串口
    print("初始化成功")


def parity(msg):
    parity = ord(msg[0])
    for i in range(1, len(msg)):
        parity = parity ^ ord(msg[i])

    return str(chr(parity))


if __name__=="__main__":
    import sys
    initialize()
    app=QApplication(sys.argv)
    myshow = InputDialog()
    myshow.show()
    sys.exit(app.exec_())
