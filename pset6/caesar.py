import sys
from sys import argv
from cs50 import get_string

encrypted = ""
syntax = ""

if len(sys.argv) != 2:
    print("missing command-line argument")
    sys.exit(1)

key = int(sys.argv[1])
plaintext = get_string("plaintext: ")
print("ciphertext: ", end="");
for letter in plaintext:

    if (letter.islower()):
          print(chr((ord(letter)-ord('a')+key)%26 +ord('a')), end="")
    elif (letter.isupper()):
         print(chr((ord(letter)-ord('A')+key)%26 +ord('A')), end="")
    else:
         print(letter, end="")
print()
