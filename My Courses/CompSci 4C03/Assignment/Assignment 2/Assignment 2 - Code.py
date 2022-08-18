#!/usr/bin/python3
#==============================================================================
#description     :This is a skeleton code for programming assignment 
#usage           :python Skeleton.py trackerIP trackerPort
#python_version  :3.5
#Authors         :Yongyong Wei, Rong Zheng
#==============================================================================

import socket, sys, threading, json, time, os, ssl
import os.path
import glob
import json
import optparse

def validate_ip(s):

    """
    Validate the IP address of the correct format
    Arguments: 
    s -- dot decimal IP address in string
    Returns:
    True if valid; False otherwise
    """

    a = s.split('.')
    if len(a) != 4:
        return False
    for x in a:
        if not x.isdigit():
            return False
        i = int(x)
        if i < 0 or i > 255:
            return False
    return True

def validate_port(x):

    """
    Validate the port number is in range [0,2^16 -1 ]
    Arguments:
    x -- port number
    Returns:
    True if valid; False, otherwise
    """

    if not x.isdigit():
        return False
    i = int(x)
    if i < 0 or i > 65535:
        return False
    return True

def get_file_info():

    """
    Get file info in the local directory (subdirectories are ignored) 
    Return: a JSON array of {'name':file,'mtime':mtime}
    i.e, [{'name':file,'mtime':mtime},{'name':file,'mtime':mtime},...]
    Hint: a. you can ignore subfolders, *.so, *.py, *.dll
          b. use os.path.getmtime to get mtime, and round down to integer
    """

    file_arr = []
    #YOUR CODE

    # Get all files and sub-directories in current dir
    dir_contents = os.listdir('.')
    
    # Iterate through all files and sub-dirs
    for file in dir_contents:
        # If it is  a file:
        if os.path.isfile(file):

            # Store and save filename
            name = file

            # Store and save mtime
            mtime = int (os.path.getmtime(file))

            # Append dictionary to JSON Array
            file_arr.append({'name' : name, 'mtime' : mtime})
            #print(name,"\n",mtime) # For debugging purposes
    
    # Return JSON Array
    return file_arr

def check_port_available(check_port):

    """
    Check if a port is available
    Arguments:
    check_port -- port number
    Returns:
    True if valid; False otherwise
    """

    if str(check_port) in os.popen("netstat -na").read():
        return False
    return True
    
def get_next_available_port(initial_port):

    """
    Get the next available port by searching from initial_port to 2^16 - 1
       Hint: You can call the check_port_avaliable() function
             Return the port if found an available port
             Otherwise consider next port number
    Arguments:
    initial_port -- the first port to check

    Return:
    port found to be available; False if no port is available.
    """

    #YOUR CODE

    #print(initial_port) # For debugging purposes

    for port in range(initial_port, (65535 + 1)):
        if check_port_available(port):
            return port

    '''
    Note: 
    Even though the specification says to locate a port from initial_port
    to 2^16 - 1, the second for loop is used as a fail safe in case a 
    free port cannot be found from the first range. The following for
    loop will check ports from 1 to initial_port. However, this ONLY
    happens if it cannot find a valid port from initial_port to 
    2^16 - 1. 
    '''

    for port in range(1, initial_port):
        if check_port_available(port):
            return port

    # If no port is free, return False
    # This indicates that the function failed to find a free port
    return False

def get_new_file(ip, port, filename, BUFFER_SIZE):

    """
    Sets up a socket connection to the peer containing the
    updated or new file. The name of the requested file is
    sent to the peer. The bytes are stored in a stream and
    then written to a file in the working directory

    Arguments:
        ip           -- IP address of the peer
        port         -- Port of the peer
        filename     -- Name of the requested file
        BUFFER_SIZE  -- Size of the buffer

    Return:
        N/A
    """

    peer_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    peer_socket.connect((ip, port))
    peer_socket.send(filename.encode("utf-8"))

    data = peer_socket.recv(BUFFER_SIZE)
    with open(filename, "wb") as binary_file:
        binary_file.write(data)

