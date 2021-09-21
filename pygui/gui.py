import PySimpleGUI as sg
import os
import random
import string
import fetch_data as fd
import sys

sg.theme('DarkPurple4')  # please make your windows colorful

layout = [
    [
        sg.Multiline(
            "",
            key='-REG_BOT1-',
            size=(70, 5),
            font=("Consolas", 12),
            autoscroll=False,
            background_color='Black',
            disabled=True,
            no_scrollbar=True,
        ),
        sg.Multiline(
            "",
            key='-REG_BOT2-',
            size=(70, 5),
            font=("Consolas", 12),
            autoscroll=False,
            background_color='Black',
            disabled=True,
            no_scrollbar=True,
        ),
    ],
    [
        sg.Multiline(
            "",
            key='-DIS_BOT1-',
            size=(70, 20),
            font=("Consolas", 12),
            autoscroll=False,
            background_color='Black',
            disabled=True,
            no_scrollbar=True,
        ),
        sg.Multiline(
            "",
            key='-DIS_BOT2-',
            size=(70, 20),
            font=("Consolas", 12),
            autoscroll=False,
            background_color='Black',
            disabled=True,
            no_scrollbar=True,
        ),
    ],
    [
        sg.Text('Bot1', font=("Consolas", 10)), sg.InputText(key='-BOT1-', font=("Consolas", 10), size=(20)), sg.FileBrowse(font=("Consolas", 10)),
        sg.Text('Output', font=("Consolas", 15), expand_x=True, justification='c'),
        sg.Text('Bot2', font=("Consolas", 10)), sg.InputText(key='-BOT2-', font=("Consolas", 10), size=(20)), sg.FileBrowse(font=("Consolas", 10)),
    ],
    [
        sg.Output(key='-OUT-', size=(80, 15), font=("Consolas", 12), background_color='Black', text_color="White"),
    ],
    [
        sg.Button("+", font=("Consolas", 10)),
        sg.Button("Run", font=("Consolas", 10)),
        sg.Button("Step", font=("Consolas", 10)),
        sg.Button("Stop", font=("Consolas", 10)),
        sg.Button("-", font=("Consolas", 10)),
    ]
]

window = sg.Window('Window Title', layout, element_justification='c')

def get_random_str(length):
    s = ""
    while (len(s) != length):
        s += random.choice(string.ascii_lowercase)
    return s

def update_registers():
    global window
    bot1, bot2 = fd.get_registers()
    window['-REG_BOT1-'].update(value="".join(bot1), text_color_for_value="white")
    window['-REG_BOT2-'].update(value="".join(bot2), text_color_for_value="white")

def update_disassembly():
    global window
    dis1, dis2 = fd.get_disassembly()
    window['-DIS_BOT1-'].update(value="".join(dis1), text_color_for_value="light green")
    window['-DIS_BOT2-'].update(value="".join(dis2), text_color_for_value="light green")

COUNTER = 0
RUNNING = 0
BOT1Name = None
BOT2Name = None

counter = 0
speed = 100
PID = 0
while True:  # Event Loop
    event, values = window.read(timeout=speed)
    if event == sg.WIN_CLOSED or event == 'Exit':
        os.kill(PID, 9)
        break
    if event == "Run":
        if RUNNING == False and COUNTER == 0:
            if (values['-BOT1-'] == '' or values['-BOT2-'] == ''):
                print("[!] Select Bots and then try again.")
                continue
            PID = os.fork()
            if PID == 0:
                os.system("../build/xwars %s %s" % (values['-BOT1-'], values['-BOT2-']))
            else:
                fd.create_logfifo()
            BOT1Name = values['-BOT1-'].split('/')[-1]
            BOT2Name = values['-BOT2-'].split('/')[-1]
            print("[+] Loaded bots")
            print("[+] %s VS %s" % (BOT1Name, BOT2Name))
            print("[+] The Battle Begins.")
        elif RUNNING == False and COUNTER > 0:
            print("[+] Resuming.")
        COUNTER += 1
        RUNNING = True
    if event == "Stop":
        if RUNNING == True and COUNTER > 0:
            print("[+] Stopped ...")
        RUNNING = False
    if event == "-":
        speed += 50
        if speed > 1000:
            speed = 1000
    if event == "+":
        speed -= 50
        if speed < 0:
            speed = 1
    if event == "Step":
        if RUNNING == True:
            RUNNING = False
        else:
            fd.send(b"CONT")
            res = fd.response()
            if res == b"SENDING\n":
                update_registers()
                update_disassembly()
            else:
                if b"Winner" in res:
                    winner = int(res.strip().split(" : ")[1])
                    print("[+] Winner is %s" % [BOT1Name, BOT2Name][winner - 1])
                    RUNNING = False
                    continue

    if RUNNING:
        fd.send(b"CONT")
        res = fd.response()
        if res == b"SENDING\n":
            update_registers()
            update_disassembly()
        else:
            if b"Winner" in res:
                winner = int(res.strip().split(" : ")[1])
                print("[+] Winner is %s" % [BOT1Name, BOT2Name][winner - 1])
                RUNNING = False
                continue
    counter += 1

window.close()
