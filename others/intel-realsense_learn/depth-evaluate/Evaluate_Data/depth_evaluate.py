import matplotlib.pyplot as plt
import numpy as np
from numpy.core.fromnumeric import size
from numpy.lib.function_base import _parse_gufunc_signature, append
import os


"""读取文件夹"""
filePath = '/home/guoheng/vscode/intel-realsense_learn/depth-evaluate/txt/'
def readname():
    name = os.listdir(filePath)
    return name   
names = readname()
"""读取所有和每一个txt文件"""
depth_data = np.array
depth_data_2_1 = np.array
depth_data_1_9 = np.array
depth_data_1_7 = np.array
depth_data_1_5 = np.array
depth_data_1_3 = np.array
depth_data_1_1 = np.array
depth_data_0_9 = np.array
depth_data_0_7 = np.array
depth_data_0_5 = np.array

for i in names:
    tempData = np.array
    if(i == '2.1.txt'):
        depth_data_2_1 = np.loadtxt(filePath+i)
        tempData =  np.loadtxt(filePath+i)
    if(i == '1.9.txt'):
        depth_data_1_9 = np.loadtxt(filePath+i)
        tempData =  np.loadtxt(filePath+i)
    if(i == '1.7.txt'):
        depth_data_1_7 = np.loadtxt(filePath+i)
        tempData =  np.loadtxt(filePath+i)
    if(i == '1.5.txt'):
        depth_data_1_5 = np.loadtxt(filePath+i)
        tempData =  np.loadtxt(filePath+i)
    if(i == '1.3.txt'):
        depth_data_1_3 = np.loadtxt(filePath+i)
        tempData =  np.loadtxt(filePath+i)
    if(i == '1.1.txt'):
        depth_data_1_1 = np.loadtxt(filePath+i)
        tempData =  np.loadtxt(filePath+i)
    if(i == '0.9.txt'):
        depth_data_0_9 = np.loadtxt(filePath+i)
        tempData =  np.loadtxt(filePath+i)
    if(i == '0.7.txt'):
        depth_data_0_7 = np.loadtxt(filePath+i)
        tempData =  np.loadtxt(filePath+i)
    if(i == '0.5.txt'):
        depth_data_0_5 = np.loadtxt(filePath+i)
        tempData =  np.loadtxt(filePath+i)

    depth_data = np.append(depth_data,tempData)
        
print(len(depth_data)-1) 
print(len(depth_data_2_1)) 
print(len(depth_data_1_9)) 
print(len(depth_data_1_7)) 
print(len(depth_data_1_5)) 
print(len(depth_data_1_3)) 
print(len(depth_data_1_1)) 
print(len(depth_data_0_9)) 
print(len(depth_data_0_7)) 
print(len(depth_data_0_5)) 

depth_data_dict = {"2-1":depth_data_2_1,"1-9":depth_data_1_9,"1-7":depth_data_1_7,"1-5":depth_data_1_5,"1-3":depth_data_1_3,"1-1":depth_data_1_1,"0-9":depth_data_0_9,"0-7":depth_data_0_7,"0-5":depth_data_0_5}
print(len(depth_data_dict))

"""    test-test-test
# a = np.array([1,2,3])
# b = np.array([4,4,5])
# c = np.array([6,2,3])
# d = np.array([7,8,3]) 
# people={'lifei':a,'fanming':b,'gaolan':c,'hanmeimie':d}
# # for fruit in set(people.values()):
# # for fruit in people.values():
# # for fruit in people.keys():  
# for people_key,people_value in people.items():
#     print(people_key)
#     print(people_value)
"""

'''nend picture'''
global A_Figure
global All_Points
A_Figure = False 
All_Points = False

'''所有距离统计画点的数组'''
depth_pexil_volatility_scope_mean_arr = np.array([])
depth_pexil_volatility_scope_max_arr = np.array([])
depth_pexil_volatility_scope_min_arr = np.array([])
depth_pexil_volatility_scope_var_arr = np.array([])


if All_Points:

    depth_data= np.delete(depth_data,0)
    """无效值"""
    Invalid=[]
    for i in depth_data:
        if(i==0): 
            Invalid.append(i)
    print("Invalid = ".format(len(Invalid)))

    """深度数据标号"""
    depth_value = []
    for value in range(0,depth_data.size):
        depth_value.append(value)    

    """gobal mean var std(均值 方差 标准差)"""
    depth_mean_global = np.mean(depth_data)
    depth_var_global = np.var(depth_data)
    depth_std_1_global = np.std(depth_data)
    depth_std_2_global = np.std(depth_data, ddof=1)        
    print("gobal mean{} gobal var{} depth_std_1_global{} depth_std_2_global{}".format(depth_mean_global,depth_var_global,depth_std_1_global,depth_std_2_global))
    
    """drawing"""
    plt.title("ALL-POINTS")
    ''' 散点图'''
    plt.scatter(depth_value,depth_data,color='y',s=20)
    '''画出均值线'''
    plt.axhline(y=depth_mean_global, color='r', linestyle='-')
    '''添加文本(方差和均值)'''
    plt.text(depth_value[-1], depth_mean_global, 'depth_mean_global')
    ''' draw line'''
    # plt.plot(depth_value, depth_data,color='b')
    '''x轴 y轴 显示栏设置'''
    plt.xlabel("depth_value",fontsize=14)
    plt.ylabel("depth_data",fontsize=14)
    # plt.figure(figsize=(20, 10), dpi=100)
    plt.tick_params(axis='both',labelsize=10)

    plt.show()

