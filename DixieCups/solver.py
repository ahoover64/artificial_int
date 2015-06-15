from cup import Cup
import random
import sys

# PARAMETERS THAT MAY BE PASSED
tot_pennies = int(sys.argv[1]) if len(sys.argv) > 1 else 15
choice_range = int(sys.argv[2]) if len(sys.argv) > 2 else 3
trials = int(sys.argv[3]) if len(sys.argv) > 3 else 1000

cups = []
has_input_file = False

if has_input_file:
    # READ OPTIONS FROM A FILE
    pass

for i in range(tot_pennies):
    cups.append(Cup(i+1, choice_range))

cur_pennies = tot_pennies
cup_amt = 0
usr_amt = 0
i = 0

while i < trials:

    while cur_pennies > 0:
        if cups[cur_pennies - 1].will_lose():
            # remove option from the last cups
            lastcup = cur_pennies + usr_amt + cup_amt - 1
            cups[lastcup].random_lost()
            break
        cup_amt = cups[cur_pennies - 1].random_num()
        cur_pennies = cur_pennies - cup_amt
        if cur_pennies <= 0:
            cups[cur_pennies + cup_amt - 1].random_lost()
            break

        # AI Plays against itself
        if cups[cur_pennies - 1].will_lose():
            # AI  - LAST CHOICE WON!
            lastcup = cur_pennies + cup_amt - 1
            cups[lastcup].remove_others()
            usr_amt = random.randint(1,choice_range) if cur_pennies > (choice_range-1) else random.randint(1,cur_pennies)
            cur_pennies = cur_pennies - usr_amt
            continue
        usr_amt = cups[cur_pennies - 1].random_num()
        cur_pennies = cur_pennies - usr_amt
        if cur_pennies <= 0:
            cups[cur_pennies + usr_amt - 1].random_lost()
            break
        # Random Choice (less efficient)
        '''
        usr_amt = random.randint(1,choice_range) if cur_pennies > (choice_range - 1) else random.randint(1,cur_pennies)
        cur_pennies = cur_pennies - usr_amt
        '''

    i = i + 1
    cur_pennies = tot_pennies
    cup_amt = 0
    usr_amt = 0

for cup in cups:
    print cup
