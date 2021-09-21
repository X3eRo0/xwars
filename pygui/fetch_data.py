import os

fifo_r = None
fifo_w = None

NINSTS = 20
NREGS = 4

def create_logfifo():
    global fifo_r, fifo_w
    
    try:
        os.remove("/tmp/xwars_1")
    except:
        pass
    try:
        os.remove("/tmp/xwars_2")
    except:
        pass
    try:
        os.mkfifo("/tmp/xwars_1")
    except Exception as e:
        print(e)
    try:
        os.mkfifo("/tmp/xwars_2")
    except Exception as e:
        print(e)

    fifo_w = open("/tmp/xwars_1", "wb", buffering=0)
    fifo_r = open("/tmp/xwars_2", "rb", buffering=0)

    fifo_w.write(b"INIT")
    if (fifo_r.read(4) == b"INIT"):
        print("[+] Connection Established")


def response():
    global fifo_r, fifo_w
    data = fifo_r.readline()
    return data

def send(msg):
    global fifo_w
    fifo_w.write(msg)

def readline():
    global fifo_r
    return fifo_r.readline()

def get_registers():
    bot1 = []
    bot2 = []


    if fifo_r.readline() == b"bot1->register_dump\n":
        for i in range(NREGS):
            bot1.append(fifo_r.readline().decode('latin1'))

    if fifo_r.readline() == b"bot2->register_dump\n":
        for i in range(NREGS):
            bot2.append(fifo_r.readline().decode('latin1'))

    return bot1, bot2

def get_disassembly():
    dis1 = []
    dis2 = []


    if fifo_r.readline() == b"bot1->disasm\n":
        for i in range(NINSTS):
            dis1.append(fifo_r.readline().decode('latin1'))

    if fifo_r.readline() == b"bot2->disasm\n":
        for i in range(NINSTS):
            dis2.append(fifo_r.readline().decode('latin1'))
    return dis1, dis2
