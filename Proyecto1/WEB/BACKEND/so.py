import os
from time import sleep
print("Tomando foto ....")
# os.system("fswebcam --no-banner local.jpg")
# sleep(10)
# print("Publicando foto ....")
output = os.system("echo hola")
print(output)