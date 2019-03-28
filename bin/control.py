from PyQt5 import QtCore, QtWidgets, QtGui
from interface import Ui_MainWindow
import sys


class MainWindow(object):
    def __init__(self):
        app = QtWidgets.QApplication(sys.argv)
        MainWindow = QtWidgets.QMainWindow()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(MainWindow)
        self.set_lcd_1()
        self.set_dial_1()
        self.set_lcd_2()
        self.set_dial_2()
        self.set_lcd_3()
        self.set_dial_3()
        self.set_lcd_4()
        self.set_dial_4()

        self.ui.pushButton.clicked.connect(self.ui.initialize)
        self.ui.pushButton_2.clicked.connect(self.ui.stop)
        self.ui.pushButton_3.clicked.connect(self.ui.execute)
        self.ui.pushButton_4.clicked.connect(self.ui.run_pump_1)
        self.ui.pushButton_5.clicked.connect(self.ui.run_pump_2)
        self.ui.pushButton_6.clicked.connect(self.ui.run_pump_3)
        self.ui.pushButton_7.clicked.connect(self.ui.run_pump_4)



        # self.ui.initialize()

        MainWindow.show()
        sys.exit(app.exec_())


    # 设置LCD数字1
    def set_lcd_1(self):
        self.ui.lcdNumber.display(self.ui.dial.value())
    # 刻度盘信号槽1
    def set_dial_1(self):
        self.ui.dial.valueChanged['int'].connect(self.set_lcd_1)

    # 设置LCD数字2
    def set_lcd_2(self):
        self.ui.lcdNumber_2.display(self.ui.dial_2.value())
    # 刻度盘信号槽2
    def set_dial_2(self):
        self.ui.dial_2.valueChanged['int'].connect(self.set_lcd_2)

    # 设置LCD数字3
    def set_lcd_3(self):
        self.ui.lcdNumber_3.display(self.ui.horizontalSlider.value())
    # 刻度盘信号槽3
    def set_dial_3(self):
        self.ui.horizontalSlider.valueChanged['int'].connect(self.set_lcd_3)

    # 设置LCD数字3
    def set_lcd_4(self):
        self.ui.lcdNumber_4.display(self.ui.horizontalSlider_2.value())
    # 刻度盘信号槽3
    def set_dial_4(self):
        self.ui.horizontalSlider_2.valueChanged['int'].connect(self.set_lcd_4)


if __name__ == "__main__":
    MainWindow()

