import pygame
from pygame.locals import *
# 随机
import random
import time
'''
1, 实现飞机的显示 并且可以控制飞机的移动(面对对象)
2, 设置子弹类 控制子弹的模型与运动
3, 设置敌机显示与运动 并发射子弹
'''


class CommonBullet(object):
    '''
    公共子弹类
    '''

    def __init__(self, x, y, screen, bulltType):

        self.type = bulltType
        # 设置要显示的窗口
        self.screen = screen
        if self.type == 'hero':
            self.x = x+13
            self.y = y-20
            self.imagePath = '/home/ubuntu/PycharmProjects/LearnPython/pythonwork6/10.jpg'
            pass
        elif self.type == 'enemy':
            self.x = x
            self.y = y+10
            self.imagePath = '/home/ubuntu/PycharmProjects/LearnPython/pythonwork6/10.jpg'
            pass
        # 显示生成的子弹图片
        self.srcimg = pygame.image.load(self.imagePath)
        # 转化大小
        self.image = pygame.transform.scale(self.srcimg, (30, 30))
        pass

    def move(self):
        if self.type == 'hero':
            self.y -= 2
            pass
        elif self.type == 'enemy':
            self.y += 2

    def display(self):
        '''
        子弹显示
        :return:
        '''
        self.screen.blit(self.image, (self.x, self.y))
        pass

    def judge(self):
        '''
        判断子弹是否越界
        :return:
        '''
        if self.y < 0 or self.y > 500:
            return True
        else:
            return False
            pass


# 抽象出来一个飞机的基类
class BasePlane(object):
    def __init__(self, screen, imagePath):
        '''
        初始化基类
        :param screen:
        '''
        # 设置要显示的窗口
        self.screen = screen
        # 默认移动位置
        self.direction = 'right'
        # 存储子弹的列表
        self.bulletlist = []
        # 转化大小
        self.imagePath = imagePath
        self.image = pygame.transform.scale(self.imagePath, (30, 30))
        pass

    def display(self):
        '''
        显示位置以及发射子弹位置
        :return:
        '''
        self.screen.blit(self.image, (self.x, self.y))
        # 完善子弹的展示逻辑
        needDelItemList = []
        for item in self.bulletlist:
            if item.judge():
                needDelItemList.append(item)
                pass
            pass
        for i in needDelItemList:
            self.bulletlist.remove(i)
            pass
        for bullet in self.bulletlist:
            bullet.display()  # 显示子弹的位置
            bullet.move()  # 让这个子弹进行移动 下次在显示的时候就会看到子弹在修改的位置
        pass


class Enemy(BasePlane):  # 敌机类
    def __init__(self, screen):
        '''
        敌机初始化
        :param screen:
        '''
        self.imagePath = '/home/ubuntu/PycharmProjects/LearnPython/pythonwork6/10.jpg'
        self.srcimg = pygame.image.load(self.imagePath)
        super().__init__(screen, self.srcimg)
        # 敌机默认位置
        self.x = 0
        self.y = 0
        # 默认移动位置
        self.direction = 'right'
        pass

    def sheBullet(self):
        '''
        敌机随机发射子弹
        :return:
        '''
        num = random.randint(1, 50)
        if num == 3:
            newBullt = CommonBullet(self.x, self.y, self.screen, 'enemy')
            self.bulletlist.append(newBullt)
        pass

    def move(self):
        '''
        敌机自由移动
        :return:
        '''
        if self.direction == 'right':
            self.x += 10
            pass
        elif self.direction == 'left':
            self.x -= 10
        if self.x > 350-20:
            self.direction = 'left'
            pass
        elif self.x < 0:
            self.direction = 'right'
            pass


class Hero(BasePlane):  # 玩家类
    def __init__(self, screen):
        '''
        初始化函数
        '''
        # 调用父类的构造方法
        self.imagePath = '/home/ubuntu/PycharmProjects/LearnPython/pythonwork6/10.jpg'
        self.srcimg = pygame.image.load(self.imagePath)
        super().__init__(screen, self.srcimg)
        # 初始化玩家 x , y 坐标
        self.x = 150
        self.y = 460
        pass

    def moveleft(self):
        '''
        左移动
        :return:
        '''
        if self.x>0:
            self.x-=10
        pass

    def moveright(self):
        '''
        右移动
        :return:
        '''
        if self.x < 350:
            self.x += 10
        pass

    def sheBullet(self):
        '''
        发射子弹
        :return:
        '''
        newBullet = CommonBullet(self.x, self.y, self.screen, 'hero')
        self.bulletlist.append(newBullet)
        pass
    pass


def key_control(HeroObj):
    '''
    定义普通函数 用来实现键盘的实现
    :param HeroObj:
    :return:
    '''
    # 获取键盘事件
    eventlist = pygame.event.get()
    for event in eventlist:
        if event.type == QUIT:
            print('退出')
            exit()
            pass
        elif event.type == KEYDOWN:
            if event.type == K_a or event.key == K_LEFT:
                print('按下左键')
                # 调用函数实现左移
                HeroObj.moveleft()
                pass
            elif event.type == K_d or event.key == K_RIGHT:
                print('按下右键')
                HeroObj.moveright()
                pass
            elif event.key == K_SPACE:
                print('按下空格键')
                HeroObj.sheBullet()
                pass
            pass
        pass


def main():
    # 首先创建一个窗口i 用来显示内容
    screen = pygame.display.set_mode((350, 500))
    # 设置一个背景图片对象
    background = pygame.image.load('/home/ubuntu/PycharmProjects/LearnPython/pythonwork6/1.jpg')
    # 设置一个title
    pygame.display.set_caption('飞机大战游戏')

    # 添加背景音乐
    # # 初始化
    # pygame.mixer.init()
    # # 音乐路径添加
    # pygame.mixer.music.load('')
    # # 设置音乐声音大小
    # pygame.mixer.music.set_volume(0.2)
    # # 设置音乐无限循环 -1 表示无限循环
    # pygame.mixer.music.play(-1)

    # 创建一个飞机对象
    hero = Hero(screen)
    # 创建一个敌机对象
    enemy = Enemy(screen)

    while True:
        # 设定显示内容
        screen.blit(background, (0, 0))
        # 显示玩家飞机图片
        hero.display()
        # 显示敌机
        enemy.display()
        # 敌机移动
        enemy.move()
        # 敌机发射子弹
        enemy.sheBullet()
        # 获取键盘事件
        key_control(hero)
        # 更新显示内容
        pygame.display.update()
        pygame.time.Clock().tick(20)
    pass


if __name__ == '__main__':
    main()
