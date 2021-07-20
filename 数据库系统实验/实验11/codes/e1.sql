use school
create table SC
(
    sno char(5) references Stu_Union(sno) on delete cascade,
    cno char(4) references Course(cno) on delete cascade,
    grade int,
    constraint PK_SC primary key (sno, cno)
);
insert into sc values ('95002', '0001', 2);
insert into sc values ('95002', '0002', 2);
insert into sc values ('10001', '0001', 2);
insert into sc values ('10001', '0002', 2);
select * from SC
delete from Stu_Union where sno = '10001';
select * from SC
