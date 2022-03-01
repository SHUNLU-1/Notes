from numpy import * 
"""读取数据"""
def loadDataSet(filename):
    dataMat=[]
    labelMat=[]
    fr=open(filename)
    for line in fr.readlines():
        lineArr=line.strip().split('\t')
        dataMat.append([float(lineArr[0]),float(lineArr[1])])
        labelMat.append(float(lineArr[2]))
    """返回数据特征和数据类别"""
    return dataMat,labelMat 

"""在0-m中随机选择一个不是i的整数"""
def selectJrand(i,m): 
    j=i
    while (j==i):
        j=int(random.uniform(0,m))
    return j

"""保证a在L和H范围内(L <= a <= H)"""
def clipAlpha(aj,H,L):  
    if aj>H:
        aj=H
    if L>aj:
        aj=L
    return aj

"""核函数,输入参数,X:支持向量的特征树;A:某一行特征数据;kTup:('lin',k1)核函数的类型和参数"""
def kernelTrans(X, A, kTup): 
    m,n = shape(X)
    K = mat(zeros((m,1)))
    
    """线性函数"""
    if kTup[0]=='lin': 
        K = X * A.T

        """径向基函数(radial bias function)"""
    elif kTup[0]=='rbf': 
        for j in range(m):
            deltaRow = X[j,:] - A
            K[j] = deltaRow*deltaRow.T
        """生成返回的结果"""
        K = exp(K/(-1*kTup[1]**2)) 
    else:
        raise NameError('Houston We Have a Problem -- That Kernel is not recognized')
    return K


"""定义类,方便存储数据"""
class optStruct:
    def __init__(self,dataMatIn, classLabels, C, toler, kTup):
        """
        存储各类参数
        self.X = dataMatIn                    数据特征
        self.labelMat = classLabels           数据类别
        self.C = C                            软间隔参数C,参数越大,非线性拟合能力越强
        self.tol = toler                      停止阀值
        self.m = shape(dataMatIn)[0]          数据行数
        self.alphas = mat(zeros((self.m,1)))
        self.b = 0                            初始设为0
        self.eCache = mat(zeros((self.m,2)))  缓存
        self.K = mat(zeros((self.m,self.m)))  核函数的计算结果
        """
        self.X = dataMatIn  
        self.labelMat = classLabels 
        self.C = C 
        self.tol = toler 
        self.m = shape(dataMatIn)[0] 
        self.alphas = mat(zeros((self.m,1)))
        self.b = 0 
        self.eCache = mat(zeros((self.m,2))) 
        self.K = mat(zeros((self.m,self.m))) 
        for i in range(self.m):
            self.K[:,i] = kernelTrans(self.X, self.X[i,:], kTup)

"""计算Ek(参考《统计学习方法》p127公式7.105)"""
def calcEk(oS, k): 
    fXk = float(multiply(oS.alphas,oS.labelMat).T*oS.K[:,k] + oS.b)
    Ek = fXk - float(oS.labelMat[k])
    return Ek

"""随机选取aj,并返回其E值"""
def selectJ(i, oS, Ei):
    maxK = -1
    maxDeltaE = 0
    Ej = 0
    oS.eCache[i] = [1,Ei]
    """返回矩阵中的非零位置的行数"""
    validEcacheList = nonzero(oS.eCache[:,0].A)[0]  
    if (len(validEcacheList)) > 1:
        for k in validEcacheList:
            if k == i:
                continue
            Ek = calcEk(oS, k)
            deltaE = abs(Ei - Ek)
            """返回步长最大的aj"""
            if (deltaE > maxDeltaE): 
                maxK = k
                maxDeltaE = deltaE
                Ej = Ek
        return maxK, Ej
    else:
        j = selectJrand(i, oS.m)
        Ej = calcEk(oS, j)
    return j, Ej

"""更新os数据"""
def updateEk(oS, k): 
    Ek = calcEk(oS, k)
    oS.eCache[k] = [1,Ek]

"""首先检验ai是否满足KKT条件,如果不满足,随机选择aj进行优化,更新ai,aj,b值"""
"""输入参数i和所有参数数据"""
def innerL(i, oS): 
    """计算E值"""
    Ei = calcEk(oS, i) 
    if ((oS.labelMat[i]*Ei < -oS.tol) and (oS.alphas[i] < oS.C)) or ((oS.labelMat[i]*Ei > oS.tol) and (oS.alphas[i] > 0)): #检验这行数据是否符合KKT条件 参考《统计学习方法》p128公式7.111-113
        """随机选取aj,并返回其E值"""
        j,Ej = selectJ(i, oS, Ei) 
        alphaIold = oS.alphas[i].copy()
        alphaJold = oS.alphas[j].copy()
        """以下代码的公式参考《统计学习方法》p126"""
        if (oS.labelMat[i] != oS.labelMat[j]):
            L = max(0, oS.alphas[j] - oS.alphas[i])
            H = min(oS.C, oS.C + oS.alphas[j] - oS.alphas[i])
        else:
            L = max(0, oS.alphas[j] + oS.alphas[i] - oS.C)
            H = min(oS.C, oS.alphas[j] + oS.alphas[i])
        if L==H:
            print("L==H")
            return 0
        """参考《统计学习方法》p127公式7.107"""
        eta = 2.0 * oS.K[i,j] - oS.K[i,i] - oS.K[j,j] 
        if eta >= 0:
            print("eta>=0")
            return 0
        """参考《统计学习方法》p127公式7.106"""
        oS.alphas[j] -= oS.labelMat[j]*(Ei - Ej)/eta 
        """参考《统计学习方法》p127公式7.108"""
        oS.alphas[j] = clipAlpha(oS.alphas[j],H,L) 
        updateEk(oS, j)
        """alpha变化大小阀值(自己设定)"""
        if (abs(oS.alphas[j] - alphaJold) < oS.tol): 
            print("j not moving enough")
            return 0
        """参考《统计学习方法》p127公式7.109"""
        oS.alphas[i] += oS.labelMat[j]*oS.labelMat[i]*(alphaJold - oS.alphas[j])
        """更新数据"""
        updateEk(oS, i) 
        """以下求解b的过程,参考《统计学习方法》p129公式7.114-7.116"""
        b1 = oS.b - Ei- oS.labelMat[i]*(oS.alphas[i]-alphaIold)*oS.K[i,i] - oS.labelMat[j]*(oS.alphas[j]-alphaJold)*oS.K[i,j]
        b2 = oS.b - Ej- oS.labelMat[i]*(oS.alphas[i]-alphaIold)*oS.K[i,j]- oS.labelMat[j]*(oS.alphas[j]-alphaJold)*oS.K[j,j]
        if (0 < oS.alphas[i]<oS.C):
            oS.b = b1
        elif (0 < oS.alphas[j]<oS.C):
            oS.b = b2
        else:
            oS.b = (b1 + b2)/2.0
        return 1
    else:
        return 0