else: 
   
    for depth_data_dict_key,depth_data_dict_value in depth_data_dict.items():
        print("start {}.txt To calculate".format(depth_data_dict_key))
        
        CALCULATE_GLOBAL = True
        calculate_global = False
        calculate_pixel = True
        if(calculate_global):

            """无效值"""
            Invalid=[]
            for i in depth_data_dict_value:
                if(i==0): 
                    Invalid.append(i)
                    depth_data= np.delete(depth_data,i)
            print("Invalid size ={}".format(len(Invalid)))
            print("Invalid ={} ".format(Invalid))
            print("depth_data ={} ".format(len(depth_data)))


            """深度数据标号"""
            depth_value = []
            for value in range(0,depth_data_dict_value.size):
                depth_value.append(value)    

            """gobal mean var std(均值 方差 标准差)"""
            depth_mean_global = np.mean(depth_data_dict_value)
            depth_var_global = np.var(depth_data_dict_value)
            depth_std_1_global = np.std(depth_data_dict_value)
            depth_std_2_global = np.std(depth_data_dict_value, ddof=1)        
            print("gobal mean{} gobal var{} depth_std_1_global{} depth_std_2_global{}".format(depth_mean_global,depth_var_global,depth_std_1_global,depth_std_2_global))
            
            """drawing"""
            fig = plt.figure(figsize=(10, 8))
            plt.title(depth_data_dict_key + 'gobal')
            ''' 散点图'''
            plt.scatter(depth_value,depth_data_dict_value,color='y',s=20)
            '''画出均值线'''
            plt.axhline(y=depth_mean_global, color='r', linestyle='-')
            '''添加文本(方差和均值)'''
            plt.text(depth_value[-1], depth_mean_global, 'depth_mean_global')
            ''' draw line'''
            # plt.plot(depth_value, depth_data,color='b')
            '''x轴 y轴 显示栏设置'''
            plt.xlabel("depth_value",fontsize=14)
            plt.ylabel("depth_data",fontsize=14)
            # plt.figure(figsize=(20, 10), dpi=100)
            plt.tick_params(axis='both',labelsize=10)
            plt.show()
        
        if(calculate_pixel):
            
            """无效值"""
            Invalid=[]
            for i in depth_data_dict_value:
                if(i==0): 
                    Invalid.append(i)
            print("Invalid size = {}".format(len(Invalid)))

            """深度数据标号"""
            depth_value = []
            for value in range(0,depth_data_dict_value.size):
                depth_value.append(value)  
            
            '''转化成(100*1600)二维数组 然后转置'''
            depth_data_dict_value_reshpe = np.array(depth_data_dict_value).reshape(100,int(len(depth_data_dict_value)/100))
            depth_data_dict_value_reshpe_T = depth_data_dict_value_reshpe.T


            """pexils mean var std(均值 方差 标准差)"""
            depth_mean_global = np.mean(depth_data_dict_value)
            depth_var_global = np.var(depth_data_dict_value)
            depth_std_1_global = np.std(depth_data_dict_value)
            depth_std_2_global = np.std(depth_data_dict_value, ddof=1)        
            print("gobal mean{} gobal var{} depth_std_1_global{} depth_std_2_global{}".format(depth_mean_global,depth_var_global,depth_std_1_global,depth_std_2_global))
            
            depth_var_pexils = np.array
            depth_mean_pexils = np.array
            
            depth_data_dict_value_reshpe_T_del = np.array([])
            depth_pexil_volatility_scope_arr = np.array([])
            for i in range(0,depth_data_dict_value_reshpe_T.shape[0]):
                depth_data_dict_value_reshpe_T_del_y = np.array([])
                for j in range(0,depth_data_dict_value_reshpe_T.shape[1]):
                    if(depth_data_dict_value_reshpe_T[i][j]!=0):
                        depth_data_dict_value_reshpe_T_del_y=np.append(depth_data_dict_value_reshpe_T_del_y,depth_data_dict_value_reshpe_T[i][j])

                depth_data_dict_value_reshpe_T_del = np.append(depth_data_dict_value_reshpe_T_del,depth_data_dict_value_reshpe_T_del_y)
                depth_mean_pexil = np.array
                depth_var_pexil = np.array
                '''pexils mean var'''
                depth_mean_pexil_temp = np.mean(depth_data_dict_value_reshpe_T[i])
                depth_var_pexil_temp = np.var(depth_data_dict_value_reshpe_T[i])
                '''波动范围'''
                if(depth_data_dict_value_reshpe_T_del_y.size!=0):
                    depth_max_pexil = np.max(depth_data_dict_value_reshpe_T_del_y)
                    depth_min_pexil = np.min(depth_data_dict_value_reshpe_T_del_y)
                    depth_pexil_volatility_scope = depth_max_pexil - depth_min_pexil

                depth_pexil_volatility_scope_arr = np.append(depth_pexil_volatility_scope_arr,depth_pexil_volatility_scope)
                depth_mean_pexils = np.append(depth_mean_pexils,depth_mean_pexil_temp)
                depth_var_pexils = np.append(depth_var_pexils,depth_var_pexil_temp)
            
            depth_pexil_volatility_scope_mean = np.mean(depth_pexil_volatility_scope_arr)
            depth_pexil_volatility_scope_max = np.max(depth_pexil_volatility_scope_arr)
            depth_pexil_volatility_scope_min = np.min(depth_pexil_volatility_scope_arr)
            depth_pexil_volatility_scope_var = np.var(depth_pexil_volatility_scope_arr)
            
            depth_pexil_volatility_scope_mean_arr= np.append(depth_pexil_volatility_scope_mean_arr,depth_pexil_volatility_scope_mean)
            depth_pexil_volatility_scope_max_arr= np.append(depth_pexil_volatility_scope_max_arr,depth_pexil_volatility_scope_max)
            depth_pexil_volatility_scope_min_arr= np.append(depth_pexil_volatility_scope_min_arr,depth_pexil_volatility_scope_min)
            depth_pexil_volatility_scope_var_arr= np.append(depth_pexil_volatility_scope_var_arr,depth_pexil_volatility_scope_var)

            print("depth_pexil_volatility_scope_mean={}".format(depth_pexil_volatility_scope_mean))         
            print("depth_pexil_volatility_scope_max={}".format(depth_pexil_volatility_scope_max))         
            print("depth_pexil_volatility_scope_min={}".format(depth_pexil_volatility_scope_min))         
            print("depth_pexil_volatility_scope_var={}".format(depth_pexil_volatility_scope_var))         

            print("depth_data_dict_value_reshpe_T_del={}".format(len(depth_data_dict_value_reshpe_T_del)))         
            print("depth_pexil_volatility_scope_arr.size={}".format(len(depth_pexil_volatility_scope_arr)))
            print("depth_pexil_volatility_scope_arr={}".format(depth_pexil_volatility_scope_arr))
            print("depth_data_dict_value{} ".format(len(depth_data_dict_value)))
  
            depth_mean_pexils= np.delete(depth_mean_pexils,0)
            depth_var_pexils= np.delete(depth_var_pexils,0)

            """均值数据标号"""
            depth_mean_pexils_value = []
            for value in range(0,depth_mean_pexils.size):
                depth_mean_pexils_value.append(value*100)                
            """方差数据标号"""
            depth_var_pexils_value = []
            for value in range(0,depth_var_pexils.size):
                depth_var_pexils_value.append(value*100) 
            print(len(depth_mean_pexils_value))

            depth_pexil_volatility_scope_value = []
            for value in range(0,depth_pexil_volatility_scope_arr.size):
                depth_pexil_volatility_scope_value.append(value) 

            print("depth_mean_pexils的大小={}".format(len(depth_mean_pexils)))
            print(depth_mean_pexils)
            print("depth_mean_pexils的大小={}".format(len(depth_var_pexils)))
            print(depth_var_pexils)

            """drawing"""
            fig = plt.figure(figsize=(10, 10))
            plt.grid(axis='x')
            plt.grid(axis='y')
            plt.title(depth_data_dict_key + "pixel")
            ''' 散点图'''
            # plt.scatter(depth_value,depth_data_dict_value_reshpe_T,color='y',s=20)
            # plt.scatter(depth_mean_pexils_value,depth_mean_pexils,color='b',s=20)
            # plt.scatter(depth_var_pexils_value,depth_var_pexils,color='g',s=20)
            # '''每一个像素点的波动范围'''
            # plt.scatter(depth_var_pexils_value,depth_pexil_volatility_scope_arr,color='g',s=20)

            """直方图"""
            # ax = fig.add_axes([0,0,1,1])
            # ax.bar(depth_pexil_volatility_scope_value,depth_pexil_volatility_scope_arr)
            plt.hist(depth_pexil_volatility_scope_arr)
            # plt.plot(depth_mean_pexils_value, depth_mean_pexils,color='b')

            # '''画出均值线 波动范围 min max'''
            # plt.axhline(y=depth_mean_global, color='r', linestyle='-')
            plt.axhline(y=depth_pexil_volatility_scope_max, color='m', linestyle='-')
            plt.axhline(y=depth_pexil_volatility_scope_min, color='m', linestyle='-')
            # '''添加文本(方差和均值)'''
            # plt.text(depth_value[-1], depth_mean_global, 'depth_mean_global')
            # plt.text(depth_value[-1], 0 , (len(Invalid)), fontsize=20 )
            plt.text(depth_value[0], depth_pexil_volatility_scope_max, 'depth_pexil_volatility_scope_max')
            plt.text(depth_value[0], depth_pexil_volatility_scope_min, 'depth_pexil_volatility_scope_min')

            ''' draw line'''
            # plt.plot(depth_value, depth_data,color='b')
            '''x轴 y轴 显示栏设置'''
            plt.xlabel("depth_value",fontsize=14)
            plt.ylabel("depth_data",fontsize=14)
            plt.tick_params(axis='both',labelsize=10)

            plt.show()
            
