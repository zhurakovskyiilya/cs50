from cs50 import get_string
from sys import argv
import copy
import sys


bad_words=[]

my_list=[]

words =[]


def main():

    if len(sys.argv) != 2 and len(sys.argv)>2 :
        print("Usage bleep [dictionary]")
        sys.exit(1)


    f = open(sys.argv[1], "r")

    for line in f:
        bad_words.append(line.rstrip("\n"))
    f.close()

    massage = get_string("Waht message would you like to censor: ")


    words=massage.split()

    bad_words_two = copy.copy(bad_words)

    bad_words_two = [w.upper() for w in bad_words]


    for word in words:

            if word not in bad_words:

                if word not in bad_words_two:

                    my_list.append(word)
                else:
                    a = len(word)
                    s="*"*len(word)
                    my_list.append(s)

            else:
                    a = len(word)
                    s="*"*len(word)
                    my_list.append(s)



    print(' '.join(my_list))

if __name__ == "__main__":
    main()
