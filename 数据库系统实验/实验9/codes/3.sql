use school
begin transaction T3
alter table ICBC_Card drop constraint FK__ICBC_Card__stu_c__70DDC3D8
alter table ICBC_Card add constraint FK__ICBC_Card__stu_c foreign key (stu_card_id)
    references Stu_Card(card_id) on delete set null;
delete from students where sid = '800001216';
commit transaction T3