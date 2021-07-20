use school
create table worker
(
    number char(5),
    name char(8) constraint u1 unique,
    sex char(1),
    sage int constraint u2 check (sage <= 28),
    department char(20),
    constraint pk_worker primary key(number)
)

insert into worker(number, name, sex, sage, department)
values('00001', '李勇', 'M', 14, '科技部')
select * from worker