command = "11gV2000IA3000OV2000A0G5R"
command  = "\x02" + command + "\x03"

print(ord(command[0]))

def parity(msg):
    parity = ord(msg[0])
    for i in range(1, len(msg)):
        parity = parity ^ ord(msg[i])

    return str(chr(parity))




# print(parity(command))