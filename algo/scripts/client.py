#!/usr/bin/env python3

import socket
import rospy
from std_msgs.msg import String

HOST = '192.168.0.103'  # The server's hostname or IP address
PORT = 65432        # The port used by the server
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))

def callback(data):
    s.sendall(data.data)

def talker():
    pub = rospy.Publisher('cords', String, queue_size=10)
    rospy.init_node('talker', anonymous=True)
    rospy.Subscriber("command", String, callback)
    #rate = rospy.Rate(10) # 10hz
    #s.sendall(b'Hello, world')
    data = s.recv(1024)
    while not rospy.is_shutdown():
        data = s.recv(1024)
        pub.publish(data)
        #rate.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
