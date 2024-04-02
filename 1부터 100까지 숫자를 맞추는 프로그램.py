## 1부터 100까지의 숫자를 맞추는 프로그램

import random

print("1부터 100 사이의 숫자를 맞추시오")
ran = random.randint(1,100) 
count = 0

while True :
    num = int(input("숫자를 입력하시오: "))
    if num < ran :
        count += 1
        print("너무 낮음!")
    elif num > ran : 
        count +=1
        print("너무 높음!")
    elif num == ran :
        count +=1
        print(f"축하합니다. 시도횟수 = {count}")
        break
    