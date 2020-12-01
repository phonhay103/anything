import socket
import threading

def on_new_client(client):
    try:
        username = str(client.recv(1024).decode('utf-8'))
        print ("{} has joined".format(username))
        while True:
            data = client.recv(1024)
            if data:
                data = ">>> {}: {}".format(username, str(data.decode('utf-8')))
                print(data)
    except KeyboardInterrupt:
        client.close()

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
host = 'localhost'
port = 333
server.bind((host, port))
server.listen(5)
print('Waiting for clients...')

while True:
    conn, client = server.accept()
    threading.Thread(target=on_new_client, args=(conn,)).start()