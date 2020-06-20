from gpiozero import CPUTemperature
import time
import paho.mqtt.client as mqtt #import the client
import psutil

'''
broker_address="192.168.1.17"
client = mqtt.Client("P1") #create new instance
client.connect(broker_address) #connect to broker
'''

#time.sleep(60)

mqttc=mqtt.Client("P1")
#mqttc.on_connect = onConnect
#mqttc.on_disconnect = onDisconnect
mqttc.connect("192.168.1.17", port=1883, keepalive=60)
mqttc.loop_start()
while True:
    cpu = CPUTemperature()
    #print(cpu.temperature)
    mqttc.publish("test/message",cpu.temperature)
    time.sleep(120)# sleep for 120 seconds before next call




'''

while True:
    cpu = CPUTemperature()
    print(cpu.temperature)
    #a=cpu.temperature
    #print(psutil.cpu_percent())
    #print(psutil.virtual_memory()[2])
    #print(a)
    client.publish("test/message",cpu.temperature)
    #client.publish("test/ram", psutil.virtual_memory()[2])
    #client.publish("test/cpu", psutil.cpu_percent())
    time.sleep(90)
'''