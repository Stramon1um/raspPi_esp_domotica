from gpiozero import CPUTemperature
import time
import paho.mqtt.client as mqtt #import the client1
import psutil

broker_address="192.168.1.17"
client = mqtt.Client("P1") #create new instance
client.connect(broker_address) #connect to broker

#time.sleep(60)


while True:
    cpu = CPUTemperature()
    #print(cpu.temperature)
    #a=cpu.temperature
    #print(psutil.cpu_percent())
    #print(psutil.virtual_memory()[2])
    #print(a)
    client.publish("test/message",cpu.temperature)
    #client.publish("test/ram", psutil.virtual_memory()[2])
    #client.publish("test/cpu", psutil.cpu_percent())
    time.sleep(60)