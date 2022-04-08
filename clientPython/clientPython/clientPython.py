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
    print("Recieved:    " + sock.recv(CODE_SIZE).decode(), end="")
    len = sock.recv(LEN_OF_BITS).decode()
    print(len + sock.recv(int(len)).decode())


def send_signup(sock, username, password, email):
    """
    this function sends signup request
    :param sock: socket that we send the message
    :type sock: socket
    :param username: the username of the new user
    :type username: string
    :param password: the password of the new user
    :type password: string
    :param email: the email of the new user
    :type email: string
    """
    msg = json.loads('{"username": "' + username + '", "password": "' + password + '", "email": "' + email + '"}')
    print("Send:    " + 'b' + str(len(json.dumps(msg))).rjust(LEN_OF_BITS, "0") + json.dumps(msg)) # print the message we send
    sock.sendall(str('b' + str(len(json.dumps(msg))).rjust(LEN_OF_BITS, "0") + json.dumps(msg)).encode())


def send_login(sock, username, password):
    """
    this function sends login request
    :param sock: socket that we send the message
    :type sock: socket
    :param username: the username of the new user
    :type username: string
    :param password: the password of the new user
    :type password: string
    """
    msg = json.loads('{"username": "' + username + '", "password": "' + password + '"}')
    print("Send:    " + 'a' + str(len(json.dumps(msg))).rjust(LEN_OF_BITS, "0") + json.dumps(msg)) # print the message we send
    sock.sendall(str('a' + str(len(json.dumps(msg))).rjust(LEN_OF_BITS, "0") + json.dumps(msg)).encode())


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
        send_login(sock, "Unknown", "tralala")      # login with user that has not signed up
        print_recv(sock)
        send_signup(sock, "user1", "pass1", "user1@gmail.com")     # regular signup
        print_recv(sock)
        send_signup(sock, "user1", "pass1", "user1@gmail.com")     # signup with user that already exists
        print_recv(sock)
        send_login(sock, "user1", "pass1")     # regular login
        print_recv(sock)
        send_login(sock, "user1", "pass1")     # login with user that is already loged in 
        print_recv(sock)

    except Exception as e:
        sock.close()
        print("Error!: ", e)
    sock.close()


def main():
    client_conv_with_server()
    

if __name__ == "__main__":
    main()
