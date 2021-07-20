use school
create table Stu_Card
(
    card_id char(14),
    stu_id char(10) references students (sid) on delete cascade,
    remained_money decimal (10, 2),
    constraint PK_stu_card primary key (card_id)
)
insert into Stu_Card values ('05212567', '800001216', 100.25);
insert into Stu_Card values ('05212222', '800005753', 200.50);
select * from Stu_Card;