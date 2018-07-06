import filecmp
import os
import sys

sys.setrecursionlimit(999999999)

def verifyDifference(agent_policy,otm_policy):
    arq1 = open(agent_policy,"r")
    arq2 = open(otm_policy,"r")
    content1 = arq1.readlines()
    content2 = arq2.readlines()

    print content1[0]
    num_differences = 0

    for line in xrange(len(content1)):
        for char in xrange(len(content1[0])):
            if content1[line][char] != content2[line][char]:
                num_differences += 1

    print num_differences
    arq1.close()
    arq2.close()
    if(num_differences <= 2):
        return True
    else:
        return False

def num_verifyDifference(agent_policy,otm_policy):
    arq1 = open(agent_policy,"r")
    arq2 = open(otm_policy,"r")
    content1 = arq1.readlines()
    content2 = arq2.readlines()

    print content1[0]
    num_differences = 0

    for line in xrange(len(content1)):
        for char in xrange(len(content1[0])):
            if content1[line][char] != content2[line][char]:
                num_differences += 1

    arq1.close()
    arq2.close()
    return num_differences

def searchIterationsValues(num_iterations,iter_jumps,map,agent_policy,otm_policy,command,learning_rate,discount_rate,x,y,z):
    print num_iterations,iter_jumps
    if num_iterations >= 9999990:
        if x.has_key(map):
            x[map] += [learning_rate]
        else:
            x[map] = [learning_rate]

        if y.has_key(map):
            y[map] += [discount_rate]
        else:
            y[map] = [discount_rate]
            
        if z.has_key(map):
            z[map] += [num_iterations + num_verifyDifference(agent_policy,otm_policy)*iter_jumps]
        else:
            z[map] = [num_iterations + num_verifyDifference(agent_policy,otm_policy)*iter_jumps]
        return
    else:
        os.system(command + " " + str(num_iterations))
        if verifyDifference(agent_policy,otm_policy):
            if iter_jumps <= 5:
                if x.has_key(map):
                    x[map] += [learning_rate]
                else:
                    x[map] = [learning_rate]

                if y.has_key(map):
                    y[map] += [discount_rate]
                else:
                    y[map] = [discount_rate]
                    
                if z.has_key(map):
                    z[map] += [num_iterations]
                else:
                    z[map] = [num_iterations]
                return
            else:            
                searchIterationsValues(num_iterations-iter_jumps,iter_jumps/2,map,agent_policy,otm_policy,command,learning_rate,discount_rate,x,y,z)
        else:
            searchIterationsValues(num_iterations+iter_jumps,iter_jumps,map,agent_policy,otm_policy,command,learning_rate,discount_rate,x,y,z)

def getData(map_name,map_dir,agent_policy,iter_jumps,executable,range_values):
    x_values = {}
    y_values = {}
    z_values = {}

    for learning_rate in range_values:
        for discount_rate in range_values:
            otm_policy = "pi_star_" + map_name
            command = "./" + executable + " " + map_dir + map_name + " " + str(learning_rate) + " " + str(discount_rate)
            searchIterationsValues(0,iter_jumps,map_name,agent_policy,otm_policy,command,learning_rate,discount_rate,x_values,y_values,z_values)
    
    return x_values,y_values,z_values

def write_data(x_values,y_values,z_values):
    maps = ["pacmaze-01-tiny.txt","pacmaze-02-mid-sparse.txt","pacmaze-03-tricky.txt"]
    for map in maps:
        arq = open("results_" + map,"w")
        for x in x_values[map]:
            arq.write(str(x))
        arq.write("\n")
        for y in y_values[map]:
            arq.write(str(y))
        arq.write("\n")
        for z in z_values[map]:
            arq.write(str(z))
        arq.close()

n_maps = ["pacmaze-01-tiny.txt","pacmaze-02-mid-sparse.txt","pacmaze-03-tricky.txt"]
n_executable = "qlearning.sh"
n_map_dir = "maps/"
n_agent_policy = "pi.txt"
n_iter_jumps = 999999
n_range_values = [0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0]

for map_n in n_maps:
    x,y,z = getData(map_n,n_map_dir,n_agent_policy,n_iter_jumps,n_executable,n_range_values)
    write_data(x,y,z)