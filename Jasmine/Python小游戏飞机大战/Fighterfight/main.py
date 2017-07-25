# -*- coding: utf-8 -*
import pygame
import sys
import traceback
import mainplane
import enemy
import bullet
from pygame.locals import *
from random import *

#初始化游戏
pygame.init()
#初始化混音器
pygame.mixer.init()

#载入游戏音乐
pygame.mixer.music.load("sound/game_music.ogg")
pygame.mixer.music.set_volume(0.2)
upgrade_sound = pygame.mixer.Sound("sound/upgrade.wav")
upgrade_sound.set_volume(0.5)
me_down_sound = pygame.mixer.Sound("sound/me_down.wav")
me_down_sound.set_volume(0.5)
bullet_sound = pygame.mixer.Sound("sound/bullet.wav")
bullet_sound.set_volume(0.3)
enemy1_down_sound = pygame.mixer.Sound("sound/enemy1_down.wav")
enemy1_down_sound.set_volume(0.5)
enemy2_down_sound = pygame.mixer.Sound("sound/enemy2_down.wav")
enemy2_down_sound.set_volume(0.8)
enemy3_down_sound = pygame.mixer.Sound("sound/enemy3_down.wav")
enemy3_down_sound.set_volume(0.8)

bg_size=width,height=480,700
#创建窗口
screen=pygame.display.set_mode(bg_size)
#设置窗口标题
pygame.display.set_caption("Fighterfight")

#把图片载入background变量
background=pygame.image.load("images/background.png").convert()


#往机组中添加飞机的add函数实现
def add_small_enemies(group1,group2,num):
    for i in range(num):
        e = enemy.SmallEnemy(bg_size)
        group1.add(e)
        group2.add(e)

def add_mid_enemies(group1,group2,num):
    for i in range(num):
        e = enemy.MidEnemy(bg_size)
        group1.add(e)
        group2.add(e)

def add_big_enemies(group1,group2,num):
    for i in range(num):
        e = enemy.BigEnemy(bg_size)
        group1.add(e)
        group2.add(e)

def increase_speed(target,n):
    for each in target:
        each.speed += n


