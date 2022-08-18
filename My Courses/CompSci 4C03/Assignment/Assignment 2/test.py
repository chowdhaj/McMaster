import os.path
import json

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
            file_arr.append({"name" : name, "mtime" : mtime})
            #print(name,"\n",mtime) # For debugging purposes

    #print(type(file_arr))

    json_string = json.dumps(file_arr)
    #print(type(json_string))
    #print(json_string)
    
    # Return JSON Array
    return json_string

##print(get_file_info())
##tempDict = {'port' : 234}
###tempDict['port'] = 234
##tempDict['files'] = get_file_info()
##print(json.dumps(tempDict))

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

    ports_exhausted = False

    for port in range(initial_port, (65535 + 1)):
        if check_port_available(port):
            return port

    for port in range(1, initial_port):
        if check_port_available(port):
            return port

    return False

get_next_available_port(80)
