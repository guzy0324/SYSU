use school
set transaction isolation level repeatable read
select * from students where sid='889358356'
delete from students where sid='889358356'
select * from students where sid='889358356'
