use school
go
create view v as
select sid, sname, card_id
from students, stu_card
where sid = stu_id