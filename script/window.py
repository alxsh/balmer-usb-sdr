# -*- coding: UTF-8 -*-
# balmer@inbox.ru 2014 RLC Meter
import sys, os, csv
from PyQt4 import QtCore, QtGui

import matplotlib
import time
import datetime
import threading
import json
import os.path
import usb_commands

class FormMain(QtGui.QMainWindow):
	def __init__(self, title, parent=None):
		super(FormMain, self).__init__(parent)
		self.F = 0
		self.setWindowTitle(title)
		self.createMainFrame()
		pass

	def createMainFrame(self):
		self.main_frame = QtGui.QWidget()
		vbox = QtGui.QVBoxLayout()
		hbox = QtGui.QHBoxLayout()

		self.freq_label = QtGui.QLabel(u'info');
		hbox.addWidget(self.freq_label);

		self.serial_combo_box = QtGui.QComboBox()
		self.serial_combo_box.addItem('980')
		self.serial_combo_box.addItem('3592')
		self.serial_combo_box.addItem('5322')
		self.serial_combo_box.addItem('7117')
		self.serial_combo_box.addItem('10092')
		#self.serial_combo_box.addItem('14142')
		self.serial_combo_box.addItem('14130')
		self.serial_combo_box.addItem('18102')
		self.serial_combo_box.setCurrentIndex(0)
		self.serial_combo_box.currentIndexChanged.connect(self.OnDiapazon)
		hbox.addWidget(self.serial_combo_box)

		vbox.addLayout(hbox)

		hbox = QtGui.QHBoxLayout()

		self.info_label = QtGui.QLabel(u'1 KHz');
		hbox.addWidget(self.info_label);

		self.freq_slider = QtGui.QSlider(QtCore.Qt.Horizontal)
		self.freq_slider.setMinimumWidth(512)
		self.freq_slider.valueChanged.connect(self.OnSliderValueChanged)
		self.freq_slider.sliderReleased.connect(self.OnSliderReleased)
		self.freq_slider.setRange (0, 100)
		hbox.addWidget(self.freq_slider)

		vbox.addLayout(hbox)

		hbox = QtGui.QHBoxLayout()

		self.info_label = QtGui.QLabel(u'10 Hz');
		hbox.addWidget(self.info_label);

		self.freq_slider_low = QtGui.QSlider(QtCore.Qt.Horizontal)
		self.freq_slider_low.setMinimumWidth(512)
		self.freq_slider_low.valueChanged.connect(self.OnSliderValueChangedLow)
		self.freq_slider_low.sliderReleased.connect(self.OnSliderReleased)
		self.freq_slider_low.setRange (0, 100)
		hbox.addWidget(self.freq_slider_low)

		vbox.addLayout(hbox)

		button_close = QtGui.QPushButton(u'Закончить.')
		button_close.clicked.connect(self.close)
		vbox.addWidget(button_close)

		self.UpdateFreq()
		self.main_frame.setLayout(vbox)
		self.setCentralWidget(self.main_frame)
		pass

	def UpdateFreq(self):
		index1KHz = self.freq_slider.value()
		index10Hz = self.freq_slider_low.value()
		F = int(self.serial_combo_box.currentText())*1000
		F += index1KHz*1000
		F += index10Hz*10
		Fcor = +9800
		#Fcor = 0

		if self.F>0 and self.F==F:
			return
		self.freq_label.setText(str(int(F))+' Hz');
		print "freq=", F
		usb_commands.setFreq((F-Fcor)*2)

		self.F = F
		pass

	def OnDiapazon(self, index):
		self.UpdateFreq()
		pass

	def OnSliderValueChanged (self, index):
		self.freq_slider.setValue(index)
		self.UpdateFreq()
		pass

	def OnSliderValueChangedLow (self, index):
		self.freq_slider_low.setValue(index)
		self.UpdateFreq()
		pass

	def OnSliderReleased(self):
		index = self.freq_slider.value()
		self.UpdateFreq()
		pass

	def closeEvent(self, event):
		print "closeEvent"
		event.accept()
		pass

def main():
	if not usb_commands.findDevice():
		sys.exit(0)
	app = QtGui.QApplication(sys.argv)
	form = FormMain("Radio Tuner")
	form.show()
	app.exec_()


if __name__ == "__main__":
    main()
