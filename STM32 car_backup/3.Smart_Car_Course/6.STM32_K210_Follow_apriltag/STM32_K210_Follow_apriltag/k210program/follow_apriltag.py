import sensor, image, time, math, lcd
from modules import ybserial


def Massage_send(x,y):
    x_str = str(x)
    y_str = str(y)
    if len(x_str) < 3:
        i=3-len(x_str)
        x_str = ('0'*i)+x_str
    if len(y_str) < 3:
        i=3-len(y_str)
        y_str = ('0'*i)+y_str

    send_buf = '$'+x_str+y_str+'#'
    ser.send(send_buf)
    print(send_buf)

    
ser = ybserial()



lcd.init()
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQVGA)
#sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 100)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)
clock = time.clock()


tag_families = 0
tag_families |= image.TAG16H5   # comment out to disable this family
tag_families |= image.TAG25H7   # comment out to disable this family
tag_families |= image.TAG25H9   # comment out to disable this family
tag_families |= image.TAG36H10  # comment out to disable this family
tag_families |= image.TAG36H11  # comment out to disable this family (default family)
tag_families |= image.ARTOOLKIT # comment out to disable this family


def family_name(tag):
    if(tag.family() == image.TAG16H5):
        return "TAG16H5"
    if(tag.family() == image.TAG25H7):
        return "TAG25H7"
    if(tag.family() == image.TAG25H9):
        return "TAG25H9"
    if(tag.family() == image.TAG36H10):
        return "TAG36H10"
    if(tag.family() == image.TAG36H11):
        return "TAG36H11"
    if(tag.family() == image.ARTOOLKIT):
        return "ARTOOLKIT"

state = 0

while(True):
    clock.tick()
    img = sensor.snapshot()
    fps = clock.fps()
    #img = img.resize(292, 210)
    index = 0
    for tag in img.find_apriltags(families=tag_families):
        index = index + 1
        #img.draw_rectangle(tag.rect(), color = (255, 0, 0))
        #img.draw_cross(tag.cx(), tag.cy(), color = (0, 255, 0))
        #print_args = (family_name(tag), tag.id(), (180 * tag.rotation()) / math.pi)
        #print("Tag Family %s, Tag ID %d, rotation %f (degrees)" % print_args)
        if index == 1:
            tag_max = tag.w()*tag.h()
            tag1 = tag
        else:
            temp = tag.w()*tag.h()
            if temp > tag_max:
                tag_max = temp
                tag1 = tag
        state = 1

    if state == 1:
        #print("area:", index, area.w(), area.h())
        img.draw_rectangle(tag1.rect(), color = (255, 0, 0))
        img.draw_cross(tag1.cx(), tag1.cy(), color = (0, 255, 0))
        Massage_send(tag1.cx(), tag1.cy())
        print("tag_xy:", tag1.cx(), tag1.cy())
        state = 2
    elif state == 2:
        Massage_send(80, 60) #检测不到默认中间
        state = 0
    img.draw_string(0, 0, "%2.1ffps" %(fps), color=(0, 60, 128), scale=1.0)
    lcd.display(img)
    #print(fps)