#进入主函数
def main():
    #循环播放背景音乐
    pygame.mixer.music.play(-1)

    #引入帧率
    clock=pygame.time.Clock()

    #设置分数变量
    score = 0

    #设置生命数
    life_num = 3
    life_image = pygame.image.load("images/life.png").convert_alpha()
    life_rect = life_image.get_rect()
    
    #设置字体，实例化font模块的Font类
    score_font = pygame.font.Font("font/font.ttf",38)

    #设置难度级别
    level = 1

    #生成我方飞机
    myplane = mainplane.MyPlane(bg_size)

    #生成普通子弹
    bullet1 = []
    BULLET1_NUM = 4
    for i in range(BULLET1_NUM):
        bullet1.append(bullet.Bullet(myplane.rect.midtop))
    #设置一个子弹的索引指针，在bullet列表中循环指向
    bullet1_index = 0 

    #创建敌机组，包含三类敌机，方便进行碰撞检测
    enemies = pygame.sprite.Group()
    
    #生成小型敌机
    small_enemies = pygame.sprite.Group()
    #编写添加小敌机的函数，放入两个组，每次添加15个
    add_small_enemies(small_enemies,enemies,15)

    #生成中型敌机
    mid_enemies = pygame.sprite.Group()
    #编写添加中敌机的函数，放入两个组，每次添加8个
    add_mid_enemies(enemies,mid_enemies,8)

    #生成大型敌机
    big_enemies = pygame.sprite.Group()
    #编写添加大敌机的函数，放入两个组，每次添加2个
    add_big_enemies(enemies,big_enemies,2)

    #用于延迟
    delay=100

    #游戏结束画面
    gameover_font = pygame.font.Font("font/font.TTF", 48)
    again_image = pygame.image.load("images/again.png").convert_alpha()
    again_rect = again_image.get_rect()
    gameover_image = pygame.image.load("images/gameover.png").convert_alpha()
    gameover_rect = gameover_image.get_rect()
    
    
    running=True

    while running:
        for event in pygame.event.get():
            if event.type==QUIT:
                pygame.quit()
                sys.exit()

        #增加难度
        if level == 1 and score > 30000:
            level = 2
            upgrade_sound.play()
            #增加3辆小敌机，2架中敌机，1架大敌机
            add_small_enemies(small_enemies,enemies,5)
            add_mid_enemies(mid_enemies,enemies,3)
            add_big_enemies(big_enemies,enemies,1)
            #提升小型敌机的速度
            increase_speed(small_enemies,1)

        elif level == 2 and score > 100000:
            level = 3
            upgrade_sound.play()
            #增加5辆小敌机，3架中敌机，2架大敌机
            add_small_enemies(small_enemies,enemies,8)
            add_mid_enemies(mid_enemies,enemies,5)
            add_big_enemies(big_enemies,enemies,3)
            #提升小和中型敌机的速度
            increase_speed(small_enemies,1)
            increase_speed(mid_enemies,1)

        elif level == 3 and score > 600000:
            level = 4
            upgrade_sound.play()
            #增加8辆小敌机，5架中敌机，3架大敌机
            add_small_enemies(small_enemies,enemies,8)
            add_mid_enemies(mid_enemies,enemies,5)
            add_big_enemies(big_enemies,enemies,3)
            #提升小和中型敌机的速度
            increase_speed(small_enemies,1)
            increase_speed(mid_enemies,1)

        elif level == 4 and score > 1000000:
            level = 5
            upgrade_sound.play()
            #增加10辆小敌机，8架中敌机，5架大敌机
            add_small_enemies(small_enemies,enemies,8)
            add_mid_enemies(mid_enemies,enemies,5)
            add_big_enemies(big_enemies,enemies,3)
            #提升小，中和大型敌机的速度
            increase_speed(small_enemies,1)
            increase_speed(mid_enemies,1)
            increase_speed(big_enemies,1)


        if life_num:
            #导入key_press模块，接受键盘传入的序列数，返回按键的布尔值
            key_pressed = pygame.key.get_pressed()

            if key_pressed[K_UP]:
               myplane.MOVEUP()
            elif key_pressed[K_DOWN]:
                myplane.MOVEDOWN()
            elif key_pressed[K_LEFT]:
                myplane.MOVELEFT()
            elif key_pressed[K_RIGHT]:
                myplane.MOVERIGHT()

                
            #拷贝背景图
            screen.blit(background,(0,0))

            #检测我方飞机是否被撞，调用sprite模块里的collide_mask方式进行检测
            enemies_down = pygame.sprite.spritecollide(myplane,enemies,False,pygame.sprite.collide_mask)
            if enemies_down:
                myplane.active = False
                for i in enemies_down:
                    i.active = False

            #字符串显示，白色无锯齿
            score_text = score_font.render("Score : %s"%str(score),True,(255,255,255))
            screen.blit(score_text,(10,640))
            
            #画我方飞机
            if myplane.active:
                screen.blit(myplane.image,myplane.rect)
            else:
                #绘制毁灭图像
                if not (delay%4):
                    for i in range(4):
                        screen.blit(myplane.destroy[i],myplane.rect)
                    me_down_sound.play()
                    life_num -= 1
                    myplane.reset()

            #绘制剩余生命
            if life_num:
                for i in range(life_num):
                    screen.blit(life_image,\
                                (width-10-(i+1)*life_rect.width,\
                                 height-10-life_rect.height))

            #每12帧绘制一次子弹的发射
            if not (delay%12):
                bullet_sound.play()
                bullet1[bullet1_index].reset(myplane.rect.midtop)
                bullet1_index = (bullet1_index+1)%BULLET1_NUM

            #检测子弹是否击中敌机
            for b in bullet1:
                if b.active:
                    b.move()
                    screen.blit(b.image,b.rect)
                    bullet_hit=pygame.sprite.spritecollide(b,enemies,False,pygame.sprite.collide_mask)
                    if bullet_hit:
                        b.active = False
                        for e in bullet_hit:
                            if e in mid_enemies or e in big_enemies:
                                e.energy -= 1
                                if e.energy == 0:
                                    e.active = False
                            else:
                                e.active = False
            
            #画敌方飞机（按大中小的顺序进行绘制）

            #大型机
            for each in big_enemies:
                if each.active:
                    each.move()
                    screen.blit(each.image,each.rect)
                else:
                    #播放毁灭动画
                    if not (delay%4):
                        for i in range(4):
                            screen.blit(each.destroy[i],each.rect)
                            each.reset()
                        enemy3_down_sound.play()
                        score += 8000

            #中型机
            for each in mid_enemies:
                if each.active:
                    each.move()
                    screen.blit(each.image,each.rect)
                else:
                    #播放毁灭动画
                    if not (delay%4):
                        for i in range(4):
                            screen.blit(each.destroy[i],each.rect)
                            each.reset()
                        enemy2_down_sound.play()
                        score += 3000
            
            #小型机
            for each in small_enemies:
                if each.active:
                    each.move()
                    screen.blit(each.image,each.rect)
                else:
                    #播放毁灭动画
                    if not (delay%4):
                        for i in range(4):
                            screen.blit(each.destroy[i],each.rect)
                            each.reset()
                        enemy1_down_sound.play()
                        score += 1000

        #绘制游戏结束画面
        else:
            #背景音乐关闭
            pygame.mixer.music.stop()
            #绘制结束界面
            gameover_text1 = gameover_font.render("Your Score", True, (255, 255, 255))
            gameover_text1_rect = gameover_text1.get_rect()
            gameover_text1_rect.left, gameover_text1_rect.top = \
                                 (width - gameover_text1_rect.width) // 2, height // 3
            screen.blit(gameover_text1, gameover_text1_rect)

            gameover_text2 = gameover_font.render(str(score), True, (255, 255, 255))
            gameover_text2_rect = gameover_text2.get_rect()
            gameover_text2_rect.left, gameover_text2_rect.top = \
                                 (width - gameover_text2_rect.width) // 2, \
                                 gameover_text1_rect.bottom + 10
            screen.blit(gameover_text2, gameover_text2_rect)

            again_rect.left, again_rect.top = \
                             (width - again_rect.width) // 2, \
                             gameover_text2_rect.bottom + 50
            screen.blit(again_image, again_rect)

            gameover_rect.left, gameover_rect.top = \
                                (width - again_rect.width) // 2, \
                                again_rect.bottom + 10
            screen.blit(gameover_image, gameover_rect)

            # 检测用户的鼠标操作
            # 如果用户按下鼠标左键
            if pygame.mouse.get_pressed()[0]:
                # 获取鼠标坐标
                pos = pygame.mouse.get_pos()
                # 如果用户点击“重新开始”
                if again_rect.left < pos[0] < again_rect.right and \
                   again_rect.top < pos[1] < again_rect.bottom:
                    # 调用main函数，重新开始游戏
                    main()
                # 如果用户点击“结束游戏”            
                elif gameover_rect.left < pos[0] < gameover_rect.right and \
                     gameover_rect.top < pos[1] < gameover_rect.bottom:
                    # 退出游戏
                    pygame.quit()
                    sys.exit()

        #每过一帧，delay自减,小于0重新定义为100
        delay = delay-1
        if not delay:
            delay=100

        #显示窗口
        pygame.display.flip()
        #帧率为60，表示每秒动作不超过60帧
        clock.tick(60)
        
if __name__=="__main__":
    try:
        main()
    except SystemExit:
        pass
    except:
        traceback.print_exc()
        pygame.quit()
        input()
    
