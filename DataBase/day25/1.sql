#创建数据库cos
##已经创建好了
use cos;
#创建表patron
create table patron(
patron_id int(4),
patron_name varchar(20),
address varchar(20),
email varchar(20)
);
#创建表menu
create table menu(
menu_id int(4),
menu_name varchar(20),
menu_date date
);
#创建表food_item
create table food_item(
food_id int(4),
food_name varchar(20),
food_description varchar(100),
food_price varchar(20),
menu_id int(4)
);
#修改表patron结构
alter table patron add column IDcard varchar(20);
#删除表patron结构中的IDcard
alter table patron drop IDcard;
#创建一张新表aaa
create table aaa;
#删除表aaa
drop table aaa;

#查询表patron中parton_name字段的长度小于3的所有人记录
select * from patron where length(parton_name)<3;

#添加一种菜类型
insert into menu value('01','菜系1','2015-8-24');
#添加该菜系的菜3样
insert into food_item value('01','菜系1-菜1','菜系1-菜1','12.0','01');
insert into food_item value('02','菜系1-菜2','菜系1-菜2','12.0','01');
insert into food_item value('03','菜系1-菜3','菜系1-菜3','12.0','01');

#新建视图，包含patron表中的patron_name，email
create view Pat as select patron_name,email from cos.patron;
select * from Pat;

#查询food_item表中的总记录数
select count(*)  from food_item;
             
#查询patron表中手机尾号为’5728‘的记录
alter table patron add column phone varchar(20);
update patron set phone='18356095728' where patron_id='01';
select * from patron where phone like '%5728';

#将menu表按时间升序
select * from menu order by date asc;

#查询出food_item表中menu_id以及对应的menu_id的菜的个数
select menu_id,count(*) as foodnum
from food_item
group by menu_id;
                     
#查询出patron 表中的前5条记录
select * from patron limit 5;
                     
#查询出菜名为’土豆丝’的菜的价格,菜的描述以及它所属的菜的种类(menu)的名字
insert into food_item value('04','tudousi','xxx','xx','x');
select food_price,food_description,menu_id from food_item where food_name='tudousi';

#查询出food_item表中和’土豆丝’一样菜价的菜的名字,价格
select food_name,food_price
from food_item
where food_price in (select food_price from food_item where food_name='tudousi')
and food_name <>'tudousi';