/*==============================================================*/
/* DBMS name:      MySQL 5.0                                    */
/* Created on:     2018/8/27 20:03:30                           */
/*==============================================================*/


drop table if exists all_order;

drop table if exists food_item;

drop table if exists menu;

drop table if exists "order-menu";

drop table if exists patron;

/*==============================================================*/
/* Table: all_order                                             */
/*==============================================================*/
create table all_order
(
   order_id             smallint not null,
   patron_id            int not null,
   order_state          int,
   start_date           varchar(10),
   delivery_time        varchar(10),
   finish_time          varchar(10),
   address              varchar(45),
   primary key (order_id)
);

/*==============================================================*/
/* Table: food_item                                             */
/*==============================================================*/
create table food_item
(
   menu_id              int not null,
   food_price           int,
   food_name            varchar(20)
);

/*==============================================================*/
/* Table: menu                                                  */
/*==============================================================*/
create table menu
(
   menu_id              int not null,
   inventory            int,
   menu_name            varchar(20),
   menu_data            varchar(20),
   primary key (menu_id)
);

/*==============================================================*/
/* Table: "order-menu"                                          */
/*==============================================================*/
create table "order-menu"
(
   order_id             smallint not null,
   menu_id              int not null,
   primary key (order_id, menu_id)
);

/*==============================================================*/
/* Table: patron                                                */
/*==============================================================*/
create table patron
(
   patron_id            int not null,
   name                 varchar(10),
   address1             varchar(45),
   address2             varchar(45),
   withholding          varchar(20),
   primary key (patron_id)
);

alter table all_order add constraint "FK_order-patron" foreign key (patron_id)
      references patron (patron_id) on delete restrict on update restrict;

alter table food_item add constraint "FK_menu-food" foreign key (menu_id)
      references menu (menu_id) on delete restrict on update restrict;

alter table "order-menu" add constraint "FK_order-menu" foreign key (order_id)
      references all_order (order_id) on delete restrict on update restrict;

alter table "order-menu" add constraint "FK_order-menu" foreign key (menu_id)
      references menu (menu_id) on delete restrict on update restrict;

