import socket

SERVER_IP = "127.0.0.1"
SERVER_PORT = 8826

def client_conv_with_server():
    """
    this function will communicate with the server and receive all client info and print all the server's response
    for the client messages
    :return: none
    """
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server_address = (SERVER_IP, SERVER_PORT)
        sock.connect(server_address)
        server_msg = sock.recv(5)
        server_msg = server_msg.decode()
        print(server_msg)
        msg = "hello"
        sock.sendall(msg.encode())
    except Exception as e:
        print("Error!: ", e)
    sock.close()


def main():
    client_conv_with_server()

if __name__ == "__main__":
    main()