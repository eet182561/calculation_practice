#Python file

import configparser
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt

def display_result(results):
    #results are described as follows:
    #Reuslt
    #   problem1
    #       epochs number of problems
    #   problem2
    #       epochs number of problems
    '''
    Each problem is stored in this fashion
    [operand_1 operand_2 correct_answer user_answer is_true? error_between_actual_and_user]
    ****Error between actual and user can be used when approximating large numbers
    '''
    result_array = np.array(results)
    ax = [x for x in range(result_array.shape[0])]
    sns.barplot(y = np.mean(results,axis=1)[-2],x = ax)
    plt.show()
    print(result_array.shape)

def play(mode,params_dict):
    if mode==1:
        a,A,b,B,s,S,epochs = params_dict.values()        
        cont = 'y'
        games = []
        while cont=='y':
            problems = []
            for i in range(int(epochs)):
                op1=np.random.randint(a,A)
                op2=np.random.randint(b,B)
                while op1+op2<int(s) and op1+op2>int(S):
                    op1 = np.random.randint(a,A)
                    op2 = np.random.randint(b,B)
                print(str(op1) + ' + ' + str(op2) + ' = ' )
                su = int(input())
                problem = [op1,op2,op1+op2,su,op1==op2,su-op1-op2]
                problems.append(problem)
            games.append(problems)
            print("Continue?")
            cont = input()
        display_result(games)
    return games


print('Enter the mode. 1,2?')
config = configparser.ConfigParser()
option = int(input())
with open('py_play.config') as f:
    config.read_file(f)
    mode = 'MODE_' + str(option)
    play(option,config[mode])