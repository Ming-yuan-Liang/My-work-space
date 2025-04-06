import sensor, image, time, lcd
from maix import KPU
from modules import ybserial
import time



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

x_ = 0
y_ = 0
w_ = 0
h_ = 0
cx = 0
cy = 0

ser = ybserial()
lcd.init()
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 100)
clock = time.clock()

od_img = image.Image(size=(320,256))

anchor = (0.893, 1.463, 0.245, 0.389, 1.55, 2.58, 0.375, 0.594, 3.099, 5.038, 0.057, 0.090, 0.567, 0.904, 0.101, 0.160, 0.159, 0.255)
kpu = KPU()
kpu.load_kmodel("/sd/KPU/yolo_face_detect/yolo_face_detect.kmodel")
kpu.init_yolo2(anchor, anchor_num=9, img_w=320, img_h=240, net_w=320, net_h=256, layer_w=10, layer_h=8, threshold=0.7, nms_value=0.3, classes=1)

state = 0
while True:
    clock.tick()
    img = sensor.snapshot()
    a = od_img.draw_image(img, 0,0)
    od_img.pix_to_ai()
    kpu.run_with_output(od_img)
    dect = kpu.regionlayer_yolo2()
    fps = clock.fps()
    if len(dect) > 0:
        #print("dect:",dect)
        for l in dect :
            a = img.draw_rectangle(l[0],l[1],l[2],l[3], color=(0, 255, 0))
            x_ = l[0]
            y_ = l[1]
            w_ = l[2]
            h_ = l[3]
    a = img.draw_string(0, 0, "%2.1ffps" %(fps), color=(0, 60, 128), scale=2.0)
    lcd.display(img)
    if len(dect) > 0:
        #print(x_,y_,w_,h_)
        cx = int(x_+w_/2)
        cy = int(y_+h_/2)
        print(cx,cy)
        Massage_send(cx, cy)
        state = 1
    elif state == 1:
        Massage_send(160, 120) #检测不到就中间,只发一次
        state = 0



kpu.deinit()
