use school
create table Stu_Union
(
    sno char(5) not null unique,
    sname char(8),
    ssex char(1),
    sage int,
    sdept char(20),
    constraint PK_Stu_Union primary key(sno)
);
insert into Stu_Union values ('10001', '李勇', '0', 24, 'EE');
insert into Stu_Union values ('95002', '王敏', '1', 23, 'CS');
insert into Stu_Union values ('95003', '王浩', '0', 25, 'EE');
insert into Stu_Union values ('95005', '王杰', '0', 25, 'EE');
insert into Stu_Union values ('95009', '李勇', '0', 25, 'EE');
select * from Stu_Union;
