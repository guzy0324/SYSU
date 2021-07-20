use school
create table ICBC_Card
(
    bank_id char(20),
    stu_card_id char(14) references Stu_Card(card_id),
    restored_money decimal (10, 2),
    constraint PK_ICBC_Card primary key (bank_id)
)
insert into ICBC_Card values ('9558844022312', '05212567', 15000.1);
insert into ICBC_Card values ('9558844023645', '05212222', 50000.3);
select * from ICBC_Card;