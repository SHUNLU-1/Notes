# 数据库
# 数据表中包括ER图，表的主键，字段，数据类型，约束，表之间关系的设计
# E-R 模型主要用于定义数据的存储要求 该模型已经广泛用于关系数据库设计中 E-R 模型由实体，属性和关系三个要素构成
# 主键 ：要求没一行的记录都必须是唯一的   可以由一个字段组成也可以多个 数据库表中的主键值具有唯一性不能取空值（NULL）
# 当由数据库表中的主键有多个字段构成时 每个字段都不能取NULL值

# 实体间的关系与外键
# 实体之间可以通过外键来表示 如果表A中的一个字段a对应于表B中的主键b 则字段a称为表A的外键 此时储存在表A中字段a的值，同时这个字段值也是表B主键b的值

# 约束
# 约束是定义在表上的一种强制规则。当为某个表定义约束后，对该表做的所有SQL操作都必须满足约束规则要求，否则操作失败
# 约束类型 ：
# NOT NULL：非空约束
# UNIQUE：唯一性约束
# PRIMARY KEY ：主键约束
# FOREIGN KEY：外键约束
# CHECK ：检查性约束


# 查看当前数据库中的表 ：show tables
# comment 注释
# 查看创建表的sql语句 ： show create table 表名;
# 添加字段 alter table 表名 add 列名 类型;（给students添加一个生日段）
# 删除字段 alter table 表名 drop 字段名字;（将student表中的gender字段删除）
# 修改约束字段 alter table 表名 modify 列名 类型
# 修改字段名  alter table 表名 change 列名 字段
# 删除学生表 ：drop 表名
# 备份某一个表 ： mysqldump -uroot -p python class > class.sql
