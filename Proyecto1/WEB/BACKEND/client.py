import paho.mqtt.client as mqtt
import paho.mqtt.publish as publish
import ctypes
import base64 

# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
 
    # Subscribing in on_connect() - if we lose the connection and
    # reconnect then subscriptions will be renewed.
    client.subscribe("House/on")
    client.subscribe("House/off")
    client.subscribe("photo")
 
# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    print(msg.topic)
    prueba=msg.payload.decode('utf-8')


    if prueba == "House/on":
        print("Received message #1, do something")
        # Do something


    if prueba== "House/off":
        publish.single("House/off", "World!", hostname="test.mosquitto.org")
        print("Received message #2, do something else")
        # Do something else

    if prueba== "photo":
        publish.single("photo",on_image(), hostname="test.mosquitto.org")
        print("SALI DE FOTO")
        # Do something else


def on_image():
    with open("1.jpg", "rb") as image_file:
        encoded = base64.b64encode(image_file.read())
        image_file.close()
       # return "https://www.google.com/search?q=image&sxsrf=ALeKk039oD5igbmxMCXSAxOuUarquKm7jg:1602725481186&source=lnms&tbm=isch&sa=X&ved=2ahUKEwiIvOnXubXsAhWpp1kKHR8CCUYQ_AUoAXoECBYQAw&biw=1848&bih=981#imgrc=RkjAFRQNR5bUxM"#encoded"
        return encoded
 
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