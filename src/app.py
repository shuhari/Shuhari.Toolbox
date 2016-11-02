# -*- coding: utf-8 -*-
import sys
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from mainwindow import MainWindow
import qrc_resources


class App(QApplication):
    def __init__(self):
        super(App, self).__init__(sys.argv)
        self.setWindowIcon(QIcon(":/toolbox"))

    def run(self):
        win = MainWindow()
        win.show()

        return self.exec()