"""数据标号"""
# depth_pexil_volatility_scope_value = []
# for value in range(0,depth_pexil_volatility_scope_mean_arr.size):
#     depth_pexil_volatility_scope_value.append(value)  
depth_pexil_volatility_scope_value = [2.1,1.9,1.7,1.5,1.3,1.1,0.9,0.7,0.5]
plt.grid(axis='x')
plt.grid(axis='y')
plt.title("All pixel distance fluctuation range")
''' 根据距离的波动范围 mean max min var'''
plt.scatter(depth_pexil_volatility_scope_value,depth_pexil_volatility_scope_mean_arr,color='r',s=20)
plt.scatter(depth_pexil_volatility_scope_value,depth_pexil_volatility_scope_max_arr,color='g',s=20)
plt.scatter(depth_pexil_volatility_scope_value,depth_pexil_volatility_scope_min_arr,color='b',s=20)
plt.scatter(depth_pexil_volatility_scope_value,depth_pexil_volatility_scope_var_arr,color='y',s=20)

plt.text(depth_pexil_volatility_scope_value[0], 0.25, 'mean: r',fontsize=10,bbox=dict(boxstyle='round,pad=0.5', fc='yellow', ec='k',lw=1 ,alpha=0.5))
plt.text(depth_pexil_volatility_scope_value[0], 0.24, 'max: g',fontsize=10,bbox=dict(boxstyle='round,pad=0.5', fc='yellow', ec='k',lw=1 ,alpha=0.5))
plt.text(depth_pexil_volatility_scope_value[0], 0.23, 'min: b',fontsize=10,bbox=dict(boxstyle='round,pad=0.5', fc='yellow', ec='k',lw=1 ,alpha=0.5))
plt.text(depth_pexil_volatility_scope_value[0], 0.22, 'var: y',fontsize=10,bbox=dict(boxstyle='round,pad=0.5', fc='yellow', ec='k',lw=1 ,alpha=0.5))

