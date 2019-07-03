import zaber.serial
import serial
import serial.tools.list_ports

XDEVPORT = "DEFAULT"
YDEVPORT = "DEFAULT"
ZDEVPORT = "Arduino"

class Maya:

    def __init__(self):
        com_ports = list(serial.tools.list_ports.comports())
        x_com_port = "NULL"
        y_com_port = "NULL"
        z_com_port = "NULL"
        for port in com_ports:
            print(port)
            if XDEVPORT in port[1]:
                x_com_port = port[0]
            if YDEVPORT in port[1]:
                y_com_port = port[0]
            if ZDEVPORT in port[1]:
                z_com_port = port[0]
        if "NULL" == x_com_port:
            self.x_axis_device = "NULL"
            print("Could not find x-axis device")
        else:
            self.x_axis_device = BinarySerial(x_com_port, 1)
        if "NULL" == y_com_port:
            self.y_axis_device = "NULL"
            print("Could not find y-axis device")
        else:
            self.y_axis_device = BinarySerial(y_com_port, 2)
        if "NULL" == z_com_port:
            self.z_axis_device = "NULL"
            print("Could not find z-axis device")
        else:
            self.z_axis_device = serial.Serial(z_com_port, 9600)

    def move_dev(self, move_type, axis, position):
        if "z" == axis.lower():
            if "NULL" != self.z_axis_device:
                if "move_abs" == move_type:
                    self.z_axis_device.write(("MA,"+position).encode('ascii'))
                    #print(self.z_axis_device.readline())
                elif "move_rel" == move_type:
                    self.z_axis_device.write(("MR,"+position).encode('ascii'))
                    #print(self.z_axis_device.readline())
                elif "home" == move_type:
                    self.z_axis_device.write("H,".encode('ascii'))
                    #print(self.z_axis_device.readline())
                else:
                    print("ERROR: invalid move type")
            else:
                print("ERROR: z-axis device wasn't found during init")
        elif "y" == axis.lower():
            if "NULL" != self.y_axis_device:
                if "move_abs" == move_type:
                    self.y_axis_device.move_abs(position)
                elif "move_rel" == move_type:
                    self.y_axis_device.move_rel(position)
                elif "home" == move_type:
                    self.y_axis_device.home(position)
            else:
                print("ERROR: y-axis device wasn't found during init")
        elif "x" == axis.lower():
            if "NULL" != self.x_axis_device:
                if "move_abs" == move_type:
                    self.x_axis_device.move_abs(position)
                elif "move_rel" == move_type:
                    self.x_axis_device.move_rel(position)
                elif "home" == move_type:
                    self.x_axis_device.home(position)
            else:
                print("ERROR: x-axis device wasn't found during init")
        else:
            print("ERROR: invalid axis")

maya = Maya()
while True:
    user_input = input("command: ").split()
    command = user_input[0]
    axis = user_input[1]
    position = user_input[2]
    maya.move_dev(command, axis, position)
    
