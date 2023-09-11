import sys  # sys нужен для передачи argv в QApplication
from PyQt5 import QtWidgets
from PyQt5.QtWidgets import (QMainWindow, QApplication, QWidget, QPushButton, QAction, QLineEdit, QMessageBox,
                             QTextEdit, QFileDialog, QHBoxLayout, QFrame)
from PyQt5.QtGui import QIcon, QDoubleValidator, QIntValidator, QPixmap, QPainter, QColor
from PyQt5.QtCore import Qt
import design  # Это наш конвертированный файл дизайна
import dialog
import dialogfile
import dialogfileres
import dialogres
import matplotlib
from main import *
from main2 import *
import pyqtgraph as pg
import pyqtgraph.exporters
import numpy as np


class ResFile(QtWidgets.QDialog, dialogfileres.Ui_Dialog):

    def __init__(self, data):
        super().__init__()
        self.setupUi(self)
        self.setWindowTitle('Результаты работы')
        self.setWindowFlags(Qt.FramelessWindowHint)
        self.resef = []
        self.count = []
        self.resNeuro(data)
        self.pushButton.clicked.connect(self.on_cli)
        self.pushButton_2.clicked.connect(self.on_clo)
        self.pushButton_3.clicked.connect(self.plot)
        self.pushButton_7.clicked.connect(self.on_clo)

    def resNeuro(self, data):
        res = []
        res = FileWork(data)
        self.resef = FileWorkEf(data) * 100
        res_str = ""
        res_str += '№   Результат   P Вихря нет    P Появление    P Вихрь есть   P Возникла ошибка Эффективность\n'
        for i in range(len(res)):
            self.count += [i]
            res_str += str(i + 1)
            for j in range(4 - len(str(i + 1))):
                res_str += " "
            if (np.argmax(res[i]) == 0):
                res_str += 'Вихря нет   '
            if (np.argmax(res[i]) == 1):
                res_str += 'Появление   '
            if (np.argmax(res[i]) == 2):
                res_str += 'Вихрь есть  '
            if (np.argmax(res[i]) == 3):
                res_str += 'Oшибка      '
            for x in res[i]:
                res_str += str(x)
                for j in range(15 - len(str(x))):
                    res_str += " "
            res_str += "   " + str(self.resef[i][0]) + "\n"
        self.textEdit.setText(res_str)

    def plot(self):
        # define the data
        theTitle = "График эффективности электродиализа"
        y = [x[0] for x in self.resef]  # [2,4,6,8,10,12,14,16,18,20]
        x = range(0, len(y))
        # create plot
        plt = pg.plot(x, y, title=theTitle, pen='r')
        plt.setBackground('w')
        plt.showGrid(x=True, y=True)
        # set properties
        plt.setLabel('left', 'Эффективность', units='y')
        plt.setLabel('bottom', 'Номер элемента из выборки', units='x')
        plt.plot(x, y, pen='r', symbol='o', symbolPen='r', symbolBrush=0.2, name='blue')

    def on_cli(self):
        self.close()

    def on_clo(self):
        fname = QFileDialog.getSaveFileName(self, 'Save file', '/result_neyro.txt')[0]
        f = open(fname, "w")
        f.write(self.textEdit.toPlainText())
        f.close()


class OpenFile(QtWidgets.QDialog, dialogfile.Ui_Dialog):

    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.setWindowTitle('Выберите файл для расчета нейросети')
        self.setWindowFlags(Qt.FramelessWindowHint)
        self.showDialog()
        self.pushButton.clicked.connect(self.on_click)
        self.pushButton_2.clicked.connect(self.on_close)
        self.pushButton_7.clicked.connect(self.on_close)

    def showDialog(self):
        self.show()
        fname = QFileDialog.getOpenFileName(self, 'Open file', '/home')[0]

        f = open(fname, 'r')
        data = f.read()
        self.textEdit.setText(data)
        f.close()

    def on_click(self):
        self.close()
        self.d = ResFile(self.textEdit.toPlainText())
        self.d.show()

    def on_close(self):
        self.close()


