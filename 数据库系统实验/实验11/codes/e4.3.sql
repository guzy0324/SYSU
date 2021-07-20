use school
alter table choices drop [FK_CHOICES_STUDENTS];
alter table choices add
    constraint [FK_CHOICES_STUDENTS] foreign key ([sid]) references [dbo].[students] ([sid]) on delete cascade;
delete from students where sid = '800001216';
select * from Stu_Card;
select * from ICBC_Card;