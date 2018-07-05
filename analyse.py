import filecmp
import os

def searchIterationsValues(num_iterations,iter_jumps,map,agent_policy,otm_policy,command,learning_rate,discount_rate,x,y,z):
    print num_iterations,iter_jumps
    os.system(command + " " + str(num_iterations))
    if filecmp.cmp(agent_policy,otm_policy):
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

def getData():
    maps = ["pacmaze-01-tiny.txt","pacmaze-02-mid-sparse.txt","pacmaze-03-tricky.txt"]
    executable = "qlearning.sh"
    map_dir = "maps/"
    agent_policy = "pi.txt"
    iter_jumps = 999999

    range_values = [0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0]

    x_values = {}
    y_values = {}
    z_values = {}

    for map in maps:
        for learning_rate in range_values:
            for discount_rate in range_values:
                otm_policy = "pi_star_" + map
                command = "./" + executable + " " + map_dir + map + " " + str(learning_rate) + " " + str(discount_rate)
                searchIterationsValues(0,iter_jumps,map,agent_policy,otm_policy,command,learning_rate,discount_rate,x_values,y_values,z_values)
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

x,y,z = getData()
write_data(x,y,z)
