# GIt 学习和使用教程

## Git工具的使用

### GitHubDesktop

![image-20230812154248558](git学习/GIt 学习和使用教程.assets/image-20230812154248558.png)



在Idea上使用Git

![image-20230812190304685](C:\Users\tang3\Desktop\GIt 学习和使用教程.assets\image-20230812190304685.png)

## 一、Git工作流程

Git有四个区域

+ 3个本地区域
  + 工作区（Workspace）：存放项目代码的地方
  + 暂存区（Stage）：存放临时的改动，事实上它只是一个文件，保存即将提交的文件列表信息。
  + 资源库（Repository）：安全存放数据的位置，这里面有提交到所有版本的数据。其中 HEAD 指向最新放入仓库的版本。

+ 1个远程区域
  + 远程库（Remote）：托管代码的服务器

![image-20230812152349276](C:\Users\tang3\AppData\Roaming\Typora\typora-user-images\image-20230812152349276.png)

![image-20230812203519204](C:\Users\tang3\Desktop\GIt 学习和使用教程.assets\image-20230812203519204.png)



![image-20230812202000235](C:\Users\tang3\Desktop\GIt 学习和使用教程.assets\image-20230812202000235.png)

![image-20230812201850127](C:\Users\tang3\Desktop\GIt 学习和使用教程.assets\image-20230812201850127.png)

![image-20230812212236704](C:\Users\tang3\Desktop\GIt 学习和使用教程.assets\image-20230812212236704.png)

## Git一些常用的基础指令

+ git -v  查看git的版本
  + ![image-20230812203807299](C:\Users\tang3\Desktop\GIt 学习和使用教程.assets\image-20230812203807299.png)
+ git init  在当前目录下创建仓库
  + ![image-20230812204020363](C:\Users\tang3\Desktop\GIt 学习和使用教程.assets\image-20230812204020363.png)

+ git clone ... 将远程仓库克隆到本地
  + ![image-20230812204513281](C:\Users\tang3\Desktop\GIt 学习和使用教程.assets\image-20230812204513281.png)

+ 配置邮箱和地址
  + git config user.name ....
  + git config user.email ....
  + ![image-20230812204700355](C:\Users\tang3\Desktop\GIt 学习和使用教程.assets\image-20230812204700355.png)

+ git status   查看暂存区的状态
  + ![image-20230812205550923](C:\Users\tang3\Desktop\GIt 学习和使用教程.assets\image-20230812205550923.png)

+ git add 将工作区的数据，推送到暂存区做比对操作
  + ![image-20230812205833465](C:\Users\tang3\Desktop\GIt 学习和使用教程.assets\image-20230812205833465.png)
  + ![image-20230812205911259](C:\Users\tang3\Desktop\GIt 学习和使用教程.assets\image-20230812205911259.png)

+ git rm --cached a.txt  将暂存区的文件，移动到工作区去  
  + ![image-20230812210128635](C:\Users\tang3\Desktop\GIt 学习和使用教程.assets\image-20230812210128635.png)

+ git commit -m 将暂存区的文件，移动到存储区
  + ![image-20230812210253120](C:\Users\tang3\Desktop\GIt 学习和使用教程.assets\image-20230812210253120.png)
  + ![image-20230812210331724](C:\Users\tang3\Desktop\GIt 学习和使用教程.assets\image-20230812210331724.png)

+ git log 查看提交日志
  + ![image-20230812210545041](C:\Users\tang3\Desktop\GIt 学习和使用教程.assets\image-20230812210545041.png)

+ git restore 文件误删后，可以通过这个语句来恢复文件

  + 若是没有通过 git commit提交前:

  + ![image-20230812211132172](C:\Users\tang3\Desktop\GIt 学习和使用教程.assets\image-20230812211132172.png)

+ 若是用了git commit 提交后，则需要采用   git reset --hard 版本号   来恢复   不过缺点是，把我们的提交过程丢失了
  + ![image-20230812211558408](C:\Users\tang3\Desktop\GIt 学习和使用教程.assets\image-20230812211558408.png)

+ 使用 git revert 版本号，相当于创建了一个新的提交
  + ![image-20230812212426690](C:\Users\tang3\Desktop\GIt 学习和使用教程.assets\image-20230812212426690.png)

+ 创建分支  git branch ....
  + ![image-20230812212917385](C:\Users\tang3\Desktop\GIt 学习和使用教程.assets\image-20230812212917385.png)

+ 切换分支  git checkout user 
  + ![image-20230812213039567](C:\Users\tang3\Desktop\GIt 学习和使用教程.assets\image-20230812213039567.png)

+ 创建并切换分支   git checkout -b ....
  + ![image-20230812213149448](C:\Users\tang3\Desktop\GIt 学习和使用教程.assets\image-20230812213149448.png)

+ 删除分支  git branch -d user
  + ![image-20230812213308105](C:\Users\tang3\Desktop\GIt 学习和使用教程.assets\image-20230812213308105.png)

+ git merge 合并操作
  + ![image-20230812213907217](C:\Users\tang3\Desktop\GIt 学习和使用教程.assets\image-20230812213907217.png)

+ 增加标签  git tag 标签名 版本号
  + ![image-20230812214617361](C:\Users\tang3\Desktop\GIt 学习和使用教程.assets\image-20230812214617361.png)

+ 远程仓库  git remote add url
+ git push url
+ git pull url
