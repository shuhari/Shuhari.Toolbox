# -*- coding: utf-8 -*-
import sys
from PyQt5.QtWidgets import *
from mainwindow import MainWindow


class App(QApplication):
    def __init__(self):
        super(App, self).__init__(sys.argv)

    def run(self):
        win = MainWindow()
        win.show()

        return self.exec()
