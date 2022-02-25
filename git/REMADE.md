# 如何熟练的使用git上传代码到github
![](https://pic2.zhimg.com/v2-f75dde0f283c93dd6cef387b1e1b2e42_1440w.jpg?source=172ae18b)
## 一、初始配置git
第一次使用git需要配置。
### (1)、下载git
所谓工欲善其事，必先利其器
```bash
sudo apt-get install git
```
### (2)、配置git
```bash
git git config --global user.name <your-name> #输入你github的用户名
git config --global user.email <your-email> #输入你的邮箱
git config --list #可以查看你刚刚的配置
```
### (3)、通过ssh密钥连接github
因为代码托管到github，需要SSH Key验证，所以执行以下命令创建SSH Key：
```bash
ssh-keygen -t rsa -C "你的邮箱地址"
```
创建后会在~/.ssh目录下生成id_rsa和id_rsa.pub两个文件。这两个就是生成的秘钥对，其中id_rsa是私钥，不能暴露出去；另一个是公钥，也就是我们等会要用到的，把里面的内容复制出来。

![](https://s2.loli.net/2022/02/25/wyqCFfKSUl6aMNt.png)

回到github网址，依次选择：点击自己头像下的Settings-->SSH and GPG keys –> New SSH key”,填写title，然后把刚刚复制的内容黏贴Key上去就可以了。

![](https://s2.loli.net/2022/02/25/5obTDKkxN6Vmnse.png)

### (4)、验证是否连接成功

接下来，测试一下连接是否成功，输入：
```bash
ssh -T git@github.com、
```
![](https://s2.loli.net/2022/02/25/3fEd54xGUPFD1Ji.png)


## 二、上传代码到github
### (1)、github新建仓库
在github网站新建仓库，然后在本地目录拉取。
```bash
git clone https://github.com/用户名/项目名称.git
```
### (2)、上传代码到github
+ 在你需要上传的文件夹
```bash
git init
```
+ 上传之前，我们需要添加上传的文件。这里使用到的指令是：

```bash
git add file # file是我们想要添加的文件
git add ./ # 将整个文件夹内容都添加进去
```

+ 检查当前git状态

```bash
git status
```
+ commit推送
将缓存区的修改提交到本地仓库
```bash
git commit -m "Update Readme Files(Version of Chinese & English)"
```
+ 添加文件到远程库
```bash
git remote add origin https://github.com/用户名/项目名称.git
```
如果此时出现错误：fatal: remote origin already exists. 这时候说明远程仓库已经存在。这时候需要先删除origin仓库，然后再重新添加该远程仓库。指令如下：
```bash
git remote -v # git查看远程仓库地址
git remote rm origin  # 删除已经存在且不需要的origin
git remote add origin https://github.com/用户名/项目名称.git
```
+ 进行上传
第一次上传需要指定分支
```bash
git push origin master # 需要指定分支
```
后续上传
```bash
git push
```
push结束后，在GitHub端的对应仓库上刷新一下，内容就改变了。说明项目内容已经上传成功了～

+ 某些push错误的情况
有时候对新建的仓库进行push操作，会出现上传失败的情况。通常出现这种情况的原因，是新建的仓库往往会有一个文件Readme.md文件，而本地仓库中没有这个文件，也就是说本地仓库与服务器端仓库没有实现同步。所以将这个Readme.md文件clone到本地，然后再commit提交，应该就没有问题了。
或者在 push 操作的时候遇到下述错误：
>error: 无法推送一些引用到 'git@github.com:upcAutoLang/BackgroundSplit-OpenCV.git'
>提示：更新被拒绝，因为远程仓库包含您本地尚不存在的提交。这通常是因为另外
>提示：一个仓库已向该引用进行了推送。再次推送前，您可能需要先整合远程变更
>提示：（如 'git pull ...'）。
>提示：详见 'git push --help' 中的 'Note about fast-forwards' 小节。

**强制推送:**
```bash
git push -u origin +master
```
**尽量先同步 Github 上的代码到本地，在上面更改之后再上传。**

## 三、vscode上到使用git
### (1)、克隆git储存库
![]()