"""SMO函数,用于快速求解出alpha"""
"""输入参数:数据特征,数据类别,参数C,阀值toler，最大迭代次数，核函数（默认线性核）"""
def smoP(dataMatIn, classLabels, C, toler, maxIter,kTup=('lin', 0)): 
    oS = optStruct(mat(dataMatIn),mat(classLabels).transpose(),C,toler, kTup)
    iter = 0
    entireSet = True
    alphaPairsChanged = 0
    while (iter < maxIter) and ((alphaPairsChanged > 0) or (entireSet)):
        alphaPairsChanged = 0
        if entireSet:
            """遍历所有数据"""
            for i in range(oS.m): 
                alphaPairsChanged += innerL(i,oS)
                """显示第多少次迭代，那行特征数据使alpha发生了改变，这次改变了多少次alpha"""
                print("fullSet, iter: %d i:%d, pairs changed %d" % (iter,i,alphaPairsChanged)) 
            iter += 1
        else:
            nonBoundIs = nonzero((oS.alphas.A > 0) * (oS.alphas.A < C))[0]
            """遍历非边界的数据"""
            for i in nonBoundIs: 
                alphaPairsChanged += innerL(i,oS)
                print("non-bound, iter: %d i:%d, pairs changed %d" % (iter,i,alphaPairsChanged))
            iter += 1
        if entireSet:
            entireSet = False
        elif (alphaPairsChanged == 0):
            entireSet = True
        print("iteration number: %d" % iter)
    return oS.b,oS.alphas

def testRbf(data_train,data_test):
    """读取训练数据"""
    dataArr,labelArr = loadDataSet(data_train) 
    """通过SMO算法得到b和alpha"""
    b,alphas = smoP(dataArr, labelArr, 200, 0.0001, 10000, ('rbf', 1.3)) 
    datMat=mat(dataArr)
    labelMat = mat(labelArr).transpose()
    """选取不为0数据的行数(也就是支持向量)"""
    svInd=nonzero(alphas)[0]  

    """支持向量的特征数据"""
    sVs=datMat[svInd]
    """支持向量的类别(1或-1)"""
    labelSV = labelMat[svInd] 
    """打印出共有多少的支持向量"""
    print("there are %d Support Vectors" % shape(sVs)[0]) 
    
    """训练数据的行列数"""
    m,n = shape(datMat) 
    errorCount = 0
    for i in range(m):
        """将支持向量转化为核函数"""
        kernelEval = kernelTrans(sVs,datMat[i,:],('rbf', 1.3)) 
        """这一行的预测结果(代码来源于《统计学习方法》p133里面最后用于预测的公式)注意最后确定的分离平面只有那些支持向量决定。"""
        predict=kernelEval.T * multiply(labelSV,alphas[svInd]) + b  
        """"sign函数 -1 if x < 0, 0 if x==0, 1 if x > 0"""
        if sign(predict)!=sign(labelArr[i]): 
            errorCount += 1
    """打印出错误率"""
    print("the training error rate is: %f" % (float(errorCount)/m)) 
    
    """读取测试数据"""
    dataArr_test,labelArr_test = loadDataSet(data_test) 
    errorCount_test = 0
    datMat_test=mat(dataArr_test)
    labelMat = mat(labelArr_test).transpose()
    m,n = shape(datMat_test)
    
    """在测试数据上检验错误率"""
    for i in range(m):
        kernelEval = kernelTrans(sVs,datMat_test[i,:],('rbf', 1.3))
        predict=kernelEval.T * multiply(labelSV,alphas[svInd]) + b
        if sign(predict)!=sign(labelArr_test[i]):
            errorCount_test += 1
    print("the test error rate is: %f" % (float(errorCount_test)/m))

"""主程序"""
def main():
    filename_traindata='C:\\Users\\Administrator\\Desktop\\data\\traindata.txt'
    filename_testdata='C:\\Users\\Administrator\\Desktop\\data\\testdata.txt'
    testRbf(filename_traindata,filename_testdata)

if __name__=='__main__':
    main()
