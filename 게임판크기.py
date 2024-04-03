num = int(input("게임판의 크기: "))
print(" ㅡ "*num)
for i in range(1,num+1):
    print("|",num*"  |")
    print(" ㅡ "*num)
