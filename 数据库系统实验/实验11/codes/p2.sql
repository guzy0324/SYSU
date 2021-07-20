use school
create table Course
(
    cno char(4) not null unique,
    cname varchar(50) not null,
    cpoints int,
    constraint PK primary key (cno)
);
insert Course values ('0001', 'ComputerNetworks', 2);
insert Course values ('0002', 'Database', 3);
select * from Course
