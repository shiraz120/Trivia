import socket
import json

SERVER_IP = "127.0.0.1"
SERVER_PORT = 8826
LEN_OF_BITS = 4
CODE_SIZE = 2


def print_recv(sock):
    """
    prints the recieved message
    input: socket
    return: none
    """
    print("Recieved:    " + sock.recv(128).decode(), end="")
   # len = calc_bin_to_len(sock)
   # print(len + sock.recv(int(len)).decode())


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
    print("Send:    " + 'b' + calc_len_to_bin(json.dumps(msg)) + json.dumps(msg)) # print the message we send
    sock.sendall(str('b' + calc_len_to_bin(json.dumps(msg)) + json.dumps(msg)).encode())


def calc_len_to_bin(msg):
    """
    this function returns the len of the message in the binary format
    :param msg: the message
    :param return: the length in binary format
    :type return: string
    """
    ln = len(msg)
    bin_str = ""
    while ln >= 255:
        bin_str += chr(255)
        ln -= 255
    bin_str += chr(ln)
    bin_str = bin_str[::-1]
    ans = ""
    needed_chars = 4 - len(bin_str)
    for _ in range(needed_chars):
        ans += '\0'
    ans += bin_str
    print(len(ans))
    return ans


def calc_bin_to_len(sock):
    """
    this function returns the len of the message in the binary format
    :param sock: the socket
    :type sock: socket
    :param return: the length in binary format
    :type return: string
    """
    len = 0
    ch = sock.recv(1).decode()
    len += int(ch) * 256**3
    ch = sock.recv(1).decode()
    len += int(ch) * 256**2
    ch = sock.recv(1).decode()
    len += int(ch) * 256
    ch = sock.recv(1).decode()
    len += int(ch)
    return len



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
    print("Send:    " + 'a' + calc_len_to_bin(json.dumps(msg)) + json.dumps(msg)) # print the message we send
    sock.sendall(str('a' + calc_len_to_bin(json.dumps(msg)) + json.dumps(msg)).encode())


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
