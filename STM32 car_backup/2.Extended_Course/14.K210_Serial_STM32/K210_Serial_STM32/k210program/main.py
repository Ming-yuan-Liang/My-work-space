from machine import UART
from board import board_info
from fpioa_manager import fm
from modules import ybrgb
import time


def set_RGB(read_data):
    if read_data == "red":
         RGB.set(1, 0, 0)
    elif read_data == "blue":
         RGB.set(0, 0, 1)
    elif read_data == "green":
         RGB.set(0, 1, 0)
    elif read_data == "yellow":
         RGB.set(1, 1, 0)
    elif read_data == "purper":
         RGB.set(1, 0, 1)
    elif read_data == "lake":
         RGB.set(0, 1, 1)
    elif read_data == "close":
         RGB.set(0, 0, 0)

    uart_A.write("$"+read_data+"#")


fm.register(8, fm.fpioa.UART1_TX, force=True)
fm.register(6, fm.fpioa.UART1_RX, force=True)

uart_A = UART(UART.UART1, 115200, 8, 0, 1, timeout=1000, read_buf_len=4096)
RGB = ybrgb()

recv_data = ''

while True:
    read_data = uart_A.read()
    if read_data != None:
        print(read_data)
        if read_data[0] != 255:
            read_str = read_data.decode('utf-8')
            read_str = read_str.replace('\x00','')#和stm32产生的
            #uart_A.write("$"+"green"+"#")
            # start -  end
            if read_str[0] == '$' and read_str[-1] == '#':
                recv_data=read_str.strip("$#")
                set_RGB(recv_data)

            #print(recv_data)



uart_A.deinit()
del uart_A
