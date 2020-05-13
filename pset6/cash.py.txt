from cs50 import get_float
while True:
    f = get_float("Change: ")
    if f>=0:
            break

tottal  = round(f* 100)
qurters = tottal//25
dimes   =(tottal%25)//10
nikels  =((tottal%25)%10)//5
pennies =((tottal%25)%10)%5

coins=qurters+dimes+nikels+pennies

print(coins)
