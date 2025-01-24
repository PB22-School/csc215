import os
import time

path = "~/csc215"
WAIT_TIME = 60 * 5

number = 1

def commit(num):
    os.system(f"cd {path}; git add .")
    os.system(f"cd {path}; git commit -m 'blackjack {num}'")
    os.system(f"cd {path}; git push")

while True:
    commit(number)
    number += 1
    time.sleep(WAIT_TIME)