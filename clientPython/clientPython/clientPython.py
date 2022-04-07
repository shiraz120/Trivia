import socket
import json

SERVER_IP = "127.0.0.1"
SERVER_PORT = 8826
LEN_OF_BITS = 4
CODE_SIZE = 1


def print_recv(sock):
    """
    prints the recieved message
    input: socket
    return: none
    """
    print("Recived:     "  + sock.recv(CODE_SIZE).decode(), end='')
    len = sock.recv(LEN_OF_BITS).decode()
    print(len, end='')
    print(sock.recv(int(len)).decode())


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
        msg = json.loads('{"username": "user1", "password": "1234", "mail":"user1@gmail.com"}')
        print("Send:    " + 'b' + str(len(json.dumps(msg))).ljust(LEN_OF_BITS, "0") + json.dumps(msg)) # print the message we send
        sock.sendall(str('b' + str(len(json.dumps(msg))).ljust(LEN_OF_BITS, "0") + json.dumps(msg)).encode())
        print_recv(sock)
        msg = json.loads('{"username": "user1", "password": "1234"}')
        print("Send:    " + 'a' + str(len(json.dumps(msg))).ljust(LEN_OF_BITS, "0") + json.dumps(msg)) # print the message we send
        sock.sendall(str('a' + str(len(json.dumps(msg))).ljust(LEN_OF_BITS, "0") + json.dumps(msg)).encode())
        print_recv(sock)
    
    except Exception as e:
        sock.close()
        print("Error!: ", e)
    sock.close()


def main():
    client_conv_with_server()


if __name__ == "__main__":
    main()