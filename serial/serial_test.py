import serial
import time

def main():
	con=serial.Serial('/dev/ttyAMA0', 115200, timeout=1)
	print con.portstr
	while 1:
		#str=con.readline()
		str=con.read(5)
		print str

if __name__ == '__main__':
	main()
