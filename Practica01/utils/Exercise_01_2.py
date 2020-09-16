import random

###### MAIN ######

quantity = 1000000
vector = []

# Numbers within of the range 0f 1 to 100
vector = [random.randint(1, 100) for x in range(quantity)] 
for x in vector:
    print(x,end=" ")
