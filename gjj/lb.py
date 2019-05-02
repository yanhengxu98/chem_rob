#coding=utf-8

import sys
from PyQt5.QtWidgets import *
from interface import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
import pymysql
import serial
import time



class MyMainWindow(QMainWindow, Ui_MainWindow):


    def __init__(self, parent = None):
        super(MyMainWindow,self).__init__(parent)
        self.setupUi(self)

        self.set_lcd_1()
        self.set_dial_1()
        self.set_lcd_2()
        self.set_dial_2()
        self.set_lcd_3()
        self.set_dial_3()
        self.set_lcd_4()
        self.set_dial_4()
        self.Datatable.setEditTriggers(QAbstractItemView.NoEditTriggers)
        self.Datatable.setRowCount(20)
        self.Datatable.setColumnCount(47)
        self.Datatable.setColumnWidth(0,55)
        self.xianzhi = QIntValidator(self)
        self.Data_N_tv.setValidator(self.xianzhi)
        for i in range(2,47):
            if (i !=5 and i!=9 and i!=13):
                self.Datatable.setColumnWidth(i,80)

        pDoubleValidator = QDoubleValidator(self)
        pDoubleValidator.setRange(0,99)
        pDoubleValidator.setNotation(QDoubleValidator.StandardNotation)
        pDoubleValidator.setDecimals(1)

        self.rdb1_start.setValidator(pDoubleValidator)
        self.rdb2_start.setValidator(pDoubleValidator)
        self.rdb3_start.setValidator(pDoubleValidator)
        self.rdb4_start.setValidator(pDoubleValidator)
        self.rdb1_end.setValidator(pDoubleValidator)
        self.rdb2_end.setValidator(pDoubleValidator)
        self.rdb3_end.setValidator(pDoubleValidator)
        self.rdb4_end.setValidator(pDoubleValidator)


        self.connection = pymysql.connect(host = '10.26.1.10',user ='root',password = 'root',db='chemistry',port = 3306,
    charset = 'utf8mb4',cursorclass = pymysql.cursors.DictCursor)
        self.Data_N_search.clicked.connect(self.Nsearch)
        self.Data_look.clicked.connect(self.showMsg)
        self.Data_R_search.clicked.connect(self.Rsearch)
        self.pushButton.clicked.connect(self.initialize)
        self.pushButton_2.clicked.connect(self.stop)
        self.pushButton_3.clicked.connect(self.execute)
        self.rdb_exec.clicked.connect(self.run__pumb)
        self.rdb_clean.clicked.connect(self.clean_pumb)
        self.Data_reaction.clicked.connect(self.auto_reaction)



        #self.initialize()


  #  def findmt(self):
    # 设置LCD数字1
    def set_lcd_1(self):
        self.lcdNumber.display(self.dial.value())
    # 刻度盘信号槽1
    def set_dial_1(self):
        self.dial.valueChanged['int'].connect(self.set_lcd_1)

    # 设置LCD数字2
    def set_lcd_2(self):
        self.lcdNumber_2.display(self.dial_2.value())
    # 刻度盘信号槽2
    def set_dial_2(self):
        self.dial_2.valueChanged['int'].connect(self.set_lcd_2)

    # 设置LCD数字3
    def set_lcd_3(self):
        self.lcdNumber_3.display(self.horizontalSlider.value())
    # 刻度盘信号槽3
    def set_dial_3(self):
        self.horizontalSlider.valueChanged['int'].connect(self.set_lcd_3)

    # 设置LCD数字3
    def set_lcd_4(self):
        self.lcdNumber_4.display(self.horizontalSlider_2.value())
    # 刻度盘信号槽3
    def set_dial_4(self):
        self.horizontalSlider_2.valueChanged['int'].connect(self.set_lcd_4)


    def closeEvent(self, event):
        reply = QtWidgets.QMessageBox.question(self,
                                               '本程序',
                                               "是否要退出程序？",
                                               QtWidgets.QMessageBox.Yes | QtWidgets.QMessageBox.No,
                                               QtWidgets.QMessageBox.No)
        if reply == QtWidgets.QMessageBox.Yes:
            event.accept()
        else:
            event.ignore()
            self.connection.close()

    def showMsg(self):

        horizontalHeader = ["实验编号","泵0注入化学式","泵0浓度","注入体积","注入质量","泵1注入化学式","泵1浓度","注入体积","注入质量","泵2注入化学式","泵2浓度","注入体积","注入质量","泵3注入化学式","泵3浓度","注入体积","注入质量","步骤1名称","操作参数","时间min","步骤2名称","操作参数","时间min","步骤3名称","操作参数","时间min","步骤4名称","操作参数","时间min","步骤5名称","操作参数","时间min","步骤6名称","操作参数","时间min","步骤7名称","操作参数","时间min","步骤8名称","操作参数","时间min","步骤9名称","操作参数","时间min","步骤10名称","操作参数","时间min"]
        self.Datatable.setHorizontalHeaderLabels(horizontalHeader)
        for i in range(20):
            for k in range(47):
                self.Datatable.setItem(i,k,QTableWidgetItem(""))

        with self.connection.cursor() as cursor:
            sql = "SELECT * FROM `反应全程`"
            cursor.execute(sql)
            self.result = cursor.fetchall()
            for column_count in range(len(self.result)):

                a = list(self.result[column_count].values())

                for row_count in range(46):

                    self.Datatable.setItem(column_count,row_count,QTableWidgetItem(str(a[row_count])))

    def Nsearch(self):

        horizontalHeader = ["实验编号","泵0注入化学式","泵0浓度","注入体积","注入质量","泵1注入化学式","泵1浓度","注入体积","注入质量","泵2注入化学式","泵2浓度","注入体积","注入质量","泵3注入化学式","泵3浓度","注入体积","注入质量","步骤1名称","操作参数","时间min","步骤2名称","操作参数","时间min","步骤3名称","操作参数","时间min","步骤4名称","操作参数","时间min","步骤5名称","操作参数","时间min","步骤6名称","操作参数","时间min","步骤7名称","操作参数","时间min","步骤8名称","操作参数","时间min","步骤9名称","操作参数","时间min","步骤10名称","操作参数","时间min"]
        self.Datatable.setHorizontalHeaderLabels(horizontalHeader)

        for i in range(20):
            for k in range(47):
                self.Datatable.setItem(i,k,QTableWidgetItem(""))

        sql = "SELECT * FROM `反应全程` WHERE `实验编号` = `%s`" % self.Data_N_tv.text()
        print(sql)

        
        with self.connection.cursor() as cursor:
            sql = "SELECT * FROM `反应全程` WHERE `实验编号` = '%s'" % self.Data_N_tv.text()
            cursor.execute(sql)
            self.result2 = cursor.fetchall()

            if len(self.result2) == 0:
                self.Datatable.setItem(0,1,QTableWidgetItem("无返回数据"))
           
            for column_count in range(len(self.result2)):

                a = list(self.result2[column_count].values())

                for row_count in range(46):

                    self.Datatable.setItem(column_count,row_count,QTableWidgetItem(str(a[row_count])))
        
        
    def Rsearch(self):

        horizontalHeader = ["实验编号","泵0注入化学式","泵0浓度","注入体积","注入质量","泵1注入化学式","泵1浓度","注入体积","注入质量","泵2注入化学式","泵2浓度","注入体积","注入质量","泵3注入化学式","泵3浓度","注入体积","注入质量","步骤1名称","操作参数","时间min","步骤2名称","操作参数","时间min","步骤3名称","操作参数","时间min","步骤4名称","操作参数","时间min","步骤5名称","操作参数","时间min","步骤6名称","操作参数","时间min","步骤7名称","操作参数","时间min","步骤8名称","操作参数","时间min","步骤9名称","操作参数","时间min","步骤10名称","操作参数","时间min"]
        self.Datatable.setHorizontalHeaderLabels(horizontalHeader)

        for i in range(20):
            for k in range(47):
                self.Datatable.setItem(i,k,QTableWidgetItem(""))

        
        with self.connection.cursor() as cursor:
            sql = "SELECT * FROM `反应全程` WHERE `泵0注入化学式` LIKE '%%%s%%' OR `泵1注入化学式` LIKE '%%%s%%' OR `泵2注入化学式` LIKE '%%%s%%' OR `泵3注入化学式` LIKE '%%%s%%' " % (self.Data_R_tx.text(),self.Data_R_tx.text(),self.Data_R_tx.text(),self.Data_R_tx.text())
            cursor.execute(sql)
            self.result3 = cursor.fetchall()

            if len(self.result3) == 0:
                self.Datatable.setItem(0,1,QTableWidgetItem("无返回数据"))
           
            for column_count in range(len(self.result3)):

                a = list(self.result3[column_count].values())

                for row_count in range(46):

                    self.Datatable.setItem(column_count,row_count,QTableWidgetItem(str(a[row_count])))

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


    def run__pumb(self):
        ser = self.open_pump_serial()
        startlist = [self.rdb1_start.text(),self.rdb2_start.text(),self.rdb3_start.text(),self.rdb4_start.text()]
        endlist = [self.rdb1_end.text(),self.rdb2_end.text(),self.rdb3_end.text(),self.rdb4_end.text()]
        
        for i in range(0, 4):
            if (len(startlist[i]) != 0) and (len(endlist[i]) != 0):
                time.sleep(0.1)
                rdbstart = float(startlist[i])
                rdbend = float(endlist[i])
                if rdbstart>=rdbend:
                    print("开始时间小于或等于结束时间，将不发送指令")
                    return
                else:
                    time1 = rdbend - rdbstart
                    order = '#p%d%03d%03d' % (i + 1, int(rdbstart * 10), int(time1 * 10))
                    # order = "#p"+str(i+1)+str(rdbstart*10)+str(int(time1*10))
                    print(order)
                    result = ser.write(order.encode("gb2312"))
                    time.sleep(0.1)
                    result1 = ser.write(order.encode("gb2312"))
                    print(result1)
                    print("写字节总数：", result) 

            elif (len(self.rdb1_end.text()) == 0) and (len(self.rdb1_start.text()) != 0):
                time.sleep(0.1)
                rdb1start = float(self.rdb1_start.text())
                order = "#p"+str(i) + str(rdb1start)+str(999)
                result = ser.write(order.encode("gb2312"))
                time.sleep(0.1)
                result1 = ser.write(order.encode("gb2312"))
                print("写字节总数：", result) 


    def clean_pumb(self):
        ser = self.open_pump_serial()
        order = "#p1000300"
        print(order)
        result = ser.write(order.encode("gb2312"))
        time.sleep(0.1)
        result1 = ser.write(order.encode("gb2312"))
        time.sleep(0.1)
        order2 = "#p2300300"
        print(order2)
        result2 = ser.write(order2.encode("gb2312"))
        time.sleep(0.1)
        result3 = ser.write(order2.encode("gb2312"))


    def absorb(self):
        return

    def auto_reaction(self):
        # pump = 1
        with self.connection.cursor() as cursor:
            sql = "SELECT * FROM `反应全程`"
            cursor.execute(sql)
            self.result = cursor.fetchall()


            a = list(self.result[0].values())

            print(a[3])
            ser = self.open_pump_serial()
            order = "#p1000%03d" % (a[3] * int(10))
            order2 = "#"
            result2 = ser.write(order.encode("gb2312"))
            time.sleep(0.1)
            result3 = ser.write(order.encode("gb2312"))
            time.sleep(0.1)

if __name__ == "__main__":
    
    app = QApplication(sys.argv)
    myWin = MyMainWindow()
    myWin.show()
    sys.exit(app.exec_())
