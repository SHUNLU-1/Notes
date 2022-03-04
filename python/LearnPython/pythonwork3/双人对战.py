#  问题分析
# 决战资金指点有两个人物,西门吹雪与叶孤城
#  属性 : name 玩家的姓名  blood 玩家血量
#  方法 : tong() 捅对方一刀,对方掉血10滴  kanren() 砍对方一刀,对方掉十五滴血 chiyao() 吃一颗药 补血十滴 __str__ 打印玩家状态
import time
class Hero:
    def __init__(self, name, blood):
        '''
        构造初始化函数
        :param name:角色名
        :param blood: 玩家血量
        '''
        self.name = name
        self.blood = blood
        pass

    def tong(self, enemy):
        '''
        捅一刀
        :param enemy: 敌人
        :return:
        '''
        enemy.blood -= 10
        info = '[%s]捅了[%s]一刀' % (self.name, enemy.name)
        print(info)
        pass
    def kanren(self, enemy):
        '''
        砍人
        :param enemy: 敌人
        :return:
        '''
        enemy.blood -= 15
        info = '[%s]砍了[%s]一刀' % (self.name, enemy.name)
        print(info)

    def chiyao(self, enemy):
        '''
        喝药
        :param enemy:
        :return:
        '''
        self.blood += 10
        info = '[%s]喝药' % self.name
        print(info)
    def __str__(self):
        '''
        返回实例类的字符
        :return:
        '''
        return '%s还剩下%s血量' % (self.name, self.blood)
        pass
Person0 = Hero('西门吹雪',100)
Person1 = Hero('叶古城', 100)
while True:
    if Person1.blood <= 0 or Person0.blood <= 0:
        # 满足条件退出
        break
        pass
    Person0.kanren(Person1)
    print(Person0)
    print(Person1)
    print('********Roubd one 结束*******')
    time.sleep(1)
    Person0.kanren(Person1)
    print(Person0)
    print(Person1)
    print('********Roubd two 结束*******')
    time.sleep(1)
    Person0.kanren(Person1)
    print(Person0)
    print(Person1)
    print('********Roubd three 结束*******')
    time.sleep(1)
    Person0.kanren(Person1)
    print(Person0)
    print(Person1)
    print('********Roubd four 结束*******')
    time.sleep(1)

print('*******对战结束********')


