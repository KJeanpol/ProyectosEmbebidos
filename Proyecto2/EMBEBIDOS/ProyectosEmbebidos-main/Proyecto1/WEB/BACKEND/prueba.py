# MQTT Client demo
# Continuously monitor two different MQTT topics for data,
# check if the received data matches two predefined 'commands'
 
import paho.mqtt.client as mqtt
import ctypes
 
 
# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
 
    # Subscribing in on_connect() - if we lose the connection and
    # reconnect then subscriptions will be renewed.
    client.subscribe("House/on")
    client.subscribe("House/off")
    client.subscribe("House/door")
 
# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    gpio = ctypes.CDLL('./gpio.so')
    print(msg.topic)
    value=msg.payload.decode('utf-8')

    if (msg.topic=="House/on"):
        print("Received message #6565, do something else")
        gpio.factorial.argtypes = (ctypes.c_int,ctypes.c_int,)
        gpio.factorial(value)

    if (msg.topic=="House/off"):
        gpio.factorial.argtypes = (ctypes.c_int,ctypes.c_int,)
        gpio.factorial(value)


    if (msg.topic=="House/door"):
        gpio.factorial.argtypes = (ctypes.c_int,ctypes.c_int,)
        gpio.factorial(value)

    if value == "World!":
        print("Received message #2, do something else")
        # Do something else
 
# Create an MQTT client and attach our routines to it.
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
 
client.connect("test.mosquitto.org", 1883, 60)
 
# Process network traffic and dispatch callbacks. This will also handle
# reconnecting. Check the documentation at
# https://github.com/eclipse/paho.mqtt.python
# for information on how to use other loop*() functions
client.loop_forever()