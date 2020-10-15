import paho.mqtt.client as mqtt
import paho.mqtt.publish as publish
import ctypes
import base64 
import os
from time import sleep

global count
count = 1

def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
    
    client.subscribe("House/on")
    client.subscribe("House/off")
    client.subscribe("photo")
    client.subscribe("door")
    
    
def on_message(client, userdata, msg):
    print(msg.topic)
    prueba=msg.payload.decode('utf-8')
    global count
    if count <= 4:
        count+=1
        print(count, "count 2")
    else:
        if prueba == "House/on1":
            os.system("./house_control 1 1")

        if prueba == "House/on2":
            os.system("./house_control 1 2")

        if prueba == "House/on3":
            os.system("./house_control 1 3")

        if prueba == "House/on4":
            os.system("./house_control 1 4")    

        if prueba == "House/on5":
            os.system("./house_control 1 5")

        if prueba== "House/off1":
            os.system("./house_control 2 1")

        if prueba== "House/off2":
            os.system("./house_control 2 2")
            
            
        if prueba== "House/off3":
            os.system("./house_control 2 3")


        if prueba== "House/off4":
            os.system("./house_control 2 4")
    
                            
        if prueba== "House/off5":
            os.system("./house_control 2 5")  


        if prueba== "photo":
            print("Tomando foto ....")
            os.system("fswebcam --no-banner 1.jpg")
            sleep(10)
            print("Publicando foto ....")
            publish.single("photo",on_image(), hostname="test.mosquitto.org")
            print("¡foto publicada!")

        if prueba== "door":
            #AQUI VIENE LO DE LA PUERTA
          ##  publish.single("photo",on_image(), hostname="test.mosquitto.org")
            print("¡foto publicada!")


def notificarPuerta():
    with open("1.jpg", "rb") as image_file:
        print("Convirtiendo foto...")
        encoded = base64.b64encode(image_file.read())
        image_file.close()
        print("foto lista base 64")
        return encoded

def on_image():
    with open("1.jpg", "rb") as image_file:
        print("Convirtiendo foto...")
        encoded = base64.b64encode(image_file.read())
        image_file.close()
        print("foto lista base 64")
        return encoded
 
# Create an MQTT client and attach our routines to it.
client = mqtt.Client()
# Configuración de pines
os.system("./house_control 0")
client.on_connect = on_connect
client.on_message = on_message

client.connect("test.mosquitto.org", 1883, 60)
 
# Process network traffic and dispatch callbacks. This will also handle
# reconnecting. Check the documentation at
# https://github.com/eclipse/paho.mqtt.python
# for information on how to use other loop*() functions
client.loop_forever()