class FileSynchronizer(threading.Thread):
    def __init__(self, trackerhost, trackerport, port, host='0.0.0.0'):

        threading.Thread.__init__(self)
        #Port for serving file requests
        self.port = port #YOUR CODE
        self.host = host #YOUR CODE

        #Tracker IP/hostname and port
        self.trackerhost = trackerhost #YOUR CODE
        self.trackerport = trackerport #YOUR CODE

        # Set max buffer size
        self.BUFFER_SIZE = 8192

        #Create a TCP socket to communicate with the tracker
        self.client = socket.socket(socket.AF_INET, socket.SOCK_STREAM) #YOUR CODE
        self.client.settimeout(180)
    
        #Store the message to be sent to the tracker. 
        #Initialize to the Init message that contains port number and file info.
        #Refer to Table 1 in Instructions.pdf for the format of the Init message
        #You can use json.dumps to conver a python dictionary to a json string
        self.msg = json.dumps({'port' : self.port, 'files' : get_file_info()}) #YOUR CODE
        
        #Create a TCP socket to serve file requests from peers.
        self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM) #YOUR CODE

        try:
            self.server.bind((self.host, self.port))
        except socket.error:
            print(('Bind failed %s' % (socket.error)))
            sys.exit()
        self.server.listen(10)

    # Not currently used. Ensure sockets are closed on disconnect
    def exit(self):
        self.server.close()

    #Handle file request from a peer(i.e., send the file content to peers)
    def process_message(self, conn, addr):

        '''
        Arguments:
        self -- self object
        conn -- socket object for an accepted connection from a peer
        addr -- address bound to the socket of the accepted connection
        '''
        #YOUR CODE
        #Step 1. read the file name contained in the request through conn
        #Step 2. read content of that file(assumming binary file <4MB), 
        #        you can open with 'rb'
        #Step 3. send the content back to the requester through conn
        #Step 4. close conn when you are done.

        filename = (conn.recv(2048)).decode('utf-8')
        if not filename: 
            print("ERROR: File Not Received")
            conn.close()
            return

        #print("File Requested:", filename) # Used for debugging purposes

        if os.path.isfile(filename):
            of = open(filename, 'rb')
            content = of.read()
            conn.sendall(content)
            conn.close()
        else:
            print("ERROR: Could Not Find File")
            conn.close()

    def run(self):
        self.client.connect((self.trackerhost,self.trackerport))
        t = threading.Timer(2, self.sync)
        t.start()
        print(('Waiting for connections on port %s' % (self.port)))
        while True:
            conn, addr = self.server.accept()
            threading.Thread(target=self.process_message, args=(conn,addr)).start()

    #Send Init or KeepAlive message to tracker, handle directory response message
    #and request files from peers
    def sync(self):
        print(('connect to: ' + self.trackerhost, self.trackerport))
        #Step 1. send Init msg to tracker (Note init msg only sent once)
        #Note: self.msg is initialized with the Init message (refer to __init__)
        #      then later self.msg contains the Keep-alive message
        
        #YOUR CODE

        self.client.sendall((self.msg).encode('utf-8'))

        #Step 2. now receive a directory response message from tracker
        #YOUR CODE
        
        directory_response_message = self.client.recv(self.BUFFER_SIZE)
        print('received from tracker:', directory_response_message)

        #Step 3. parse the directory response message. If it contains new or
        #more up-to-date files, request the files from the respective peers.
        #NOTE: compare the modified time of the files in the message and
        #that of local files of the same name.
        #Hint: a. use json.loads to parse the message from the tracker
        #      b. read all local files, use os.path.getmtime to get the mtime 
        #         (also note round down to int)
        #      c. for new or more up-to-date file, you need to create a socket, 
        #         connect to the peer that contains that file, send the file name, and 
        #         receive the file content from that peer
        #      d. finally, write the file content to disk with the file name, use os.utime
        #         to set the mtime
        
        #YOUR CODE

        # Unload directory information into a directory
        dict_dir = json.loads(directory_response_message)

        # Iterate through directory information (list of files)
        for file in dict_dir:
            if os.path.isfile(file):
                if dict_dir[file]['mtime'] > int(os.path.getmtime(file)):
                    #print("FILE IS OUTDATED:", file) # Used for debugging purposes
                    get_new_file(dict_dir[file]['ip'], dict_dir[file]['port'],
                                 file, self.BUFFER_SIZE)

                    # Set the utime of the updated file to the mtime stored on the tracker
                    os.utime(file, (os.path.getmtime(file), dict_dir[file]['mtime']))
            else:
                #print("DOES NOT EXIST:", file) # Used for debugging purposes
                get_new_file(dict_dir[file]['ip'], dict_dir[file]['port'],
                             file, self.BUFFER_SIZE)

        #Step 4. construct and send the KeepAlive message
        #Note KeepAlive msg is sent multiple times, the format can be found in Table 1
        #use json.dumps to convert python dict to json string.
        self.msg = (json.dumps({"port" : self.port})) #YOUR CODE
        print("\nHeartBeat Message:", self.msg)

        #Step 5. start timer
        t = threading.Timer(5, self.sync)
        t.start()

if __name__ == '__main__':
    #parse command line arguments
    parser = optparse.OptionParser(usage="%prog ServerIP ServerPort")
    options, args = parser.parse_args()
    if len(args) < 1:
        parser.error("No ServerIP and ServerPort")
    elif len(args) < 2:
        parser.error("No  ServerIP or ServerPort")
    else:
        if validate_ip(args[0]) and validate_port(args[1]):
            tracker_ip = args[0]
            tracker_port = int(args[1])

        else:
            parser.error("Invalid ServerIP or ServerPort")
    #get free port
    synchronizer_port = get_next_available_port(8000)
    synchronizer_thread = FileSynchronizer(tracker_ip, tracker_port, synchronizer_port)
    synchronizer_thread.start()
