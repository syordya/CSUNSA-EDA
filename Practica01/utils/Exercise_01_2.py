import random

###### MAIN ######

sizes =  [1000000, 1000500, 1001000, 1001500, 1002000, 1002500]
quantity = 1000000
vector = []

# Numbers within of the range 0f 1 to 1000000
# vector = [random.randint(1, quantity) for x in range(quantity)] 

# Numbers within of the range 0f 1 to 10
vector = [random.randint(1, 10) for x in range(quantity)] 
for x in vector:
    print(x)