plt.plot(depth_pexil_volatility_scope_value,depth_pexil_volatility_scope_mean_arr,color='r')
plt.plot(depth_pexil_volatility_scope_value,depth_pexil_volatility_scope_max_arr,color='g')
plt.plot(depth_pexil_volatility_scope_value,depth_pexil_volatility_scope_min_arr,color='b')
plt.plot(depth_pexil_volatility_scope_value,depth_pexil_volatility_scope_var_arr,color='y')

for a, b in zip(depth_pexil_volatility_scope_value, depth_pexil_volatility_scope_mean_arr):
    plt.text(a, b,  round(b, 5), ha='center', va='bottom', fontsize=10)
for a, b in zip(depth_pexil_volatility_scope_value, depth_pexil_volatility_scope_max_arr):
    plt.text(a, b,  round(b, 5), ha='center', va='bottom', fontsize=10)
for a, b in zip(depth_pexil_volatility_scope_value, depth_pexil_volatility_scope_min_arr):
    plt.text(a, b,  round(b, 5), ha='center', va='bottom', fontsize=10)
for a, b in zip(depth_pexil_volatility_scope_value, depth_pexil_volatility_scope_var_arr):
    plt.text(a, b,  round(b, 5), ha='center', va='bottom', fontsize=10)

'''添加文本(方差和均值)'''
# plt.text(depth_value[-1], depth_mean_global, 'depth_mean_global')
''' draw line'''
# plt.plot(depth_value, depth_data,color='b')
'''x轴 y轴 显示栏设置'''
plt.xlabel("distance",fontsize=14)
plt.ylabel("depth_data",fontsize=14)
plt.tick_params(axis='both',labelsize=10)

plt.show()
