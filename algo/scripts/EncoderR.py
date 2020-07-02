import rospy
import RPi.GPIO as GPIO
from std_msgs.msg import Int32
from std_msgs.msg import Float64

ticks = 0
sign = 1
def callback_from_ros(data):
    global sign
    if data < 0:
        sign = -1
    else:
        sign = 1


def callback_func():
    global ticks
    if ticks + 1 * sign > 32768:
        ticks = -32768
    elif ticks + 1 * sign < -32768:
        ticks = 32768
    else:
        ticks = ticks + 1 * sign

def talker():
    pub = rospy.Publisher('lwheel_ticks', Int32, queue_size=10)
    rospy.init_node('EncoderR', anonymous=True)
    rate = rospy.Rate(10) # 10hz
    rospy.Subscriber("EngineR", Float64, callback_from_ros)
    GPIO.add_event_detect(8, GPIO.FALLING, callback=callback_func)
    while not rospy.is_shutdown():
        pub.publish(ticks)
        rate.sleep()


if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass