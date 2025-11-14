#https://stackoverflow.com/questions/8713620/appending-to-one-list-in-a-list-of-lists-appends-to-all-other-lists-too
import numpy as np
import matplotlib.pyplot as plt
import sys

def get_parms(file, depth :int):
    lines = file.readlines(depth)
    for i in lines:
        char :str = ""

def get_time_stamp(line :str):
    print(line[:12])
    return line[:12]
    # location = line.find(">")
    # if location >= 1:
    #     return str(line[location-2:])
    # else:
    #     return -1

def get_data(line :str):
    subline = line[14:]
    location = subline.find(":") # temp solution avoids time stamp triggering this logic
    if location >= 1:
        return float(subline[location+1:])
    else:
        return -1

def main():
    filename :str = ""
    sens_list : list = []
    if (len(sys.argv) < 3):
        print("ERROR: put files to be read")
        exit()

    file = open(sys.argv[1], 'r')
    sens_list_f = open(sys.argv[2], 'r')


    for line in sens_list_f:
        sens_list.append(line.rstrip())
    sens_list_f.close()

    data_list :list = [[] for _ in range(0,len(sens_list))] 
    print(data_list)
    time_list :list = [[] for _ in range(0,len(sens_list))] 

    for line in file:
        sens_count = 0
        for sens in sens_list:
            if line.strip().find(sens) > 0:
                print(f"found {sens}")
                print(sens_count)
                data = get_data(line)
                # time_list[sens_count].append(get_time_stamp(line))
                data_list[sens_count].append(data)
            sens_count += 1

    i = 0
    print(len(sens_list))
    while i < len(sens_list):
        time_list[i] = range(0, len(data_list[i]))
        i += 1

    file.close()
    print("sens_list:")
    print(sens_list)
    print("data list:")
    print("time list:")
    print(time_list)
    sens_count = 0
    fig = plt.figure()
    if len(sens_list) > 1:
        axs = fig.subplots(len(sens_list))
        counter = 0 
        for data in data_list:
            axs[counter].plot(time_list[counter] ,data)
            axs[counter].set(ylabel=sens_list[counter])
            counter += 1
    else:
        fig = plt.figure()
        ax = fig.add_subplot(111)
        ax.plot(time_list[0], data_list[0])

    # compare the two tables
    rpm = data_list[3][3500:]
    interval = data_list[4][3500:]
    fig2, ax1 = plt.subplots(figsize=(8, 8))
    ax2 = ax1.twinx()
    ax1.plot(range(0,len(interval)), rpm)
    ax1.set_ylabel("RPM")
    ax2.plot(range(0,len(interval)), interval)
    ax2.set_ylabel("interval")
    plt.grid()
    plt.show()
if __name__ == "__main__":
    main()
