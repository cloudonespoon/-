import random


score = 0
for i in range(5):
    
    num1 = random.randint(1,100)
    num2 = random.randint(1,100)
    simbol = random.randint(1,4)
    
    if simbol == 1:
        dab = num1+num2
        print(f"{num1} + {num2}의 값은?", end="")
        X = int(input())
        if X==dab:
            print("맞았습니다.")
            score += 1
        else:
            print("틀렸습니다.")
        
    if simbol == 2:
        dab = num1-num2
        print(f"{num1} - {num2}의 값은?", end="")
        X = int(input())
        if X==dab:
            print("맞았습니다.")
            score += 1
        else:
            print("틀렸습니다.")
        
    if simbol == 3:
        dab = num1*num2
        print(f"{num1} * {num2}의 값은?", end="")
        X = int(input())
        if X==dab:
            print("맞았습니다.")
            score += 1
        else:
            print("틀렸습니다.")
        
        if simbol == 4:
            dab = num1//num2
            print(f"{num1} // {num2}의 값은?", end="")
            X = int(input())
            if X==dab:
                print("맞았습니다.")
                score += 1
 
        else:
            print("틀렸습니다.")
print(f"점수는: {score}")
    