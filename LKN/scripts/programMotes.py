#!/usr/bin/python
import sys, os, re
from subprocess import Popen, PIPE
from programMote import program


def program_all(min_range, max_range, check_range=True):
	"""
    Program a range of motes
	"""
	(devs, stderr) = Popen(['ls','/dev/'], stdout=PIPE).communicate()

	usbs = re.findall("(ttyUSB.)", devs.decode("utf-8"))
	print(usbs)

	if (max_range-min_range+1)!=len(usbs):
		exit('range does not match')

	for idx, usb in enumerate(usbs):

		# mote with id 1
		if min_range == 1 and idx == 0:
			program('/dev/'+usb, min_range+idx, 0)
		else:
			program('/dev/'+usb, min_range+idx, 0)




if __name__=='__main__':

	schedule_file=""
	if len(sys.argv)<2:
		exit('Usage: %s START_ID [END_ID]' % sys.argv[0])
	elif len(sys.argv)==2:
		min_range = int(sys.argv[1])
		max_range = int(sys.argv[1])
	elif len(sys.argv)==4:
		min_range = int(sys.argv[1])
		max_range = int(sys.argv[2])
		schedule_file = str(sys.argv[3])
		print("Schedule file found: "+schedule_file)
	else:
		min_range = int(sys.argv[1])
		max_range = int(sys.argv[2])

	os.system("python schedule.py "+schedule_file+" ../../openstack/02b-MAChigh/static_schedule.h"+" ../../openstack/02b-MAChigh/schedule.h"+" ../../openstack/02a-MAClow/IEEE802154E.h"+" ../../openapps/uinject/uinject.h")
	program_all(min_range, max_range)
