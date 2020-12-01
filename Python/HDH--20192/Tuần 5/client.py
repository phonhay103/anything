import socket

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

client.connect(('localhost', 333))
username = input('Username: ')
client.sendall(username.encode('utf-8'))

try:
    while True:
        message = input('{}: '.format(username))
        client.sendall(message.encode('utf-8'))
        # received = str(client.recv(1024).decode('utf-8'))
        # print (received)
except KeyboardInterrupt:
    client.close()