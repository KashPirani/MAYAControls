#Command line interface for MAYA (Currently only runs on Windows)
#Requirements:
#   1) Install Python 3.5+ (might work with 2.7 - untested)
#   2) Install zaber library using pip:
#       - Open command line and enter command: pip install zaber.serial
#command format: [command] [axis] [position]
#example: move_rel x -1000
#example: home y
#example: move_abs z 50

from zaber.serial import BinarySerial, BinaryDevice, BinaryCommand, BinaryReply
import serial
import serial.tools.list_ports

XYDEVPORT = "COM10"
ZDEVPORT = "Arduino"

#class to create communicate with devices in MAYA
class Maya:
    #init creates serial connections to devices
    def __init__(self):
        com_ports = list(serial.tools.list_ports.comports())
        xy_com_port = "NULL"
        z_com_port = "NULL"
        
        #detect com ports
        for port in com_ports:
            print(port)
            if XYDEVPORT in port[1]:
                xy_com_port = port[0]
            if ZDEVPORT in port[1]:
                z_com_port = port[0]
                
        if "NULL" == xy_com_port:
            self.x_axis_device = "NULL"
            self.y_axis_device = "NULL"
            print("Could not find xy-axis device")
        #connects to devices if found
        else:
            port = BinarySerial(xy_com_port)
            self.x_axis_device = BinaryDevice(port, 1)
            self.y_axis_device = BinaryDevice(port, 2)
        if "NULL" == z_com_port:
            self.z_axis_device = "NULL"
            print("Could not find z-axis device")
        else:
            self.z_axis_device = serial.Serial(z_com_port, 9600)

    #move a device in a specified way/direction
    #@param move_type:
    #   move_rel: move in position steps in the positive or negative position
    #   move_abs: move to the absolution position specified by position
    #       - requires positive position
    #   home: move to the home position of the device
    #@param axis:
    #   x,y, or z
    #@param position:
    #   a positive or negative number indicating direction and distance to move
    def move_dev(self, move_type, axis, position):
        if "z" == axis.lower():
            if "NULL" != self.z_axis_device:
                if "move_abs" == move_type:
                    self.z_axis_device.write(("MA,"+position).encode('ascii'))
                elif "move_rel" == move_type:
                    self.z_axis_device.write(("MR,"+position).encode('ascii'))
                elif "home" == move_type:
                    self.z_axis_device.write("H,".encode('ascii'))
                else:
                    print("ERROR: invalid move type")
            else:
                print("ERROR: z-axis device wasn't found during init")
        elif "y" == axis.lower():
            if "NULL" != self.y_axis_device:
                if "move_abs" == move_type:
                    self.y_axis_device.move_abs(int(position))
                elif "move_rel" == move_type:
                    self.y_axis_device.move_rel(int(position))
                elif "home" == move_type:
                    self.y_axis_device.home()
            else:
                print("ERROR: y-axis device wasn't found during init")
        elif "x" == axis.lower():
            if "NULL" != self.x_axis_device:
                if "move_abs" == move_type:
                    self.x_axis_device.move_abs(int(position))
                elif "move_rel" == move_type:
                    self.x_axis_device.move_rel(int(position))
                elif "home" == move_type:
                    self.x_axis_device.home()
            else:
                print("ERROR: x-axis device wasn't found during init")
        else:
            print("ERROR: invalid axis")

#User interface
maya = Maya()
while True:
    user_input = input("command: ").split()
    command = user_input[0]
    axis = user_input[1]
    position = 0
    if not command == "home":
        position = user_input[2]
    maya.move_dev(command, axis, position)
    
