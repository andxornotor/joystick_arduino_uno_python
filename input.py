#Importação de bibliotecas e recursos de bibliotecas
import time                                         #Biblioteca "time"
import serial                                       #Biblioteca "serial" (necessário instalar "pyserial")
from pynput.keyboard import Key                     #Biblioteca "pynput" (necessário instalá-la)
from pynput.mouse import Button
from pynput import keyboard
from pynput import mouse

#Inicialização da conexão Serial
port = "COM3"
baudrate = 9600
connect = serial.Serial(port, baudrate)             #Inicio de conexão

#Definição de variáveis
leftPressed = False                                 #Variável de pressionamento do mouse (bot. esq.)
spacePressed = False                                #Variável de pressionamento da tecla "Espaço"
senseControle = 20                                  #Velocidade de movimentação do cursor (controle)
sensibilidade = 15                                  #Velocidade de movimentação do cursor (joystick)


#Definição de controladores (biblioteca pynput)
mouse = mouse.Controller()                          #Controlador de mouse (pynput)
keyboard = keyboard.Controller()                    #Controlador de teclado (pynput)


#Tratamento de códigos recebidos via Serial
while True:
    comando = connect.readline()                    #Leitura de linha vinda pela Serial
    comando = comando[0:6]                          #Recorte de linha
    comando = comando.decode()                      #Conversão de byte pra String
    #Tratamento de casos
    if (comando == "FFA25D"): #power
        keyboard.press(Key.esc)
        keyboard.release(Key.esc)
    elif (comando == "FFE21D"): #flash
        mouse.press(Button.right)
        mouse.release(Button.right)
    elif (comando == "FF02FD"): #up
        mouse.move(0, -senseControle)
    elif (comando == "FF9867"): #down
        mouse.move(0, senseControle)
    elif (comando == "FFE01F"): #left
        mouse.move(-senseControle, 0)
    elif (comando == "FF906F"): #right
        mouse.move(senseControle, 0)
    elif (comando == "FFA857"): #ok
        mouse.press(Button.left)
        mouse.release(Button.left)
    elif (comando == "FF30CF"): #a
        mouse.scroll(0, 1)
    elif (comando == "FF18E7"): #b
        if(spacePressed == False):
            keyboard.press(Key.space)
            spacePressed = True
        else:
            keyboard.release(Key.space)
            spacePressed = False
    elif (comando == "FF7A85"): #c
        mouse.scroll(0, -1)
    elif (comando == "FF10EF"): #d
        keyboard.press('f')
        keyboard.release('f')
    elif (comando == "FF38C7"): #e
        keyboard.press('e')
        keyboard.release('e')
        '''
        elif (comando == "FF5AA5"): #f
            #comando para tecla f
        elif (comando == "FF42BD"): #g
            #comando para tecla g
        elif (comando == "FF4AB5"): #h
            #comando para tecla h
        elif (comando == "FF52AD"): #i
            #comando para tecla i
        '''
    elif (comando == "JASWSW"): #botao JA
        if(leftPressed == False):
            mouse.press(Button.left)
            leftPressed = True
        else:
            mouse.release(Button.left)
            leftPressed = False
        time.sleep(0.030)
    elif (comando == "JBSWSW"): #botao JB
        mouse.press(Button.right)
        mouse.release(Button.right)
        time.sleep(0.030)
    elif (comando == "JBURUR"): #JB cima-direita
        mouse.move(sensibilidade, -sensibilidade)
    elif (comando == "JBDRDR"): #JB baixo-direita
        mouse.move(sensibilidade, sensibilidade)
    elif (comando == "JBRRRR"): #JB direita
        mouse.move(sensibilidade, 0)
    elif (comando == "JBULUL"): #JB cima-esquerda
        mouse.move(-sensibilidade, -sensibilidade)
    elif (comando == "JBDLDL"): #JB baixo-esquerda
        mouse.move(-sensibilidade, sensibilidade)
    elif (comando == "JBLLLL"): #JB esquerda
        mouse.move(-sensibilidade, 0)
    elif (comando == "JBUUUU"): #JB cima
        mouse.move(0, -sensibilidade)
    elif (comando == "JBDDDD"): #JB baixo
        mouse.move(0, sensibilidade)
    elif (comando == "JAURUR"): #JA cima-direita
        keyboard.press('w')
        keyboard.press('d')
        keyboard.release('a')
        keyboard.release('s')
    elif (comando == "JADRDR"): #JA baixo-direita
        keyboard.press('s')
        keyboard.press('d')
        keyboard.release('w')
        keyboard.release('a')
    elif (comando == "JARRRR"): #JA direita
        keyboard.press('d')
        keyboard.release('a')
        keyboard.release('w')
        keyboard.release('s')
    elif (comando == "JAULUL"): #JA cima-esquerda
        keyboard.press('w')
        keyboard.press('a')
        keyboard.release('s')
        keyboard.release('d')
    elif (comando == "JADLDL"): #JA baixo-esquerda
        keyboard.press('a')
        keyboard.press('s')
        keyboard.release('w')
        keyboard.release('d')
    elif (comando == "JALLLL"): #JA esquerda
        keyboard.press('a')
        keyboard.release('s')
        keyboard.release('w')
        keyboard.release('d')
    elif (comando == "JAUUUU"): #JA cima
        keyboard.press('w')
        keyboard.release('a')
        keyboard.release('s')
        keyboard.release('d')
    elif (comando == "JADDDD"): #JA baixo
        keyboard.press('s')
        keyboard.release('a')
        keyboard.release('w')
        keyboard.release('d')
    elif (comando == "JANNNN"): #JA parado
        keyboard.release('a')
        keyboard.release('w')
        keyboard.release('d')
        keyboard.release('s')