class DialogRes(QtWidgets.QDialog, dialogres.Ui_Dialog):
    def __init__(self, tv1, tv2, tv3, tv4):
        # Это здесь нужно для доступа к переменным, методам
        # и т.д. в файле design.py
        super().__init__()
        self.ForPaintRes = 0
        self.setupUi(self)  # Это нужно для инициализации нашего дизайна
        self.setWindowTitle('Результаты расчета нейросети')
        self.setWindowFlags(Qt.FramelessWindowHint)
        self.lineEdit.hide()
        self.lineEdit_2.hide()
        self.lineEdit_3.hide()
        self.lineEdit_4.hide()
        self.label_2.hide()
        self.label_3.hide()
        self.label_4.hide()
        self.label_5.hide()
        self.label_6.hide()
        self.res(tv1, tv2, tv3, tv4)
        self.pushButton.clicked.connect(self.on_close)
        self.pushButton_2.clicked.connect(self.on_show)
        self.pushButton_3.clicked.connect(self.on_close)
        self.pushButton_4.clicked.connect(self.on_sh)

    def paintEvent(self, e):
        painter = QPainter(self)
        painter.setRenderHint(QPainter.Antialiasing)
        painter.setPen(QColor('#d4d4d4'))
        painter.setBrush(QColor(255, 106, 69))
        res = self.ForPaintRes
        ress = res * 100
        self.label_9.setText(str(ress))
        kk = res * 5750
        # painter.drawPie(100, 100, 200, 200, 0, 5750)#5750
        painter.drawPie(285, 250, 100, 100, 0, kk)
        painter.setBrush(QColor(148, 153, 255))
        painter.drawPie(285, 250, 100, 100, kk, 5750 - kk)

    def on_show(self):
        self.lineEdit.show()
        self.lineEdit_2.show()
        self.lineEdit_3.show()
        self.lineEdit_4.show()
        self.label_2.show()
        self.label_3.show()
        self.label_4.show()
        self.label_5.show()
        self.label_6.show()

    def on_sh(self):
        self.lineEdit.hide()
        self.lineEdit_2.hide()
        self.lineEdit_3.hide()
        self.lineEdit_4.hide()
        self.label_2.hide()
        self.label_3.hide()
        self.label_4.hide()
        self.label_5.hide()
        self.label_6.hide()

    def res(self, tv1, tv2, tv3, tv4):
        res = []
        resef = []
        res = VvodWork(tv1, tv2, tv3, tv4)
        resef = VvodWorkEf(tv1, tv2, tv3, tv4)
        self.lineEdit.setText(str(res[0][0]))
        self.lineEdit_2.setText(str(res[0][1]))
        self.lineEdit_3.setText(str(res[0][2]))
        self.lineEdit_4.setText(str(res[0][3]))
        if (np.argmax(res) == 0):
            self.label_7.setText('Вихря нет')
        if (np.argmax(res) == 1):
            self.label_7.setText('Появление')
        if (np.argmax(res) == 2):
            self.label_7.setText('Вихрь есть')
        if (np.argmax(res) == 3):
            self.label_7.setText('Возникла ошибка')
        self.lineEdit_6.setText(str(resef[0][0] * 100))
        self.ForPaintRes = resef[0][0]

    def on_close(self):
        self.close()


class Dialog(QtWidgets.QDialog, dialog.Ui_Dialog):
    def __init__(self):
        # Это здесь нужно для доступа к переменным, методам
        # и т.д. в файле design.py
        super().__init__()
        self.setupUi(self)  # Это нужно для инициализации нашего дизайна
        self.setWindowTitle('Введите параметры для расчета нейросети')
        self.setWindowFlags(Qt.FramelessWindowHint)
        self.pushButton.clicked.connect(self.on_click)
        self.pushButton_2.clicked.connect(self.on_close)
        self.pushButton_3.clicked.connect(self.close_d)
        self.lineEdit.setPlaceholderText('Интервал: 1..100')
        self.lineEdit_2.setPlaceholderText('Интервал: 0,1..1,0')
        self.lineEdit_3.setPlaceholderText('Интервал: 3..15')
        self.lineEdit_4.setPlaceholderText('Интервал: -0,1..-0,4')
        self.lineEdit.setValidator(QIntValidator(0, 100))
        # self.lineEdit_2.setValidator(QDoubleValidator(0.1, 1.0, 1, notation=QDoubleValidator.StandardNotation))
        self.lineEdit_3.setValidator(QIntValidator(3, 15))
        # self.lineEdit_4.setValidator(QDoubleValidator(-0.1, -0.4, 1, notation=QDoubleValidator.StandardNotation))

    def on_click(self):
        textboxValue1 = float(self.lineEdit.text())
        textboxValue2 = float(self.lineEdit_2.text())
        textboxValue3 = float(self.lineEdit_3.text())
        textboxValue4 = float(self.lineEdit_4.text())
        self.d = DialogRes(textboxValue1, textboxValue2, textboxValue3, textboxValue4)
        self.d.show()

    def on_close(self):
        self.close()

    def close_d(self):
        self.close()


class ExampleApp(QtWidgets.QMainWindow, design.Ui_MainWindow):
    def __init__(self):
        # Это здесь нужно для доступа к переменным, методам
        # и т.д. в файле design.py
        super().__init__()
        self.setupUi(self)  # Это нужно для инициализации нашего дизайна
        self.setWindowTitle('Добро пожаловать')
        self.setWindowFlags(Qt.FramelessWindowHint)
        self.pushButton.clicked.connect(self.show_dialog)
        self.pushButton_2.clicked.connect(self.show_dialog_file)
        self.pushButton_3.clicked.connect(self.close_d)

    def show_dialog(self):
        self.d = Dialog()
        self.d.show()

    def show_dialog_file(self):
        self.d = OpenFile()

    def close_d(self):
        self.close()


def main():
    app = QtWidgets.QApplication(sys.argv)  # Новый экземпляр QApplication
    window = ExampleApp()  # Создаём объект класса ExampleApp
    window.show()  # Показываем окно

    app.exec_()  # и запускаем приложение


if __name__ == '__main__':  # Если мы запускаем файл напрямую, а не импортируем
    main()  # то запускаем функцию main()
